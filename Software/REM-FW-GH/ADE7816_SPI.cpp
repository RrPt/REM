/*
	Name:        ADE7816_SPI.cpp
	Description: SPI interface to ADE7816  
	Project:     REM  (Rainer's Energy Mesaurement) power measurement in AC networks
	Created:	 20.06.2020
	Author:      Rainer Petzoldt  R.Petzoldt@web.de
*/

#include "ADE7816.h"
#include <SPI.h>
#include "Logger.h"

ADE7816_SPI::ADE7816_SPI(int pin)
{
    _cs = pin;
	interface = IsSPI;
	reset();					// Reset after startup needed
}

///
/// Initialisierung des ADE7816
///  wenn initBus == true wird auch der SPI-Bus initialisiert
///
int ADE7816_SPI::init(bool initBus, String name)
{
	Logger.debug("Start ADE7816_SPI::init(%d)", initBus);

	Logger.info("Schnittstelle: SPI");
	if (initBus)
	{	// Bus bei Bedarf initialisieren
		SPI.begin();	
	}

	pinMode(_cs, OUTPUT);

	// Switch to SPI
	for (int i = 0; i<4;i++)	// 4 times needed! ( not 3 times like written in datasheet) 
	{
		digitalWrite(_cs, LOW);
		delay(10);
		digitalWrite(_cs, HIGH);
		delay(10);
	}
	Logger.debug("End ADE7816_SPI::init(%d)", initBus);

	return ADE7816::init(name);
}

// Write len Bytes of val to register reg
int ADE7816_SPI::_writeRegisterBytes(const unsigned int reg, const  byte *val, const unsigned int len)
{
	byte idx = 0;
	digitalWrite(_cs, LOW);
	SPI.transfer(0x00);
	SPI.transfer16(reg);
	for (idx = 0; idx < len; idx++)
	{
		SPI.transfer(val[idx]);
	}
	digitalWrite(_cs, HIGH);

	return 0;	// keine Fehlerprüfung möglich
}

// read len Bytes of register reg to val
int ADE7816_SPI::_readRegisterBytes(const unsigned int reg, byte *val, unsigned int len)
{
	byte idx = 0;
	digitalWrite(_cs, LOW);
	SPI.transfer(0x01);
	SPI.transfer16(reg);
	for (idx = 0; idx < len; idx++)
	{
		val[idx] = SPI.transfer(0x00);
	}
	digitalWrite(_cs, HIGH);

	return 0;	// keine Fehlerprüfung möglich
}
