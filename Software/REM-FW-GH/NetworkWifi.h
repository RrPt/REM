/*
	Name:        NetworkWifi.h
	Description: network based on Ethernet
	Project:     REM  (Rainer's Energy Mesaurement) power measurement in AC networks
	Created:	 20.06.2020
	Author:      Rainer Petzoldt  R.Petzoldt@web.de
*/


#pragma once

#include "Network.h"
#include <WiFi.h>
#include <ArduinoOTA.h>


class NetworkWiFiClass : public virtual NetworkClass
{
protected:
	const char* _ssid;
	const char* _password;
	ulong dhcpTimeout = 30000; // ms
	ulong wifiTimeout = 60000;  //ms

 public:
	WiFiClient client;
	ArduinoOTAClass OTA;

	NetworkWiFiClass(const char* ssid, 	const char* password);  // Konstruktor
	void SetPassword(const char* ssid, const char* password);  // Credentials
	void init(IPAddress defaultIp, IPAddress defaultGw = (uint32_t)0x00000000, IPAddress defaultSubnet= (uint32_t)0xFFFFFF00);
	void otaInit(void(*beforeUpdateFnk)() = NULL);
	void handleUpdater();
	IPAddress getNtpServer();
	void(*beforeUpdateFunction)();
};

