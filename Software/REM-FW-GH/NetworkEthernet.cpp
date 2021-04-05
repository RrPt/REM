/*
	Name:        NetworkEthernet.cpp
	Description: network based on Ethernet
	Project:     REM  (Rainer's Energy Mesaurement) power measurement in AC networks
	Created:	 20.06.2020
	Author:      Rainer Petzoldt  R.Petzoldt@web.de
*/


#include "NetworkEthernet.h"
#include "Logger.h"


NetworkEthernetClass::NetworkEthernetClass()
{
}

void NetworkEthernetClass::init(IPAddress defaultIp, esp_mac_type_t mac_type, IPAddress defaultGw , IPAddress defaultSubnet)
{
	byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
	// Get MAC address for WiFi station
	esp_read_mac(mac, mac_type);
	Logger.info("MAC=%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
	Logger.debug("Ethernet.init...");
	Ethernet.init(5);
	Logger.debug("Ethernet.begin(mac)...");
	if (Ethernet.begin(mac) == 0) {
		Logger.warning("Failed to configure Ethernet using DHCP");
		// no point in carrying on, so do nothing forevermore:
		// try to congifure using IP address instead of DHCP:
		Ethernet.begin(mac, defaultIp);
	}
	//Ethernet._state;
	// give the Ethernet shield a second to initialize:
	delay(1000);  //  leider habe ich keine Methode gefunden die eine fertige Initialisierung anzeigt
	Logger.info("IP=%s\n",Ethernet.localIP().toString().c_str());

	Logger.debug("Connected to the Ethernet");

	//Logger.printf(WiFi.localIP());  // todo
}

void NetworkEthernetClass::otaInit(void (* beforeUpdateFnk)())
{
	beforeUpdateFunction = beforeUpdateFnk;
	OTE
		.onStart([&]() {
		String type;
		if (OTE.getCommand() == U_FLASH)
			type = "sketch";
		else // U_SPIFFS
			type = "filesystem";

		// NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
		if (beforeUpdateFunction != NULL)
		{
			Logger.info("Pointer=%d", beforeUpdateFunction);
			beforeUpdateFunction();
		}
		else Logger.info("Pointer = null");
			
		Logger.info("Start updating %s", type.c_str());

	})
		.onEnd([]() {
		Logger.info("End");
	})
		.onProgress([](unsigned int progress, unsigned int total) {
		Logger.debug("Progress: %3d%%  %d / %d Bytes", (progress / (total / 100)), progress, total);
	})
		.onError([](ota_error_t error) {
		Logger.error("Error[%u]: ", error);
		if (error == OTA_AUTH_ERROR) Logger.error("Auth Failed");
		else if (error == OTA_BEGIN_ERROR) Logger.error("Begin Failed");
		else if (error == OTA_CONNECT_ERROR) Logger.error("Connect Failed");
		else if (error == OTA_RECEIVE_ERROR) Logger.error("Receive Failed");
		else if (error == OTA_END_ERROR) Logger.error("End Failed");
	});

	OTE.begin();
}


void NetworkEthernetClass::handleUpdater()
{
	OTE.handle();
}

IPAddress NetworkEthernetClass::getNtpServer()
{
	// der ntp Server wird von Ethernet nicht geliefert, deshalb versuchsweise das Gateway liefern
	// todo prüfen ob der DHCP einen NTP Server geliefert hat (vermutlich nur über eigene DHCP Pakete)
	IPAddress ip = Ethernet.gatewayIP();
	return ip;
}