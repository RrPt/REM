/*
	Name:        ADE7816Data.cpp
	Description: ADE7816 Measure Data
	Project:     REM  (Rainer's Energy Mesaurement) power measurement in AC networks
	Created:	 20.06.2020
	Author:      Rainer Petzoldt  R.Petzoldt@web.de
*/

#include "ADE7816Data.h"
#include "Logger.h"

void ADE7816DataClass::init()
{
	Logger.debug("ADE7816DataClass::init()");
	for (int i = 0; i < 6; i++)
	{
		chan[i].init();
	}
}




