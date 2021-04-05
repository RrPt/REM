/*
	Name:        RemMM.h
	Description: Handler für REM-MM modul
	Project:     REM  (Rainer's Energy Mesaurement) power measurement in AC networks
	Created:	 03.07.2020
	Author:      Rainer Petzoldt  R.Petzoldt@web.de
*/


#pragma once

#include "ADE7816.h"


#define MAXREMMMMODULES 10
#define PWR_SWITCH 32  // IO port der Power der REMM Module schaltet

class RemMMClass
{
 protected:
 public:
	static int anzModules ;							// Anzahl der gefundenen Module
	static int  allRemMmAdrList[MAXREMMMMODULES];	// Liste der Moduladressen
	static RemMMClass *remMM[MAXREMMMMODULES];		// Liste der Modulinstancen
	static long startTime ;                         // Startzeitpunkt

private:
	static int selectedAdr;							

 public:
	static int initModules();		// legt instanzen für alle gefundenen Module an
	static bool handleAllNewData(void(*func_ptr)(RemMMClass* data_ptr));
	static void saveAllEnergyCounter();  // Energiezähler in Flash schreiben
	static bool restoreAllEnergyCounter();  // Energiezähler aus Flash wiederherstellen
	static void powerSwitch(bool z);
	static int getModuleIdx(String name);

 private:
	static int scanModules();
	static String getModulesList();
	static int getModuleAdr(int idx);
	static RemMMClass getModule(String name);

// Instanzfunktionen

public:
	char name[10];
	int _adr;
	ushort idx;
	ADE7816_I2C ade7816;
	bool taste;

	bool handleNewData(void(*func_ptr)(RemMMClass * data_ptr));
	bool handleIO();

	RemMMClass(int adr);
	void init();
	void kalibCurrentGain(double sollCurrent);  // in Ampere
	void kalibCurrentOffset();  
	void setCurrentGain(int sollGain);
	void setCurrentOffset(int sollOffset);

	void kalibVoltageGain(double sollCurrent);  // in Volt
	void kalibVoltageOffset();
	void setVoltageGain(int sollGain);
	void setVoltageOffset(int sollOffset);

	void kalibPowerGain(double sollCurrent,  bool isReactive = false);  // in Watt
	void kalibPowerOffset( bool isReactive = false);
	void setPowerGain(int sollGain, bool isReactive = false);
	void setPowerOffset(int sollOffset, bool isReactive = false);


	bool setParameter(String paraName, double sollValue, int chan = -1);
	void setAllPcfCoeff(int sollValue);
	void kalibAllPcfCoeff(double phi);
	bool resetEnergy(int chan);

	void writePara();  // alle Parameter in Flash schreiben

	bool setLed(bool on);
	bool resetAde7816();
	int readRegister32(int reg);

private:
	int select();
	void deselect(int lastAdr);
	byte getMcpRegister(byte adr);
	void setMcpRegister(byte adr, byte val);


};




