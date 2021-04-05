/*
	Name:        HtmlServer.cpp
	Description: WebServer  mit spezifischern Seiten
	Project:     REM  (Rainer's Energy Mesaurement) power measurement in AC networks
	Created:	 03.07.2020
	Author:      Rainer Petzoldt  R.Petzoldt@web.de
*/

#define JSONDOCSIZE 7000

#include "HtmlServer.h"
#include "RemMM.h"
#include <SPIFFS.h>
#include "Logger.h"
#include "ArduinoJson.h"    // https://arduinojson.org/
#include <math.h>
#include "Zeit.h"

File fsUploadFile;

void HtmlServerClass::init()
{

	SPIFFS.begin();
	serveStatic("/", SPIFFS, "/index.html");
	serveStatic("/KalibCurrent", SPIFFS, "/KalibCurrent.html");
	serveStatic("/KalibVoltage", SPIFFS, "/KalibVoltage.html");
	serveStatic("/KalibPower", SPIFFS, "/KalibPower.html");
	serveStatic("/KalibPhase", SPIFFS, "/KalibPhase.html");
	serveStatic("/KalibPowerReactive", SPIFFS, "/KalibPowerReactive.html");
	serveStatic("/Parameter", SPIFFS, "/Parameter.html");
	serveStatic("/AllVParameter", SPIFFS, "/AllVParameter.html");
	serveStatic("/AllCParameter", SPIFFS, "/AllCParameter.html");
	serveStatic("/templateHandler.js", SPIFFS, "/templateHandler.js");
	serveStatic("/Command", SPIFFS, "/Command.html");
	serveStatic("/Files", SPIFFS, "/Files.html");

	//getSpifFilesDoc();


	on("/api/KalibData", HTTPMethod::HTTP_GET, [&]()
	{
		String response;
		Logger.debug("request %s", uri().c_str());

		for (size_t i = 0; i < args(); i++)
		{
			Logger.debug("ARG[%d]=%s:%s", i, argName(i).c_str(), arg(i).c_str());
		}
		Logger.debug("Anz REM-MM=%d  Docsize = %d", RemMMClass::anzModules, RemMMClass::anzModules * 2000);
		DynamicJsonDocument doc(RemMMClass::anzModules * 2000);
		char timeStr[40];
		doc["time"] = Zeit.getFormattedDateTime(timeStr, 40);

		JsonObject jmods = doc.createNestedObject("modules");

		for (size_t mod = 0; mod < RemMMClass::anzModules; mod++)
		{
			JsonObject jmod = jmods.createNestedObject(RemMMClass::remMM[mod]->name);
			jmod["voltageRaw"] = RemMMClass::remMM[mod]->ade7816.data.voltageRaw;
			jmod["voltage"] = RemMMClass::remMM[mod]->ade7816.data.voltage;
			jmod["Gain"] = RemMMClass::remMM[mod]->ade7816.parameter.pGain;
			jmod["vxGAIN"] = RemMMClass::remMM[mod]->ade7816.parameter.pVGAIN;
			jmod["vxRMSOS"] = RemMMClass::remMM[mod]->ade7816.parameter.pVRMSOS;
			jmod["lineCyc"] = RemMMClass::remMM[mod]->ade7816.parameter.lineCyc;
			jmod["APNOLOAD"] = RemMMClass::remMM[mod]->ade7816.parameter.pAPNOLOAD;
			jmod["VARNOLOAD"] = RemMMClass::remMM[mod]->ade7816.parameter.pVARNOLOAD;
			JsonArray jchans = jmod.createNestedArray("channels");
			for (size_t chan = 0; chan < nCHANELS; chan++)
			{
				JsonObject jchan = jchans.createNestedObject();
				jchan["channel"] = chan;
				jchan["currentRaw"] = RemMMClass::remMM[mod]->ade7816.data.chan[chan].currentRaw;
				jchan["current"] = RemMMClass::remMM[mod]->ade7816.data.chan[chan].current;
				jchan["ixGAIN"] = RemMMClass::remMM[mod]->ade7816.parameter.chan[chan].IxGAIN;
				jchan["ixRMSOS"] = RemMMClass::remMM[mod]->ade7816.parameter.chan[chan].IxRMSOS;
				jchan["powerActiveRaw"] = RemMMClass::remMM[mod]->ade7816.data.chan[chan].PowerActiveRaw;
				jchan["powerActive"] = RemMMClass::remMM[mod]->ade7816.data.chan[chan].PowerActive;
				jchan["wGAIN"] = RemMMClass::remMM[mod]->ade7816.parameter.chan[chan].WGAIN;
				jchan["wRMSOS"] = RemMMClass::remMM[mod]->ade7816.parameter.chan[chan].WATTOS;
				jchan["powerReactiveRaw"] = RemMMClass::remMM[mod]->ade7816.data.chan[chan].PowerReactiveRaw;
				jchan["powerReactive"] = RemMMClass::remMM[mod]->ade7816.data.chan[chan].PowerReactive;
				jchan["varGAIN"] = RemMMClass::remMM[mod]->ade7816.parameter.chan[chan].VARGAIN;
				jchan["varOS"] = RemMMClass::remMM[mod]->ade7816.parameter.chan[chan].VAROS;
				jchan["PCF_COEFF"] = RemMMClass::remMM[mod]->ade7816.parameter.chan[chan].PCF_COEFF;
			}
		}
		Logger.debug("KalibData JSONDoc size= %d  %d", measureJson(doc), measureJsonPretty(doc));
		sendJsonDoc(200, doc);
	});

	on("/api/KalibCurrent", HTTPMethod::HTTP_GET, [&]()
	{	// ein Kalib Button wurde gedrückt
		// Parameter:  
		// KalibBef: 1=KAlibGain  2= KalibOffset  3=SetGain  4=SetOffset
		// Modulindex 
		// SollValue falls erforderlich
		String response;
		long long val;
		long long refVal;
		Logger.info("request %s", uri().c_str());

	err:
		for (size_t i = 0; i < args(); i++)
		{
			Logger.warning("ARG[%d]=%s:%s", i, argName(i).c_str(), arg(i).c_str());
		}
		int kalibBef = arg("kalibBef").toInt();
		int moduleNo = arg("module").toInt();
		String moduleName = String(RemMMClass::remMM[moduleNo]->name);
		double sollValue = arg("sollValue").toDouble();  // todo falsche Eingabe abfangen
		Logger.warning("KalibCurrent Bef=%d mod=%d  %s  sollVal=%f", kalibBef, moduleNo, moduleName.c_str(), sollValue);

		if (kalibBef == 1)	RemMMClass::remMM[moduleNo]->kalibCurrentGain(sollValue);
		if (kalibBef == 2)	RemMMClass::remMM[moduleNo]->kalibCurrentOffset();
		if (kalibBef == 3)	RemMMClass::remMM[moduleNo]->setCurrentGain(sollValue);
		if (kalibBef == 4)	RemMMClass::remMM[moduleNo]->setCurrentOffset(sollValue);

		send(200, "application/json", "{}");
	});

	on("/api/KalibVoltage", HTTPMethod::HTTP_GET, [&]()
	{	// ein Kalib Button wurde gedrückt
		// Parameter:  
		// KalibBef: 1=KAlibGain  2= KalibOffset  3=SetGain  4=SetOffset
		// Modulindex 
		// SollValue falls erforderlich
		String response;
		long long val;
		long long refVal;
		Logger.info("request %s", uri().c_str());

	err:
		for (size_t i = 0; i < args(); i++)
		{
			Logger.warning("ARG[%d]=%s:%s", i, argName(i).c_str(), arg(i).c_str());
		}
		int kalibBef = arg("kalibBef").toInt();
		int moduleNo = arg("module").toInt();
		String moduleName = String(RemMMClass::remMM[moduleNo]->name);
		double sollValue = arg("sollValue").toDouble();  // todo falsche Eingabe abfangen
		Logger.warning("KalibVoltage Bef=%d mod=%d  %s  sollVal=%f", kalibBef, moduleNo, moduleName.c_str(), sollValue);

		if (kalibBef == 1)	RemMMClass::remMM[moduleNo]->kalibVoltageGain(sollValue);
		if (kalibBef == 2)	RemMMClass::remMM[moduleNo]->kalibVoltageOffset();
		if (kalibBef == 3)	RemMMClass::remMM[moduleNo]->setVoltageGain(sollValue);
		if (kalibBef == 4)	RemMMClass::remMM[moduleNo]->setVoltageOffset(sollValue);

		send(200, "application/json", "{}");
	});

	on("/api/KalibPower", HTTPMethod::HTTP_GET, [&]()
	{	// ein Kalib Button wurde gedrückt
		// Parameter:  
		// KalibBef: 1=KAlibGain  2= KalibOffset  3=SetGain  4=SetOffset
		// Modulindex 
		// SollValue falls erforderlich
		String response;
		long long val;
		long long refVal;
		Logger.info("request %s", uri().c_str());

	err:
		for (size_t i = 0; i < args(); i++)
		{
			Logger.warning("ARG[%d]=%s:%s", i, argName(i).c_str(), arg(i).c_str());
		}
		int kalibBef = arg("kalibBef").toInt();
		int moduleNo = arg("module").toInt();
		String moduleName = String(RemMMClass::remMM[moduleNo]->name);
		double sollValue = arg("sollValue").toDouble();  // todo falsche Eingabe abfangen
		Logger.warning("KalibPower Bef=%d mod=%d  %s  sollVal=%f", kalibBef, moduleNo, moduleName.c_str(), sollValue);

		if (kalibBef == 1)	RemMMClass::remMM[moduleNo]->kalibPowerGain(sollValue);
		if (kalibBef == 2)	RemMMClass::remMM[moduleNo]->kalibPowerOffset();
		if (kalibBef == 3)	RemMMClass::remMM[moduleNo]->setPowerGain(sollValue);
		if (kalibBef == 4)	RemMMClass::remMM[moduleNo]->setPowerOffset(sollValue);
		if (kalibBef == 11)	RemMMClass::remMM[moduleNo]->kalibPowerGain(sollValue, true);
		if (kalibBef == 12)	RemMMClass::remMM[moduleNo]->kalibPowerOffset(true);
		if (kalibBef == 13)	RemMMClass::remMM[moduleNo]->setPowerGain(sollValue, true);
		if (kalibBef == 14)	RemMMClass::remMM[moduleNo]->setPowerOffset(sollValue, true);

		send(200, "application/json", "{}");
	});

	on("/api/KalibPhase", HTTPMethod::HTTP_GET, [&]()
	{	// ein Kalib Button wurde gedrückt
		// Parameter:  
		// KalibBef: 1=KAlibGain  2= KalibOffset  3=SetGain  4=SetOffset
		// Modulindex 
		// SollValue falls erforderlich
		String response;
		long long val;
		long long refVal;
		Logger.info("request %s", uri().c_str());

	err:
		for (size_t i = 0; i < args(); i++)
		{
			Logger.warning("ARG[%d]=%s:%s", i, argName(i).c_str(), arg(i).c_str());
		}
		int kalibBef = arg("kalibBef").toInt();
		int moduleNo = arg("module").toInt();
		String moduleName = String(RemMMClass::remMM[moduleNo]->name);
		double sollValue = arg("sollValue").toDouble();  // todo falsche Eingabe abfangen
		Logger.warning("KalibPhase Bef=%d mod=%d  %s  sollVal=%f", kalibBef, moduleNo, moduleName.c_str(), sollValue);

		if (kalibBef == 1)	RemMMClass::remMM[moduleNo]->setAllPcfCoeff(sollValue);
		if (kalibBef == 2)	RemMMClass::remMM[moduleNo]->kalibAllPcfCoeff(sollValue);

		send(200, "application/json", "{}");
	});

	on("/api/modules", HTTPMethod::HTTP_GET, [&]()
	{
		Logger.debug("request %s", uri().c_str());

		if (args() > 0)
		{
			for (size_t i = 0; i < args(); i++)
			{
				Logger.debug("ARG[%d]=%s:%s", i, argName(i).c_str(), arg(i).c_str());
			}

			int bef = arg("Bef").toInt();
			int moduleNo = arg("module").toInt();
			int chan = arg("chan").toInt();
			String moduleName = String(RemMMClass::remMM[moduleNo]->name);
			Logger.debug(" Bef=%d mod=%d  %s  chan=%d", bef, moduleNo, moduleName.c_str(), chan);

			if (bef == 1)	RemMMClass::remMM[moduleNo]->resetEnergy(chan); // für einen Kanal

			send(200, "application/json", "{}");
		}
		else
		{
			Logger.debug("/api/modules Anz REM-MM=%d  Docsize = %d", RemMMClass::anzModules, RemMMClass::anzModules * 1500);
			DynamicJsonDocument doc(RemMMClass::anzModules * 1500);
			char timeStr[40];
			doc["time"] = Zeit.getFormattedDateTime(timeStr, 40);
			doc["timeRaw"] = Zeit.getActualTime();
			char startTimeStr[40];
			doc["startTime"] = Zeit.formatDateTime(startTimeStr, 40, RemMMClass::startTime);
			JsonObject jmods = doc.createNestedObject("modules");

			for (size_t mod = 0; mod < RemMMClass::anzModules; mod++)
			{
				JsonObject jmod = jmods.createNestedObject(RemMMClass::remMM[mod]->name);
				jmod["noOfMeasurements"] = RemMMClass::remMM[mod]->ade7816.data.noOfMeasurements;
				jmod["voltage"] = round(RemMMClass::remMM[mod]->ade7816.data.voltage * 10) / 10;
				jmod["freq"] = round(RemMMClass::remMM[mod]->ade7816.data.frequency * 1000) / 1000;

				JsonArray jchans = jmod.createNestedArray("channels");
				for (size_t chan = 0; chan < nCHANELS; chan++)
				{
					JsonObject jchan = jchans.createNestedObject();
					jchan["channel"] = chan;
					jchan["desc"] = RemMMClass::remMM[mod]->ade7816.parameter.chan[chan].description;
					jchan["amps"] = round(RemMMClass::remMM[mod]->ade7816.data.chan[chan].current * 10000) / 10000;
					jchan["power"] = round(RemMMClass::remMM[mod]->ade7816.data.chan[chan].PowerActive * 100) / 100;
					jchan["powerreactive"] = round(RemMMClass::remMM[mod]->ade7816.data.chan[chan].PowerReactive * 100) / 100;
					jchan["energy"] = round(RemMMClass::remMM[mod]->ade7816.data.chan[chan].EnergyActive / 3.6) / 1000000;  // in kWh
					jchan["energyreactive"] = round(RemMMClass::remMM[mod]->ade7816.data.chan[chan].EnergyReactive / 3.6) / 1000000;  // in kVAh
					char startTimeBuf[40];
					jchan["energyStartTime"] = Zeit.formatDateTime(startTimeBuf, 40, RemMMClass::remMM[mod]->ade7816.data.chan[chan].EnergyStartTime);
				}
			}
			Logger.debug("/api/modules JSONDoc size= %d  %d", measureJson(doc), measureJsonPretty(doc));

			sendJsonDoc(200, doc);
		}
	});

	on("/api/Parameter", HTTPMethod::HTTP_GET, [&]()
	{
		//String response;
		Logger.debug("request %s", uri().c_str());

		for (size_t i = 0; i < args(); i++)
		{
			Logger.debug("ARG[%d]=%s:%s", i, argName(i).c_str(), arg(i).c_str());
		}
		Logger.debug("/api/Parameter Anz REM-MM=%d  Docsize = %d", RemMMClass::anzModules, RemMMClass::anzModules * 200);
		DynamicJsonDocument doc(RemMMClass::anzModules * 200);
		char timeStr[40];
		doc["time"] = Zeit.getFormattedDateTime(timeStr, 40);

		JsonObject jmods = doc.createNestedObject("modules");

		for (size_t mod = 0; mod < RemMMClass::anzModules; mod++)
		{
			JsonObject jmod = jmods.createNestedObject(RemMMClass::remMM[mod]->name);
			jmod["lineCyc"] = RemMMClass::remMM[mod]->ade7816.parameter.lineCyc;
			jmod["Gain"] = RemMMClass::remMM[mod]->ade7816.parameter.pGain;
			jmod["APNOLOAD"] = RemMMClass::remMM[mod]->ade7816.parameter.pAPNOLOAD;
			jmod["VARNOLOAD"] = RemMMClass::remMM[mod]->ade7816.parameter.pVARNOLOAD;
			jmod["OILVL"] = RemMMClass::remMM[mod]->ade7816.parameter.pOILVL;
			jmod["OVLVL"] = RemMMClass::remMM[mod]->ade7816.parameter.pOVLVL;
			JsonArray jchans = jmod.createNestedArray("channels");
			//for (size_t chan = 0; chan < nCHANELS; chan++)
			//{
			//	//val = RemMMClass::remMM[mod]->ade7816.data.chan[chan].currentRaw;
			//	//val = refVal / val - (1 << 23);
			//	JsonObject jchan = jchans.createNestedObject();
			//	jchan["channel"] = chan;
			//	jchan["PCF_COEFF"] = RemMMClass::remMM[mod]->ade7816.parameter.chan[chan].PCF_COEFF;
			//}
		}
		Logger.debug("/api/Parameter JSONDoc size= %d  %d", measureJson(doc), measureJsonPretty(doc));

		sendJsonDoc(200, doc);

	});

	on("/api/SetParameter", HTTPMethod::HTTP_GET, [&]()
	{	// ein Set Button wurde gedrückt
		// Parameter:  
		// todo Beschreibung
		// KalibBef: 1=KAlibGain  2= KalibOffset  3=SetGain  4=SetOffset
		// Modulindex 
		// SollValue falls erforderlich  
		String response;
		long long val;
		long long refVal;
		Logger.info("request %s", uri().c_str());

	err:
		for (size_t i = 0; i < args(); i++)
		{
			Logger.warning("ARG[%d]=%s:%s", i, argName(i).c_str(), arg(i).c_str());
		}
		int bef = arg("Bef").toInt();
		int moduleNo = arg("module").toInt();
		int chan = arg("chan").toInt();
		String moduleName = String(RemMMClass::remMM[moduleNo]->name);
		String paraName = arg("Para");
		double sollValue = arg("sollValue").toDouble();  // todo falsche Eingabe abfangen
		Logger.warning("SetParameter Bef=%d mod=%d  %s  chan=%d Para=%s sollVal=%f", bef, moduleNo, moduleName.c_str(), chan, paraName.c_str(), sollValue);

		if (bef == 1)	RemMMClass::remMM[moduleNo]->setParameter(paraName, sollValue); // für alle Kanäle
		if (bef == 2)	RemMMClass::remMM[moduleNo]->setParameter(paraName, sollValue, chan); // für einen Kanäle

		send(200, "application/json", "{}");
	});

	on("/api/ParaToFlash", HTTPMethod::HTTP_GET, [&]()
	{
		// Button "All Para to Flash" wurde gedrückt
		Logger.info("request %s", uri().c_str());

		for (size_t mod = 0; mod < RemMMClass::anzModules; mod++)
		{
			RemMMClass::remMM[mod]->writePara();
		}

	});

	on("/api/time", HTTPMethod::HTTP_GET, [&]()
	{
		Logger.debug("request %s", uri().c_str());

		{
			Logger.debug("/api/modules Anz REM-MM=%d  Docsize = %d", RemMMClass::anzModules, RemMMClass::anzModules * 1500);
			DynamicJsonDocument doc(RemMMClass::anzModules * 1500);
			char timeStr[40];
			doc["time"] = Zeit.getFormattedDateTime(timeStr, 40);
			doc["timeRaw"] = Zeit.getActualTime();
			char startTimeStr[40];
			doc["startTime"] = Zeit.formatDateTime(startTimeStr, 40, RemMMClass::startTime);
			Logger.debug("/api/time JSONDoc size= %d  %d", measureJson(doc), measureJsonPretty(doc));

			sendJsonDoc(200, doc);
		}
	});

	on("/api/command/Rescan", HTTPMethod::HTTP_GET, [&]()
	{
		Logger.info("request %s", uri().c_str());
		Logger.info("Rescan for REM-MM");
		RemMMClass::initModules();
		send(200, "application/json", "{}");
	});

	on("/api/command/ResetMM", HTTPMethod::HTTP_GET, [&]()
	{
		Logger.info("request %s", uri().c_str());
		RemMMClass::saveAllEnergyCounter();
		for (size_t mod = 0; mod < RemMMClass::anzModules; mod++)
		{
			Logger.warning("Reset %s", RemMMClass::remMM[mod]->name);
			RemMMClass::remMM[mod]->resetAde7816();
		}
		RemMMClass::restoreAllEnergyCounter();
		send(200, "application/json", "{}");
	});

	on("/api/command/HardResetMM", HTTPMethod::HTTP_GET, [&]()
	{
		Logger.info("request %s", uri().c_str());
		RemMMClass::saveAllEnergyCounter();
		RemMMClass::powerSwitch(false);
		Logger.warning("Off\n");
		delay(1000);  // 1s warten
		RemMMClass::powerSwitch(true);
		Logger.warning("switch Power On\n");
		// und dann wieder initialisieren
		for (size_t mod = 0; mod < RemMMClass::anzModules; mod++)
		{
			Logger.warning("Reset %s", RemMMClass::remMM[mod]->name);
			RemMMClass::remMM[mod]->resetAde7816();
		}
		RemMMClass::restoreAllEnergyCounter();
		send(200, "application/json", "{}");
	});

	on("/api/command/ResetC", HTTPMethod::HTTP_GET, [&]()
	{
		Logger.info("request %s", uri().c_str());
		Logger.warning("Restart ESP");
		send(200, "application/json", "{}");
		RemMMClass::saveAllEnergyCounter();
		ESP.restart();
	});

	on("/api/command/SaveCounter", HTTPMethod::HTTP_GET, [&]()
	{
		Logger.info("request %s", uri().c_str());
		Logger.warning("Save Counter");
		send(200, "application/json", "{}");
		RemMMClass::saveAllEnergyCounter();
	});

	on("/api/files", HTTPMethod::HTTP_GET, [&]()
	{
		Logger.warning("request %s", uri().c_str());

		for (size_t i = 0; i < args(); i++)
		{
			Logger.warning("ARG[%d]=%s:%s", i, argName(i).c_str(), arg(i).c_str());
		}
		getSpifFilesDoc();
		sendJsonDoc(200, *spifFilesDoc);
	});

	on("/fs", HTTPMethod::HTTP_GET, [&]() {
		String response;
		Logger.debug("WebRequest: /fs");
		String fn = "no";
		Logger.info("Headerfile:%s\n", response.c_str());
		if (args() == 0)
		{
			response += "<a href=""/"">Hauptseite</a><br><br><p>Kein Dateiname angegeben!</p>";
			send(404, "text/html", response);
			return;
		};
		for (size_t i = 0; i < args(); i++)
		{
			Logger.debug("ARG[%d]=%s:%s", i, argName(i).c_str(), arg(i).c_str());
		}
		fn = arg("fn");
		Logger.debug("Get fn=%s", fn.c_str());
		String fileType = "text/html";
		if (fn.indexOf("json") > 0) fileType = "application/json";

		File file = SPIFFS.open(fn, "r");
		streamFile(file, fileType);

		file.close();

	});

	on("/Command", HTTP_POST,                       // if the client posts to the upload page
		[&](){},
		[&]()
	{
		Logger.info("POST /Command");
		handleFileUpload();

	}
		);

	begin();
}

void HtmlServerClass::handleFileUpload()
{ // upload a new file to the SPIFFS
	HTTPUpload& upload1 = upload();
	Logger.info("handleFileUpload(%s) status=%d", upload1.filename.c_str(), upload1.status);
	if (upload1.status == UPLOAD_FILE_START) {
		String filename = upload1.filename;
		if (!filename.startsWith("/")) filename = "/" + filename;
		Logger.info("Start handleFileUpload");
		fsUploadFile = SPIFFS.open(filename, "w");            // Open the file for writing in SPIFFS (create if it doesn't exist)
		filename = String();
	}
	else if (upload1.status == UPLOAD_FILE_WRITE) {
		Logger.info("File Write currentSize=%d", upload1.currentSize);
		if (fsUploadFile)
			fsUploadFile.write(upload1.buf, upload1.currentSize); // Write the received bytes to the file
	}
	else if (upload1.status == UPLOAD_FILE_END) {
		if (fsUploadFile) {                                    // If the file was successfully created
			fsUploadFile.close();                               // Close the file again
			Logger.info("handleFileUpload Size: %d",upload1.totalSize);
			sendHeader("Location", "/Command");      // Redirect the client to the success page
			send(303);
		}
		else {
			Serial.printf("File End size=%d", upload1.currentSize);
			send(500, "text/plain", "500: couldn't create file");
		}
	}
}

void HtmlServerClass::getSpifFilesDoc()
{
	this->spifFilesDoc = new DynamicJsonDocument(2000);
	char timeStr[40];
	(*spifFilesDoc)["time"] = Zeit.getFormattedDateTime(timeStr, 40);

	JsonArray jfiles1 = spifFilesDoc->createNestedArray("files");

	File root = SPIFFS.open("/");
	if (!root) {
		Logger.warning("- failed to open directory");
	}
	if (!root.isDirectory()) {
		Logger.warning(" - not a directory");
	}

	File file = root.openNextFile();
	while (file)
	{
		if (file.isDirectory())
		{
			Logger.error("Directorys in SPIFFS nicht unterstuetzt");
		}
		else
		{
			Logger.debug("File: %s", file.name());
			JsonObject jmod = jfiles1.createNestedObject();
			jmod["filename"] = String(file.name());
			jmod["size"] = file.size();
		}
		file.close();
		file = root.openNextFile();
	}
	file.close();
	root.close();

	Logger.debug("doc.size = %d ", measureJson(*spifFilesDoc));

}

