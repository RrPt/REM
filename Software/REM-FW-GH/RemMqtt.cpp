/*
	Name:        RemMqtt.cpp
	Description: Handler für REM-MQTT
	Project:     REM  (Rainer's Energy Mesaurement) power measurement in AC networks
	Created:	 Dez 2020
	Author:      Rainer Petzoldt  R.Petzoldt@web.de
*/


#include "RemMqtt.h"
#include "Logger.h"
#include "Zeit.h"


bool RemMqttClass::restoreEneryCounter = false;
static RemMqttDataClass *remMqttDataList[MAXREMMMMODULES];		// Liste der REM-MQTT-Daten
static long mqttReconnectFail=0;
static long mqttReconnectOk=0;

void RemMqttClass::init(Client *ethClient, RemParaClass remPara)

{
	this->remPara = remPara;
	client = new PubSubClient(*ethClient);
	IPAddress ip;
	ip.fromString(remPara.mqttIP);
	client->setServer(ip, 1883);
	client->setCallback(MqttReceived);
	reconnect();
	for (size_t idx = 0; idx < RemMMClass::anzModules; idx++)
	{
		remMqttDataList[idx] = new RemMqttDataClass(idx);
		for (size_t i = 0; i < 6; i++)
		{
			remMqttDataList[idx]->chan[i] = new RemMqttIDataClass(idx,i);
		}
	}

}


void RemMqttClass::mqttHandleNewData(RemMMClass *remMMData)
{
	sendVValues(remMqttDataList[remMMData->idx]);
	for (size_t i = 0; i < 6; i++)
	{
		sendIValues(remMqttDataList[remMMData->idx]->chan[i]);
	}
}


void RemMqttClass::sendVValues(RemMqttDataClass *remMqttData)
{
	String prefix = String(remPara.mqttMask);
	char modAdr[10];
	itoa(remMqttData->remMM->_adr, modAdr, 16);
	prefix.replace("<REMMM>", modAdr);
	char timeStr[40];
	bool send = false;
	double frequency = remMqttData->remMM->ade7816.data.frequency;
	double voltage = remMqttData->remMM->ade7816.data.voltage;
	if (millis() - remMqttData->sentTime > remPara.maxMqttSendDelay)
	{
		send = true;
		Logger.debug("sent MQTT V Data wegen Zeitablauf");
	}
	//else if (abweichung(frequency, remMqttData->sentFrequency,1.0,0.02))
	//{
	//	send = true;
	//	Logger.debug("sent MQTT V Data wegen Frequenzaenderung");
	//}
	else if (abweichung(voltage, remMqttData->sentVoltage, 1.0,2.0))
	{
		send = true;
		Logger.debug("sent MQTT V Data wegen Spannungsaenderung");
	}

	if (send)
	{
		//mqttPublish(prefix, "time", String(Zeit.getFormattedDateTime(timeStr, 40)));
		//mqttPublish(prefix, "measurementNo", String(remMqttData->remMM->ade7816.data.noOfMeasurements));
		mqttPublish(prefix, "voltage", String(voltage) + " V");
		//mqttPublish(prefix, "frequency", String(frequency)+"Hz");
		remMqttData->sentTime = millis();
		remMqttData->sentFrequency = frequency;
		remMqttData->sentVoltage = voltage;
		remMqttData->sentNoOfMeasurements = remMqttData->remMM->ade7816.data.noOfMeasurements;
	}
}


void RemMqttClass::sendIValues(RemMqttIDataClass *remMqttIData)
{
	String prefix = String(remPara.mqttMaskChan);
	char modAdr[10];
	itoa(remMqttIData->remMM->_adr, modAdr, 16);
	prefix.replace("<REMMM>", modAdr);
	prefix.replace("<CHAN>", String(remMqttIData->chan));
	char timeStr[40];
	bool send = false;
	ADE7816IDataClass chanData =  remMqttIData->remMM->ade7816.data.chan[remMqttIData->chan];
	double current = chanData.current;			// in A
	double PowerActive = chanData.PowerActive;		// in W
	double PowerReactive = chanData.PowerReactive;		// in VA
	double EnergyActive = chanData.EnergyActive;		// in Ws = J
	double EnergyReactive = chanData.EnergyReactive;		// in VAs


	if (millis() - remMqttIData->sentTime > remPara.maxMqttSendDelay)
	{
		send = true;
		Logger.debug("sent MQTT I Data chan %d wegen Zeitaenderung", remMqttIData->chan);
	}
	else if (abweichung(current, remMqttIData->sentCurrent, 5.0, 0.002))
	{
		send = true;
		Logger.debug("sent MQTT I Data chan %d wegen Stromaenderung", remMqttIData->chan);
	}
	else if (abweichung(PowerActive, remMqttIData->sentPowerActive, 5.0,0.5))
	{
		send = true;
		Logger.debug("sent MQTT I Data chan %d wegen Leistungsaenderung", remMqttIData->chan);
	}

	if (send)
	{
		//mqttPublish(prefix, "time", String(Zeit.getFormattedDateTime(timeStr, 40)));
		mqttPublish(prefix, "current", String(current) + " A");
		mqttPublish(prefix, "PowerActive", String(PowerActive) + " W");
		//mqttPublish(prefix, "PowerReactive", String(PowerReactive)+"VA");  
		mqttPublish(prefix, "EnergyActive", String(EnergyActive / 3600000, 7)+" kWh");
		//mqttPublish(prefix, "EnergyReactive", String(EnergyReactive/3600000,7)+" kVAh");        
		remMqttIData->sentTime = millis();
		remMqttIData->sentCurrent = current;
		remMqttIData->sentPowerActive = PowerActive;
		remMqttIData->sentPowerReactive = PowerReactive;
		remMqttIData->sentEnergyActive = EnergyActive;
		remMqttIData->sentEnergyReactive = EnergyReactive;
	}
}



bool RemMqttClass::abweichung(double val, double lastVal, double prozent, double minAbw)
{
	if (val == 0.0) return false;
	double abw  = fabs(val - lastVal);
	if (abw < minAbw) return false;
	double v = abw / val * 100;
	Logger.debug("abweichung: val=%f  last=%f  abw=%f abwProz=%f proz=%f  minAbw=%f erg=%d",val,lastVal,abw,v,prozent,minAbw,v>prozent);
	return v > prozent;
}


void RemMqttClass::mqttPublish(String prefix, String name, String value)
{
	char adr[40];
	snprintf(adr, 40, "%s/%s", prefix.c_str(), name.c_str());
	client->publish(adr, value.c_str(),true);
}

void RemMqttClass::handleClient() {
	client->loop();
}

void RemMqttClass::reconnect() 
{
	// reconnect if needed
	if (!client->connected())
	{
		String prefix = String(remPara.mqttMask);
		prefix.replace("<REMMM>", "REMC");
		Logger.info("Attempting MQTT connection from %s...", remPara.mqttClientName.c_str());
		// Attempt to connect
		if (client->connect(remPara.mqttClientName.c_str(),remPara.mqttUser.c_str(), remPara.mqttPassword.c_str())) 
		{
			mqttReconnectOk++;
			Logger.info("connected  count: ok=%d  fail=%d", mqttReconnectOk, mqttReconnectFail);
			client->publish((prefix+"/mqttReconnectOk").c_str(),String(mqttReconnectOk).c_str(),true);
			client->publish((prefix + "/mqttReconnectFail").c_str(), String(mqttReconnectFail).c_str(), true);
			// Subscribe
			// todo auf was will ich reagieren?  client.subscribe("esp32/output");
		}
		else 
		{
			mqttReconnectFail++;
			Logger.warning("MQTT connect failed, rc=%d try again in 1 second  count: ok=%d  fail=%d\n", client->state(), mqttReconnectOk, mqttReconnectFail);
			client->publish((prefix + "/mqttReconnectFail").c_str(), String(mqttReconnectFail).c_str(),true);
			client->publish((prefix + "/mqttReconnectOk").c_str(), String(mqttReconnectOk).c_str(), true);
		}
	}
}

void RemMqttClass::sendTime()
{
	String prefix = String(remPara.mqttMask);
	prefix.replace("<REMMM>", "REMC");
	char timeStr[40];
	mqttPublish(prefix, "time", String(Zeit.getFormattedTimeMs(timeStr, 40)));
}

void RemMqttClass::MqttReceived(char* topic, byte* payload, unsigned int length) 
{
	if (restoreEneryCounter)
	{
		String top = String(topic);
		if (top.endsWith("EnergyActive"))
		{
			if (length > 39) return;  // zu lang
			char valueStr[40];
			memcpy(valueStr, payload, length);
			valueStr[length] = 0;

			// Einheit entfernen
			for (size_t i = 0; i < length; i++)
			{
				if (valueStr[i] == ' ') valueStr[i] = 0;
			}
			int moduleNo;
			int chan;
			char remName[40];
			sscanf(topic, "%4s/%d/%d",&remName, &moduleNo, &chan);
			int modIdx = RemMMClass::getModuleIdx("REMMM"+String(moduleNo));
			if (modIdx < 0) return;
			double valueNew = atof(valueStr);
			Logger.info("Energy found: [%s]= %s-%d(%d)-%d : %f",topic,remName, moduleNo,modIdx,chan,valueNew);

			double* val = &RemMMClass::remMM[modIdx]->ade7816.data.chan[chan].EnergyActive;

			if (valueNew > *val)
			{
				Logger.info("    updatet from %f to %f", *val, valueNew);
				*val = valueNew*3600000;   // Setzen und Umrechnung von kWh in J
			}

		}
	}
}

bool RemMqttClass::getLastEnergyCounter()
{
	String prefix = String(remPara.mqttMask);
	prefix.replace("<REMMM>", "#");
	client->subscribe(prefix.c_str());

	ulong startMillis = millis();

	restoreEneryCounter = true;
	while (millis() - startMillis < 2000)   // 2s auf MQTT warten
	{
		handleClient();
	}
	restoreEneryCounter = false;
	client->unsubscribe(prefix.c_str());
	return false;
}

RemMqttClass RemMqtt;

