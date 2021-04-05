/*
	Name:        RemMqttDataClass.cpp
	Description: Handler für REM-MQTT Data per Module
	Project:     REM  (Rainer's Energy Mesaurement) power measurement in AC networks
	Created:	 Dez 2020
	Author:      Rainer Petzoldt  R.Petzoldt@web.de
*/


#include "RemMqttData.h"

RemMqttDataClass::RemMqttDataClass(ushort index)
{
	idx = index;
	remMM = RemMMClass::remMM[idx];
}

