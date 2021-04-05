/*
	Name:        Network.h
	Description: Abstract Class, merges Ethernet2 and Wifi
	Project:     REM  (Rainer's Energy Mesaurement) power measurement in AC networks
	Created:	 20.06.2020
	Author:      Rainer Petzoldt  R.Petzoldt@web.de
*/
#pragma once
#include <ArduinoOTA.h>

class NetworkClass 
{
public:
	NetworkClass();
	void init();
	void otaInit();
	void handleUpdater();
	IPAddress getNtpServer();
};




