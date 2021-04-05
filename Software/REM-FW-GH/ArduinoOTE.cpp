/*
	Name:        ArduinoOTE.cpp
	Description: Basic OTA Updater over Ethernet (instead of WiFi)
	Project:     REM  (Rainer's Energy Mesaurement) power measurement in AC networks
	Created:	 20.06.2020
	Author:      Rainer Petzoldt  R.Petzoldt@web.de
*/

#ifndef LWIP_OPEN_SRC
#define LWIP_OPEN_SRC
#endif
#include <functional>
//#include <WiFiUdp.h>
#include "ArduinoOTE.h"
#include "ESPmDNS.h"
#include "MD5Builder.h"
#include "Update.h"
#include "Logger.h"


//#define OTA_DEBUG Serial

ArduinoOTEClass::ArduinoOTEClass()
	: _port(0)
	, _initialized(false)
	, _rebootOnSuccess(true)
	, _mdnsEnabled(true)
	, _state(OTA_IDLE)
	, _size(0)
	, _cmd(0)
	, _ota_port(0)
	, _start_callback(NULL)
	, _end_callback(NULL)
	, _error_callback(NULL)
	, _progress_callback(NULL)
{
	Serial.printf("OTE-Konstruktor\n");
}

ArduinoOTEClass::~ArduinoOTEClass() {
	_udp_ota.stop();
}

ArduinoOTEClass& ArduinoOTEClass::onStart(THandlerFunction fn) {
	_start_callback = fn;
	return *this;
}

ArduinoOTEClass& ArduinoOTEClass::onEnd(THandlerFunction fn) {
	_end_callback = fn;
	return *this;
}

ArduinoOTEClass& ArduinoOTEClass::onProgress(THandlerFunction_Progress fn) {
	_progress_callback = fn;
	return *this;
}

ArduinoOTEClass& ArduinoOTEClass::onError(THandlerFunction_Error fn) {
	_error_callback = fn;
	return *this;
}

ArduinoOTEClass& ArduinoOTEClass::setPort(uint16_t port) {
	if (!_initialized && !_port && port) {
		_port = port;
	}
	return *this;
}

ArduinoOTEClass& ArduinoOTEClass::setHostname(const char * hostname) {
	if (!_initialized && !_hostname.length() && hostname) {
		_hostname = hostname;
	}
	return *this;
}

String ArduinoOTEClass::getHostname() {
	return _hostname;
}

ArduinoOTEClass& ArduinoOTEClass::setPassword(const char * password) {
	if (!_initialized && !_password.length() && password) {
		MD5Builder passmd5;
		passmd5.begin();
		passmd5.add(password);
		passmd5.calculate();
		_password = passmd5.toString();
	}
	return *this;
}

ArduinoOTEClass& ArduinoOTEClass::setPasswordHash(const char * password) {
	if (!_initialized && !_password.length() && password) {
		_password = password;
	}
	return *this;
}

ArduinoOTEClass& ArduinoOTEClass::setRebootOnSuccess(bool reboot) {
	_rebootOnSuccess = reboot;
	return *this;
}

ArduinoOTEClass& ArduinoOTEClass::setMdnsEnabled(bool enabled) {
	_mdnsEnabled = enabled;
	return *this;
}

void ArduinoOTEClass::begin() {
	if (_initialized) {
		log_w("already initialized");
		return;
	}

	if (!_port) {
		_port = 3232;
	}

	if (!_udp_ota.begin(_port)) {
		log_e("udp bind failed");
		return;
	}


	if (!_hostname.length()) {
		char tmp[20];
		uint8_t mac[6];
		esp_read_mac(mac, ESP_MAC_WIFI_STA);
		sprintf(tmp, "esp32-%02x%02x%02x%02x%02x%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
		Logger.debug("Ethernet MAC=%s\n", tmp);
		_hostname = tmp;
	}
	if (_mdnsEnabled) {
		MDNS.begin(_hostname.c_str());
		MDNS.enableArduino(_port, (_password.length() > 0));
	}
	_initialized = true;
	_state = OTA_IDLE;
#ifdef OTA_DEBUG
	OTA_DEBUG.printf("OTA server at: %s.local:%u\n", _hostname.c_str(), _port);
#endif
}

int ArduinoOTEClass::parseInt() {
	char data[INT_BUFFER_SIZE];
	uint8_t index = 0;
	char value;
	while (_udp_ota.peek() == ' ') _udp_ota.read();
	while (index < INT_BUFFER_SIZE - 1) {
		value = _udp_ota.peek();
		if (value < '0' || value > '9') {
			data[index++] = '\0';
			return atoi(data);
		}
		data[index++] = _udp_ota.read();
	}
	return 0;
}

String ArduinoOTEClass::readStringUntil(char end) {
	String res = "";
	char value;
	while (true) {
		value = _udp_ota.read();
		if (value == '\0' || value == end) {
			return res;
		}
		res += value;
	}
	return res;
}

void ArduinoOTEClass::_onRx() {
	if (_state == OTA_IDLE) {
		int cmd = parseInt();
		if (cmd != U_FLASH && cmd != U_SPIFFS)
			return;
		_cmd = cmd;
		_ota_port = parseInt();
		_size = parseInt();
		_udp_ota.read();
		_md5 = readStringUntil('\n');
		_md5.trim();
		if (_md5.length() != 32) {
			return;
		}

		if (_password.length()) {
			MD5Builder nonce_md5;
			nonce_md5.begin();
			nonce_md5.add(String(micros()));
			nonce_md5.calculate();
			_nonce = nonce_md5.toString();

			_udp_ota.beginPacket(_udp_ota.remoteIP(), _udp_ota.remotePort());
			_udp_ota.printf("AUTH %s", _nonce.c_str());
			_udp_ota.endPacket();
			_state = OTA_WAITAUTH;
			return;
		}
		else {
			_udp_ota.beginPacket(_udp_ota.remoteIP(), _udp_ota.remotePort());
			_udp_ota.print("OK");
			_udp_ota.endPacket();
			_ota_ip = _udp_ota.remoteIP();
			_state = OTA_RUNUPDATE;
		}
	}
	else if (_state == OTA_WAITAUTH) {
		int cmd = parseInt();
		if (cmd != U_AUTH) {
			_state = OTA_IDLE;
			return;
		}
		_udp_ota.read();
		String cnonce = readStringUntil(' ');
		String response = readStringUntil('\n');
		if (cnonce.length() != 32 || response.length() != 32) {
			_state = OTA_IDLE;
			return;
		}

		String challenge = _password + ":" + String(_nonce) + ":" + cnonce;
		MD5Builder _challengemd5;
		_challengemd5.begin();
		_challengemd5.add(challenge);
		_challengemd5.calculate();
		String result = _challengemd5.toString();

		if (result.equals(response)) {
			_udp_ota.beginPacket(_udp_ota.remoteIP(), _udp_ota.remotePort());
			_udp_ota.print("OK");
			_udp_ota.endPacket();
			_ota_ip = _udp_ota.remoteIP();
			_state = OTA_RUNUPDATE;
		}
		else {
			_udp_ota.beginPacket(_udp_ota.remoteIP(), _udp_ota.remotePort());
			_udp_ota.print("Authentication Failed");
			_udp_ota.endPacket();
			if (_error_callback) _error_callback(OTA_AUTH_ERROR);
			_state = OTA_IDLE;
		}
	}
}

void ArduinoOTEClass::_runUpdate() {
	if (!Update.begin(_size, _cmd)) {
#ifdef OTA_DEBUG
		Update.printError(OTA_DEBUG);
#endif
		if (_error_callback) {
			_error_callback(OTA_BEGIN_ERROR);
		}
		_state = OTA_IDLE;
		return;
	}
	Update.setMD5(_md5.c_str());

	if (_start_callback) {
		_start_callback();
	}
	if (_progress_callback) {
		_progress_callback(0, _size);
	}

	EthernetClient client;
	if (!client.connect(_ota_ip, _ota_port)) {
		if (_error_callback) {
			_error_callback(OTA_CONNECT_ERROR);
		}
		_state = OTA_IDLE;
	}

	uint32_t written = 0, total = 0, tried = 0;
	while (!Update.isFinished() && client.connected()) {
		size_t waited = 1000;
		size_t available = client.available();
		while (!available && waited) {
			delay(1);
			waited -= 1;
			available = client.available();
		}
		if (!waited) {
			if (written && tried++ < 3) {
#ifdef OTA_DEBUG
				OTA_DEBUG.printf("Try[%u]: %u\n", tried, written);
#endif
				if (!client.printf("%u", written)) {
#ifdef OTA_DEBUG
					OTA_DEBUG.printf("failed to respond\n");
#endif
					_state = OTA_IDLE;
					break;
				}
				continue;
			}
#ifdef OTA_DEBUG
			OTA_DEBUG.printf("Receive Failed\n");
#endif
			if (_error_callback) {
				_error_callback(OTA_RECEIVE_ERROR);
			}
			_state = OTA_IDLE;
			Update.abort();
			return;
		}
		if (!available) {
#ifdef OTA_DEBUG
			OTA_DEBUG.printf("No Data: %u\n", waited);
#endif
			_state = OTA_IDLE;
			break;
		}
		tried = 0;
		static uint8_t buf[1460];
		if (available > 1460) {
			available = 1460;
		}
		size_t r = client.read(buf, available);
		if (r != available) {
			log_w("didn't read enough! %u != %u", r, available);
		}

		written = Update.write(buf, r);
		if (written > 0) {
			if (written != r) {
				log_w("didn't write enough! %u != %u", written, r);
			}
			if (!client.printf("%u", written)) {
#ifdef OTA_DEBUG
				OTA_DEBUG.printf("failed to respond\n");
#endif
			}
			total += written;
			if (_progress_callback) {
				_progress_callback(total, _size);
			}
		}
		else {
#ifdef OTA_DEBUG
			Update.printError(OTA_DEBUG);
#endif
		}
	}

	if (Update.end()) {
		client.print("OK");
		client.stop();
		delay(10);
		if (_end_callback) {
			_end_callback();
		}
		if (_rebootOnSuccess) {
			//let serial/network finish tasks that might be given in _end_callback
			delay(100);
			ESP.restart();
		}
	}
	else {
		if (_error_callback) {
			_error_callback(OTA_END_ERROR);
		}
		Update.printError(client);
		client.stop();
		delay(10);
#ifdef OTA_DEBUG
		OTA_DEBUG.print("Update ERROR: ");
		Update.printError(OTA_DEBUG);
#endif
		_state = OTA_IDLE;
	}
}

void ArduinoOTEClass::end() {
	_initialized = false;
	_udp_ota.stop();
	if (_mdnsEnabled) {
		MDNS.end();
	}
	_state = OTA_IDLE;
#ifdef OTA_DEBUG
	OTA_DEBUG.println("OTA server stopped.");
#endif
}

void ArduinoOTEClass::handle() {
	if (_state == OTA_RUNUPDATE) {
		_runUpdate();
		_state = OTA_IDLE;
	}
	if (_udp_ota.parsePacket()) {
		_onRx();
	}
	_udp_ota.flush(); // always flush, even zero length packets must be flushed.
}

int ArduinoOTEClass::getCommand() {
	return _cmd;
}

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_ARDUINOOTA)
ArduinoOTEClass ArduinoOTE;
#endif
