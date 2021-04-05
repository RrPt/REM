/*
	Name:        ADE7816Data.h
	Description: ADE7816 Measure Data for all Channels (voltage, frequency, ...)
	Project:     REM  (Rainer's Energy Mesaurement) power measurement in AC networks
	Created:	 20.06.2020
	Author:      Rainer Petzoldt  R.Petzoldt@web.de
*/


#pragma once

#include "ADE7816IData.h"

class ADE7816DataClass
{
 protected:


 public:
	 double voltage = 0;
	 double frequency = 0;
	 int voltageRaw = 0;
	 int periodRaw = 0;
	 double period = 0;
	 long noOfMeasurements = 0;
	 ADE7816IDataClass chan[6];

	 void init();
};


