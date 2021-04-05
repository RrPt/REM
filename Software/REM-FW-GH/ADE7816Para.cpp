/*
	Name:        ADE7816Para.cpp
	Description: ADE7816 Parameter
	Project:     REM  (Rainer's Energy Mesaurement) power measurement in AC networks
	Created:	 20.06.2020
	Author:      Rainer Petzoldt  R.Petzoldt@web.de
*/


#include "ADE7816Para.h"
#include "ArduinoJson.h"    // https://arduinojson.org/
#include "SPIFFS.h"
#include <FS.h>
#include "Logger.h"


void ADE7816ParaClass::init(String _name)
{
	Logger.info("ADE7816ParaClass::init(%s)", name.c_str());
	name = _name;
	setDefaultValues();

	// Initialize SPIFFS
	if (!SPIFFS.begin(true)) {
		Logger.error("An Error has occurred while mounting SPIFFS");
		return;
	}
	Logger.debug("SPIFFS: used %d Bytes von %d", SPIFFS.usedBytes(), SPIFFS.totalBytes());
	read();
}


// Set to Default
void ADE7816ParaClass::setDefaultValues()
{
	lineCyc = 501;
	pAPNOLOAD = 123;
}


// Einlesen der Parameter aus dem Flash
bool ADE7816ParaClass::read(String explizitFilename)
{
	Logger.info("ADE7816ParaClass::read(%s)", explizitFilename.c_str());

	String fn = "/" + name + ".json";
	
	if (explizitFilename != "")
	{
		fn = explizitFilename;
	}

	Logger.debug("Filename: %s", fn.c_str());
	File file = SPIFFS.open(fn, FILE_READ);
	if (!file) {
		Logger.error("There was an error opening the file %s for read", fn.c_str());
		return false;
	}
	if (file.size()==0) {
		Logger.error("file %s didn't exist or is empty, using Default.json ", fn.c_str());
		fn = "/Default.json";
		file = SPIFFS.open(fn, FILE_READ);
		if (!file) {
			Logger.error("There was an error opening the file %s for read", fn.c_str());
			return false;
		}
		if (file.size() == 0) {
			Logger.error("file %s didn't exist or s empty, taking program defaults ", fn.c_str());
			return false;
		}
	}
	Logger.debug("Filesize=%d  filehandle=%d", file.size(),file);
	StaticJsonDocument<1500> doc;  //  size muss bei größerem Parametersatz angepasst weden
	Logger.debug("JsobDoc Memory: %d  von %d used", doc.memoryUsage(), doc.capacity());
	// Deserialize the JSON document
	DeserializationError error = deserializeJson(doc, file);
	Logger.debug("JsobDoc Memory: %d  von %d used", doc.memoryUsage(), doc.capacity());
	file.close();

	// Test if parsing succeeds.
	if (error) {
		Logger.error("deserializeJson() failed: %s",error.c_str());
	}

	lineCyc = doc["lineCyc"] ;
	if (lineCyc < 1)		// Abfangen, da sonst division by zero exception
	{
		Logger.warning("LineCycle ist %d, das ist zu klein, wird auf 499 gesetzt", lineCyc);
		lineCyc = 499;  
	}
	Logger.debug("lineCycle=%d", lineCyc);
	pAPNOLOAD = doc["APNOLOAD"] ;
	pVARNOLOAD =doc["VARNOLOAD"]  ;
	pOILVL = doc["OILVL"];
	pOVLVL = doc["OVLVL"];
	pVRMSOS = doc["VRMSOS"]  ;
	pVGAIN = doc["VGAIN"];
	pGain = doc["Gain"];
	for (size_t i = 0; i < 6; i++)
	{
		chan[i].description = doc["DESCRIPTION" + String(i)].as<String>();
		chan[i].PCF_COEFF = doc["PCF_COEFF" + String(i)]  ;
		chan[i].WGAIN = doc["WGAIN" + String(i)] ;
		chan[i].WATTOS = doc["WATTOS" + String(i)];
		chan[i].VARGAIN = doc["VARGAIN" + String(i)]  ;
		chan[i].VAROS = doc["VAROS" + String(i)]  ;
		chan[i].IxGAIN = doc["IxGAIN" + String(i)]  ;
		chan[i].IxRMSOS = doc["IxRMSOS" + String(i)]  ;
	}
	//show();  // todo nur debugging
	return true;
}

// Schreiben der Parameter in den Flash
void ADE7816ParaClass::write()
{ 
	Logger.info("ADE7816ParaClass::write(%s)", name.c_str());
	String fn = "/" + name + ".json";
	Logger.debug("Filename: %s", fn.c_str());
	File file = SPIFFS.open(fn, FILE_WRITE);  
	if (!file) {
		Logger.error("There was an error opening the file %s for writing",fn.c_str());
	}
	Logger.debug("Filesize=%d", file.size());
	StaticJsonDocument<1500> doc;  //  size muss bei größerem Parametersatz angepasst weden
	//Logger.debug("A"); delay(200);
	doc["Filename"] = fn;
	//Logger.debug("B"); delay(200);
	doc["lineCyc"] = lineCyc;
	//Logger.debug("C"); delay(200);
	doc["APNOLOAD"] = pAPNOLOAD ;
	doc["VARNOLOAD"] = pVARNOLOAD;
	doc["OILVL"] = pOILVL;
	doc["OVLVL"] = pOVLVL ;
	doc["VRMSOS"] = pVRMSOS;
	doc["VGAIN"] = pVGAIN;
	doc["Gain"] = pGain;
	//Logger.debug("D"); delay(200);
	for (size_t i = 0; i < 6; i++)
	{
		doc["DESCRIPTION" + String(i)] = chan[i].description;
		doc["PCF_COEFF"+String(i)] = chan[i].PCF_COEFF;
		doc["WGAIN" + String(i)] = chan[i].WGAIN;
		doc["WATTOS" + String(i)] = chan[i].WATTOS;
		doc["VARGAIN" + String(i)] = chan[i].VARGAIN;
		doc["VAROS" + String(i)] = chan[i].VAROS;
		doc["IxGAIN" + String(i)] = chan[i].IxGAIN;
		doc["IxRMSOS" + String(i)] = chan[i].IxRMSOS;
	}
	int anz = serializeJsonPretty(doc, file);
	if (anz == 0) {
		Logger.error("Failed to write to file");
	}
	Logger.debug("%d Filesize=%d", anz,  file.size());

	file.close();
}

// Show all Parameters
void ADE7816ParaClass::show()
{
	Logger.debug("lineCyc=%d", lineCyc);
	Logger.debug("APNOLOAD=%d", pAPNOLOAD);
	Logger.debug("VARNOLOAD=%d", pVARNOLOAD);
	Logger.debug("OILVL=%d", pOILVL);
	Logger.debug("OVLVL=%d", pOVLVL);
	Logger.debug("VRMS_OS=%d", pVRMSOS);
	Logger.debug("VGAIN=%d", pVGAIN);
	Logger.debug("GAIN=%d", pGain);
	for (size_t i = 0; i < 6; i++)
	{
		Logger.debug("DESCRIPTION[%d]=%s", i, chan[i].description.c_str());
		Logger.debug("PCF_COEFF[%d]=%d",i, chan[i].PCF_COEFF);
		Logger.debug("WGAIN[%d]=%d", i, chan[i].WGAIN);
		Logger.debug("WATTOS[%d]=%d", i, chan[i].WATTOS);
		Logger.debug("VARGAIN[%d]=%d", i, chan[i].VARGAIN);
		Logger.debug("VAROS[%d]=%d", i, chan[i].VAROS);
		Logger.debug("IxGAIN[%d]=%d", i, chan[i].IxGAIN);
		Logger.debug("IxRMSOS[%d]=%d", i, chan[i].IxRMSOS);
	}

}

