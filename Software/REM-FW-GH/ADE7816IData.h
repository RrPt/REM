/*
	Name:        ADE7816IData.h
	Description: ADE7816 Measure Data for current channel
	Project:     REM  (Rainer's Energy Mesaurement) power measurement in AC networks
	Created:	 7.07.2020
	Author:      Rainer Petzoldt  R.Petzoldt@web.de
*/


#pragma once

class ADE7816IDataClass
{
 protected:


 public:
	 double current = 0;			// in A
	 double PowerActive = 0;		// in W
	 double PowerReactive = 0;		// in VA
	 double EnergyActive = 0;		// in Ws = J
	 double EnergyReactive = 0;		// in VAs
	 double timeshift = 0;			// in ms
	 double phi = 0 ;				// in Grad
	 double cosPhi = 0;
	 long EnergyStartTime = 0;      // in sec

	 int currentRaw = 0;
	 int PowerActiveRaw = 0;
	 int PowerReactiveRaw = 0;
	 int timeshiftRaw = 0;

	 void init();
	 void resetEnergy();
};



