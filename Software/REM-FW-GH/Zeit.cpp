/*
	Name:        Zeit.cpp
	Description: Handling Time in REM
	Project:     REM  (Rainer's Energy Mesaurement) power measurement in AC networks
	Created:	 23.11.2020
	Author:      Rainer Petzoldt  R.Petzoldt@web.de
*/

#include "Zeit.h"

#ifdef USE_ETH
#include <EthernetUdp.h>
EthernetUDP ntpUDP;
#else
#include <WiFiUdp.h>
WiFiUDP ntpUDP;
#endif

#include <TimeLib.h>

void ZeitClass::init(IPAddress ntpServerIp)
{
	//Serial.println("1");
	timeClient = new NTPClient(ntpUDP, ntpServerIp);
	//Serial.println("2");
	timeClient->begin();
	//Serial.println("3");
	timeClient->update();
	//Serial.println("4");
}

void ZeitClass::handleTime()
{
	timeClient->update();
}

char* ZeitClass::getFormattedTimeMs(char *buf, unsigned int bufsize)
{
	if (Zeit.timeClient)
	{
		Zeit.timeClient->getFormattedTimeMs().toCharArray(buf, bufsize);
	}
	else
	{
		snprintf(buf, bufsize, "%02d:%02d:%02d.%03d", millis() / 3600000, (millis() / 60000) % 60, (millis() / 1000) % 60, millis() % 1000);
	}
	return buf;
}

char* ZeitClass::getFormattedTime(char *buf, unsigned int bufsize)
{
	if (Zeit.timeClient)
	{
		Zeit.timeClient->getFormattedTime().toCharArray(buf, bufsize);
	}
	else
	{
		snprintf(buf, bufsize, "%02d:%02d:%02d", millis() / 3600000, (millis() / 60000) % 60, (millis() / 1000) % 60);
	}
	return buf;
}

char* ZeitClass::getFormattedDate(char *buf, unsigned int bufsize)
{
	time_t t_unix_date1 = millis() / 1000;
	if (Zeit.timeClient)
	{
		t_unix_date1 = Zeit.timeClient->getEpochTime();
	}
	snprintf(buf, bufsize, "%02d.%02d.%04d", day(t_unix_date1), month(t_unix_date1), year(t_unix_date1));
	return buf;
}

char* ZeitClass::getFormattedDateTime(char *buf, unsigned int bufsize)
{
	time_t t_unix_date1 = millis() / 1000;
	if (Zeit.timeClient)
	{
		t_unix_date1 = Zeit.timeClient->getEpochTime();
	}
	snprintf(buf, bufsize, "%02d.%02d.%04d %02d:%02d:%02d", day(t_unix_date1), month(t_unix_date1), year(t_unix_date1), hour(t_unix_date1), minute(t_unix_date1), second(t_unix_date1));
	return buf;
}

char* ZeitClass::formatDateTime(char *buf, unsigned int bufsize, long time)
{
	snprintf(buf, bufsize, "%02d.%02d.%04d %02d:%02d:%02d", day(time), month(time), year(time), hour(time), minute(time), second(time));
	return buf;
}


long ZeitClass::scanDateTime(const char *timeStr)
{
	int year, month, day, hour, minute, second;
	tmElements_t tm;

	//Serial.printf("scanDateTime(%s)", timeStr);
	sscanf(timeStr, "%02d.%02d.%04d %02d:%02d:%02d", &day,&month, &year,  &hour, &minute, &second);
	//Serial.printf("  scan:  %02d.%02d.%04d %02d:%02d:%02d\n", year, month,day, hour, minute, second);
	tm.Year = year - 1970;
	tm.Month = month;
	tm.Day = day;
	tm.Hour = hour;
	tm.Minute = minute;
	tm.Second = second;
	//Serial.printf("    tm:  %02d.%02d.%04d %02d:%02d:%02d\n", tm.Year, tm.Month, tm.Day, tm.Hour, tm.Minute, tm.Second);

	time_t time =  makeTime(tm);
	return time;
}


long ZeitClass::getActualTime()
{
	return Zeit.timeClient->getEpochTime();
}

ZeitClass Zeit;

