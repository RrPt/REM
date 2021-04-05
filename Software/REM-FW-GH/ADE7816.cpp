/*
	Name:        ADE7816.cpp
	Description: ADE7816 class für  SPI und I2C
	Project:     REM  (Rainer's Energy Mesaurement) power measurement in AC networks
	Created:	 20.06.2020
	Author:      Rainer Petzoldt  R.Petzoldt@web.de
*/

#include "ADE7816.h"
#include "Logger.h"



///
/// Initialisierung des ADE7816
///
int ADE7816::init(String _name )
{
	name = _name;
	int anz = 0;
	int erg = 0;
	Logger.debug(" Start ADE7816::init(%s)",name.c_str());

	parameter.init(name);
	data.init();

	while (anz < 3)	
	{
		int erg = writeRegister8(CONFIG2, 0x2);	// sperren der Interfaceauswahl  (Datasheet page 33)
		anz++;
		Logger.debug(" %d write CONF2 erg = %d", anz,erg);
		if (erg == 0) break;
	}
	
	if (erg != 0) Logger.error("Initialisierung fehlgeschlagen");  

	// Register initialisieren
	writeRegister32(WTHR1, WTHR1_DEFAULT);
	writeRegister32(WTHR0, WTHR0_DEFAULT);
	writeRegister32(VARTHR1, VARTHR1_DEFAULT);
	writeRegister32(VARTHR0, VARTHR0_DEFAULT);
	writeRegister32(PCF_A_COEFF, PCF_COEFF_50HZ);
	writeRegister32(PCF_B_COEFF, PCF_COEFF_50HZ);
	writeRegister32(PCF_C_COEFF, PCF_COEFF_50HZ);
	writeRegister32(PCF_D_COEFF, PCF_COEFF_50HZ);
	writeRegister32(PCF_E_COEFF, PCF_COEFF_50HZ);
	writeRegister32(PCF_F_COEFF, PCF_COEFF_50HZ);

	writeRegister32(DICOEFF, DICOEFF_DEFAULT);	// three times required see Datasheet page 20
	writeRegister32(DICOEFF, DICOEFF_DEFAULT);
	writeRegister32(DICOEFF, DICOEFF_DEFAULT);

	writeRegister16(Run, 0x1);		// Start DSP

	Logger.debug("ADE7816 konfigurieren...");
	writeParaToADE7816();

	Logger.debug(" Ende ADE7816::init()" );

	return erg;
}


// calculation of the IxGain Value for channel chan
// all channels must habe the same current !
int ADE7816::calibIxGain(int chan, int sollCurrentRaw, int istCurrentRaw)	// chan = 0..5   
{
	//if (chan == -1)
	//{	// all channels 0..5
	//	for (size_t c = 0; c < 6; c++)
	//	{
	//		calibIxGain(c, sollCurrentRaw);
	//	}
	//}
	//else
	//{
	Logger.debug(" calibIxGain(%d,%d,%d)", chan, sollCurrentRaw, istCurrentRaw);
	double val = (double)sollCurrentRaw / (double)istCurrentRaw;
	double val2 = val - 1;
	int ixGain = val2 * (1 << 23);
	Logger.debug("sollCurrentRaw=%d  istCurrentRaw=%d  %f  %f  IxGain=%d  [%X]", sollCurrentRaw, istCurrentRaw, val, val2, ixGain, ixGain);
	Logger.info("altes ixGain=%d", parameter.chan[chan].IxGAIN);
	//parameter.chan[chan].IxGAIN = ixGain;   
	setIxGain(chan, ixGain);
	Logger.info("neues ixGain=%d", parameter.chan[chan].IxGAIN);
	//}
}


// calculation of the VGain Value for channel chan
int ADE7816::calibVGain(int sollVoltageRaw, int istVoltageRaw)
{
	//if (chan == -1)
	//{	// all channels 0..5
	//	for (size_t c = 0; c < 6; c++)
	//	{
	//		calibIxGain(c, sollCurrentRaw);
	//	}
	//}
	//else
	//{
		Logger.debug(" calibVGain(%d,%d)", sollVoltageRaw, istVoltageRaw);
		double val = (double)sollVoltageRaw / (double)istVoltageRaw;
		double val2 = val - 1;
		int vGain = val2 * (1 << 23);
		Logger.debug("sollVoltageRaw=%d  istVoltageRaw=%d  %f  %f  vGain=%d  [%X]", sollVoltageRaw, istVoltageRaw, val, val2, vGain, vGain);
		Logger.info("altes vGain=%d", parameter.pVGAIN);
		setVGain(vGain);
		Logger.info("neues vGain=%d", parameter.pVGAIN);
	//}
}


// calculation of the WGain Value for channel chan
// all channels must habe the same current !
int ADE7816::calibWGain(int chan, int sollPowerRaw, int istPowerRaw)	// chan = 0..5   
{
	Logger.debug(" calibWGain(%d,%d,%d)", chan, sollPowerRaw, istPowerRaw);
	double val = (double)sollPowerRaw / (double)istPowerRaw;
	double val2 = val - 1;
	int wGain = val2 * (1 << 23);
	Logger.debug("sollPowerRaw=%d  istPowerRaw=%d  %f  %f  wGain=%d  [%X]", sollPowerRaw, istPowerRaw, val, val2, wGain, wGain);
	Logger.info("altes WGain=%d", parameter.chan[chan].WGAIN);
	//parameter.chan[chan].IxGAIN = ixGain;   
	setWGain(chan, wGain);
	Logger.info("neues WGain=%d", parameter.chan[chan].WGAIN);
}


// calculation of the VarGain Value for channel chan
// all channels must habe the same current !
int ADE7816::calibVarGain(int chan, int sollPowerRaw, int istPowerRaw)	// chan = 0..5   
{
	Logger.debug(" calibVarGain(%d,%d,%d)", chan, sollPowerRaw, istPowerRaw);
	double val = (double)sollPowerRaw / (double)istPowerRaw;
	double val2 = val - 1;
	int varGain = val2 * (1 << 23);
	Logger.debug("sollPowerRaw=%d  istPowerRaw=%d  %f  %f  varGain=%d  [%X]", sollPowerRaw, istPowerRaw, val, val2, varGain, varGain);
	Logger.info("altes VarGain=%d", parameter.chan[chan].VARGAIN);
	//parameter.chan[chan].IxGAIN = ixGain;   
	setVarGain(chan, varGain);
	Logger.info("neues VarGain=%d", parameter.chan[chan].VARGAIN);
}


// ----- Current ---------------------
#pragma region Current
int ADE7816::getIxRMS(byte chan)
{
	int ixRMS = -1;
	readRegister32(IARMS + chan, &ixRMS);
	return ixRMS;
}

int ADE7816::getIxGain(byte chan)
{
	int val;
	readRegister32(IAGAIN + chan, &val);
	return val;
}

int ADE7816::setIxGain(byte chan, int val)
{
	Logger.info("setIxGain(%d, %d)", chan, val);
	parameter.chan[chan].IxGAIN = val;
	writeRegister32(IAGAIN + chan, val);
}

int ADE7816::getIxRMSOS(byte chan)
{
	int val;
	readRegister32(IARMSOS + chan, &val);
	return val;
}

int ADE7816::setIxRMSOS(byte chan, int val)	// chan = 0..5   
{
	Logger.info("setIxRMSOS(%d, %d)", chan, val);
	parameter.chan[chan].IxRMSOS = val;
	writeRegister32(IARMSOS + chan, val);
}
#pragma endregion


// ------ Voltage --------------
#pragma region Voltage

int ADE7816::getVRMS()
{
	int iRMS = -1;
	readRegister32(VRMS, &iRMS);
	return iRMS;
}

int ADE7816::getVGain()
{
	int val;
	readRegister32(VGAIN, &val);
	return val;
}

int ADE7816::setVGain(int val)
{
	Logger.info("setVGain(%d)", val);
	parameter.pVGAIN = val;
	writeRegister32(VGAIN, val);
}

int ADE7816::getVRMSOS()
{
	int val;
	readRegister32(VRMSOS, &val);
	return val;
}

int ADE7816::setVRMSOS(int val)
{
	Logger.info("setVRMSOS(%d)", val);
	parameter.pVRMSOS = val;
	writeRegister32(VRMSOS, val);
}
#pragma endregion


// ----- Power ---------------------
#pragma region Power
int ADE7816::getWRMS(byte chan)
{
	int ixRMS = -1;
	readRegister32( AWATTHR + chan, &ixRMS);
	return ixRMS;
}

int ADE7816::getWGain(byte chan)
{
	int val;
	readRegister32(AWGAIN + 2*chan, &val);
	return val;
}

int ADE7816::setWGain(byte chan, int val)
{
	Logger.info("setWGain(%d, %d)", chan, val);
	parameter.chan[chan].WGAIN = val;
	writeRegister32(AWGAIN + 2*chan, val);
}

int ADE7816::getWATTOS(byte chan)
{
	int val;
	readRegister32(AWATTOS + 2*chan, &val);
	return val;
}

int ADE7816::setWATTOS(byte chan, int val)	// chan = 0..5   
{
	Logger.info("setWATTOS(%d, %d)", chan, val);
	parameter.chan[chan].WATTOS = val;
	writeRegister32(AWATTOS + 2*chan, val);
}

// reactive

int ADE7816::getVarRMS(byte chan)
{
	int ixRMS = -1;
	readRegister32(AVARHR + chan, &ixRMS);
	return ixRMS;
}

int ADE7816::getVarGain(byte chan)
{
	int val;
	readRegister32(AVARGAIN + 2 * chan, &val);
	return val;
}

int ADE7816::setVarGain(byte chan, int val)
{
	Logger.info("setVarGain(%d, %d)", chan, val);
	parameter.chan[chan].VARGAIN = val;
	writeRegister32(AVARGAIN + 2 * chan, val);
}

int ADE7816::getVarOS(byte chan)
{
	int val;
	readRegister32(AVAROS + 2 * chan, &val);
	return val;
}

int ADE7816::setVarOS(byte chan, int val)	// chan = 0..5   
{
	Logger.info("setVarOS(%d, %d)", chan, val);
	parameter.chan[chan].VAROS = val;
	writeRegister32(AVAROS + 2 * chan, val);
}

double ADE7816::ScaleVoltageRawToVoltWithGain()
{
	ushort bits = (parameter.pGain >> 3) & 7;
	return ScaleVoltageRawToVolt / (1 << bits);
}

double ADE7816::ScaleCurrentRawToAmpereWithGain(size_t chan)
{
	ushort bits = parameter.pGain  & 7;
	if (chan>2) bits = (parameter.pGain >> 6) & 7;
	//Logger.info("ScaleCurrentRawToAmpereWithGain  pGain=x%x  x%x  noGain=%12.9f  reg=%d  addScale=%d  withGain=%12.9f", parameter.pGain, parameter.pGain & 7, ScaleCurrentRawToAmpere, bits, 1 << bits, ScaleCurrentRawToAmpere / (1 << bits));
	return ScaleCurrentRawToAmpere / (1 << bits);

}

double ADE7816::ScalePowerRawToWattWithGain(size_t chan)
{
	ushort bits = parameter.pGain & 7;
	if (chan > 2) bits = (parameter.pGain >> 6) & 7;
	double val = ScalePowerRawToWatt / (1 << bits) /  parameter.lineCyc;
	//Logger.info("ScalePowerRawToWattWithGain  pGain=x%x  x%x  noGain=%12.9f  reg=%d  addScale=%d  withGain=%12.9f",		parameter.pGain, parameter.pGain & 7, ScalePowerRawToWatt, bits, 1 << bits, val);
	return val;

}

#pragma endregion

unsigned short ADE7816::getGainRegister()
{
	unsigned short val;
	readRegister16(Gain, &val);
	return val;
}

unsigned short ADE7816::setGainRegister(unsigned short val)
{
	Logger.info("setGain(%d)", val);
	parameter.pGain = val;
	writeRegister32(Gain, val);
}

int ADE7816::setPcfCoeff(byte chan, int val)
{
	Logger.info("setPcfCoeff(%d, %d)", chan, val);
	parameter.chan[chan].PCF_COEFF = val;
	writeRegister32(PCF_A_COEFF + chan, val);
}


// Setzt den PCF_COEFF Wert so, dass bei einer Phasenverschiebung phi
// die Leistung und Blindleistung poassen
// die Werte werden in Parameter und im ADE7816 gesetzt
// die Werte werden nicht ins Flash geschrieben
int ADE7816::kalibPcfCoeff(byte chan, double phi)
{
	Logger.info("kalibPcfCoeff(%d, %f)", chan, phi);
	double istKorrWinkel = calcPCF2Winkel(parameter.chan[chan].PCF_COEFF);
	double theta = calcPhaseErr(phi,data.chan[chan].PowerActive, data.chan[chan].PowerReactive);
	int sollPCF = calcWinkel2PCF(theta + istKorrWinkel,true);

	parameter.chan[chan].PCF_COEFF = sollPCF;
	writeRegister32(PCF_A_COEFF + chan, sollPCF);
}


//
// Bestimmt den Phasenfehler (siehe Datenblatt)
//
double ADE7816::calcPhaseErr(double winkel, double p, double b)
{
	double phi = winkel / 180 * 3.1415;
	double t = (p*sin(phi) - b * cos(phi)) / (b*sin(phi) + p * cos(phi));
	double erg = atan(t) * 180 / 3.1415;
	return erg;
}

//
// Bestimmt den PCF Wert aus dem Winkel (siehe Datenblatt)
//
int ADE7816::calcWinkel2PCF(double winkel, bool shift) 
{
	double theta = winkel / 180 * 3.1415;
	double w = 314.15 / 8000;
	double pcf_frac = (sin(theta + 3 * w) - sin(w)) / (sin(theta + 4 * w));
	double pcf = (1 << 23) * pcf_frac;
	if ((pcf < 0)&(shift)) pcf += (1 << 28);
	return (int)pcf;
}

//
// Bestimmt den Winkel aus dem PCF Wert  (siehe Datenblatt)
//
double ADE7816::calcPCF2Winkel(int pcf) 
{
	int pcf1 = pcf;
	if (pcf > 100000000) pcf1 -= (1 << 28);
	double wu = -6;
	double wo = 6;
	double w = 0;
	double pm = 0;

	while (wo - wu > 0.0001) {
		w = (wo + wu) / 2;
		pm = calcWinkel2PCF(w,false);
		if (pcf1 > pm) wu = w;
		else wo = w;
	}
	return wo;
}



//
// Hat der Chip neue Werte bereit?  (Achtung_ wird beim Aufruf zurückgesetzt, so dass erst wieder bei den nächsten neuen Werten true)
//
bool ADE7816::hasNewValues()
{
	int st0 = -1;
	int ret = readRegister32(STATUS0, &st0);
	if (ret != 0) Logger.error("readRegister32(STATUS0,..) gibt Error %d in Modul %s", ret, name.c_str());
	//Logger.debug("module %s status=%X",name.c_str(), st0);
	if (st0 & 0x20)
	{
		writeRegister32(STATUS0, 0x20);	// Flag zurücksetzen
		return true;
	}
	return false;
}

//
// die Daten werden vom Chip ausgelesen und in den Datenstrukturen gespeichert
//
bool ADE7816::handleNewData()
{
	data.noOfMeasurements++;
	Logger.info("MessungNo %d in %s", data.noOfMeasurements, name.c_str());
	data.voltageRaw = getOneValueRaw(VRMS);
	data.voltage = ((double)data.voltageRaw) * ScaleVoltageRawToVoltWithGain(); ;
	Logger.debug(" VRMS= %8.3f V  (%d)  Freq= %8.3f Hz   Period=%8.6f s  (%d)", data.voltage , data.voltageRaw, data.frequency, data.period, data.periodRaw);
	//double val = getOneValue16(Period);
	data.periodRaw = getOneValue16Raw(Period);
	data.period = (double)(data.periodRaw + 1) / 256000  ;
	data.frequency = 1 / data.period;
	//Logger.info(" Freq= %8.3f Hz   Period=%8.6f s  (%d)", data.frequency,data.period,data.periodRaw);

	for (size_t chan = 0; chan < nCHANELS; chan++)
	{
		data.chan[chan].currentRaw = getOneValueRaw(IARMS + chan); 
		data.chan[chan].current = ((double)data.chan[chan].currentRaw) * ScaleCurrentRawToAmpereWithGain(chan); 
		Logger.debug(" I(%d)= %8.6f A  (%d)",chan, data.chan[chan].current, data.chan[chan].currentRaw);

		data.chan[chan].PowerActiveRaw = getOneValueRaw(AWATTHR + chan);
		data.chan[chan].PowerActive = ((double)data.chan[chan].PowerActiveRaw) * ScalePowerRawToWattWithGain(chan) ;
		if (abs(data.chan[chan].PowerActive) < 0.25) data.chan[chan].PowerActive = 0.0;  // alle Werte kleiner 0.25 werden auf 0 gesetzt
		data.chan[chan].EnergyActive += data.chan[chan].PowerActive * (float)parameter.lineCyc / 100;
		Logger.debug(" Pa(%d)= %8.2f W  (%d)", chan, data.chan[chan].PowerActive, data.chan[chan].PowerActiveRaw);

		data.chan[chan].PowerReactiveRaw = getOneValueRaw(AVARHR + chan);
		data.chan[chan].PowerReactive = ((double)data.chan[chan].PowerReactiveRaw) * ScalePowerRawToWattWithGain(chan) ;
		data.chan[chan].EnergyReactive += data.chan[chan].PowerReactive * (float)parameter.lineCyc / 100;
		Logger.debug(" Pr(%d)= %8.2f W", chan, data.chan[chan].PowerReactive);

		// todo  es gibt nur 3 Angle register!
		data.chan[chan].timeshiftRaw = getOneValue16Raw(ANGLE0+chan);
		data.chan[chan].timeshift = ((double)data.chan[chan].timeshiftRaw) * 1 / 256000;
		data.chan[chan].phi = data.chan[chan].timeshift * 50 * 360;
		if (data.chan[chan].phi > 180) data.chan[chan].phi = -360 + data.chan[chan].phi;
		data.chan[chan].cosPhi = cos(data.chan[chan].phi /180 * 3.1415);
		Logger.debug(" dt(%d)= %8.6f s  phi= %8.6f Grad  cosPhi= %8.6f  ", chan, data.chan[chan].timeshift, data.chan[chan].phi, data.chan[chan].cosPhi);

	}
	return true;
}

//
// Setzen der Parameter im ADE7816
//
void ADE7816::writeParaToADE7816()
{
	writeRegister8(LCYCMODE, 0x3B);  // 0x3b = line cycle accumulation mode
	writeRegister16(LINECYC, parameter.lineCyc);  // 100 = 1s mitteln
	writeRegister16(Gain, parameter.pGain);  // Eingangsverstärker
	Logger.info("writeParaToADE7816: Gain == %d",  parameter.pGain);

	writeRegister32(VGAIN, parameter.pVGAIN);
	writeRegister32(VRMSOS, parameter.pVRMSOS);

	writeRegister32(APNOLOAD, parameter.pAPNOLOAD);
	writeRegister32(VARNOLOAD, parameter.pVARNOLOAD);
	writeRegister32(OILVL, parameter.pOILVL);
	writeRegister32(OVLVL, parameter.pOVLVL);

	for (size_t chan = 0; chan < 6; chan++)
	{
		writeRegister32(PCF_A_COEFF + chan, parameter.chan[chan].PCF_COEFF);
		writeRegister32(AWGAIN + 2*chan, parameter.chan[chan].WGAIN);
		writeRegister32(AWATTOS+ 2 *chan, parameter.chan[chan].WATTOS);
		writeRegister32(AVARGAIN+2*chan, parameter.chan[chan].VARGAIN);
		writeRegister32(AVAROS+2*chan, parameter.chan[chan].VAROS);
		writeRegister32(IARMSOS+chan, parameter.chan[chan].IxRMSOS);
		writeRegister32(IAGAIN + chan, parameter.chan[chan].IxGAIN);
	}
}


//
// Setzt die Parameter in den Datenstrukturen und im Chip
// bei Parametern für alle Kanäle muss chan=-1 sein
//
bool ADE7816::setParameter(String paraName, double sollValue, int chan )
{
	paraName.toUpperCase();
	if (chan == -1)
	{	// Parameter für alle Kanäle
		if (paraName.equals("LINECYC")) parameter.lineCyc = (int)sollValue;
		if (paraName.equals("GAIN"))
		{
			parameter.pGain = (unsigned short)sollValue;
			Logger.info("setParameter %s = %d", paraName.c_str(), parameter.pGain);
		}
		if (paraName.equals("APNOLOAD")) parameter.pAPNOLOAD = (int)sollValue;
		if (paraName.equals("VARNOLOAD")) parameter.pVARNOLOAD = (int)sollValue;
		if (paraName.equals("OILVL")) parameter.pOILVL = (int)sollValue;
		if (paraName.equals("OVLVL")) parameter.pOVLVL = (int)sollValue;
	}
	else
	{	// Parameter für einen Kanal
		if (paraName.equals("PCF_COEFF")) parameter.chan[chan].PCF_COEFF = (int)sollValue;
		
	}
	writeParaToADE7816();  // die Parameter nun auch in den ADE7816 schreiben
}


int ADE7816::getOneValueRaw(int reg)
{
	int dataInt;
	int erg = readRegister32(reg, &dataInt);
	return dataInt;
}

int ADE7816::getOneValue16Raw(int reg)
{
	unsigned short data;
	int erg = readRegister16(reg, &data);
	return (int) data;
}


double ADE7816::getOneValue(int reg, double scale , double offset)
{
	int dataInt;
	int erg = readRegister32(reg, &dataInt);
	double v = (double)dataInt * scale + offset;
	//Logger.info("   ->value(%04X)=%6x = %8.3f V", reg, dataInt, v);
	return v;
}

double ADE7816::getOneValue16(int reg, double scale, double offset)
{
	unsigned short data;
	int erg = readRegister16(reg, &data);
	double v = (double)data * scale + offset;
	//Logger.info("   ->value(&04X=%6x = %6.3f", reg, data, v);
	return v;
}


int ADE7816::writeRegister8(const unsigned int reg, byte val )
{
	return _writeRegisterBytes(reg,&val,1);
}

int ADE7816::readRegister8(const unsigned int reg,  byte *val)
{
	int erg = _readRegisterBytes(reg, val, 1);
	return erg;
}


int ADE7816::writeRegister16(const unsigned int reg, unsigned short int val)
{
	byte dataBytes[2];
	dataBytes[0] = val>>8;
	dataBytes[1] = val&0xFF;

	return _writeRegisterBytes(reg, dataBytes, 2);
}

int ADE7816::readRegister16(const unsigned int reg, unsigned short int * val)
{
	byte dataBytes[2];
	int erg = _readRegisterBytes(reg, dataBytes, 2);
	//Logger.printf((" [%x] [%x] ", dataBytes[0], dataBytes[1]);
	*val = (dataBytes[0] << 8) + dataBytes[1];
	return erg;
}

int ADE7816::writeRegister32(const unsigned int reg, unsigned int  val)
{
	byte dataBytes[4];
	dataBytes[0] = (val >> 24) & 0xFF;
	dataBytes[1] = (val>>16) & 0xFF;
	dataBytes[2] = (val >> 8) & 0xFF; 
	dataBytes[3] = val & 0xFF;
	return _writeRegisterBytes(reg, dataBytes, 4);
}

int ADE7816::readRegister32(const unsigned int reg, unsigned int * val)
{
	byte dataBytes[4];
	int erg = _readRegisterBytes(reg, dataBytes, 4);
	*val = (dataBytes[0] << 24) + (dataBytes[1] << 16) + (dataBytes[2] << 8)+ (dataBytes[3] );
	return erg;
}

int ADE7816::writeRegister32(const unsigned int reg, int  val)
{
	byte dataBytes[4];
	dataBytes[0] = (val >> 24) & 0xFF;
	dataBytes[1] = (val >> 16) & 0xFF;
	dataBytes[2] = (val >> 8) & 0xFF;
	dataBytes[3] = val & 0xFF;
	return _writeRegisterBytes(reg, dataBytes, 4);
}

int ADE7816::readRegister32(const unsigned int reg, int * val)
{
	byte dataBytes[4];
	int erg = _readRegisterBytes(reg, dataBytes, 4);
	*val = (dataBytes[0] << 24) + (dataBytes[1] << 16) + (dataBytes[2] << 8) + (dataBytes[3]);
	return erg;
}
