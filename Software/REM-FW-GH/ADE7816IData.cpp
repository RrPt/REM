/*
	Name:        ADE7816IData.h
	Description: ADE7816 Measure Data for current channel
	Project:     REM  (Rainer's Energy Mesaurement) power measurement in AC networks
	Created:	 7.07.2020
	Author:      Rainer Petzoldt  R.Petzoldt@web.de
*/



#include "ADE7816IData.h"
#include "Zeit.h"
#include "Logger.h"

void ADE7816IDataClass::init()
{
	Logger.debug("  ADE7816IDataClass::init()");
	resetEnergy();
}


void ADE7816IDataClass::resetEnergy()
{
	Logger.debug("  ADE7816IDataClass::resetEnergy()");
	EnergyActive = 0;
	EnergyReactive = 0;	
	EnergyStartTime = Zeit.getActualTime();
}


