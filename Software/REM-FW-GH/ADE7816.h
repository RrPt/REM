/*
	Name:        ADE7816.h
	Description: ADE7816 class f�r  SPI und I2C
	Project:     REM  (Rainer's Energy Mesaurement) power measurement in AC networks
	Created:	 20.06.2020
	Author:      Rainer Petzoldt  R.Petzoldt@web.de
*/

#ifndef __ADE7816_H__
#define __ADE7816_H__

#include <Arduino.h>
#include "ADE7816Para.h"
#include "ADE7816Data.h"


#define ADE7816_ADDR (0x38)
#define nCHANELS 6

#pragma region Register
// Calibration and Power Quality Registers
#define VGAIN		(0x4380)   // Voltage gain adjustment.
#define IAGAIN		(0x4381)   // Current Channel A current gain adjustment.
#define IBGAIN		(0x4382)   // Current Channel B current gain adjustment.
#define ICGAIN		(0x4383)   // Current Channel C current gain adjustment.
#define IDGAIN		(0x4384)   // Current Channel D current gain adjustment.
#define IEGAIN		(0x4385)   // Current Channel E current gain adjustment.
#define IFGAIN		(0x4386)   // Current Channel F current gain adjustment.
#define DICOEFF		(0x4388)   // Register used in the digital integrator algorithm. When the integrator is enabled, this register should be set to (0xFFF8000).
#define HPFDIS 		(0x4389)   // Disables the high-pass filter for all channels.
#define VRMSOS 		(0x438A)   // Voltage rms offset.
#define IARMSOS 	(0x438B)   // Current Channel A current rms offset.
#define IBRMSOS 	(0x438C)   // Current Channel B current rms offset.
#define ICRMSOS 	(0x438D)   // Current Channel C current rms offset.
#define IDRMSOS 	(0x438E)   // Current Channel D current rms offset.
#define IERMSOS 	(0x438F)   // Current Channel E current rms offset.
#define IFRMSOS 	(0x4390)   // Current Channel F current rms offset.
#define AWGAIN 		(0x4391)   // Channel A active power gain adjust.
#define AWATTOS 	(0x4392)   // Channel A active power offset adjust.
#define BWGAIN 		(0x4393)   // Channel B active power gain adjust.
#define BWATTOS 	(0x4394)   // Channel B active power offset adjust.
#define CWGAIN 		(0x4395)   // Channel C active power gain adjust.
#define CWATTOS 	(0x4396)   // Channel C active power offset adjust.
#define DWGAIN 		(0x4397)   // Channel D active power gain adjust
#define DWATTOS 	(0x4398)   // Channel D active power offset adjust.
#define EWGAIN 		(0x4399)   // Channel E active power gain adjust.
#define EWATTOS 	(0x439A)   // Channel E active power offset adjust.
#define FWGAIN 		(0x439B)   // Channel F active power gain adjust.
#define FWATTOS 	(0x439C)   // Channel F active power offset adjust.
#define AVARGAIN 	(0x439D)   // Channel A reactive power gain adjust.
#define AVAROS 		(0x439E)   // Channel A reactive power offset adjust.
#define BVARGAIN 	(0x439F)   // Channel B reactive power gain adjust.
#define BVAROS 		(0x43A0)   // Channel B reactive power offset adjust.
#define CVARGAIN 	(0x43A1)   // Channel C reactive power gain adjust.
#define CVAROS 		(0x43A2)   // Channel C reactive power offset adjust.
#define DVARGAIN 	(0x43A3)   // Channel D reactive power gain adjust.
#define DVAROS 		(0x43A4)   // Channel D reactive power offset adjust.
#define EVARGAIN 	(0x43A5)   // Channel E reactive power gain adjust.
#define EVAROS 		(0x43A6)   // Channel E reactive power offset adjust.
#define FVARGAIN 	(0x43A7)   // Channel F reactive power gain adjust.
#define FVAROS 		(0x43A8)   // Channel F reactive power offset adjust.
#define WTHR1 		(0x43AB)   // Most significant 24 bits of the WTHR[47:0] threshold.
#define WTHR0 		(0x43AC)   // Least significant 24 bits of the WTHR[47:0] threshold.
#define VARTHR1		(0x43AD)   // Most significant 24 bits of the VARTHR[47:0] threshold.
#define VARTHR0		(0x43AE)   // Least significant 24 bits of the VARTHR[47:0] threshold.
#define APNOLOAD	(0x43AF)   // No load threshold in the active power datapath.
#define VARNOLOAD	(0x43B0)   // No load threshold in the reactive power datapath.
#define PCF_A_COEFF	(0x43B1)   // Phase calibration coefficient for Channel A. Set to (0x400C4A for a 50 Hz system and (0x401235 for a 60 Hz system.
#define PCF_B_COEFF	(0x43B2)   // Phase calibration coefficient for Channel B. Set to (0x400C4A for a 50 Hz system and (0x401235 for a 60 Hz system.
#define PCF_C_COEFF	(0x43B3)   // Phase calibration coefficient for Channel C. Set to (0x400C4A for a 50 Hz system and (0x401235 for a 60 Hz system.
#define PCF_D_COEFF	(0x43B4)   // Phase calibration coefficient for Channel D. Set to (0x400C4A for a 50 Hz system and (0x401235 for a 60 Hz system.
#define PCF_E_COEFF	(0x43B5)   // Phase calibration coefficient for Channel E. Set to (0x400C4A for a 50 Hz system and (0x401235 for a 60 Hz system.
#define PCF_F_COEFF	(0x43B6)   // Phase calibration coefficient for Channel F. Set to (0x400C4A for a 50 Hz system and (0x401235 for a 60 Hz system.
#define VRMS		(0x43C0)   // Voltage rms value.
#define IARMS		(0x43C1)   // Current Channel A current rms value.
#define IBRMS		(0x43C2)   // Current Channel B current rms value.
#define ICRMS		(0x43C3)   // Current Channel C current rms value.
#define IDRMS		(0x43C4)   // Current Channel D current rms value.
#define IERMS		(0x43C5)   // Current Channel E current rms value.
#define IFRMS		(0x43C6)   // Current Channel F current rms value.  


// Run Register
#define Run	(0xE228)   // This register starts and stops the DSP

// Billable Registers
#define AWATTHR	(0xE400)   // Channel A active energy accumulation.
#define BWATTHR	(0xE401)   // Channel B active energy accumulation.
#define CWATTHR	(0xE402)   // Channel C active energy accumulation.
#define DWATTHR	(0xE403)   // Channel D active energy accumulation.
#define EWATTHR	(0xE404)   // Channel E active energy accumulation.
#define FWATTHR	(0xE405)   // Channel F active energy accumulation.
#define AVARHR	(0xE406)   // Channel A reactive energy accumulation.
#define BVARHR	(0xE407)   // Channel B reactive energy accumulation.
#define CVARHR	(0xE408)   // Channel C reactive energy accumulation.
#define DVARHR	(0xE409)   // Channel D reactive energy accumulation.
#define EVARHR	(0xE40A)   // Channel E reactive energy accumulation.
#define FVARHR	(0xE40B)   // Channel F reactive energy accumulation.

// Configuration and Power Quality Registers
#define IPEAK 		(0xE500)   // Current peak register.
#define VPEAK 		(0xE501)   // Voltage peak register.
#define STATUS0 	(0xE502)   // Interrupt Status Register 0.
#define STATUS1 	(0xE503)   // Interrupt Status Register 1.
#define OILVL 		(0xE507)   // Overcurrent threshold.
#define OVLVL 		(0xE508)   // Overvoltage threshold.
#define SAGLVL 		(0xE509)   // Voltage sag level threshold.
#define MASK0 		(0xE50A)   // Interrupt Enable Register 0.
#define MASK1 		(0xE50B)   // Interrupt Enable Register 1.
#define IAWV_IDWV 	(0xE50C)   // Instantaneous Current Channel A and Instantaneous Current Channel D.
#define IBWV_IEWV 	(0xE50D)   // Instantaneous Current Channel B and Instantaneous Current Channel E.
#define ICWV_IFWV 	(0xE50E)   // Instantaneous Current Channel C and Instantaneous Current Channel F.
#define Reserved 	(0xE50F)   // This register should be ignored.
#define VWV 		(0xE510)   // Instantaneous voltage.
#define Checksum 	(0xE51F)   // Checksum verification (see the Checksum section for details)   //.
#define CHSTATUS 	(0xE600)   // Channel peak register.
#define ANGLE0 		(0xE601)   // Time Delay 0 (see the Angle Measurements section for details)   //.
#define ANGLE1 		(0xE602)   // Time Delay 1 (see the Angle Measurements section for details)   //.
#define ANGLE2 		(0xE603)   // Time Delay 2 (see the Angle Measurements section for details)   //.
#define Period		(0xE607)   // Line period.
#define CHNOLOAD	(0xE608)   // Channel no load register.
#define LINECYC 	(0xE60C)   // Line cycle accumulation mode count.
#define ZXTOUT 		(0xE60D)   // Zero-crossing timeout count.
#define COMPMODE 	(0xE60E)   // Computation mode register.
#define Gain 		(0xE60F)   // PGA gains at ADC inputs (see Table 22)   //.
#define CHSIGN 		(0xE617)   // Power sign register.
#define CONFIG 		(0xE618)   // Configuration register.
#define MMODE 		(0xE700)   // Measurement mode register.
#define ACCMODE 	(0xE701)   // Accumulation mode register.
#define LCYCMODE 	(0xE702)   // Line accumulation mode.
#define PEAKCYC 	(0xE703)   // Peak detection half line cycles.
#define SAGCYC 		(0xE704)   // Sag detection half line cycles.
#define HSDC_CFG 	(0xE706)   // HSDC configuration register.
#define Version 	(0xE707)   // Version of die.
// #define Reserved 	(0xE7E3)   // Register protection (see the Register Protection section).
// #define Reserved 	(0xE7FE)   // Register protection key (see the Register Protection section).
// #define Reserved 	(0xEBFF)   // This address can be used in manipulating the SS/HSA pin when SPI is chosen as the active port (see the Communication section for details)   //.
#define CONFIG2		(0xEC01)   // Configuration register (see Table 29).

// Register Defaults
#define WTHR1_DEFAULT (0x000002)
#define WTHR0_DEFAULT (0x000000)

#define VARTHR1_DEFAULT (0x000002)
#define VARTHR0_DEFAULT (0x000000)

#define PCF_COEFF_50HZ (0x400CA4)
#define PCF_COEFF_60HZ (0x401235)

#define DICOEFF_DEFAULT (0xFFF8000)
#pragma endregion

#define IsSPI 0x01
#define IsI2C 0x02

// 0.5V peak = 353 mV rms ergeben 0x3FF6A6 mal den Spannungsteiler von 667 (= 220k/330)
#define ScaleVoltageRawToVolt ( 0.353 / 0x3FF6A6  * 666.666)
// 0.5V peak = 353 mV rms ergeben 0x3FF6A6 mal  Rlast = 47 Ohm * �ebersetzungsverh�ltnis 2000
#define ScaleCurrentRawToAmpere (  0.353 / 0x3FF6A6  / 47  * 2000 )
// pro Halbwelle (= 1 LineCycle)     Gain und LineCycles werden in ScalePowerRawToWattWithGain() ber�cksichtigt
#define ScalePowerRawToWatt  (  100 * 0.5 / 1)

class ADE7816
{
    public:
		byte interface = 0;			// IsI2C  or IsSPI
		String name;
		ADE7816ParaClass parameter;	// alle Konfigurationsparameter
		ADE7816DataClass data;		// alle Messdaten

        int init(String name = "no");				// initialisiert den ADE7816-Chip mit den Parametern
		bool hasNewValues();						// Fragt den Cip ab ob er neue Werte hat. Wird bei aufruf aus false zur�ckgesetzt!
		// Current
		int getIxRMS(byte chan);
		int setIxGain(byte chan, int val);
		int getIxGain(byte chan);
		int setIxRMSOS(byte chan, int val);
		int getIxRMSOS(byte chan);
		// Voltage
		int getVRMS();
		int setVGain(int val);
		int getVGain();
		int setVRMSOS(int val);
		int getVRMSOS();
		// Power
		int getWRMS(byte chan);
		int setWGain(byte chan, int val);
		int getWGain(byte chan);
		int setWATTOS(byte chan, int val);
		int getWATTOS(byte chan);
		int getVarRMS(byte chan);
		int setVarGain(byte chan, int val);
		int getVarGain(byte chan);
		int setVarOS(byte chan, int val);
		int getVarOS(byte chan);

		unsigned short getGainRegister();
		unsigned short setGainRegister(unsigned short val);

		// Scale factors
		double ScaleVoltageRawToVoltWithGain();
		double ScaleCurrentRawToAmpereWithGain(size_t chan);
		double ScalePowerRawToWattWithGain(size_t chan);

		// special functions for kalibration
		int setPcfCoeff(byte i, int sollValue);
		int kalibPcfCoeff(byte chan, double val);
		double calcPhaseErr(double winkel, double p, double b);
		int calcWinkel2PCF(double winkel, bool shift);
		double calcPCF2Winkel(int pcf);


		//
		// Read Clibation Parameter from Flash
		//
		void readKalibration();
		void writeParaToADE7816();		// set Kalibration Parameter
		bool setParameter(String paraName,double sollValue,int chan=-1);

		// calculation of the IxGain Value for channel chan and set it 
		// soll current / istCurrent
		// all channels must habe the same current !
		int calibIxGain(int chan, int sollCurrentRaw,int istCurrentRaw);	// chan = 0..5   
		int calibVGain( int sollVoltageRaw, int istVoltageRaw);	
		int calibWGain(int chan, int sollPowerRaw, int istPowerRaw);	// chan = 0..5   
		int calibVarGain(int chan, int sollPowerRaw, int istPowerRaw);	// chan = 0..5   

		bool handleNewData();						// die Daten werden vom Chip ausgelesen und in den Datenstrukturen gespeichert
		int getOneValueRaw(int reg);
		int getOneValue16Raw(int reg);
		double getOneValue(int reg, double scale = 1, double offset = 0);
		double getOneValue16(int reg, double scale = 1, double offset = 0);

#pragma region Registeroperations

		int writeRegister8(const unsigned int reg, byte val);
		int readRegister8(const unsigned int reg, byte *val);

		int writeRegister16(const unsigned int reg, unsigned short int val);
		int readRegister16(const unsigned int reg, unsigned short int * val);

		int writeRegister32(const unsigned int reg, unsigned int val);
		int readRegister32(const unsigned int reg, unsigned int * val);

		int writeRegister32(const unsigned int reg, int val);
		int readRegister32(const unsigned int reg, int * val);

#pragma endregion




		void reset();

		protected:
		byte _resetPin;
		virtual int _writeRegisterBytes(const unsigned int reg, const  byte *val, const unsigned int len)=0;
		virtual int _readRegisterBytes(const unsigned int reg, byte *val, unsigned int len) = 0;

};


//
//  Die Registerzugriffe werden je nach verwendetem Protokoll definiert
//
#include "ADE7816_SPI.h"
#include "ADE7816_I2C.h"

#endif