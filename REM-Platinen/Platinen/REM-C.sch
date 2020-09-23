EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Label 3500 1400 0    50   ~ 0
L1
Text Label 3550 1700 0    50   ~ 0
N1
Text Label 3550 2050 0    50   ~ 0
L2
Text Label 3600 2350 0    50   ~ 0
N2
Text Label 3600 2700 0    50   ~ 0
L3
Text Label 3600 3000 0    50   ~ 0
N3
Wire Wire Line
	4700 1700 4900 1700
Wire Wire Line
	4700 2350 4900 2350
Wire Wire Line
	4700 3000 4900 3000
Wire Wire Line
	4150 2700 4350 2700
Wire Wire Line
	4150 2050 4350 2050
Wire Wire Line
	4700 2700 4900 2700
Wire Wire Line
	4700 2050 4900 2050
Wire Wire Line
	4700 1400 4900 1400
Wire Wire Line
	2350 1400 3850 1400
Wire Wire Line
	2450 1700 4350 1700
Wire Wire Line
	2550 2150 2550 2050
Wire Wire Line
	2550 2050 3850 2050
Wire Wire Line
	2550 2250 2550 2350
Wire Wire Line
	2550 2350 4350 2350
Wire Wire Line
	2450 2700 3850 2700
Wire Wire Line
	2350 3000 4350 3000
Wire Wire Line
	4900 3000 4900 3050
Connection ~ 4900 3000
Wire Wire Line
	4900 2400 4900 2350
Connection ~ 4900 2350
Wire Wire Line
	4900 1750 4900 1700
Connection ~ 4900 1700
Wire Wire Line
	4900 1400 5300 1400
Connection ~ 4900 1400
Wire Wire Line
	4900 2050 5300 2050
Connection ~ 4900 2050
Wire Wire Line
	4900 2700 5300 2700
Connection ~ 4900 2700
Text Label 5150 1400 0    50   ~ 0
VP1
Text Label 5150 2050 0    50   ~ 0
VP2
Text Label 5150 2700 0    50   ~ 0
VP3
Wire Wire Line
	9400 1650 9250 1650
Wire Wire Line
	9250 1650 9250 1550
Wire Wire Line
	9250 1550 9400 1550
$Comp
L power:GND #PWR0104
U 1 1 5ED43034
P 9100 1600
F 0 "#PWR0104" H 9100 1350 50  0001 C CNN
F 1 "GND" H 9105 1427 50  0000 C CNN
F 2 "" H 9100 1600 50  0001 C CNN
F 3 "" H 9100 1600 50  0001 C CNN
	1    9100 1600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 5ED43918
P 10450 1300
F 0 "#PWR0105" H 10450 1050 50  0001 C CNN
F 1 "GND" H 10455 1127 50  0000 C CNN
F 2 "" H 10450 1300 50  0001 C CNN
F 3 "" H 10450 1300 50  0001 C CNN
	1    10450 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	10450 1300 10450 1250
Wire Wire Line
	10450 1250 10350 1250
Wire Wire Line
	10350 1250 10350 1550
Wire Wire Line
	10200 1550 10350 1550
Wire Wire Line
	9100 1600 9100 1550
Wire Wire Line
	9100 1550 9250 1550
Connection ~ 9250 1550
Wire Wire Line
	10700 1650 10700 1550
Wire Wire Line
	10200 1750 10350 1750
Wire Wire Line
	10350 1750 10350 1650
Wire Wire Line
	10350 1650 10700 1650
$Comp
L power:+3.3V #PWR0106
U 1 1 5ED46C1E
P 10700 1550
F 0 "#PWR0106" H 10700 1400 50  0001 C CNN
F 1 "+3.3V" H 10715 1723 50  0000 C CNN
F 2 "" H 10700 1550 50  0001 C CNN
F 3 "" H 10700 1550 50  0001 C CNN
	1    10700 1550
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0107
U 1 1 5ED46E89
P 6050 1400
F 0 "#PWR0107" H 6050 1250 50  0001 C CNN
F 1 "+3.3V" H 6065 1573 50  0000 C CNN
F 2 "" H 6050 1400 50  0001 C CNN
F 3 "" H 6050 1400 50  0001 C CNN
	1    6050 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 1400 6050 1450
$Comp
L power:+5V #PWR0109
U 1 1 5ED4A39F
P 6350 2900
F 0 "#PWR0109" H 6350 2750 50  0001 C CNN
F 1 "+5V" H 6365 3073 50  0000 C CNN
F 2 "" H 6350 2900 50  0001 C CNN
F 3 "" H 6350 2900 50  0001 C CNN
	1    6350 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 2900 6350 3000
Wire Wire Line
	6350 3000 6550 3000
$Comp
L power:GND #PWR0110
U 1 1 5ED4B2FA
P 6350 3150
F 0 "#PWR0110" H 6350 2900 50  0001 C CNN
F 1 "GND" H 6355 2977 50  0000 C CNN
F 2 "" H 6350 3150 50  0001 C CNN
F 3 "" H 6350 3150 50  0001 C CNN
	1    6350 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 3100 6350 3100
Wire Wire Line
	6350 3100 6350 3150
Wire Wire Line
	8050 2400 10300 2400
Wire Wire Line
	10300 2400 10300 2050
Wire Wire Line
	10300 2050 10200 2050
Wire Wire Line
	8050 2500 9250 2500
Wire Wire Line
	9250 2500 9250 1750
Wire Wire Line
	9250 1750 9400 1750
Wire Wire Line
	8050 2600 9150 2600
Wire Wire Line
	9150 2600 9150 1850
Wire Wire Line
	9150 1850 9400 1850
Wire Wire Line
	8050 2700 9100 2700
Wire Wire Line
	9100 2700 9100 1950
$Comp
L power:GND #PWR0111
U 1 1 5ED5171E
P 8350 3350
F 0 "#PWR0111" H 8350 3100 50  0001 C CNN
F 1 "GND" H 8355 3177 50  0000 C CNN
F 2 "" H 8350 3350 50  0001 C CNN
F 3 "" H 8350 3350 50  0001 C CNN
	1    8350 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	8050 2800 8200 2800
Wire Wire Line
	8050 3300 8350 3300
Wire Wire Line
	8350 3300 8350 3350
$Comp
L power:+3.3V #PWR0113
U 1 1 5ED5519B
P 8200 1900
F 0 "#PWR0113" H 8200 1750 50  0001 C CNN
F 1 "+3.3V" V 8215 2028 50  0000 L CNN
F 2 "" H 8200 1900 50  0001 C CNN
F 3 "" H 8200 1900 50  0001 C CNN
	1    8200 1900
	0    1    1    0   
$EndComp
Wire Wire Line
	8200 1900 8050 1900
$Comp
L power:GND #PWR0114
U 1 1 5ED56E97
P 8400 2200
F 0 "#PWR0114" H 8400 1950 50  0001 C CNN
F 1 "GND" H 8500 2200 50  0000 C CNN
F 2 "" H 8400 2200 50  0001 C CNN
F 3 "" H 8400 2200 50  0001 C CNN
	1    8400 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	8050 2200 8150 2200
Wire Wire Line
	8050 2300 8150 2300
Wire Wire Line
	8150 2300 8150 2200
Connection ~ 8150 2200
Wire Wire Line
	8150 2200 8400 2200
Wire Wire Line
	8050 2000 8750 2000
Wire Wire Line
	8050 2100 8750 2100
Text Label 8650 2000 0    50   ~ 0
SCL
Text Label 8650 2100 0    50   ~ 0
SDA
Wire Wire Line
	8850 4400 8650 4400
Wire Wire Line
	8850 4500 8650 4500
Wire Wire Line
	8850 4600 8650 4600
Wire Wire Line
	9350 4400 9600 4400
Wire Wire Line
	9350 4500 9600 4500
Wire Wire Line
	8300 4300 8850 4300
Text Label 8650 4400 0    50   ~ 0
SCL
Text Label 8650 4500 0    50   ~ 0
VP1
Text Label 8650 4600 0    50   ~ 0
VP3
Text Label 9450 4500 0    50   ~ 0
VP2
Text Label 9450 4400 0    50   ~ 0
SDA
$Comp
L power:+3.3V #PWR0116
U 1 1 5ED7735E
P 9750 4150
F 0 "#PWR0116" H 9750 4000 50  0001 C CNN
F 1 "+3.3V" H 9765 4323 50  0000 C CNN
F 2 "" H 9750 4150 50  0001 C CNN
F 3 "" H 9750 4150 50  0001 C CNN
	1    9750 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 1400 2350 1850
Wire Wire Line
	2350 1850 1950 1850
Wire Wire Line
	1950 1950 2450 1950
Wire Wire Line
	2450 1950 2450 1700
Wire Wire Line
	1950 2150 2550 2150
Wire Wire Line
	1950 2250 2550 2250
Wire Wire Line
	1950 2550 2350 2550
Wire Wire Line
	2350 2550 2350 3000
Wire Wire Line
	1950 2450 2450 2450
Wire Wire Line
	2450 2450 2450 2700
Wire Wire Line
	2000 3950 2150 3950
Wire Wire Line
	2000 4050 2150 4050
Wire Wire Line
	2250 4050 2250 4150
Wire Wire Line
	2250 4150 2450 4150
$Comp
L power:GND #PWR0118
U 1 1 5ED9320A
P 3400 4250
F 0 "#PWR0118" H 3400 4000 50  0001 C CNN
F 1 "GND" H 3405 4077 50  0000 C CNN
F 2 "" H 3400 4250 50  0001 C CNN
F 3 "" H 3400 4250 50  0001 C CNN
	1    3400 4250
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0119
U 1 1 5ED93ED2
P 3400 3850
F 0 "#PWR0119" H 3400 3700 50  0001 C CNN
F 1 "+5V" H 3415 4023 50  0000 C CNN
F 2 "" H 3400 3850 50  0001 C CNN
F 3 "" H 3400 3850 50  0001 C CNN
	1    3400 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 3950 3400 3950
Wire Wire Line
	3400 3950 3400 3850
Wire Wire Line
	3250 4150 3400 4150
Wire Wire Line
	3400 4150 3400 4250
Text Label 2300 3950 0    50   ~ 0
L
Text Label 2300 4150 0    50   ~ 0
N
Wire Wire Line
	10400 3800 5900 3800
Wire Wire Line
	5900 3800 5900 2600
Wire Wire Line
	5900 2600 6550 2600
Wire Wire Line
	10400 1950 10400 3800
Text Notes 2750 1400 0    20   ~ 0
+-1,48mA
Text Notes 3900 1500 0    20   ~ 0
P=240mW
Text Notes 4850 1650 1    20   ~ 0
+-1,48mA
Text Notes 5150 1450 0    20   ~ 0
+-488mV
Wire Wire Line
	8850 4200 8300 4200
Wire Wire Line
	8300 4200 8300 4300
Wire Wire Line
	9350 4300 9750 4300
Wire Wire Line
	9750 4300 9750 4200
Wire Wire Line
	9350 4200 9750 4200
Connection ~ 9750 4200
Wire Wire Line
	9750 4200 9750 4150
Wire Wire Line
	9350 4600 9600 4600
$Comp
L power:GNDA #PWR0101
U 1 1 5EE20BA6
P 9600 4750
F 0 "#PWR0101" H 9600 4500 50  0001 C CNN
F 1 "GNDA" H 9605 4577 50  0000 C CNN
F 2 "" H 9600 4750 50  0001 C CNN
F 3 "" H 9600 4750 50  0001 C CNN
	1    9600 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	9600 4600 9600 4750
$Comp
L power:GNDA #PWR0102
U 1 1 5EE24909
P 4900 2400
F 0 "#PWR0102" H 4900 2150 50  0001 C CNN
F 1 "GNDA" H 4905 2227 50  0000 C CNN
F 2 "" H 4900 2400 50  0001 C CNN
F 3 "" H 4900 2400 50  0001 C CNN
	1    4900 2400
	1    0    0    -1  
$EndComp
$Comp
L power:GNDA #PWR0103
U 1 1 5EE2531F
P 4900 1750
F 0 "#PWR0103" H 4900 1500 50  0001 C CNN
F 1 "GNDA" H 4905 1577 50  0000 C CNN
F 2 "" H 4900 1750 50  0001 C CNN
F 3 "" H 4900 1750 50  0001 C CNN
	1    4900 1750
	1    0    0    -1  
$EndComp
$Comp
L power:GNDA #PWR0117
U 1 1 5EE25557
P 4900 3050
F 0 "#PWR0117" H 4900 2800 50  0001 C CNN
F 1 "GNDA" H 4905 2877 50  0000 C CNN
F 2 "" H 4900 3050 50  0001 C CNN
F 3 "" H 4900 3050 50  0001 C CNN
	1    4900 3050
	1    0    0    -1  
$EndComp
Text Label 9450 4600 0    50   ~ 0
GNDA
$Comp
L Connector_Generic:Conn_01x02 J4
U 1 1 5ED8C4D3
P 1800 3950
F 0 "J4" H 1880 3942 50  0000 L CNN
F 1 "Conn_01x02" H 1880 3851 50  0000 L CNN
F 2 "REM:W237-102" H 1800 3950 50  0001 C CNN
F 3 "https://cdn-reichelt.de/documents/datenblatt/C100/AKL073%23RIA.pdf" H 1800 3950 50  0001 C CNN
F 4 "0,50" H 1800 3950 50  0001 C CNN "Preis"
F 5 "https://www.reichelt.de/fahrstuhlklemme-2-pol-4-mm-rm-5-08-akl-073-02-p36620.html" H 1800 3950 50  0001 C CNN "Reichelt"
F 6 "Reichelt" H 1800 3950 50  0001 C CNN "Lieferant"
F 7 "https://www.reichelt.de/fahrstuhlklemme-2-pol-4-mm-rm-5-08-akl-073-02-p36620.html" H 1800 3950 50  0001 C CNN "Link"
	1    1800 3950
	-1   0    0    -1  
$EndComp
$Comp
L REM:AC-DC-Wandler PS1
U 1 1 5ED8A6FA
P 2850 4050
F 0 "PS1" H 2850 4375 50  0000 C CNN
F 1 "AC-DC-Wandler" H 2850 4284 50  0000 C CNN
F 2 "REM:AC-DC_Wandler" H 2850 3750 50  0001 C CNN
F 3 "http://www.hlktech.net/product_detail.php?ProId=54" H 3250 3700 50  0001 C CNN
F 4 "https://de.aliexpress.com/item/33030791040.html" H 2850 4050 50  0001 C CNN "Ali"
F 5 "1,31" H 2850 4050 50  0001 C CNN "Preis"
F 6 "AliExpress" H 2850 4050 50  0001 C CNN "Lieferant"
F 7 "https://de.aliexpress.com/item/33030791040.html" H 2850 4050 50  0001 C CNN "Link"
F 8 "https://de.aliexpress.com/item/33030791040.html" H 2850 4050 50  0001 C CNN "Reichelt"
	1    2850 4050
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J3
U 1 1 5ED42664
P 1750 2450
F 0 "J3" H 1830 2442 50  0000 L CNN
F 1 "Conn_01x02" H 1830 2351 50  0000 L CNN
F 2 "REM:W237-102" H 1750 2450 50  0001 C CNN
F 3 "https://cdn-reichelt.de/documents/datenblatt/C100/AKL073%23RIA.pdf" H 1750 2450 50  0001 C CNN
F 4 "0,50" H 1750 2450 50  0001 C CNN "Preis"
F 5 "https://www.reichelt.de/fahrstuhlklemme-2-pol-4-mm-rm-5-08-akl-073-02-p36620.html" H 1750 2450 50  0001 C CNN "Reichelt"
F 6 "Reichelt" H 1750 2450 50  0001 C CNN "Lieferant"
F 7 "https://www.reichelt.de/fahrstuhlklemme-2-pol-4-mm-rm-5-08-akl-073-02-p36620.html" H 1750 2450 50  0001 C CNN "Link"
	1    1750 2450
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J2
U 1 1 5ED4223F
P 1750 2150
F 0 "J2" H 1830 2142 50  0000 L CNN
F 1 "Conn_01x02" H 1830 2051 50  0000 L CNN
F 2 "REM:W237-102" H 1750 2150 50  0001 C CNN
F 3 "https://cdn-reichelt.de/documents/datenblatt/C100/AKL073%23RIA.pdf" H 1750 2150 50  0001 C CNN
F 4 "0,50" H 1750 2150 50  0001 C CNN "Preis"
F 5 "https://www.reichelt.de/fahrstuhlklemme-2-pol-4-mm-rm-5-08-akl-073-02-p36620.html" H 1750 2150 50  0001 C CNN "Reichelt"
F 6 "Reichelt" H 1750 2150 50  0001 C CNN "Lieferant"
F 7 "https://www.reichelt.de/fahrstuhlklemme-2-pol-4-mm-rm-5-08-akl-073-02-p36620.html" H 1750 2150 50  0001 C CNN "Link"
	1    1750 2150
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J1
U 1 1 5ED400B9
P 1750 1850
F 0 "J1" H 1830 1842 50  0000 L CNN
F 1 "Conn_01x02" H 1830 1751 50  0000 L CNN
F 2 "REM:W237-102" H 1750 1850 50  0001 C CNN
F 3 "https://cdn-reichelt.de/documents/datenblatt/C100/AKL073%23RIA.pdf" H 1750 1850 50  0001 C CNN
F 4 "0,50" H 1750 1850 50  0001 C CNN "Preis"
F 5 "https://www.reichelt.de/fahrstuhlklemme-2-pol-4-mm-rm-5-08-akl-073-02-p36620.html" H 1750 1850 50  0001 C CNN "Reichelt"
F 6 "Reichelt" H 1750 1850 50  0001 C CNN "Lieferant"
F 7 "https://www.reichelt.de/fahrstuhlklemme-2-pol-4-mm-rm-5-08-akl-073-02-p36620.html" H 1750 1850 50  0001 C CNN "Link"
	1    1750 1850
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x05_Odd_Even J7
U 1 1 5ED617A7
P 9050 4400
F 0 "J7" H 9100 4717 50  0000 C CNN
F 1 "Conn_02x05_Odd_Even" H 9000 4050 50  0001 C CNN
F 2 "REM:PinHeader_2x05_P2.54mm_Vertical_mit_Stecker" H 9050 4400 50  0001 C CNN
F 3 "https://cdn-reichelt.de/documents/datenblatt/C140/DS_MPE_087.pdf" H 9050 4400 50  0001 C CNN
F 4 "0,23" H 9050 4400 50  0001 C CNN "Preis"
F 5 "https://www.reichelt.de/stiftleisten-2-54-mm-2x05-gerade-mpe-087-2-010-p119895.html" H 9050 4400 50  0001 C CNN "Reichelt"
F 6 "Reichelt" H 9050 4400 50  0001 C CNN "Lieferant"
F 7 "https://www.reichelt.de/stiftleisten-2-54-mm-2x05-gerade-mpe-087-2-010-p119895.html" H 9050 4400 50  0001 C CNN "Link"
	1    9050 4400
	1    0    0    -1  
$EndComp
$Comp
L REM:USR-ES1 U2
U 1 1 5ED66B07
P 9800 1950
F 0 "U2" H 9800 2575 50  0000 C CNN
F 1 "USR-ES1" H 9800 2484 50  0000 C CNN
F 2 "REM:USR-ES1_gesockelt" H 9825 2150 50  0001 C CNN
F 3 "D:\\Daten\\Petzoldt\\Rainer\\Entwicklung\\Dokumentation\\Bauteiledokumentation\\Adapter\\USR-ES1-EN-V1.0.pdf" H 9825 2150 50  0001 C CNN
F 4 "https://de.aliexpress.com/item/4000923964703.html" H 9800 1950 50  0001 C CNN "Ali"
F 5 "3,33" H 9800 1950 50  0001 C CNN "Preis"
F 6 "AliExpress" H 9800 1950 50  0001 C CNN "Lieferant"
	1    9800 1950
	1    0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 5ED2A855
P 4900 2850
F 0 "R6" H 4970 2896 50  0000 L CNN
F 1 "330" H 4970 2805 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4830 2850 50  0001 C CNN
F 3 "https://cdn-reichelt.de/documents/datenblatt/B300/NGMBX-SMA_DATA_E.pdf" H 4900 2850 50  0001 C CNN
F 4 "0,04" H 4900 2850 50  0001 C CNN "Preis"
F 5 "https://www.reichelt.de/duennschichtwiderstand-axial-0-6-w-330-ohm-1-vi-mbb02070c3300-p233724.html" H 4900 2850 50  0001 C CNN "Reichelt"
F 6 "Reichelt" H 4900 2850 50  0001 C CNN "Lieferant"
F 7 "https://www.reichelt.de/duennschichtwiderstand-axial-0-6-w-330-ohm-1-vi-mbb02070c3300-p233724.html" H 4900 2850 50  0001 C CNN "Link"
	1    4900 2850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R5
U 1 1 5ED2A005
P 4900 2200
F 0 "R5" H 4970 2246 50  0000 L CNN
F 1 "330" H 4970 2155 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4830 2200 50  0001 C CNN
F 3 "https://cdn-reichelt.de/documents/datenblatt/B300/NGMBX-SMA_DATA_E.pdf" H 4900 2200 50  0001 C CNN
F 4 "0,04" H 4900 2200 50  0001 C CNN "Preis"
F 5 "https://www.reichelt.de/duennschichtwiderstand-axial-0-6-w-330-ohm-1-vi-mbb02070c3300-p233724.html" H 4900 2200 50  0001 C CNN "Reichelt"
F 6 "Reichelt" H 4900 2200 50  0001 C CNN "Lieferant"
F 7 "https://www.reichelt.de/duennschichtwiderstand-axial-0-6-w-330-ohm-1-vi-mbb02070c3300-p233724.html" H 4900 2200 50  0001 C CNN "Link"
	1    4900 2200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 5ED298DB
P 4900 1550
F 0 "R4" H 4970 1596 50  0000 L CNN
F 1 "330" H 4970 1505 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4830 1550 50  0001 C CNN
F 3 "https://cdn-reichelt.de/documents/datenblatt/B300/NGMBX-SMA_DATA_E.pdf" H 4900 1550 50  0001 C CNN
F 4 "0,04" H 4900 1550 50  0001 C CNN "Preis"
F 5 "https://www.reichelt.de/duennschichtwiderstand-axial-0-6-w-330-ohm-1-vi-mbb02070c3300-p233724.html" H 4900 1550 50  0001 C CNN "Reichelt"
F 6 "Reichelt" H 4900 1550 50  0001 C CNN "Lieferant"
F 7 "https://www.reichelt.de/duennschichtwiderstand-axial-0-6-w-330-ohm-1-vi-mbb02070c3300-p233724.html" H 4900 1550 50  0001 C CNN "Link"
	1    4900 1550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5ED26B7F
P 4000 1400
F 0 "R1" V 3793 1400 50  0000 C CNN
F 1 "220k" V 3884 1400 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0414_L11.9mm_D4.5mm_P15.24mm_Horizontal" V 3930 1400 50  0001 C CNN
F 3 "https://www.reichelt.de/index.html?ACTION=7&LA=3&OPEN=0&INDEX=0&FILENAME=B300%2FNHMBX-SMA_DATA_EN.pdf" H 4000 1400 50  0001 C CNN
F 4 "1W" V 4000 1400 50  0001 C CNN "Leistung"
F 5 "0,13" H 4000 1400 50  0001 C CNN "Preis"
F 6 "https://www.reichelt.de/duennschichtwiderstand-axial-1-w-220-kohm-1-vi-mbe04140c2203-p233820.html" H 4000 1400 50  0001 C CNN "Reichelt"
F 7 "Reichelt" H 4000 1400 50  0001 C CNN "Lieferant"
F 8 "https://www.reichelt.de/duennschichtwiderstand-axial-1-w-220-kohm-1-vi-mbe04140c2203-p233820.html" H 4000 1400 50  0001 C CNN "Link"
	1    4000 1400
	0    1    1    0   
$EndComp
$Comp
L REM:ZMCT10x T3
U 1 1 5ED24BCC
P 4750 2850
F 0 "T3" H 4450 2600 50  0000 L CNN
F 1 "ZMPT107-1" H 4350 3150 50  0000 L CNN
F 2 "REM:ZMPT107" H 4750 3050 50  0001 C CNN
F 3 "D:\\Daten\\Petzoldt\\Rainer\\Entwicklung\\REM\\Bauteile\\ZMPT101B specification.pdf" H 4750 3050 50  0001 C CNN
F 4 "https://de.aliexpress.com/item/10000007567815.html" H 4750 2850 50  0001 C CNN "Ali"
F 5 "0,95" H 4750 2850 50  0001 C CNN "Preis"
F 6 "AliExpress" H 4750 2850 50  0001 C CNN "Lieferant"
F 7 "https://de.aliexpress.com/item/10000007567815.html" H 4750 2850 50  0001 C CNN "Link"
F 8 "https://de.aliexpress.com/item/10000007567815.html" H 4750 2850 50  0001 C CNN "Reichelt"
	1    4750 2850
	1    0    0    -1  
$EndComp
$Comp
L REM:ZMCT10x T2
U 1 1 5ED2473A
P 4750 2200
F 0 "T2" H 4450 1950 50  0000 L CNN
F 1 "ZMPT107-1" H 4350 2500 50  0000 L CNN
F 2 "REM:ZMPT107" H 4750 2400 50  0001 C CNN
F 3 "D:\\Daten\\Petzoldt\\Rainer\\Entwicklung\\REM\\Bauteile\\ZMPT101B specification.pdf" H 4750 2400 50  0001 C CNN
F 4 "https://de.aliexpress.com/item/10000007567815.html" H 4750 2200 50  0001 C CNN "Ali"
F 5 "0,95" H 4750 2200 50  0001 C CNN "Preis"
F 6 "AliExpress" H 4750 2200 50  0001 C CNN "Lieferant"
F 7 "https://de.aliexpress.com/item/10000007567815.html" H 4750 2200 50  0001 C CNN "Link"
F 8 "https://de.aliexpress.com/item/10000007567815.html" H 4750 2200 50  0001 C CNN "Reichelt"
	1    4750 2200
	1    0    0    -1  
$EndComp
$Comp
L REM:ZMCT10x T1
U 1 1 5ED23A54
P 4750 1550
F 0 "T1" H 4450 1300 50  0000 L CNN
F 1 "ZMPT107-1" H 4350 1850 50  0000 L CNN
F 2 "REM:ZMPT107" H 4750 1750 50  0001 C CNN
F 3 "D:\\Daten\\Petzoldt\\Rainer\\Entwicklung\\REM\\Bauteile\\ZMPT101B specification.pdf" H 4750 1750 50  0001 C CNN
F 4 "https://de.aliexpress.com/item/10000007567815.html" H 4750 1550 50  0001 C CNN "Ali"
F 5 "0,95" H 4750 1550 50  0001 C CNN "Preis"
F 6 "AliExpress" H 4750 1550 50  0001 C CNN "Lieferant"
F 7 "https://de.aliexpress.com/item/10000007567815.html" H 4750 1550 50  0001 C CNN "Link"
F 8 "https://de.aliexpress.com/item/10000007567815.html" H 4750 1550 50  0001 C CNN "Reichelt"
	1    4750 1550
	1    0    0    -1  
$EndComp
Text Label 8200 2700 0    50   ~ 0
CS
Text Label 8200 2600 0    50   ~ 0
SCK
Text Label 8200 2500 0    50   ~ 0
MOSI
Text Label 8200 2400 0    50   ~ 0
MISO
$Comp
L Device:CP_Small C2
U 1 1 5EE8262F
P 4100 4050
F 0 "C2" H 4188 4096 50  0000 L CNN
F 1 "10u" H 4188 4005 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.00mm" H 4100 4050 50  0001 C CNN
F 3 "https://cdn-reichelt.de/documents/datenblatt/B300/KEM_C0XXX_X7R_DB-EN.pdf" H 4100 4050 50  0001 C CNN
F 4 "0,10" H 4100 4050 50  0001 C CNN "Preis"
F 5 "https://www.reichelt.de/elko-radial-10-uf-50-v-105-c-low-esr-fr-a-10u-50-p200268.html" H 4100 4050 50  0001 C CNN "Reichelt"
F 6 "Reichelt" H 4100 4050 50  0001 C CNN "Lieferant"
F 7 "https://www.reichelt.de/elko-radial-10-uf-50-v-105-c-low-esr-fr-a-10u-50-p200268.html" H 4100 4050 50  0001 C CNN "Link"
	1    4100 4050
	1    0    0    -1  
$EndComp
$Comp
L Device:CP_Small C6
U 1 1 5EE832B6
P 3500 5100
F 0 "C6" H 3588 5146 50  0000 L CNN
F 1 "10u" H 3588 5055 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.00mm" H 3500 5100 50  0001 C CNN
F 3 "https://cdn-reichelt.de/documents/datenblatt/B300/KEM_C0XXX_X7R_DB-EN.pdf" H 3500 5100 50  0001 C CNN
F 4 "0,10" H 3500 5100 50  0001 C CNN "Preis"
F 5 "https://www.reichelt.de/elko-radial-10-uf-50-v-105-c-low-esr-fr-a-10u-50-p200268.html" H 3500 5100 50  0001 C CNN "Reichelt"
F 6 "Reichelt" H 3500 5100 50  0001 C CNN "Lieferant"
F 7 "https://www.reichelt.de/elko-radial-10-uf-50-v-105-c-low-esr-fr-a-10u-50-p200268.html" H 3500 5100 50  0001 C CNN "Link"
	1    3500 5100
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C1
U 1 1 5EE83C30
P 3650 4050
F 0 "C1" H 3742 4096 50  0000 L CNN
F 1 "100n" H 3742 4005 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3650 4050 50  0001 C CNN
F 3 "https://cdn-reichelt.de/documents/datenblatt/B300/KEM_C0XXX_Y5V_DB-EN.pdf" H 3650 4050 50  0001 C CNN
F 4 "0,02" H 3650 4050 50  0001 C CNN "Preis"
F 5 "https://de.aliexpress.com/item/4000923964703.html" H 3650 4050 50  0001 C CNN "Reichelt"
F 6 "Reichelt" H 3650 4050 50  0001 C CNN "Lieferant"
F 7 "https://de.aliexpress.com/item/4000923964703.html" H 3650 4050 50  0001 C CNN "Link"
	1    3650 4050
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C3
U 1 1 5EE8524D
P 2250 5100
F 0 "C3" H 2342 5146 50  0000 L CNN
F 1 "100n" H 2342 5055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2250 5100 50  0001 C CNN
F 3 "https://cdn-reichelt.de/documents/datenblatt/B300/KEM_C0XXX_Y5V_DB-EN.pdf" H 2250 5100 50  0001 C CNN
F 4 "0,02" H 2250 5100 50  0001 C CNN "Preis"
F 5 "https://de.aliexpress.com/item/4000923964703.html" H 2250 5100 50  0001 C CNN "Reichelt"
F 6 "Reichelt" H 2250 5100 50  0001 C CNN "Lieferant"
F 7 "https://de.aliexpress.com/item/4000923964703.html" H 2250 5100 50  0001 C CNN "Link"
	1    2250 5100
	1    0    0    -1  
$EndComp
Connection ~ 3400 3950
Wire Wire Line
	3650 3950 4100 3950
Connection ~ 3650 3950
Connection ~ 3400 4150
Wire Wire Line
	3650 4150 4100 4150
Connection ~ 3650 4150
$Comp
L power:GND #PWR02
U 1 1 5EE95757
P 2250 5350
F 0 "#PWR02" H 2250 5100 50  0001 C CNN
F 1 "GND" H 2255 5177 50  0000 C CNN
F 2 "" H 2250 5350 50  0001 C CNN
F 3 "" H 2250 5350 50  0001 C CNN
	1    2250 5350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 5EE95D93
P 3500 5350
F 0 "#PWR04" H 3500 5100 50  0001 C CNN
F 1 "GND" H 3505 5177 50  0000 C CNN
F 2 "" H 3500 5350 50  0001 C CNN
F 3 "" H 3500 5350 50  0001 C CNN
	1    3500 5350
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR03
U 1 1 5EE95FF7
P 3500 4900
F 0 "#PWR03" H 3500 4750 50  0001 C CNN
F 1 "+3.3V" H 3515 5073 50  0000 C CNN
F 2 "" H 3500 4900 50  0001 C CNN
F 3 "" H 3500 4900 50  0001 C CNN
	1    3500 4900
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR01
U 1 1 5EE969A6
P 2250 4900
F 0 "#PWR01" H 2250 4750 50  0001 C CNN
F 1 "+3.3V" H 2265 5073 50  0000 C CNN
F 2 "" H 2250 4900 50  0001 C CNN
F 3 "" H 2250 4900 50  0001 C CNN
	1    2250 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 4900 2250 5000
Wire Wire Line
	3500 4900 3500 5000
Wire Wire Line
	2250 5200 2250 5350
Wire Wire Line
	3500 5200 3500 5350
$Comp
L Device:C_Small C4
U 1 1 5EEBE132
P 2650 5100
F 0 "C4" H 2742 5146 50  0000 L CNN
F 1 "100n" H 2742 5055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2650 5100 50  0001 C CNN
F 3 "https://cdn-reichelt.de/documents/datenblatt/B300/KEM_C0XXX_Y5V_DB-EN.pdf" H 2650 5100 50  0001 C CNN
F 4 "0,02" H 2650 5100 50  0001 C CNN "Preis"
F 5 "https://de.aliexpress.com/item/4000923964703.html" H 2650 5100 50  0001 C CNN "Reichelt"
F 6 "Reichelt" H 2650 5100 50  0001 C CNN "Lieferant"
F 7 "https://de.aliexpress.com/item/4000923964703.html" H 2650 5100 50  0001 C CNN "Link"
	1    2650 5100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR08
U 1 1 5EEBE13C
P 2650 5350
F 0 "#PWR08" H 2650 5100 50  0001 C CNN
F 1 "GND" H 2655 5177 50  0000 C CNN
F 2 "" H 2650 5350 50  0001 C CNN
F 3 "" H 2650 5350 50  0001 C CNN
	1    2650 5350
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR07
U 1 1 5EEBE146
P 2650 4900
F 0 "#PWR07" H 2650 4750 50  0001 C CNN
F 1 "+3.3V" H 2665 5073 50  0000 C CNN
F 2 "" H 2650 4900 50  0001 C CNN
F 3 "" H 2650 4900 50  0001 C CNN
	1    2650 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 4900 2650 5000
Wire Wire Line
	2650 5200 2650 5350
$Comp
L Device:C_Small C5
U 1 1 5EEC3D68
P 3000 5100
F 0 "C5" H 3092 5146 50  0000 L CNN
F 1 "100n" H 3092 5055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3000 5100 50  0001 C CNN
F 3 "https://cdn-reichelt.de/documents/datenblatt/B300/KEM_C0XXX_Y5V_DB-EN.pdf" H 3000 5100 50  0001 C CNN
F 4 "0,02" H 3000 5100 50  0001 C CNN "Preis"
F 5 "https://de.aliexpress.com/item/4000923964703.html" H 3000 5100 50  0001 C CNN "Reichelt"
F 6 "Reichelt" H 3000 5100 50  0001 C CNN "Lieferant"
F 7 "https://de.aliexpress.com/item/4000923964703.html" H 3000 5100 50  0001 C CNN "Link"
	1    3000 5100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 5EEC3D72
P 3000 5350
F 0 "#PWR06" H 3000 5100 50  0001 C CNN
F 1 "GND" H 3005 5177 50  0000 C CNN
F 2 "" H 3000 5350 50  0001 C CNN
F 3 "" H 3000 5350 50  0001 C CNN
	1    3000 5350
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR05
U 1 1 5EEC3D7C
P 3000 4900
F 0 "#PWR05" H 3000 4750 50  0001 C CNN
F 1 "+3.3V" H 3015 5073 50  0000 C CNN
F 2 "" H 3000 4900 50  0001 C CNN
F 3 "" H 3000 4900 50  0001 C CNN
	1    3000 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 4900 3000 5000
Wire Wire Line
	3000 5200 3000 5350
$Comp
L Device:R R3
U 1 1 5EEED076
P 4000 2700
F 0 "R3" V 3793 2700 50  0000 C CNN
F 1 "220k" V 3884 2700 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0414_L11.9mm_D4.5mm_P15.24mm_Horizontal" V 3930 2700 50  0001 C CNN
F 3 "https://www.reichelt.de/index.html?ACTION=7&LA=3&OPEN=0&INDEX=0&FILENAME=B300%2FNHMBX-SMA_DATA_EN.pdf" H 4000 2700 50  0001 C CNN
F 4 "1W" V 4000 2700 50  0001 C CNN "Leistung"
F 5 "0,13" H 4000 2700 50  0001 C CNN "Preis"
F 6 "https://www.reichelt.de/duennschichtwiderstand-axial-1-w-220-kohm-1-vi-mbe04140c2203-p233820.html" H 4000 2700 50  0001 C CNN "Reichelt"
F 7 "Reichelt" H 4000 2700 50  0001 C CNN "Lieferant"
F 8 "https://www.reichelt.de/duennschichtwiderstand-axial-1-w-220-kohm-1-vi-mbe04140c2203-p233820.html" H 4000 2700 50  0001 C CNN "Link"
	1    4000 2700
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 5EEED745
P 4000 2050
F 0 "R2" V 3793 2050 50  0000 C CNN
F 1 "220k" V 3884 2050 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0414_L11.9mm_D4.5mm_P15.24mm_Horizontal" V 3930 2050 50  0001 C CNN
F 3 "https://www.reichelt.de/index.html?ACTION=7&LA=3&OPEN=0&INDEX=0&FILENAME=B300%2FNHMBX-SMA_DATA_EN.pdf" H 4000 2050 50  0001 C CNN
F 4 "1W" V 4000 2050 50  0001 C CNN "Leistung"
F 5 "0,13" H 4000 2050 50  0001 C CNN "Preis"
F 6 "https://www.reichelt.de/duennschichtwiderstand-axial-1-w-220-kohm-1-vi-mbe04140c2203-p233820.html" H 4000 2050 50  0001 C CNN "Reichelt"
F 7 "Reichelt" H 4000 2050 50  0001 C CNN "Lieferant"
F 8 "https://www.reichelt.de/duennschichtwiderstand-axial-1-w-220-kohm-1-vi-mbe04140c2203-p233820.html" H 4000 2050 50  0001 C CNN "Link"
	1    4000 2050
	0    1    1    0   
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J5
U 1 1 5EE18451
P 4650 4050
F 0 "J5" H 4730 4042 50  0000 L CNN
F 1 "Conn_01x02" H 4730 3951 50  0000 L CNN
F 2 "REM:W237-102" H 4650 4050 50  0001 C CNN
F 3 "https://cdn-reichelt.de/documents/datenblatt/C100/AKL073%23RIA.pdf" H 4650 4050 50  0001 C CNN
F 4 "0,50" H 4650 4050 50  0001 C CNN "Preis"
F 5 "https://www.reichelt.de/fahrstuhlklemme-2-pol-4-mm-rm-5-08-akl-073-02-p36620.html" H 4650 4050 50  0001 C CNN "Reichelt"
F 6 "Reichelt" H 4650 4050 50  0001 C CNN "Lieferant"
F 7 "https://www.reichelt.de/fahrstuhlklemme-2-pol-4-mm-rm-5-08-akl-073-02-p36620.html" H 4650 4050 50  0001 C CNN "Link"
	1    4650 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 4150 4100 4150
Connection ~ 4100 4150
Wire Wire Line
	4100 3950 4350 3950
Wire Wire Line
	4350 3950 4350 4050
Wire Wire Line
	4350 4050 4450 4050
Connection ~ 4100 3950
$Comp
L Connector_Generic:Conn_01x02 J6
U 1 1 5EE244F4
P 4450 5150
F 0 "J6" H 4530 5142 50  0000 L CNN
F 1 "Conn_01x02" H 4530 5051 50  0000 L CNN
F 2 "REM:W237-102" H 4450 5150 50  0001 C CNN
F 3 "https://cdn-reichelt.de/documents/datenblatt/C100/AKL073%23RIA.pdf" H 4450 5150 50  0001 C CNN
F 4 "0,50" H 4450 5150 50  0001 C CNN "Preis"
F 5 "https://www.reichelt.de/fahrstuhlklemme-2-pol-4-mm-rm-5-08-akl-073-02-p36620.html" H 4450 5150 50  0001 C CNN "Reichelt"
F 6 "Reichelt" H 4450 5150 50  0001 C CNN "Lieferant"
F 7 "https://www.reichelt.de/fahrstuhlklemme-2-pol-4-mm-rm-5-08-akl-073-02-p36620.html" H 4450 5150 50  0001 C CNN "Link"
	1    4450 5150
	1    0    0    1   
$EndComp
$Comp
L power:+3.3V #PWR0120
U 1 1 5EE25F5A
P 4200 4900
F 0 "#PWR0120" H 4200 4750 50  0001 C CNN
F 1 "+3.3V" H 4215 5073 50  0000 C CNN
F 2 "" H 4200 4900 50  0001 C CNN
F 3 "" H 4200 4900 50  0001 C CNN
	1    4200 4900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0121
U 1 1 5EE26847
P 4200 5350
F 0 "#PWR0121" H 4200 5100 50  0001 C CNN
F 1 "GND" H 4205 5177 50  0000 C CNN
F 2 "" H 4200 5350 50  0001 C CNN
F 3 "" H 4200 5350 50  0001 C CNN
	1    4200 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 5150 4200 5150
Wire Wire Line
	4200 5150 4200 5350
Wire Wire Line
	4200 4900 4200 5050
Wire Wire Line
	4200 5050 4250 5050
$Comp
L Mechanical:MountingHole H1
U 1 1 5EE4A458
P 1500 6450
F 0 "H1" H 1600 6496 50  0000 L CNN
F 1 "MountingHole" H 1600 6405 50  0000 L CNN
F 2 "kicad:MountingHole_2.2mm_M2" H 1500 6450 50  0001 C CNN
F 3 "~" H 1500 6450 50  0001 C CNN
F 4 "no" H 1500 6450 50  0001 C CNN "Lieferant"
	1    1500 6450
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 5EE4C0E0
P 1500 6700
F 0 "H2" H 1600 6746 50  0000 L CNN
F 1 "MountingHole" H 1600 6655 50  0000 L CNN
F 2 "kicad:MountingHole_2.2mm_M2" H 1500 6700 50  0001 C CNN
F 3 "~" H 1500 6700 50  0001 C CNN
F 4 "no" H 1500 6700 50  0001 C CNN "Lieferant"
	1    1500 6700
	1    0    0    -1  
$EndComp
$Comp
L REM:Logo L1
U 1 1 5EE3D6C3
P 6250 7100
F 0 "L1" H 6250 7200 50  0001 C CNN
F 1 "Logo" H 6320 7108 50  0000 L CNN
F 2 "REM:LogoRP_6mm" H 6250 7200 50  0001 C CNN
F 3 "" H 6250 7200 50  0001 C CNN
F 4 "no" H 6250 7100 50  0001 C CNN "Lieferant"
	1    6250 7100
	1    0    0    -1  
$EndComp
$Comp
L REM:Logo L2
U 1 1 5EE44BB7
P 6250 7250
F 0 "L2" H 6250 7350 50  0001 C CNN
F 1 "Logo" H 6320 7258 50  0000 L CNN
F 2 "REM:LogoRP_6mm" H 6250 7350 50  0001 C CNN
F 3 "" H 6250 7350 50  0001 C CNN
F 4 "no" H 6250 7250 50  0001 C CNN "Lieferant"
	1    6250 7250
	1    0    0    -1  
$EndComp
Text Label 6150 2600 0    50   ~ 0
RST
$Comp
L Transistor_FET:IRF3205 Q1
U 1 1 5EF2A503
P 7250 4500
F 0 "Q1" H 7455 4546 50  0000 L CNN
F 1 "IRF3708" H 7455 4455 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 7500 4425 50  0001 L CIN
F 3 "http://www.irf.com/product-info/datasheets/data/irf3205.pdf" H 7250 4500 50  0001 L CNN
	1    7250 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7350 4700 7350 4800
Wire Wire Line
	7350 4300 7350 4200
Wire Wire Line
	7350 4200 8300 4200
Connection ~ 8300 4200
Text Label 7600 4200 0    50   ~ 0
GND_Switched
Text Label 6300 2000 2    50   ~ 0
PWR_Switch
Text Label 6700 4500 2    50   ~ 0
PWR_Switch
$Comp
L Device:R_Small R7
U 1 1 5EF41965
P 6800 4500
F 0 "R7" V 6604 4500 50  0000 C CNN
F 1 "100k" V 6695 4500 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 6800 4500 50  0001 C CNN
F 3 "~" H 6800 4500 50  0001 C CNN
	1    6800 4500
	0    1    1    0   
$EndComp
Wire Wire Line
	6900 4500 7050 4500
$Comp
L power:GND #PWR0115
U 1 1 5EF53C4A
P 7350 4800
F 0 "#PWR0115" H 7350 4550 50  0001 C CNN
F 1 "GND" H 7355 4627 50  0000 C CNN
F 2 "" H 7350 4800 50  0001 C CNN
F 3 "" H 7350 4800 50  0001 C CNN
	1    7350 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 2000 6300 2000
Text Label 7700 5700 0    50   ~ 0
SCL
Text Label 7200 5700 2    50   ~ 0
SDA
$Comp
L power:+3.3V #PWR0123
U 1 1 5EF3E184
P 8250 5350
F 0 "#PWR0123" H 8250 5200 50  0001 C CNN
F 1 "+3.3V" H 8265 5523 50  0000 C CNN
F 2 "" H 8250 5350 50  0001 C CNN
F 3 "" H 8250 5350 50  0001 C CNN
	1    8250 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	8250 5400 8250 5350
Text Label 7700 5800 0    50   ~ 0
MISO
Text Label 7700 5900 0    50   ~ 0
MOSI
Text Label 7200 5900 2    50   ~ 0
SCK
Text Label 7200 5800 2    50   ~ 0
CS2
Text Label 6300 2100 2    50   ~ 0
CS2
Wire Wire Line
	6550 2100 6300 2100
NoConn ~ 8050 3000
NoConn ~ 8050 3100
NoConn ~ 8050 3200
NoConn ~ 8050 3400
NoConn ~ 8050 3500
NoConn ~ 6550 2900
NoConn ~ 6550 2800
NoConn ~ 6550 2700
NoConn ~ 6550 2500
NoConn ~ 6550 2400
NoConn ~ 6550 2200
NoConn ~ 6550 1900
NoConn ~ 6550 1800
Wire Wire Line
	4150 1400 4350 1400
NoConn ~ 9400 2050
Wire Wire Line
	10200 1650 10350 1650
Connection ~ 10350 1650
$Comp
L power:PWR_FLAG #FLG0103
U 1 1 5EFF237F
P 2150 3950
F 0 "#FLG0103" H 2150 4025 50  0001 C CNN
F 1 "PWR_FLAG" H 2150 4123 50  0000 C CNN
F 2 "" H 2150 3950 50  0001 C CNN
F 3 "~" H 2150 3950 50  0001 C CNN
	1    2150 3950
	1    0    0    -1  
$EndComp
Connection ~ 2150 3950
Wire Wire Line
	2150 3950 2450 3950
$Comp
L power:PWR_FLAG #FLG0104
U 1 1 5EFF28FA
P 2150 4050
F 0 "#FLG0104" H 2150 4125 50  0001 C CNN
F 1 "PWR_FLAG" H 2150 4223 50  0000 C CNN
F 2 "" H 2150 4050 50  0001 C CNN
F 3 "~" H 2150 4050 50  0001 C CNN
	1    2150 4050
	-1   0    0    1   
$EndComp
Connection ~ 2150 4050
Wire Wire Line
	2150 4050 2250 4050
Wire Wire Line
	3400 3950 3650 3950
Wire Wire Line
	3400 4150 3650 4150
$Comp
L power:GNDA #PWR0124
U 1 1 5EFFAAA3
P 5350 3700
F 0 "#PWR0124" H 5350 3450 50  0001 C CNN
F 1 "GNDA" H 5355 3527 50  0000 C CNN
F 2 "" H 5350 3700 50  0001 C CNN
F 3 "" H 5350 3700 50  0001 C CNN
	1    5350 3700
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5EFFADFB
P 5350 3700
F 0 "#FLG0101" H 5350 3775 50  0001 C CNN
F 1 "PWR_FLAG" H 5350 3873 50  0000 C CNN
F 2 "" H 5350 3700 50  0001 C CNN
F 3 "~" H 5350 3700 50  0001 C CNN
	1    5350 3700
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 5EFFB3DD
P 1800 5150
F 0 "#FLG0102" H 1800 5225 50  0001 C CNN
F 1 "PWR_FLAG" H 1800 5323 50  0000 C CNN
F 2 "" H 1800 5150 50  0001 C CNN
F 3 "~" H 1800 5150 50  0001 C CNN
	1    1800 5150
	-1   0    0    1   
$EndComp
Wire Wire Line
	6050 1450 6400 1450
Wire Wire Line
	10400 1950 10200 1950
Wire Wire Line
	9100 1950 9400 1950
$Comp
L REM:Lolin32 U1
U 1 1 5ED48FB0
P 7050 2550
F 0 "U1" H 7300 3747 60  0000 C CNN
F 1 "Lolin32" H 7300 3641 60  0000 C CNN
F 2 "REM:Lolin32_gesockelt" H 6900 2400 60  0001 C CNN
F 3 "D:\\Daten\\Petzoldt\\Rainer\\Entwicklung\\Dokumentation\\Bauteiledokumentation\\uController\\ESP32" H 6900 2400 60  0001 C CNN
F 4 "https://de.aliexpress.com/item/4000340140634.html" H 7050 2550 50  0001 C CNN "Ali"
F 5 "3,61" H 7050 2550 50  0001 C CNN "Preis"
F 6 "AliExpress" H 7050 2550 50  0001 C CNN "Lieferant"
F 7 "https://de.aliexpress.com/item/4000340140634.html" H 7050 2550 50  0001 C CNN "Link"
F 8 "https://de.aliexpress.com/item/4000340140634.html" H 7050 2550 50  0001 C CNN "Reichelt"
	1    7050 2550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0122
U 1 1 5F03052B
P 6850 5200
F 0 "#PWR0122" H 6850 4950 50  0001 C CNN
F 1 "GND" H 6855 5027 50  0000 C CNN
F 2 "" H 6850 5200 50  0001 C CNN
F 3 "" H 6850 5200 50  0001 C CNN
	1    6850 5200
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0125
U 1 1 5EF36DB4
P 6600 5500
F 0 "#PWR0125" H 6600 5350 50  0001 C CNN
F 1 "+5V" H 6615 5673 50  0000 C CNN
F 2 "" H 6600 5500 50  0001 C CNN
F 3 "" H 6600 5500 50  0001 C CNN
	1    6600 5500
	1    0    0    -1  
$EndComp
Text Label 8400 1700 0    50   ~ 0
TX
Text Label 7200 5600 2    50   ~ 0
TX
Wire Wire Line
	7700 5400 8250 5400
Wire Wire Line
	7200 5500 6600 5500
Wire Wire Line
	7200 5200 7200 5400
$Comp
L power:GND #PWR09
U 1 1 5EF42E83
P 5600 1900
F 0 "#PWR09" H 5600 1650 50  0001 C CNN
F 1 "GND" H 5605 1727 50  0000 C CNN
F 2 "" H 5600 1900 50  0001 C CNN
F 3 "" H 5600 1900 50  0001 C CNN
	1    5600 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 1700 5600 1700
Wire Wire Line
	6550 1600 6400 1600
Wire Wire Line
	6400 1600 6400 1450
$Comp
L Device:C_Small C7
U 1 1 5EF64226
P 5600 1800
F 0 "C7" H 5692 1846 50  0000 L CNN
F 1 "1u" H 5692 1755 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5600 1800 50  0001 C CNN
F 3 "https://cdn-reichelt.de/documents/datenblatt/B300/KEM_C0XXX_X5R_DB-EN.pdf" H 5600 1800 50  0001 C CNN
F 4 "0,07" H 5600 1800 50  0001 C CNN "Preis"
F 5 "https://de.aliexpress.com/item/4000923964703.html" H 5600 1800 50  0001 C CNN "Reichelt"
F 6 "Reichelt" H 5600 1800 50  0001 C CNN "Lieferant"
F 7 "https://www.reichelt.de/vielschicht-kerko-1-0-f-25v-85-c-kem-x5r0805-1-0u-p207085.html" H 5600 1800 50  0001 C CNN "Link"
	1    5600 1800
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x06_Odd_Even J8
U 1 1 5EF659CC
P 7400 5600
F 0 "J8" H 7450 5900 50  0000 C CNN
F 1 "Conn_02x06_Odd_Even" H 7500 5150 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x06_P2.54mm_Vertical" H 7400 5600 50  0001 C CNN
F 3 "~" H 7400 5600 50  0001 C CNN
	1    7400 5600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 5200 7200 5200
NoConn ~ 6550 2300
Text Label 8400 1800 0    50   ~ 0
RX
Wire Wire Line
	8050 1700 8400 1700
Wire Wire Line
	8050 1800 8400 1800
Wire Wire Line
	8250 1450 8150 1450
Wire Wire Line
	8150 1600 8050 1600
$Comp
L power:GND #PWR0108
U 1 1 5ED47EF1
P 8250 1450
F 0 "#PWR0108" H 8250 1200 50  0001 C CNN
F 1 "GND" H 8255 1277 50  0000 C CNN
F 2 "" H 8250 1450 50  0001 C CNN
F 3 "" H 8250 1450 50  0001 C CNN
	1    8250 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	8150 1450 8150 1600
Text Label 7700 5600 0    50   ~ 0
RX
$Comp
L power:+3.3V #PWR0112
U 1 1 5ED51D32
P 8200 2800
F 0 "#PWR0112" H 8200 2650 50  0001 C CNN
F 1 "+3.3V" V 8215 2928 50  0000 L CNN
F 2 "" H 8200 2800 50  0001 C CNN
F 3 "" H 8200 2800 50  0001 C CNN
	1    8200 2800
	0    1    1    0   
$EndComp
NoConn ~ 8050 2900
Text Label 7700 5500 0    50   ~ 0
GND_Switched
$Comp
L power:+3.3V #PWR0126
U 1 1 5F15B0EE
P 1800 4900
F 0 "#PWR0126" H 1800 4750 50  0001 C CNN
F 1 "+3.3V" H 1815 5073 50  0000 C CNN
F 2 "" H 1800 4900 50  0001 C CNN
F 3 "" H 1800 4900 50  0001 C CNN
	1    1800 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 4900 1800 5150
$EndSCHEMATC