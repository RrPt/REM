// ADE7816Parameter.h

#ifndef _ADE7816PARAMETER_h
#define _ADE7816PARAMETER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Preferences.h>


class ParameterClass
{
 protected:
	 String prefNamespace;
	 Preferences preferences;

 public:
	void init(String name);
	void end();

	int getIntVal(String valName, int idx);
	void setIntVal(String valName, int idx, int value);

	void clearAll();
};


#endif

