/*
	Name:        RemPara.h
	Description: Rem Parameter
	Project:     REM  (Rainer's Energy Mesaurement) power measurement in AC networks
	Created:	 23.11.2020
	Author:      Rainer Petzoldt  R.Petzoldt@web.de
*/

#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif


class RemParaClass
{
 protected:

 public:
	String defaultIp;			    // IP wenn kein DHCP funktioniert

	int minRemmModules;				// Mindestanzehl der angeschlossenen Module
	 
	bool useMqtt = true;
	String mqttIP;					// IP des MQTT Servers
	String mqttUser;				// username am MQTT Server
	String mqttPassword;			// password am MQTT Server
	String mqttMask;				// MQTT Pfad für REM-MM Werte
	String mqttMaskChan;			// MQTT Pfad für REM-MM Kanalwerte
	String mqttClientName;
	String wifi_ssid;				// SSID für WLAN
	String wifi_password;           // Passwort für WLAN


	ulong maxMqttSendDelay = 60000;     // max Zeit in ms die ein MQTT verzögert werden darf wenn sich der Wert nicht geändert hat

	// Funktionen
	void init();
	void setDefaultValues();
	bool read(String explizitFilename="");
	void write(String explizitFilename = "");
	// debug
	void show();
};

extern RemParaClass remPara;


