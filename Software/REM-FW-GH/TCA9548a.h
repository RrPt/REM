/*
	Name:        TCA9548a.h
	Description: class for I2C multiplexer
	Project:     REM  (Rainer's Energy Mesaurement) power measurement in AC networks
	Created:	 20.06.2020
	Author:      Rainer Petzoldt  R.Petzoldt@web.de
*/

#pragma once
#include <Arduino.h>

class TCA9548a
{
public:
	static void tcaSelect(uint8_t adr, int8_t port);
	static byte getControlByte(uint8_t adr);
	static void tcaScan();

private:
	static void scan();
	static String getDevName(byte adr);

};

