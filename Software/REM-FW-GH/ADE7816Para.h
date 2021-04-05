/*
	Name:        ADE7816Para.h
	Description: ADE7816 Parameter for all channels
	Project:     REM  (Rainer's Energy Mesaurement) power measurement in AC networks
	Created:	 20.06.2020
	Author:      Rainer Petzoldt  R.Petzoldt@web.de
*/

#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
#include "ADE7816IPara.h"

class ADE7816ParaClass
{
 protected:
	 String name;

 public:
	int lineCyc = 500;		    // Anzahl der Perioden fuer die Messung (a 10ms)  d.h. 500 = 5 Sekunden

	int pVGAIN = 0;		    // Spannungsskalenfaktor
	int pVRMSOS = 0;		// Spannungsoffset
	unsigned short pGain=0;	// Verstärkung des Eingangsverstärkers

	int pAPNOLOAD = 0;	// mindest active Power
	int pVARNOLOAD = 0;	// mindest reactive Power
	int pOILVL = 0xFFFFFF;		// Überstromgrenze
	int pOVLVL = 0xFFFFFF;		// Überspannungsgrenze

	// Parameter für die 6 Stromkanäle
	ADE7816IParaClass chan[6];	// Parameter für die Stromkanäle

	void init(String name);
	void setDefaultValues();
	bool read(String explizitFilename="");
	void write();

	void show();
};


