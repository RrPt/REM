/*
	Name:        ADE7816_I2C.h
	Description: I2C interface to ADE7816
	Project:     REM  (Rainer's Energy Mesaurement) power measurement in AC networks
	Created:	 20.06.2020
	Author:      Rainer Petzoldt  R.Petzoldt@web.de
*/

#pragma once


class ADE7816_I2C : public virtual ADE7816
{
public:
	int init(bool initBus = false, String name = "noName");
	ADE7816_I2C(int addr = ADE7816_ADDR);

protected:
	virtual int _writeRegisterBytes(const unsigned int reg, const  byte *val, const unsigned int len);
	virtual int _readRegisterBytes(const unsigned int reg, byte *val, unsigned int len);

private:
	int _addr;
};

