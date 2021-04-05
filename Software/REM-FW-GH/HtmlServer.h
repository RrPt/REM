/*
	Name:        HtmlServer.h
	Description: WebServer  mit spezifischern Seiten
	Project:     REM  (Rainer's Energy Mesaurement) power measurement in AC networks
	Created:	 03.07.2020
	Author:      Rainer Petzoldt  R.Petzoldt@web.de
*/


#ifndef _HTMLSERVER_h
#define _HTMLSERVER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <BasicWebServer.h>
#include "ArduinoJson.h"    // https://arduinojson.org/

class HtmlServerClass : public WebServer
{
 protected:
	 DynamicJsonDocument* spifFilesDoc;	// Die SpiffsFiles werden beim Start einmalig eingelesen  (Da Spiffs in Callback Probleme machen)

 public:
	void init();
	void handleFileUpload();
	void getSpifFilesDoc();
};


#endif

