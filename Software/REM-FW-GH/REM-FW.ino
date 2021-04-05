/*
	Name:          REM-FW.ino
	Description:   Firmware for REM Project
	Project:       REM  (Rainer's Energy Mesaurement) power measurement in AC networks
	Created:	   20.06.2020
	Last modified: 05.04.2021
	Author:        Rainer Petzoldt  R.Petzoldt@web.de
*/


#include "RemMqtt.h"
#include "Zeit.h"
#include "HtmlServer.h"
#include "ADE7816IData.h"
#include "ADE7816Data.h"
#include "RemMM.h"
#include "TCA9548a.h"
#include "Logger.h"
#include <esp32-hal-log.h>
#include "RemPara.h"

#define USEMQTT

// Unterscheidung Wifi oder Ethernet über ein globales define  (Wifi Funktionen nicht alle getestet)
#ifdef USE_ETH
#include "NetworkEthernet.h"
NetworkEthernetClass network;
#else
#include "NetworkWifi.h"
NetworkWiFiClass network("my_ssid", "my_password");   // wird später mit denen aus RepPara.json überschrieben
#endif

int counter = 0;							// Schleifenzähler
unsigned long t1, t2;						// Zeiten
unsigned long lastTimeSent = 0;

HtmlServerClass htmlServer;

#pragma region prototypes
// Prototypen
void mqttHandleNewData(RemMMClass *remMMData);
void handleInput(char c);  // siehe unten
#pragma endregion



void setup()
{
	Serial.begin(115200);
	Logger.printf("************START*********************\n");
	remPara.init();											// Parameter aus SPIFFS einlesen
	remPara.show();											// Anzeigen der Parameter 
	IPAddress defaultIp = IPAddress(192, 168, 22, 254);		// IP greift nur falls kein DHCP und kein Configfile im Spiffs
	defaultIp.fromString(remPara.defaultIp);	            // default IP aus Parametern lesen
	Serial.printf("defaultIp="); 	Serial.println(defaultIp);
#ifndef USE_ETH
	network.SetPassword(remPara.wifi_ssid.c_str(), remPara.wifi_password.c_str());  // Passwort aus Konfigfile verwenden
#endif
	network.init(defaultIp);								// Netzwerk initialisieren
	Logger.info("Init OTA...");
	network.otaInit(RemMMClass::saveAllEnergyCounter);      // OTA initialisierern, vor Update die Energiezähler sichern
	Logger.info("Init NTP...");
	Zeit.init(network.getNtpServer());						// Zeitserver initialisierern
	lastTimeSent = millis() - Zeit.timeClient->getSeconds() * 1000 - Zeit.timeClient->getMilliseconds();
	Logger.info("Init Logger...");
	Logger.init();											// nur für Logging über Telnet erforderlich

	pinMode(PWR_SWITCH, OUTPUT);							// Pin für Power-Schalter festlegen
	RemMMClass::powerSwitch(true);	                        // Strom einschalten

	RemMMClass::initModules();								// RemMM Module initialisierern

#ifdef USEMQTT
	RemMqtt.init(&network.client, remPara);					// MQTT initialisierern
#endif
	htmlServer.init();										// HTML Server initialisierern
	bool restored = RemMMClass::restoreAllEnergyCounter();	// prüfen ob gespeicherte Energiezähler vorhanden sind, diese auslesen
	RemMqtt.getLastEnergyCounter();							// Versuchen die Energiezähler per MQTT zu restaurierern

	Logger.info("End setup() ***********************************\n");
	Logger.loglevel = LOGLEVEL_INFO;						// Loglevel auf INFO reduzierern
}


void loop()
{
	t1 = millis();								// Startzeit merken
	counter++;

	// neue Daten behandeln
	bool hasNewData = RemMMClass::handleAllNewData(mqttHandleNewData);	// hier wird auf neue Daten geprüft und dann mqttHandleNewData aufgerufen


#ifdef USEMQTT
	if (millis() - lastTimeSent >= 60000) // alle 60s Zeit per MQTT senden
	{
		lastTimeSent = millis() - Zeit.timeClient->getSeconds() * 1000 - Zeit.timeClient->getMilliseconds();  // immer volle Minute senden
		RemMqtt.sendTime();	// falls notwendig
	}
	if (counter % 100 == 0) // alle 10s MQTT Connection prüfen
	{
		RemMqtt.reconnect();	// falls notwendig
	}
	RemMqtt.handleClient(); 	// behandelt die MQTT Telegramme (Empfang)  noch nicht implementiert
#endif

	Zeit.handleTime();

	//  warten bis 100ms um sind seit start, dabei OTA, HTML-Server und Eingaben behandeln
	unsigned long t3 = millis();
	for (int w = 0; w < 100; w++)  // maximal 100 mal
	{
		network.handleUpdater();
		htmlServer.handleClient();
		Logger.handleClients();

		int c = Serial.read();
		if (c != -1) handleInput(c);

		t2 = millis();
		unsigned long dt = t2 - t1;
		// bei overflow wird sofort ein break ausgelöst, d.h. alle 50 Tage ist die Schleife 1 mal nur 30 ms lang -> kein Problem
		if (dt >= 100) break;	// wenn 100ms seit Loop-Start dann beenden

		delay(1);
	}
	Logger.debug("Schleifenzeiten: Arbeit=%d ms  Warten+HTML=%d ms   %d  %d  %d", t3 - t1, t2 - t3, t1, t3, t2);

}


//
// Diese Funktion wird aufgerufen wenn neue Daten eingetroffen sind
// sie informiert alle die benachrichtigt werden müssen
//
void mqttHandleNewData(RemMMClass *remMMData)
{
	//Logger.info("%d Messungen in %s", remMMData->ade7816.data.noOfMeasurements, remMMData->name);
#ifdef USEMQTT
	RemMqtt.mqttHandleNewData(remMMData);		// neue Daten per MQTT senden
#endif
    // hier können weitere Handler ergänzt werden ...						
}

//
// Behandlung von Debugbefehlen die über die serielle Schnittstelle eingehen
//
void handleInput(char c)
{
	String charStr = " ";
	int idx = 0;
	Logger.info("SerialIn: %c %x ", c, c);
	switch (c)
	{
	case 'c':
		Logger.loglevel = 5;
		Logger.printf("Loglevel auf CRITICAL gesetzt\n");
		break;
	case 'e':
		Logger.loglevel = 4;
		Logger.printf("Loglevel auf ERROR gesetzt\n");
		break;
	case 'w':
		Logger.loglevel = 3;
		Logger.printf("Loglevel auf WARNING gesetzt\n");
		break;
	case 'i':
		Logger.loglevel = 2;
		Logger.printf("Loglevel auf INFO gesetzt\n");
		break;
	case 'd':
		Logger.loglevel = 1;
		Logger.printf("Loglevel auf DEBUG gesetzt\n");
		break;
	case 'r':
		Logger.printf("Reset von welchem Modul? Idx=");
		charStr = Serial.readString();
		idx = charStr.toInt();
		Logger.printf("%d\nReset von Modul? %s\n", idx, RemMMClass::remMM[idx]->name);
		RemMMClass::remMM[idx]->resetAde7816();
		break;
	case 's':
		Logger.printf("Befehl s = saveEnergyCounter()\n");
		RemMMClass::saveAllEnergyCounter();
		break;
	case 'R':
		Logger.printf("Befehl s = saveEnergyCounter()\n");
		RemMMClass::restoreAllEnergyCounter();
		break;
	case 'I':
		Logger.printf("Show Info:\n");
		Logger.printf("   %d REMMM Module gefunden\n", RemMMClass::anzModules);
		for (size_t i = 0; i < RemMMClass::anzModules; i++)
		{
			Logger.printf("      %02d %s\n", i, RemMMClass::remMM[i]->name);
		}
		remPara.show();
		break;
	default:
		break;
	}
}





