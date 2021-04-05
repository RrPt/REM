/*
	Name:        Logger.h
	Description: Logging Class, for debugging to Serial, Telnet, ...
	Project:     REM  (Rainer's Energy Mesaurement) power measurement in AC networks
	Created:	 20.06.2020
	Author:      Rainer Petzoldt  R.Petzoldt@web.de
*/

#ifndef _LOGGER_h
#define _LOGGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#ifdef USE_ETH
#include "NetworkEthernet.h"
#else
#include "NetworkWifi.h"
#endif

#define LOGLEVEL_CRITICAL 5
#define LOGLEVEL_ERROR 4
#define LOGLEVEL_WARNING 3
#define LOGLEVEL_INFO 2
#define LOGLEVEL_DEBUG 1
#define LOGLEVEL_ALL 0


class LoggerClass
{
#ifdef USE_ETH
	EthernetServer* telnetServer = 0;
	EthernetClient telnetClient = 0;
#else
	WiFiServer* telnetServer = 0;
	WiFiClient telnetClient = 0;
#endif

 protected:
	 char timeStr[40];

 public:
	int loglevel = LOGLEVEL_DEBUG;
	void init();
	char* handleClients();

	size_t printf(const char * format, ...)  __attribute__((format(printf, 2, 3)));
	size_t print(const char * txt);
	size_t println(const char * txt);

	size_t critical(const char * format, ...)  __attribute__((format(printf, 2, 3)));
	size_t error(const char * format, ...)  __attribute__((format(printf, 2, 3)));
	size_t warning(const char * format, ...)  __attribute__((format(printf, 2, 3)));
	size_t info(const char * format, ...)  __attribute__((format(printf, 2, 3)));
	size_t debug(const char * format, ...)  __attribute__((format(printf, 2, 3)));
};

extern LoggerClass Logger;

#endif

