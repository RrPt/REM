/*
	Name:        ADE7816_I2C.cpp
	Description: I2C interface to ADE7816  
	Project:     REM  (Rainer's Energy Mesaurement) power measurement in AC networks
	Created:	 20.06.2020
	Author:      Rainer Petzoldt  R.Petzoldt@web.de
*/

#include "ADE7816.h"
#include <Wire.h>
#include "Logger.h"
#include <Preferences.h>

ADE7816_I2C::ADE7816_I2C(int addr)
{
	_addr = addr;
	interface = IsI2C;
}


///
/// Initialisierung des ADE7816
///  wenn initBus == true wird auch der I2C-Bus initialisiert
///
int ADE7816_I2C::init(bool initBus,String name )
{
	Logger.debug(" Start ADE7816_I2C::init(%d,%s)", initBus,name.c_str());

	Logger.info("  Schnittstelle: I2C");
	if (initBus)
	{	// Bus bei Bedarf initialisieren
		Logger.debug("  I2C init...");
		Wire.begin();
	}

	Logger.debug(" End ADE7816_I2C::init(%d)", initBus);

	return ADE7816::init(name);

}



// Write len Bytes of val to register reg
int ADE7816_I2C::_writeRegisterBytes(const unsigned int reg, const  byte *val, const unsigned int len)
{
	Wire.beginTransmission(_addr);

	byte hb = reg >> 8;
	byte lb = reg & 0xFF;
	Wire.write(hb);
	Wire.write(lb);

	for (int i = 0; i < len; i++)
	{
		Wire.write(val[i]);
	}
	int ret = Wire.endTransmission();

	return ret;
}

// read len Bytes of register reg to val
int ADE7816_I2C::_readRegisterBytes(const unsigned int reg, byte *val, unsigned int len)
{
	Wire.beginTransmission(_addr);

	byte hb = reg >> 8;
	byte lb = reg & 0xFF;
	Wire.write(hb);
	Wire.write(lb);
	int ret = Wire.endTransmission();

	Wire.requestFrom(_addr, len);

	for (int i = 0; i < len; i++)
	{
		val[i]= Wire.read();
	}
	//Logger.debug("ADE7816_I2C::_readRegisterBytes(reg=%X,val= %X %X %X %X", reg, val[0], val[1], val[2], val[3]);

	return ret;
}
