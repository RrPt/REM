/*
	Name:        ADE7816Parameter.cpp
	Description: Parameter Storage for ADE7816
	Project:     REM  (Rainer's Energy Mesaurement) power measurement in AC networks
	Created:	 20.06.2020
	Author:      Rainer Petzoldt  R.Petzoldt@web.de
*/

#include "Parameter.h"
#include "Logger.h"


void ParameterClass::init(String name)
{
	prefNamespace = name;
}

void ParameterClass::end()
{
}

//int ParameterClass::getIntVal(String valName, int idx)
//{
//	char key[20];
//	sprintf(key, "%s%d", valName.c_str(), idx);
//	preferences.begin(prefNamespace.c_str(), true);
//	int erg = preferences.getInt(key);
//	preferences.end();
//	Logger.info("  Pref getIntVal: %s.%s = %d = 0x%X", prefNamespace.c_str(), key, erg,erg);
//	return erg;
//}


void ParameterClass::setIntVal(String valName, int idx, int value)
{
	char key[20];
	sprintf(key, "%s%d", valName.c_str(), idx);
	preferences.begin(prefNamespace.c_str(), false);
	int erg = preferences.putInt(key, value);
	preferences.end();
	Logger.info("  Pref setIntVal: %s.%s = %d = 0x%X  erg=%d", prefNamespace.c_str(), key, value, value,erg);
}


void ParameterClass::clearAll()
{
	preferences.begin(prefNamespace.c_str(), false);
	preferences.clear();
	preferences.end();
}

