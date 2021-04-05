/*
	Name:        RemMqtt.h
	Description: Handler für REM-MQTT
	Project:     REM  (Rainer's Energy Mesaurement) power measurement in AC networks
	Created:	 Dez 2020
	Author:      Rainer Petzoldt  R.Petzoldt@web.de
*/


#ifndef _REMMQTT_h
#define _REMMQTT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Client.h>
#include <PubSubClient.h>  
#include "RemMM.h"
#include "RemPara.h"
#include "RemMqttData.h"

class RemMqttClass
{
 protected:
	 static bool restoreEneryCounter;
	 RemParaClass remPara;
	 PubSubClient *client;
	 void(*mqttHandleNewData_Ptr)(RemMMClass*);

 public:
	void init(Client *ethClient,RemParaClass remPara);
	void mqttHandleNewData(RemMMClass *remMMData);
	void mqttPublish(String prefix, String name, String value);
	void reconnect();
	void sendTime();
	void handleClient();
	bool getLastEnergyCounter();
	static void MqttReceived(char* topic, byte* payload, unsigned int length);


private:
	void sendVValues(RemMqttDataClass *remMqttData);
	void sendIValues(RemMqttIDataClass *remMqttIData);
	bool abweichung(double val, double lastVal, double prozent, double minAbw);
	bool abweichungAbs(double val, double lastVal, double maxAbw);
};

extern RemMqttClass RemMqtt;

#endif

