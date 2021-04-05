/*
	Name:        Logger.cpp
	Description: Logging Class, for debugging to Serial, Telnet, ...
	Project:     REM  (Rainer's Energy Mesaurement) power measurement in AC networks
	Created:	 20.06.2020
	Author:      Rainer Petzoldt  R.Petzoldt@web.de
*/


#include "Logger.h"
#include "Zeit.h"
//#include <time.h>

#ifdef USE_ETH
	#include "NetworkEthernet.h"

#else
	#include "NetworkWifi.h"
	WiFiServer telnetServer(23);
	WiFiClient telnetClient ;
#endif

#define bufLen 200
#define textBuffSize 100 //length of longest command string 
	char textBuff[textBuffSize]; //someplace to put received text
	int charsReceived = 0;

void LoggerClass::init()
{
#ifdef USE_ETH
	telnetServer = new EthernetServer(23);
#else
	telnetServer = new WiFiServer(23);
#endif
	telnetClient = 0;

	Logger.info("vor Telent .begin");
	telnetServer->begin();
	Logger.info("nach Telent .begin");
}


char* LoggerClass::handleClients()
{
#ifdef USE_ETH
	telnetClient = telnetServer->available();
#else
	// todo  Wegen eines Bugs im ESP32 wird die Telnetconnection unterbrochen wenn ein Web-request ankommt
	if (!telnetClient.connected())
	{
		if (telnetClient = telnetServer->available()) Logger.info("new telnet Connection");
	}
#endif
	if (telnetClient.connected() && telnetClient.available())
	{
		char c;
		int charsWaiting=0;
		charsReceived = 0;
		// copy waiting characters into textBuff
		//until textBuff full, CR received, or no more characters
		charsWaiting = telnetClient.available();
		//info("LoggerClass::handleClients  charsWaiting=%d", charsWaiting);
		if (charsWaiting > textBuffSize)
		{  
			warning("zu viele Zeichen in der Telnet Queue, werden geloescht");
			do {
				c = telnetClient.read();
				charsWaiting--;
			} while (charsWaiting > 0);
			return NULL;
		}
		//do {
		//	c = telnetClient.read();
		//	Serial.printf("char=%c %d\n ",c,c);
		//	textBuff[charsReceived] = c;
		//	charsReceived++;
		//	charsWaiting--;
		//} while (charsReceived <= textBuffSize && c != 0x0d && charsWaiting > 0);
		textBuff[charsReceived] = 0;
		//info("Telnet received: %s", textBuff);
		return textBuff;
	}
	return NULL;
}

size_t LoggerClass::printf(const char * format, ...)
{
	char line[bufLen];
	va_list arg;
	int done;

	va_start(arg, format);
	done = vsprintf(line, format, arg);
	va_end(arg);

	Serial.print(line);

	//Serial.printf("vor tn.con status=x%x  %d\n", telnetClient.status(),&telnetClient);
	
	if (telnetClient.connected() && telnetClient.available())
	//if (telnetClient.connected())
	{
		//Serial.println("vor tn.print");
		telnetClient.print(line);
	}

	return done;
}

size_t LoggerClass::print(const char * txt)
{
	Logger.printf("%s", txt);
}

size_t LoggerClass::println(const char * txt)
{
	Logger.printf("%s\n", txt);
}

size_t LoggerClass::critical(const char * format, ...)
{
	if (loglevel >  LOGLEVEL_CRITICAL) return 0;
	char line[bufLen];
	va_list arg;
	int done;

	va_start(arg, format);
	done = vsprintf(line, format, arg);
	va_end(arg);

	Logger.printf("%sz [CRITICAL] %s\n", Zeit.getFormattedTimeMs(timeStr, 40),line);

	return done;
}

size_t LoggerClass::error(const char * format, ...)
{
	if (loglevel >  LOGLEVEL_ERROR) return 0;
	char line[bufLen];
	va_list arg;
	int done;

	va_start(arg, format);
	done = vsprintf(line, format, arg);
	va_end(arg);

	Logger.printf("%sz [ERROR] %s\n", Zeit.getFormattedTimeMs(timeStr, 40), line);

	return done;
}
size_t LoggerClass::warning(const char * format, ...)
{
	if (loglevel >  LOGLEVEL_WARNING) return 0;

	char line[bufLen];
	va_list arg;
	int done;

	va_start(arg, format);
	done = vsprintf(line, format, arg);
	va_end(arg);

	Logger.printf("%sz [WARNING] %s\n", Zeit.getFormattedTimeMs(timeStr, 40), line);

	return done;
}
size_t LoggerClass::info(const char * format, ...)
{
	if (loglevel > LOGLEVEL_INFO) return 0;

	char line[bufLen];
	va_list arg;
	int done;

	va_start(arg, format);
	done = vsprintf(line, format, arg);
	va_end(arg);

	Logger.printf("%sz [INFO] %s\n", Zeit.getFormattedTimeMs(timeStr, 40), line);

	return done;
}
size_t LoggerClass::debug(const char * format, ...)
{
	if (loglevel > LOGLEVEL_DEBUG) return 0;

	char line[bufLen];
	va_list arg;
	int done;

	va_start(arg, format);
	done = vsprintf(line, format, arg);
	va_end(arg);

	Logger.printf("%sz [DEBUG] %s\n", Zeit.getFormattedTimeMs(timeStr, 40), line);

	return done;
}



LoggerClass Logger;

