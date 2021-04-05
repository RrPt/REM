/*
	Name:        RemMqttIDataClass.cpp
	Description: Handler für REM-MQTT Data per Channel
	Project:     REM  (Rainer's Energy Mesaurement) power measurement in AC networks
	Created:	 Dez 2020
	Author:      Rainer Petzoldt  R.Petzoldt@web.de
*/

#include "RemMqttIData.h"

RemMqttIDataClass::RemMqttIDataClass(ushort index, ushort channel)
{
	idx = index;
	chan = channel;
	remMM = RemMMClass::remMM[idx];
}

