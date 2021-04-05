/*
	Name:        ADE7816_SPI.h
	Description: SPI interface to ADE7816
	Project:     REM  (Rainer's Energy Mesaurement) power measurement in AC networks
	Created:	 20.06.2020
	Author:      Rainer Petzoldt  R.Petzoldt@web.de
*/

#pragma once
const int energy_CS = SS; // Use default SS pin for unknown Arduino

class ADE7816_SPI : public virtual ADE7816
{
public:
	int init(bool initBus = false, String name = "noName");
	ADE7816_SPI(int pin = energy_CS); 

protected:
	virtual int _writeRegisterBytes(const unsigned int reg, const  byte *val, const unsigned int len);
	virtual int _readRegisterBytes(const unsigned int reg, byte *val, unsigned int len);

private:
	int _cs;
};

