/*
	Name:        RemMqttIDataClass.h
	Description: Handler für REM-MQTT Data per Channel
	Project:     REM  (Rainer's Energy Mesaurement) power measurement in AC networks
	Created:	 Dez 2020
	Author:      Rainer Petzoldt  R.Petzoldt@web.de
*/
#pragma once

#include "RemMM.h"

class RemMqttIDataClass
{
 protected:


 public:
	 ushort idx;                // Indexnummer
	 ushort chan;               // Kanalnummer
	 RemMMClass *remMM = NULL;	// zeiger auf die zugehörigen Daten

public:
	double sentCurrent = 0;			// in A
	double sentPowerActive = 0;		// in W
	double sentPowerReactive = 0;		// in VA
	double sentEnergyActive = 0;		// in Ws = J
	double sentEnergyReactive = 0;		// in VAs
	ulong  sentTime = 0;

	RemMqttIDataClass(ushort index, ushort channel);	// Konstruktor

};




