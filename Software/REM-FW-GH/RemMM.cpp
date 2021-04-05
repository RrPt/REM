/*
	Name:        RemMM.cpp
	Description: Handler für REM-MM modul
	Project:     REM  (Rainer's Energy Measurement) power measurement in AC networks
	Created:	 03.07.2020
	Author:      Rainer Petzoldt  R.Petzoldt@web.de
*/

#include "RemMM.h"
#include "RemPara.h"
#include <Wire.h>
#include "TCA9548a.h"
#include "Logger.h"
#include "Zeit.h"
#include "SPIFFS.h"
#include "ArduinoJson.h"    // https://arduinojson.org/

#define ade7816Addr 0x38
#define MCPADR 0x20
#define MCP_IODIR 0
#define MCP_GPIO 9
#define MCP_GPPU 6
#define MCP_LED 0
#define MCP_TASTER 1
#define MCP_RESET 0x80

int RemMMClass::anzModules = 0;
//int RemMMClass::anzZyklen = 5;
int RemMMClass::allRemMmAdrList[MAXREMMMMODULES];
RemMMClass *RemMMClass::remMM[MAXREMMMMODULES];
long RemMMClass::startTime = 1234;
int RemMMClass::selectedAdr = -1;

RemMMClass::RemMMClass(int adr)
{
	_adr = adr;
	Logger.debug("RemMMClass(%X) ctor",adr);
	sprintf(name, "REMMM%03X", _adr);  // hier wird der Name generiert
	init();
}

void RemMMClass::init()
{
	Logger.debug("RemMMClass::init()  name=%s",name);
	int lastSelect = select();
	setMcpRegister(MCP_GPIO, 0x80);  // LED aus, kein Reset
	setMcpRegister(MCP_GPPU, 0x02);  // pullup resistor bei Taster
	setMcpRegister(MCP_IODIR, 0x7E);  // IO Dir setzen
	ade7816 = ADE7816_I2C();
	ade7816.init(false,name);
	deselect(lastSelect);
}

bool RemMMClass::handleAllNewData(void(*func_ptr)(RemMMClass * data_ptr))
{
	bool hasNewData = false;
	for (size_t module = 0; module < anzModules; module++)
	{
		bool newData = remMM[module]->handleNewData(func_ptr);
		hasNewData |= newData;
		if (newData) Logger.debug("%s has new Data", remMM[module]->name);
	}
	return hasNewData;
}

bool RemMMClass::handleNewData(void(*func_ptr)(RemMMClass * data_ptr))
{
	bool hasNewData = false;
	int lastSelect = select();
	hasNewData |= ade7816.hasNewValues(); 
	if (hasNewData)							// gibts neue Daten?
	{
		setLed(false);
		ade7816.handleNewData();			// Daten aus dem Chip auslesen
		func_ptr(this);						// und an alle melden die es interessiert
		setLed(true);
	}
	handleIO();								// Taste abfragen

	deselect(lastSelect);
	
	return hasNewData;
}

bool RemMMClass::handleIO()
{
	// todo: Taster abfragen, wird nur jede 2. mal erkannt, warum?
	byte io = getMcpRegister(MCP_GPIO);
	//Logger.debug("%2X", io);
	bool tasteNew = !( io & 0x02);
	if (taste != tasteNew)
	{
		taste = tasteNew;
		if (taste) Logger.info("Taste gedrueckt an Modul MM %X", _adr);
		else Logger.info("Taste losgelassen an Modul MM %X", _adr);
	}

}

void RemMMClass::setMcpRegister(byte adr, byte val)
{
	//select();  // todo  generell anders behandeln
	Wire.beginTransmission(MCPADR);
	Wire.write(adr);
	Wire.write(val);
	Wire.endTransmission();
	//deselect();  // alten Zustand wiederherstellen
}

byte RemMMClass::getMcpRegister(byte adr)
{
	int lastSelect = select();
	Wire.beginTransmission(MCPADR);
	Wire.write(adr);
	Wire.endTransmission();
	Wire.requestFrom(MCPADR, 1);
	byte ioreg = Wire.read();
	deselect(lastSelect);
	//Logger.debug("   %X %d", ioreg, ioreg);
	//Serial.println(ioreg, 2);
	return ioreg;
}

bool RemMMClass::setLed(bool on)
{
	// nur LED Port
	int lastAdr = select();  
	if (on)	setMcpRegister(MCP_GPIO, 0x1 | MCP_RESET);   //  80 = kein Reset
	else 	setMcpRegister(MCP_GPIO, 0x0 | MCP_RESET);   //  80 = kein Reset
	deselect(lastAdr);
}

bool RemMMClass::resetAde7816()
{
	Logger.warning("resetADE7816");
	// erst resetpin für 10ms auf low ziehen
	setMcpRegister(MCP_GPIO, 0x00);	// reset und LED an
	delay(10);
	setMcpRegister(MCP_GPIO, 0x81);  // reset ende und LED aus
	// dann neu initialisieren
	init();
}


int RemMMClass::select()
{ 
	if (_adr == selectedAdr) return _adr;    // Adr war schon eingestellt
	int lastAdr = selectedAdr;
	//Logger.debug("RemMMClass::select _adr=%04X", _adr);
	TCA9548a::tcaSelect(selectedAdr >> 4, -1);	// alte Adr abwählen
	TCA9548a::tcaSelect(_adr >> 4, _adr & 0x0F); // neue Adr auswählen
	selectedAdr = _adr;
	return lastAdr;	// alte adr zurückgeben
}

void RemMMClass::deselect(int newAdr=-1)
{
	if (newAdr == selectedAdr) return ;    // Adr war schon eingestellt
	//Logger.debug("RemMMClass::deselect(%X)",newAdr);

	TCA9548a::tcaSelect(selectedAdr >> 4, -1);	// alte Adr abwählen 
	if (newAdr !=-1) TCA9548a::tcaSelect(newAdr >> 4, newAdr & 0x0F);  // neue Adr einstellen
	selectedAdr = newAdr;
}


//  -------------Current---------------------------------

// Setzt die IxGain Werte auf den angegebenen Wert
// die Werte werden in Parameter und im ADE7816 gesetzt
// die Werte werden nicht ins Flash geschrieben
void RemMMClass::setCurrentGain(int sollGain)  
{
	Logger.debug("RemMMClass::setCurrentGain(%d)", sollGain);
	for (size_t i = 0; i < 6; i++)
	{
		int lastAdr = select();
		ade7816.setIxGain(i, sollGain);
		deselect(lastAdr);
	}
}


// Setzt die IxRMSOS Werte auf den angegebenen Wert
// die Werte werden in Parameter und im ADE7816 gesetzt
// die Werte werden nicht ins Flash geschrieben
void RemMMClass::setCurrentOffset(int sollOffset)
{
	Logger.debug("RemMMClass::setCurrentOffset(%d)", sollOffset);
	for (size_t i = 0; i < 6; i++)
	{
		int lastAdr = select();
		ade7816.setIxRMSOS(i, sollOffset);
		deselect(lastAdr);
	}
}




// Bestimmt die IxGain Werte
// setzt IxGain so, dass der Strom sollCurrent gemessen wird
// die Werte werden in Parameter und im ADE7816 gesetzt
// die Werte werden nicht ins Flash geschrieben
void RemMMClass::kalibCurrentGain(double sollCurrent)  // in Ampere
{
	Logger.debug("RemMMClass::kalibCurrentGain(%f)", sollCurrent);
	// bestimmen des RawCurent
	for (size_t i = 0; i < 6; i++)
	{
		double sollCurrentRawD = sollCurrent / ade7816.ScaleCurrentRawToAmpereWithGain(i);
		int sollCurrentRaw = (int)sollCurrentRawD;
		Logger.debug("sollCurrentRaw = %d  (%X)", sollCurrentRaw, sollCurrentRaw);
		// hier wird der aktuell eingestellete Gain herausgerechnet  (nicht der Vorverstärker, der ist schon 3 Zeilen weiter oben berücksichtigt)
		int currentRaw = ade7816.data.chan[i].currentRaw; // nur debug
		double korrFaktor = (double)ade7816.parameter.chan[i].IxGAIN / (1 << 23);
		if ((korrFaktor > 1.0) | (korrFaktor < -1.0))
		{
			Logger.warning("kalibCurrentGain: korrFaktor=%f ist nicht plausibel, wird auf 0 gesetzt", korrFaktor);
			korrFaktor = 0.0;
		}
		korrFaktor += 1.0;
		int currentRawCorrected = (int)((double)ade7816.data.chan[i].currentRaw / korrFaktor);
		Logger.debug("currentRaw=%d  korrFaktor=%f  -> Korrected=%d", currentRaw, korrFaktor, currentRawCorrected);

		int lastAdr = select();
		ade7816.calibIxGain(i, sollCurrentRaw, currentRawCorrected);
		deselect(lastAdr);
	}
}


// Bestimmt die IxRMSOS Werte
// setzt  so, dass gerade noch der Strom 0 A gemessen wird
// die Werte werden in Parameter und im ADE7816 gesetzt
// die Werte werden nicht ins Flash geschrieben
void RemMMClass::kalibCurrentOffset()
{
	Logger.info("RemMMClass::kalibCurrentOffset()");
	for (size_t i = 0; i < 6; i++)
	{
		int currentRaw = ade7816.data.chan[i].currentRaw;
		int currentOffset = ade7816.parameter.chan[i].IxRMSOS -currentRaw * currentRaw / 128;
		Logger.debug("currentRaw=%d  currentOffset=%d", currentRaw, currentOffset);
		int lastAdr = select();
		ade7816.setIxRMSOS(i, currentOffset);
		deselect(lastAdr);
	}
}



//  -------------Voltage---------------------------------

// Setzt die VGain Werte auf den angegebenen Wert
// die Werte werden in Parameter und im ADE7816 gesetzt
// die Werte werden nicht ins Flash geschrieben
void RemMMClass::setVoltageGain(int sollGain)
{
	Logger.debug("RemMMClass::setVoltageGain(%d)", sollGain);
	int lastAdr = select();
	ade7816.setVGain(sollGain);
	deselect(lastAdr);
}


// Setzt die VRMSOS Werte auf den angegebenen Wert
// die Werte werden in Parameter und im ADE7816 gesetzt
// die Werte werden nicht ins Flash geschrieben
void RemMMClass::setVoltageOffset(int sollOffset)
{
	Logger.debug("RemMMClass::setVoltageOffset(%d)", sollOffset);
		int lastAdr = select();
		ade7816.setVRMSOS(sollOffset);
		deselect(lastAdr);
}




// Bestimmt die VGain Werte
// setzt VGain so, dass die Spannung sollVoltage gemessen wird
// die Werte werden in Parameter und im ADE7816 gesetzt
// die Werte werden nicht ins Flash geschrieben
void RemMMClass::kalibVoltageGain(double sollVoltage)  // in Volt
{
	Logger.debug("RemMMClass::kalibCurrentGain(%f)", sollVoltage);
	// bestimmen des RawVoltage
	double sollVoltageD = sollVoltage / ade7816.ScaleVoltageRawToVoltWithGain();
	int sollVoltageRaw = (int)sollVoltageD;
	Logger.debug("sollVoltageRaw = %d  (%X)", sollVoltageRaw, sollVoltageRaw);
	{
		// hier wird der aktuell eingestellete Gain herausgerechnet
		int voltageRaw = ade7816.data.voltageRaw;
		double korrFaktor = (double)ade7816.parameter.pVGAIN / (1 << 23);
		if ((korrFaktor > 1.0) | (korrFaktor < -1.0))
		{
			Logger.warning("kalibVoltageGain: korrFaktor=%f ist nicht plausibel, wird auf 0 gesetzt", korrFaktor);
			korrFaktor = 0.0;
		}
		korrFaktor += 1.0;
		int voltageRawCorrected = (int)((double)voltageRaw / korrFaktor);
		Logger.debug("voltageRaw=%d  korrFaktor=%f  -> Korrected=%d", voltageRaw, korrFaktor, voltageRawCorrected);

		int lastAdr = select();
		ade7816.calibVGain(sollVoltageRaw, voltageRawCorrected);
		deselect(lastAdr);
	}
}


// Bestimmt die VRMSOS Werte
// setzt  so, dass gerade noch die Spannung 0 V gemessen wird
// die Werte werden in Parameter und im ADE7816 gesetzt
// die Werte werden nicht ins Flash geschrieben
void RemMMClass::kalibVoltageOffset()
{
	Logger.info("RemMMClass::kalibVoltageOffset()");
	{
		int voltageRaw = ade7816.data.voltageRaw;
		int voltageOffset = ade7816.parameter.pVRMSOS - voltageRaw * voltageRaw / 128;
		Logger.debug("voltageRaw=%d  voltageOffset=%d", voltageRaw, voltageOffset);
		int lastAdr = select();
		ade7816.setVRMSOS(voltageOffset);
		deselect(lastAdr);
	}
}



//  -------------Power---------------------------------

// Setzt die WGain Werte auf den angegebenen Wert
// die Werte werden in Parameter und im ADE7816 gesetzt
// die Werte werden nicht ins Flash geschrieben
void RemMMClass::setPowerGain(int sollGain, bool isReactive)
{
	Logger.debug("RemMMClass::setPowerGain(%d,%d)", sollGain,isReactive);
	for (size_t i = 0; i < 6; i++)
	{
		int lastAdr = select();
		if (isReactive)	ade7816.setVarGain(i, sollGain);
		else 	ade7816.setWGain(i, sollGain);
		deselect(lastAdr);
	}
}


// Setzt die WRMSOS Werte auf den angegebenen Wert
// die Werte werden in Parameter und im ADE7816 gesetzt
// die Werte werden nicht ins Flash geschrieben
void RemMMClass::setPowerOffset(int sollOffset, bool isReactive)
{
	Logger.debug("RemMMClass::setPowerOffset(%d,%d)", sollOffset,isReactive);
	for (size_t i = 0; i < 6; i++)
	{
		int lastAdr = select();
		if (isReactive)	ade7816.setVarOS(i,sollOffset);
		else 	ade7816.setWATTOS(i, sollOffset);
		deselect(lastAdr);
	}
}




// Bestimmt die WGain Werte
// setzt WGain so, dass die Leistung sollPower gemessen wird
// die Werte werden in Parameter und im ADE7816 gesetzt
// die Werte werden nicht ins Flash geschrieben
void RemMMClass::kalibPowerGain(double sollPower,bool isReactive)  // in Watt
{
	Logger.debug("RemMMClass::kalibCurrentGain(%f)", sollPower);
	// bestimmen der RawPower
	for (size_t i = 0; i < 6; i++)
	{
		double sollPowerRawD = sollPower / ade7816.ScalePowerRawToWattWithGain(i);
		int sollPowerRaw = (int)sollPowerRawD;
		Logger.debug("sollPowerRaw = %d  (%X)", sollPowerRaw, sollPowerRaw);
		// hier wird der aktuell eingestellete Gain herausgerechnet (nicht der Vorverstärker, der ist schon 3 Zeilen weiter oben berücksichtigt)
		int powerRaw;
		double korrFaktor = 0;
		if (isReactive)
		{
			powerRaw = ade7816.data.chan[i].PowerReactiveRaw;
			korrFaktor = (double)ade7816.parameter.chan[i].VARGAIN / (1 << 23);
		}
		else
		{
			powerRaw = ade7816.data.chan[i].PowerActiveRaw;
			korrFaktor = (double)ade7816.parameter.chan[i].WGAIN / (1 << 23);
		}
		if ((korrFaktor > 1.0) | (korrFaktor < -1.0))
		{
			Logger.warning("kalibPowerGain: korrFaktor=%f ist nicht plausibel, wird auf 0 gesetzt", korrFaktor);
			korrFaktor = 0.0;
		}
		korrFaktor += 1.0;
		int powerRawCorrected = (int)((double)powerRaw / korrFaktor);
		Logger.debug("powerRaw=%d  korrFaktor=%f  -> Korrected=%d", powerRaw, korrFaktor, powerRawCorrected);

		int lastAdr = select();
		if (isReactive)		ade7816.calibVarGain(i, sollPowerRaw, powerRawCorrected);
		else 		ade7816.calibWGain(i, sollPowerRaw, powerRawCorrected);
		deselect(lastAdr);
	}
}


// Bestimmt die WRMSOS Werte
// setzt  so, dass gerade noch die Leistung 0 W gemessen wird
// die Werte werden in Parameter und im ADE7816 gesetzt
// die Werte werden nicht ins Flash geschrieben
void RemMMClass::kalibPowerOffset(bool isReactive)
{
	Logger.info("RemMMClass::kalibPowerOffset()");
	for (size_t i = 0; i < 6; i++)
	{
		int powerRaw = ade7816.data.chan[i].PowerActiveRaw;
		int powerOffset = ade7816.parameter.chan[i].WATTOS - (int)((double)powerRaw / ade7816.parameter.lineCyc * 100 * 0x2000000 / 8000);
		Logger.info("linCyc==%d  korr=%d", ade7816.parameter.lineCyc, (int)((double)powerRaw / ade7816.parameter.lineCyc * 100 * 0x2000000 / 8000));
		Logger.info("powerRaw=%d  powerOffset=%d", powerRaw, powerOffset);
		int lastAdr = select();
		if (isReactive)	ade7816.setVarOS(i, powerOffset);
		else ade7816.setWATTOS(i, powerOffset);
		deselect(lastAdr);
	}
}

//    Phase

// Setzt die PCF_COEFF Werte auf den angegebenen Wert
// die Werte werden in Parameter und im ADE7816 gesetzt
// die Werte werden nicht ins Flash geschrieben
void RemMMClass::setAllPcfCoeff(int sollValue)
{
	Logger.debug("RemMMClass::setAllPcfCoeff(%d)", sollValue);
	for (size_t i = 0; i < 6; i++)
	{
		int lastAdr = select();
		ade7816.setPcfCoeff(i,sollValue);
		deselect(lastAdr);
	}
}

// Setzt die PCF_COEFF Werte so, dass bei einer Phasenverschiebung phi
// die Leistung und Blindleistung poassen
// die Werte werden in Parameter und im ADE7816 gesetzt
// die Werte werden nicht ins Flash geschrieben
void RemMMClass::kalibAllPcfCoeff(double phi)
{
	Logger.info("RemMMClass::kalibAllPcfCoeff(%f)", phi);
	for (size_t i = 0; i < 6; i++)
	{
		int lastAdr = select();
		ade7816.kalibPcfCoeff(i, phi);
		deselect(lastAdr);
	}
}



void RemMMClass::writePara()  // alle Parameter in Flash schreiben
{
	Logger.debug("RemMMClass::writePara()  %s", name);
	int lastSelect = select();
	ade7816.parameter.write();
	deselect(lastSelect);
}


void RemMMClass::saveAllEnergyCounter()
{
	Logger.info("saveEnergyCounter()");

	String fn = "/EnergyCounter.json";
	File file = SPIFFS.open(fn, FILE_WRITE);
	if (!file) {
		Logger.error("There was an error opening the file %s for writing", fn.c_str());
	}
	Logger.debug("Filesize=%d", file.size());
	DynamicJsonDocument doc(RemMMClass::anzModules * 1000);
	doc["Filename"] = fn;
	char buf[40];
	doc["time"] = Zeit.getFormattedDateTime(buf, 40);
	JsonObject jmods = doc.createNestedObject("modules");

	for (size_t mod = 0; mod < RemMMClass::anzModules; mod++)
	{
		JsonObject jmod = jmods.createNestedObject(RemMMClass::remMM[mod]->name);

		Logger.info("  %02d %s", mod, RemMMClass::remMM[mod]->name);
		for (size_t chan = 0; chan < 6; chan++)
		{
			JsonObject jchan = jmod.createNestedObject(itoa(chan,buf,10));
			Logger.info("    %d  E=%f", chan, RemMMClass::remMM[mod]->ade7816.data.chan[chan].EnergyActive);
			// todo implementieren
			jchan["EnergyActive"] = RemMMClass::remMM[mod]->ade7816.data.chan[chan].EnergyActive;
			jchan["EnergyResetDate"] = RemMMClass::remMM[mod]->ade7816.data.chan[chan].EnergyStartTime;
		}
	}
	int anz = serializeJsonPretty(doc, file);
	if (anz == 0) {
		Logger.error("Failed to write to file");
	}
	Logger.info("%d Filesize=%d", anz, file.size());

	file.close();

}

bool RemMMClass::restoreAllEnergyCounter()
{
	Logger.info("restoreEnergyCounter()");

	String fn = "/EnergyCounter.json";
	File file = SPIFFS.open(fn, FILE_READ);
	if (!file) {
		Logger.error("There was an error opening the file %s for reading", fn.c_str());
		return false;
	}
	if (file.size() == 0) {
		Logger.error("file %s didn't exist or is empty, restore EneryCounter impossible", fn.c_str());
		return false;
	}
	Logger.debug("Filesize=%d", file.size());
	DynamicJsonDocument doc(RemMMClass::anzModules * 1000);
	DeserializationError error = deserializeJson(doc, file);
	Logger.debug("JsobDoc Memory: %d  von %d used", doc.memoryUsage(), doc.capacity());
	file.close();

	// Test if parsing succeeds.
	if (error) {
		Logger.error("deserializeJson() failed: %s", error.c_str());
		return false;
	}

	doc["Filename"] = fn;
	char buf[40];
	String saveTimeStr = doc["time"];
	Logger.info("Sicherungszeit=%s", saveTimeStr.c_str());
	// Datum prüfen aufräumen
	long saveTime = Zeit.scanDateTime(saveTimeStr.c_str());
	long now = Zeit.getActualTime();
	long diff = now - saveTime;
	Logger.info(" Pruefe: Speicherzeit=%d  jetzt=%d  Alter=%ds", saveTime, now, diff);

	if (diff > 900)
	{
		Logger.warning("EneryConter Sicherung ist zu alt, wird nicht eingelesen");
		return false;
	}

	JsonObject jmods = doc["modules"];
	for (JsonPair kv : jmods)
	{
		int modIdx = RemMMClass::getModuleIdx(String(kv.key().c_str()));
		if (modIdx < 0)
		{
			Logger.warning("Index für %s nicht gefunden", kv.key().c_str());
			continue;
		}
		Logger.warning(" modName=%s  modIdx=%d", kv.key().c_str(),modIdx);

		RemMMClass* mod = RemMMClass::remMM[modIdx];

		Logger.info("  %02d %s", modIdx, mod->name);
		for (JsonPair kvc : kv.value().as<JsonObject>())
		{
			int chan = atoi(kvc.key().c_str());
			double value = kvc.value()["EnergyActive"].as<double>();
			RemMMClass::remMM[modIdx]->ade7816.data.chan[chan].EnergyActive = value;   

			long resetDate = kvc.value()["EnergyResetDate"].as<long>();
			RemMMClass::remMM[modIdx]->ade7816.data.chan[chan].EnergyStartTime = resetDate;

			Logger.info("  read mod=%s  chan=%d  val=%f -> %f  resetTime=%d", mod->name, chan, RemMMClass::remMM[modIdx]->ade7816.data.chan[chan].EnergyActive, value, resetDate);

		}
	}
	return true;
}


bool RemMMClass::setParameter(String paraName, double sollValue, int chan)
{
	Logger.debug("RemMMClass::setParameter(%s,%f,%d)", paraName, sollValue,  chan);
	int lastSelect = select();
	ade7816.setParameter( paraName,  sollValue,  chan);
	deselect(lastSelect);
}

bool RemMMClass::resetEnergy(int chan)
{
	Logger.debug("RemMMClass::resetEnergy(%d)",  chan);
	ade7816.data.chan[chan].resetEnergy();
}

int RemMMClass::readRegister32(int reg)
{
	int value = 0;
	Logger.debug("RemMMClass::readRegister32(%d)", reg);
	int lastSelect = select();
	ade7816.readRegister32(reg,&value);
	deselect(lastSelect);
	return value;
}


#pragma region static functions
//
// Scannt alle module und legt die Instancen an
//
int RemMMClass::initModules()
{
	int count = 1;
	int anz = RemMMClass::scanModules();
	while (anz < remPara.minRemmModules)
	{
		Logger.warning("Scanversuch %d: nur %d von %d Modulen gefunden", count++, anz, remPara.minRemmModules);
		delay(1000);
		anz = RemMMClass::scanModules();
		if (count > 60) break;   // dann aufgeben und die vorhandenen nehmen
	}
	if (count>60) Logger.warning("Im %d. Scan nur %d von %d Modulen gefunden, gebe auf!", count, anz, remPara.minRemmModules);
	else Logger.info("Im %d. Scan %d von mind. %d Modulen gefunden", count, anz, remPara.minRemmModules);
	RemMMClass::getModulesList();
	for (size_t i = 0; i < anz; i++)
	{
		char name[10];
		int adr = RemMMClass::getModuleAdr(i);
		delete remMM[i];  // evtl. vorher gespeicherte Objekte freigeben
		remMM[i] = new RemMMClass(adr);
		remMM[i]->idx = i;
	}
	startTime = Zeit.getActualTime();
}


int RemMMClass::scanModules()
{
	byte error, tcaAddr;
	int nTca, nAde7816;
	anzModules = 0;

	// Scan für TCA9548a
	Wire.begin();

	nTca = 0;
	nAde7816 = 0;
	// Search all TCA9548
	// zuerst TCA suchen, dann alle Ports abschalten
	for (tcaAddr = 0x70; tcaAddr < 0x78; tcaAddr++)
	{
		// The i2c_scanner uses the return value of the Write.endTransmisstion to see if
		// a device did acknowledge to the address.
		Wire.beginTransmission(tcaAddr);
		error = Wire.endTransmission();

		if (error == 0)
		{
			TCA9548a::tcaSelect(tcaAddr, -1);
			Logger.info("REM-M module found at address 0x%02X switched all ports off", tcaAddr);
		}
	}
	// nun nochmal nach Modulen Scannen
	for (tcaAddr = 0x70; tcaAddr < 0x78; tcaAddr++)
	{
		// The i2c_scanner uses the return value of the Write.endTransmisstion to see if
		// a device did acknowledge to the address.
		Wire.beginTransmission(tcaAddr);
		error = Wire.endTransmission();

		if (error == 0)
		{
			nTca++;
			Logger.info("REM-M module found at address 0x%02X", tcaAddr);
			// nun alle Ports scannen
			for (size_t port = 0; port < 8; port++)
			{
				//Logger.printf("   scan port 0x%02X\n", port);
				TCA9548a::tcaSelect(tcaAddr, port);
				Wire.beginTransmission(ade7816Addr);
				error = Wire.endTransmission();
				if (error == 0)
				{
					Logger.info("     REM-MM pcb found on address 0x%02X port 0x%02X", tcaAddr, port);
					if (anzModules < MAXREMMMMODULES)
					{
						allRemMmAdrList[anzModules] = (tcaAddr << 4) + port;
					}
					anzModules++;
				}
				else if (error == 4) Logger.warning("Unknown error at address 0x%02X", tcaAddr);
			}
			TCA9548a::tcaSelect(tcaAddr, -1);   // ports abschalten

		}
		else if (error == 4)
		{
			Logger.warning("Unknown error at address 0x%02X", tcaAddr);
		}
	}
	if (nTca == 0)
	{	// keine TCA gefunden, evtl. ein ADE7816 am Hauptbus?
		Wire.beginTransmission(ade7816Addr);
		error = Wire.endTransmission();
		if (error == 0)
		{
			Logger.info("     REM-MM pcb found on Mainbus address 0x%02X port 0x%02X", 0, 0);
			if (anzModules < MAXREMMMMODULES)
			{
				allRemMmAdrList[anzModules] = 0;
			}
			anzModules++;
		}

	}

	if (nTca == 0)
		Logger.warning("No REM-M module found");
	else
		Logger.info("Found %d REM-M modules", nTca);
	if (anzModules == 0)
		Logger.warning("No REM-MM pcbs found");
	else
		Logger.info("Found %d REM-MM pcbs", anzModules);

	return anzModules;
}



String RemMMClass::getModulesList()
{
	String erg = "";
	for (size_t i = 0; i < anzModules; i++)
	{
		erg += "0x" + String(allRemMmAdrList[i], 16);
		if (i<anzModules-1) erg += ",";
		Logger.debug("  [0x%03X]", allRemMmAdrList[i]);
	}
	Logger.debug("getModulesList: %s", erg.c_str());

	return erg;
}

int RemMMClass::getModuleAdr(int idx)
{
	if ((idx < 0) | (idx > MAXREMMMMODULES)) return -1;
	return allRemMmAdrList[idx];
}

int RemMMClass::getModuleIdx(String name)
{
	Logger.debug("getModuleIdx(%s)", name.c_str());
	for (size_t i = 0; i < anzModules; i++)
	{
		Logger.debug("  idx=%d vergleiche %s <> %s",i, remMM[i]->name, name.c_str());
		if (!strcasecmp(remMM[i]->name, name.c_str()))
		{
			Logger.info("   return idx=%d", i);
			return i;
		}
	}
	Logger.info("   return idx=%d", -1);
	return -1;
}

RemMMClass RemMMClass::getModule(String name)
{
	for (size_t i = 0; i < anzModules; i++)
	{
		if (remMM[i]->name==name.c_str()) return *remMM[i];
	}
	return NULL;
}


//
// Spannung der REMM Module ein/ausschalten
//
void RemMMClass::powerSwitch(bool z)
{
	if (z)
	{
		digitalWrite(PWR_SWITCH, 1);
		Logger.debug("switch Power On\n");
	}
	else
	{
		digitalWrite(PWR_SWITCH, 0);
		Logger.debug("switch Power Off\n");
	}
}


#pragma endregion
