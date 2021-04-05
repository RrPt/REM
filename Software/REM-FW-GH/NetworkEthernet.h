/*
	Name:        NetworkEthernet.h
	Description: network based on Ethernet
	Project:     REM  (Rainer's Energy Mesaurement) power measurement in AC networks
	Created:	 20.06.2020
	Author:      Rainer Petzoldt  R.Petzoldt@web.de
*/

#pragma once

#include "Network.h"
#include <Ethernet.h>
#include "ArduinoOTE.h"

class NetworkEthernetClass : public virtual NetworkClass
{
 public:
	EthernetClient client;
	ArduinoOTEClass OTE;

	NetworkEthernetClass();  // Konstruktor
	void init(IPAddress defaultIp, esp_mac_type_t mac_type = ESP_MAC_WIFI_STA, IPAddress defaultGw = (uint32_t)0x00000000, IPAddress defaultSubnet = (uint32_t)0xFFFFFF00);
	void otaInit(void (* beforeUpdateFnk)() = NULL);
	void handleUpdater();
	IPAddress getNtpServer();
	void(*beforeUpdateFunction)(); 
};

