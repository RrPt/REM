/*
	Name:        ArduinoOTE.h
	Description: Basic OTA Updater over Ethernet (instead of WiFi)
	Project:     REM  (Rainer's Energy Mesaurement) power measurement in AC networks
	Created:	 20.06.2020
	Author:      Rainer Petzoldt  R.Petzoldt@web.de
*/
#ifndef __ARDUINO_OTE_H
#define __ARDUINO_OTE_H

#include <Ethernet.h>
#include <functional>
#include "Update.h"
#include <ArduinoOTA.h>

#define INT_BUFFER_SIZE 16

class ArduinoOTEClass : public virtual ArduinoOTAClass
{
public:
	typedef std::function<void(void)> THandlerFunction;
	typedef std::function<void(ota_error_t)> THandlerFunction_Error;
	typedef std::function<void(unsigned int, unsigned int)> THandlerFunction_Progress;

	ArduinoOTEClass();
	~ArduinoOTEClass();

	//Sets the service port. Default 3232
	ArduinoOTEClass& setPort(uint16_t port);

	//Sets the device hostname. Default esp32-xxxxxx
	ArduinoOTEClass& setHostname(const char *hostname);
	String getHostname();

	//Sets the password that will be required for OTA. Default NULL
	ArduinoOTEClass& setPassword(const char *password);

	//Sets the password as above but in the form MD5(password). Default NULL
	ArduinoOTEClass& setPasswordHash(const char *password);

	//Sets if the device should be rebooted after successful update. Default true
	ArduinoOTEClass& setRebootOnSuccess(bool reboot);

	//Sets if the device should advertise itself to Arduino IDE. Default true
	ArduinoOTEClass& setMdnsEnabled(bool enabled);

	//This callback will be called when OTA connection has begun
	ArduinoOTEClass& onStart(THandlerFunction fn);

	//This callback will be called when OTA has finished
	ArduinoOTEClass& onEnd(THandlerFunction fn);

	//This callback will be called when OTA encountered Error
	ArduinoOTEClass& onError(THandlerFunction_Error fn);

	//This callback will be called when OTA is receiving data
	ArduinoOTEClass& onProgress(THandlerFunction_Progress fn);

	//Starts the ArduinoOTA service
	void begin();

	//Ends the ArduinoOTA service
	void end();

	//Call this in loop() to run the service
	void handle();

	//Gets update command type after OTA has started. Either U_FLASH or U_SPIFFS
	int getCommand();

private:
	int _port;
	String _password;
	String _hostname;
	String _nonce;
	EthernetUDP _udp_ota;
	bool _initialized;
	bool _rebootOnSuccess;
	bool _mdnsEnabled;
	ota_state_t _state;
	int _size;
	int _cmd;
	int _ota_port;
	IPAddress _ota_ip;
	String _md5;

	THandlerFunction _start_callback;
	THandlerFunction _end_callback;
	THandlerFunction_Error _error_callback;
	THandlerFunction_Progress _progress_callback;

	void _runUpdate(void);
	void _onRx(void);
	int parseInt(void);
	String readStringUntil(char end);
};

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_ARDUINOOTA)
extern ArduinoOTEClass ArduinoOTE;
#endif

#endif /* __ARDUINO_OTE_H */
