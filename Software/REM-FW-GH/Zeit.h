/*
	Name:        Zeit.h
	Description: Handling Time in REM
	Project:     REM  (Rainer's Energy Mesaurement) power measurement in AC networks
	Created:	 23.11.2020
	Author:      Rainer Petzoldt  R.Petzoldt@web.de
*/

#ifndef _ZEIT_h
#define _ZEIT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "NTPClient.h"


class ZeitClass 
{
 public:
	NTPClient * timeClient;
	
 public:
	void init(IPAddress ntpServerIp);
	void handleTime();
	char* getFormattedTime(char *buf, unsigned int bufsize);
	char* getFormattedTimeMs(char *buf, unsigned int bufsize);
	char* getFormattedDate(char *buf, unsigned int bufsize);
	char* getFormattedDateTime(char *buf, unsigned int bufsize);
	long getActualTime();

	static char* formatDateTime(char *buf, unsigned int bufsize, long time);
	static long scanDateTime(const char *timeStr);
};

extern ZeitClass Zeit;

#endif

