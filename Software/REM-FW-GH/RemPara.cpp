/*
	Name:        RemPara.cpp
	Description: Rem Parameter
	Project:     REM  (Rainer's Energy Mesaurement) power measurement in AC networks
	Created:	 20.06.2020
	Author:      Rainer Petzoldt  R.Petzoldt@web.de
*/

#include "RemPara.h"
#include "ArduinoJson.h"    // https://arduinojson.org/
#include "SPIFFS.h"
#include <FS.h>
#include "Logger.h"


void RemParaClass::init()
{
	Logger.info("RemParaClass::init()");
	setDefaultValues();

	// Initialize SPIFFS
	if (!SPIFFS.begin(true)) {
		Logger.error("An Error has occurred while mounting SPIFFS");
		return;
	}
	Logger.debug("SPIFFS: used %d Bytes von %d", SPIFFS.usedBytes(), SPIFFS.totalBytes());
	// MAC bestimmen
	byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
	esp_read_mac(mac, ESP_MAC_WIFI_STA);
	char fn[30];
	snprintf(fn,30,"/RemPara%02X%02X%02X%02X%02X%02X.json", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
	Logger.info("Read %s", fn);
	read(fn);
	snprintf(fn, 30, "/RemPara%02X%02X%02X%02X%02X%02X_w.json", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
	Logger.info("Write %s", fn);
	write(fn);
}


// Set to Default
void RemParaClass::setDefaultValues()
{
	minRemmModules = 0;
	useMqtt = true;
	mqttIP = "192.168.22.100";			        // IP des MQTT Servers
	mqttUser = "<user>";					    // username am MQTT Server
	mqttPassword = "<pw>";				        // password am MQTT Server
	mqttMask = "REM0/<REMMM>/";				    // MQTT Pfad für REM-MM Werte
	mqttMaskChan = "REM0/<REMMM>/<CHAN>/";	    // MQTT Pfad für REM-MM Kanalwerte
	mqttClientName = "REMClient0";				// MQTT Client name (nur wichtig wenn mehrere zugreifen, müssen dann unterschiedlich sein)
	defaultIp = "192.168.22.254";				// Default IP wenn kein DHCP verfügbar
	maxMqttSendDelay = 60000;			        // Default 1 Minute
	wifi_ssid = "defaultSSID";	                // Default SSID wenn nicht in RemPara.json angegeben
	wifi_password = "defaultPW";	            // Default passwort wenn nicht in RemPara.json angegeben
}


// Einlesen der Parameter aus dem Flash
bool RemParaClass::read(String explizitFilename)
{
	Logger.info("RemParaClass::read(%s)", explizitFilename.c_str());

	String fn = "/RemPara.json";
	
	if (explizitFilename != "")
	{
		fn = explizitFilename;
	}

	Logger.debug("Filename: %s", fn.c_str());
	File file = SPIFFS.open(fn, FILE_READ);
	if (!file) {
		Logger.error("There was an error opening the file %s for read, trying /RemPara.json", fn.c_str());
		return false;
	}
	if (file.size()==0) {
		Logger.error("file %s didn't exist or is empty, using RemPara.json ", fn.c_str());
		fn = "/RemPara.json";
		file = SPIFFS.open(fn, FILE_READ);
		if (!file) {
			Logger.error("There was an error opening the file %s for read", fn.c_str());
			return false;
		}
		if (file.size() == 0) {
			Logger.error("file %s didn't exist or s empty, taking program defaults ", fn.c_str());
			return false;
		}
	}
	Logger.debug("Filesize=%d  filehandle=%d", file.size(),file);
	StaticJsonDocument<1500> doc;  //  size muss bei größerem Parametersatz angepasst weden
	Logger.debug("JsobDoc Memory: %d  von %d used", doc.memoryUsage(), doc.capacity());
	// Deserialize the JSON document
	DeserializationError error = deserializeJson(doc, file);
	Logger.debug("JsobDoc Memory: %d  von %d used", doc.memoryUsage(), doc.capacity());
	file.close();

	// Test if parsing succeeds.
	if (error) {
		Logger.error("deserializeJson() failed: %s",error.c_str());
	}
	
	if (doc.containsKey("minRemmModules")) minRemmModules = doc["minRemmModules"];

	if (doc.containsKey("mqttIP")) mqttIP = doc["mqttIP"].as<String>();
	if (doc.containsKey("mqttUser")) mqttUser = doc["mqttUser"].as<String>();
	if (doc.containsKey("mqttPassword"))mqttPassword = doc["mqttPassword"].as<String>();
	if (doc.containsKey("mqttMask")) mqttMask = doc["mqttMask"].as<String>();
	if (doc.containsKey("mqttMaskChan")) mqttMaskChan = doc["mqttMaskChan"].as<String>();
	if (doc.containsKey("useMqtt")) useMqtt = doc["useMqtt"];
	if (doc.containsKey("mqttMaskChan"))  mqttClientName = doc["mqttClientName"].as<String>();
	if (doc.containsKey("maxMqttSendDelay"))  maxMqttSendDelay = doc["maxMqttSendDelay"];
	if (doc.containsKey("defaultIp"))  defaultIp = doc["defaultIp"].as<String>();
	if (doc.containsKey("wifi_ssid"))  wifi_ssid = doc["wifi_ssid"].as<String>();
	if (doc.containsKey("wifi_password"))  wifi_password = doc["wifi_password"].as<String>();

	
	//show();  // todo nur debugging
	return true;
}

// Schreiben der Parameter in den Flash
void RemParaClass::write(String explizitFilename)
{
	Logger.info("RemParaClass::write(%s)",explizitFilename.c_str());
	String fn = "/RemPara.json";

	if (explizitFilename != "")
	{
		fn = explizitFilename;
	}
	Logger.debug("Filename: %s", fn.c_str());
	File file = SPIFFS.open(fn, FILE_WRITE);  
	if (!file) {
		Logger.error("There was an error opening the file %s for writing",fn.c_str());
	}
	Logger.debug("Filesize=%d", file.size());
	StaticJsonDocument<1500> doc;  //  size muss bei größerem Parametersatz angepasst weden
	////Logger.debug("A"); delay(200);
	doc["Filename"] = fn;
	doc["minRemmModules"] = minRemmModules;
	doc["defaultIp"] = defaultIp;
	doc["useMqtt"] = useMqtt;
	doc["mqttIP"] = mqttIP;
	doc["mqttUser"] = mqttUser;
	doc["mqttPassword"] = mqttPassword;
	doc["mqttMask"] = mqttMask;
	doc["mqttMaskChan"] = mqttMaskChan;
	doc["maxMqttSendDelay"] = maxMqttSendDelay;
	doc["mqttClientName"] = mqttClientName;
	doc["wifi_ssid"] = wifi_ssid;
	doc["wifi_password"] = wifi_password;


	int anz = serializeJsonPretty(doc, file);
	if (anz == 0) {
		Logger.error("Failed to write to file");
	}
	Logger.debug("%d Filesize=%d", anz,  file.size());

	file.close();
}

// Show all Parameters
void RemParaClass::show()
{
	Logger.printf("RemPara:\n");
	Logger.printf("  defaultIp=%s\n", defaultIp.c_str());
	Logger.printf("  minRemmModules=%d\n", minRemmModules);
	Logger.printf("  useMqtt=%d\n", useMqtt);
	Logger.printf("  mqttIP=%s\n", mqttIP.c_str());
	Logger.printf("  mqttUser=%s\n", mqttUser.c_str());
	Logger.printf("  mqttPassword=%s\n", mqttPassword.c_str());
	Logger.printf("  mqttMask=%s\n", mqttMask.c_str());
	Logger.printf("  mqttMaskChan=%s\n", mqttMaskChan.c_str());
	Logger.printf("  maxMqttSendDelay=%d\n", maxMqttSendDelay);
	Logger.printf("  mqttClientName=%s\n", mqttClientName.c_str());
	Logger.printf("  wifi_ssid=%s\n", wifi_ssid.c_str());
	Logger.printf("  wifi_password=%s\n", wifi_password.c_str());
}

RemParaClass remPara;