/*
	Name:        TCA9548a.cpp
	Description: class for I2C multiplexer
	Project:     REM  (Rainer's Energy Mesaurement) power measurement in AC networks
	Created:	 20.06.2020
	Author:      Rainer Petzoldt  R.Petzoldt@web.de
*/

#include "TCA9548a.h"
#include <Wire.h>
#include "Logger.h"


//#define TCAADDR 0x70


// Port == -1 --> deselect all
 void TCA9548a::tcaSelect(uint8_t adr, int8_t port) {
	 if (port > 7)
	 {
		 Logger.error("Port=%d > 7 in TCA9548a::tcaSelect",port);
		 return; 
	 }
	//Logger.debug("TCA9548a::tcaSelect adr=%02X  port=%02X", adr, port);
	Wire.beginTransmission(adr);
	if (port>=0) Wire.write(1 << port); // Port selektieren
	else  Wire.write(0);				// alle Ports aus
	Wire.endTransmission();
}


 byte TCA9548a::getControlByte(uint8_t adr) {
	 //Logger.debug("TCA9548a::getControlByte adr=%02X ", adr);
	 Wire.beginTransmission(adr);
	 Wire.endTransmission();
	 Wire.requestFrom(adr, (uint8_t) 1);
	 int erg = Wire.read();
	 //Logger.debug("    controlByte = %X", erg);
	 return (byte)erg;
 }


String TCA9548a::getDevName(byte adr)
{
	switch (adr)
	{
	case 0x20:
		return "MCP2300x";
	case 0x21:
	case 0x22:
	case 0x23:
	case 0x25:
	case 0x26:
	case 0x27:
		return "MCP2300x";
	case 0x24:
		return "RFID-Reader of MCP2300x (alt)";
	case 0x38:
		return "ADE7816";
	case 0x29:
		return "TSL2561";
	case 0x39:
		return "TSL2561 (alt)";
	case 0x3C:
		return "OLED 128x64";
	case 0x3D:
		return "OLED 128x64 (alt)";
	case 0x40:
		return "INA219";
	case 0x41:
	case 0x44:
	case 0x45:
		return "INA219 (alt)";
	case 0x48:
		return "ADS1115";
	case 0x49:
		return "TSL2561 or ADS1115 (alt)";
	case 0x4A:
	case 0x4B:
		return "ADS1115 (alt)";
	case 0x3F:
		return "Display 2x16";
	case 0x62:
		return "MCP4725";
	case 0x63:
		return "MCP4725 (alt)";
	case 0x70:
		return "TCA9548a";
	case 0x71:
	case 0x72:
	case 0x73:
	case 0x74:
	case 0x75:
		return "TCA9548a (alt)";
	case 0x76:
		return "BMP280 or TCA9548a (alt)";
	case 0x77:
		return "BMP280 (alt) or TCA9548a (alt)";

	default:
		return "?";
		break;
	}
}