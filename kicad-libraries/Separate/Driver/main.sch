EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr User 15748 13780
encoding utf-8
Sheet 1 1
Title "Spectrometer Full System"
Date "2021-06-02"
Rev "2.2"
Comp "Team Spectrometer"
Comment1 "0:uC, 1:Bt, 2+3:IR, 4:TIA, 5:Pwr"
Comment2 "First digit in reference value indicates subsection"
Comment3 "All bypass capacitors currenty use mfg. suggested values"
Comment4 "Most current revision listed below; specific subsection revisions written in respective notes"
$EndDescr
$Comp
L power:+5V #PWR0116
U 1 1 60B3B158
P 3400 9350
F 0 "#PWR0116" H 3400 9200 50  0001 C CNN
F 1 "+5V" H 3415 9523 50  0000 C CNN
F 2 "" H 3400 9350 50  0001 C CNN
F 3 "" H 3400 9350 50  0001 C CNN
	1    3400 9350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 9550 4600 9550
Wire Wire Line
	4600 9550 4600 9750
Connection ~ 4600 9750
Wire Wire Line
	4600 9750 4600 9900
$Comp
L Device:C C21
U 1 1 60B4EDBC
P 3200 10350
F 0 "C21" H 3300 10400 50  0000 L CNN
F 1 "2n2" H 3300 10300 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 3238 10200 50  0001 C CNN
F 3 "~" H 3200 10350 50  0001 C CNN
	1    3200 10350
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR0117
U 1 1 60B60307
P 3200 10650
F 0 "#PWR0117" H 3200 10400 50  0001 C CNN
F 1 "GND" H 3205 10477 50  0000 C CNN
F 2 "" H 3200 10650 50  0001 C CNN
F 3 "" H 3200 10650 50  0001 C CNN
	1    3200 10650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0118
U 1 1 60B612B5
P 3550 10650
F 0 "#PWR0118" H 3550 10400 50  0001 C CNN
F 1 "GND" H 3555 10477 50  0000 C CNN
F 2 "" H 3550 10650 50  0001 C CNN
F 3 "" H 3550 10650 50  0001 C CNN
	1    3550 10650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 10500 3200 10650
$Comp
L power:GND #PWR0119
U 1 1 60B6AA18
P 4600 10650
F 0 "#PWR0119" H 4600 10400 50  0001 C CNN
F 1 "GND" H 4605 10477 50  0000 C CNN
F 2 "" H 4600 10650 50  0001 C CNN
F 3 "" H 4600 10650 50  0001 C CNN
	1    4600 10650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 10600 4600 10650
Wire Wire Line
	3200 10050 3200 10200
Connection ~ 3400 9550
Wire Wire Line
	3400 9350 3400 9550
Wire Wire Line
	3400 9550 3400 9750
$Comp
L Device:R_US R20
U 1 1 60BE92E2
P 4000 9550
F 0 "R20" V 4205 9550 50  0000 C CNN
F 1 "0R133" V 4114 9550 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3930 9550 50  0001 C CNN
F 3 "~" H 4000 9550 50  0001 C CNN
	1    4000 9550
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R33
U 1 1 60BEEDAC
P 4600 10450
F 0 "R33" H 4668 10496 50  0000 L CNN
F 1 "0R233" H 4668 10405 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4530 10450 50  0001 C CNN
F 3 "~" H 4600 10450 50  0001 C CNN
	1    4600 10450
	1    0    0    -1  
$EndComp
$Comp
L Device:L L20
U 1 1 60D19639
P 5650 10050
F 0 "L20" V 5950 10050 50  0000 C CNN
F 1 "1200u" V 5850 10050 50  0000 C CNN
F 2 "spectrometer_core:1130-122K-RC" H 5650 10050 50  0001 C CNN
F 3 "https://www.mouser.com/datasheet/2/597/sm_pl_filter-1605720.pdf" H 5650 10050 50  0001 C CNN
F 4 "1130-122K-RC" V 5750 10050 50  0000 C CNN "PN"
	1    5650 10050
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N5819 D20
U 1 1 60D1A583
P 5300 10400
F 0 "D20" V 5200 10500 50  0000 L CNN
F 1 "1N5819" V 5300 10500 50  0000 L CNN
F 2 "Diode_THT:D_DO-41_SOD81_P7.62mm_Horizontal" H 5300 10225 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88525/1n5817.pdf" H 5300 10400 50  0001 C CNN
F 4 "0.45 V" V 5400 10500 50  0000 L CNN "Vf"
	1    5300 10400
	0    1    1    0   
$EndComp
Wire Wire Line
	5300 10050 5300 10250
Connection ~ 5300 10050
Wire Wire Line
	5300 10050 5500 10050
Wire Wire Line
	5800 10050 6000 10050
Wire Wire Line
	6000 10050 6000 10250
Connection ~ 6000 10050
$Comp
L power:GND #PWR0131
U 1 1 60DB999D
P 5300 10650
F 0 "#PWR0131" H 5300 10400 50  0001 C CNN
F 1 "GND" H 5305 10477 50  0000 C CNN
F 2 "" H 5300 10650 50  0001 C CNN
F 3 "" H 5300 10650 50  0001 C CNN
	1    5300 10650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0132
U 1 1 60DB9E32
P 6000 10650
F 0 "#PWR0132" H 6000 10400 50  0001 C CNN
F 1 "GND" H 6005 10477 50  0000 C CNN
F 2 "" H 6000 10650 50  0001 C CNN
F 3 "" H 6000 10650 50  0001 C CNN
	1    6000 10650
	1    0    0    -1  
$EndComp
Text Notes 3450 12050 0    50   ~ 0
Emitter Driver Ver 1.2. \nRevisions from 1.2:\nRemoved schottky flyback\nRevisions from 1.1:\nChanged topology from BJT driver to BJT controlled PNP driver\nAdded flyback schottkey antiparallel to L20\nChanged L20 part\nRemoved zener at end of emitter chain
Wire Wire Line
	6000 10550 6000 10650
Wire Wire Line
	5300 10550 5300 10650
$Comp
L Device:CP1_Small C20
U 1 1 60C2FF3D
P 3200 9550
F 0 "C20" V 2972 9550 50  0000 C CNN
F 1 "10u" V 3063 9550 50  0000 C CNN
F 2 "Capacitor_SMD:CP_Elec_4x3" H 3200 9550 50  0001 C CNN
F 3 "~" H 3200 9550 50  0001 C CNN
	1    3200 9550
	0    1    1    0   
$EndComp
Wire Wire Line
	3400 9550 3300 9550
Wire Wire Line
	3100 9550 3000 9550
$Comp
L power:GND #PWR0135
U 1 1 60BD5E86
P 3000 9550
F 0 "#PWR0135" H 3000 9300 50  0001 C CNN
F 1 "GND" H 3005 9377 50  0000 C CNN
F 2 "" H 3000 9550 50  0001 C CNN
F 3 "" H 3000 9550 50  0001 C CNN
	1    3000 9550
	1    0    0    -1  
$EndComp
$Comp
L Device:CP1 C22
U 1 1 61126947
P 6000 10400
F 0 "C22" H 6115 10446 50  0000 L CNN
F 1 "220u" H 6115 10355 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_6.3x5.9" H 6000 10400 50  0001 C CNN
F 3 "~" H 6000 10400 50  0001 C CNN
	1    6000 10400
	1    0    0    -1  
$EndComp
Text Label 2750 9900 1    50   ~ 0
Scan_PWM
Wire Wire Line
	6000 10050 6300 10050
Text Notes 3450 12200 0    50   ~ 0
Ref values reserved for emitters: 20-39
Wire Wire Line
	2750 9000 2750 9900
Wire Wire Line
	3400 9550 3850 9550
$Comp
L Connector:Conn_01x02_Female J23
U 1 1 612EE80D
P 6500 10050
F 0 "J23" H 6450 9900 50  0000 R CNN
F 1 "C_01x02" H 6500 10200 50  0000 C CNN
F 2 "spectrometer_core:1x02_Vert_P2.00_Molex_Micro-Latch" H 6500 10050 50  0001 C CNN
F 3 "~" H 6500 10050 50  0001 C CNN
	1    6500 10050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2750 9900 3550 9900
Wire Wire Line
	4600 9750 4450 9750
Wire Wire Line
	3400 9750 3550 9750
Wire Wire Line
	3550 10200 3550 10650
Wire Wire Line
	3550 10050 3200 10050
Wire Wire Line
	4450 10050 5300 10050
Wire Wire Line
	4600 9900 4450 9900
$Comp
L spectrometer_core:NCP3066 U20
U 1 1 6093404D
P 4000 10000
F 0 "U20" H 4000 9700 50  0000 C CNN
F 1 "NCP3066" H 4000 9600 50  0000 C CNN
F 2 "spectrometer_core:SOIC-8" H 4000 9575 50  0001 C CNN
F 3 "https://www.onsemi.com/pdf/datasheet/ncp3066-d.pdf" H 4000 10075 50  0001 C CNN
F 4 "Constant current buck LED driver" H 4000 9050 50  0000 C CNN "Desc"
	1    4000 10000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 10200 4600 10300
Connection ~ 4600 10200
Wire Wire Line
	4600 10200 6300 10200
Wire Wire Line
	4450 10200 4600 10200
Wire Wire Line
	6300 10200 6300 10150
Wire Wire Line
	2750 9000 5800 9000
Wire Wire Line
	5800 4700 6600 4700
Wire Wire Line
	5800 4700 5800 9000
Wire Wire Line
	6550 4800 6550 4900
Wire Wire Line
	6600 4800 6550 4800
$Comp
L power:GND #PWR0143
U 1 1 611B9819
P 6550 4900
F 0 "#PWR0143" H 6550 4650 50  0001 C CNN
F 1 "GND" H 6450 4800 50  0000 C CNN
F 2 "" H 6550 4900 50  0001 C CNN
F 3 "" H 6550 4900 50  0001 C CNN
	1    6550 4900
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0142
U 1 1 60F9B99F
P 6550 4550
F 0 "#PWR0142" H 6550 4400 50  0001 C CNN
F 1 "+5V" H 6565 4723 50  0000 C CNN
F 2 "" H 6550 4550 50  0001 C CNN
F 3 "" H 6550 4550 50  0001 C CNN
	1    6550 4550
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Female J20
U 1 1 60F2CC0E
P 6800 4700
F 0 "J20" H 6600 4550 50  0000 L CNN
F 1 "C_01x03" H 6800 4450 50  0000 C CNN
F 2 "spectrometer_core:1x03_Vert_P2.00_Molex_Micro-Latch" H 6800 4700 50  0001 C CNN
F 3 "~" H 6800 4700 50  0001 C CNN
	1    6800 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 4600 6600 4600
Wire Wire Line
	6550 4550 6550 4600
Text Label 6150 4700 0    50   ~ 0
Scan_PWM
$EndSCHEMATC
