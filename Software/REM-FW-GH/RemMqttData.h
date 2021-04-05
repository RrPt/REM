/*
	Name:        RemMqttDataClass.h
	Description: Handler für REM-MQTT Data per Module
	Project:     REM  (Rainer's Energy Mesaurement) power measurement in AC networks
	Created:	 Dez 2020
	Author:      Rainer Petzoldt  R.Petzoldt@web.de
*/


#pragma once

#include "RemMM.h"
#include "RemMqttIData.h"


class RemMqttDataClass
{
 protected:


 public:
	 ushort idx;                // Indexnummer
	 RemMMClass *remMM = NULL;	// zeiger auf die zugehörigen Daten

public:
	double sentVoltage = 0;
	double sentFrequency = 0;
	long sentNoOfMeasurements = 0;
	ulong sentTime = 0;
	RemMqttIDataClass *chan[6];

	RemMqttDataClass(ushort index);	// Konstruktor

};




