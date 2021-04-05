/*
	Name:        NetworkWifi.cpp
	Description: network based on Ethernet
	Project:     REM  (Rainer's Energy Mesaurement) power measurement in AC networks
	Created:	 20.06.2020
	Author:      Rainer Petzoldt  R.Petzoldt@web.de
*/


#include "NetworkWifi.h"
#include "Logger.h"

NetworkWiFiClass::NetworkWiFiClass(const char* ssid, const char* password)  // Konstruktor
{
	_ssid = ssid;
	_password = password;
}

void NetworkWiFiClass::SetPassword(const char* ssid, const char* password)  // Credentials
{
	_ssid = ssid;
	_password = password;
}

void NetworkWiFiClass::init(IPAddress defaultIp, IPAddress defaultGw, IPAddress defaultSubnet)
{
	WiFi.begin(_ssid, _password);
	ulong startTime = millis();
	while (WiFi.status() != WL_CONNECTED) {
		Logger.info("%d Connecting to WiFi DHCP .. status=%d", (startTime + dhcpTimeout - millis())/1000, WiFi.status());
		WiFi.begin(_ssid, _password);
		delay(500);
		if (millis() - startTime > dhcpTimeout) break;
	}
	//if ((uint32_t)defaultGw == (uint32_t)0x00000000)
	//{
	//	defaultGw = defaultIp;
	//	defaultGw[3] = 1;
	//}
	//WiFi.config(defaultIp,defaultGw,defaultSubnet);
	//WiFi.begin(_ssid, _password);
	//while (WiFi.status() != WL_CONNECTED) {
	//	Logger.info("%d Connecting to WiFi IP .. status=%d\n", (startTime + dhcpTimeout - millis()) / 1000, WiFi.status());
	//	delay(500);
	//	if (millis() - startTime > wifiTimeout) break;
	//}

	if (WiFi.status() != WL_CONNECTED) 
	{
		Logger.printf("Not Connected to the WiFi network\n");
		Logger.printf("IP=%s\n", WiFi.localIP().toString().c_str());
	}
	else
	{
		Logger.printf("Connected to the WiFi network\n");
		Logger.printf("IP=%s\n", WiFi.localIP().toString().c_str());
	}
}


void NetworkWiFiClass::otaInit(void(*beforeUpdateFnk)())
{
	beforeUpdateFunction = beforeUpdateFnk;
	OTA
		.onStart([&]() {
		String type;
		if (OTA.getCommand() == U_FLASH)
			type = "sketch";
		else // U_SPIFFS
			type = "filesystem";

		// NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
		Logger.printf("Start updating %s\n", type.c_str());
	})
		.onEnd([]() {
		Logger.printf("\nEnd");
	})
		.onProgress([](unsigned int progress, unsigned int total) {
		Logger.printf("Progress: %3d%%  %d / %d Bytes\n", (progress / (total / 100)),progress,total);
	})
		.onError([](ota_error_t error) {
		Logger.printf("Error[%u]: ", error);
		if (error == OTA_AUTH_ERROR) Logger.printf("Auth Failed");
		else if (error == OTA_BEGIN_ERROR) Logger.printf("Begin Failed\n");
		else if (error == OTA_CONNECT_ERROR) Logger.printf("Connect Failed\n");
		else if (error == OTA_RECEIVE_ERROR) Logger.printf("Receive Failed\n");
		else if (error == OTA_END_ERROR) Logger.printf("End Failed\n");
	});

	OTA.begin();
}


void NetworkWiFiClass::handleUpdater()
{
	OTA.handle();
}



IPAddress NetworkWiFiClass::getNtpServer()
{
	// der ntp Server wird von WiFi nicht geliefert, deshalb versuchsweise das Gateway liefern
	// todo prüfen ob der DHCP einen NTP Server geliefert hat (vermutlich nur über eigene DHCP Pakete)
	IPAddress ip = WiFi.gatewayIP();
	Serial.println(ip);
	return ip;
}