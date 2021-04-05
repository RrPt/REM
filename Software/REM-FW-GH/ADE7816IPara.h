/*
	Name:        ADE7816IPara.h
	Description: ADE7816 Parameter for current channel
	Project:     REM  (Rainer's Energy Mesaurement) power measurement in AC networks
	Created:	 16.07.2020
	Author:      Rainer Petzoldt  R.Petzoldt@web.de
*/


#pragma once

class ADE7816IParaClass
{
 public:
	 String description = "??";        // Beschreibung
	 int PCF_COEFF = 0x400CA4;		// Phasenkorektur
	 int WGAIN = 0;			// Skalenfaktor active Power
	 int WATTOS = 0;		// Offset active Power
	 int VARGAIN = 0;		// Skalenfaktor reactive Power
	 int VAROS = 0;			// Offset reactive Power
	 int IxRMSOS = 0;		// Offset Strom 
	 int IxGAIN = 2;		//  Skalenfaktor Strom
};



