EESchema Schematic File Version 4
EELAYER 29 0
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
$Comp
L spectrometer_core:LMS33460 U1
U 1 1 609F7D65
P 5600 3300
F 0 "U1" H 5600 3050 50  0000 C CNN
F 1 "LMS33460" H 5600 2950 50  0000 C CNN
F 2 "spectrometer_core:SC70" H 5600 2950 50  0001 C CNN
F 3 "https://www.ti.com/lit/ds/symlink/lms33460.pdf" H 5600 3100 50  0001 C CNN
F 4 "3V undervoltage detector" H 5600 2850 50  0000 C CNN "Desc"
	1    5600 3300
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J2
U 1 1 609FD282
P 4650 3400
F 0 "J2" H 4568 3717 50  0000 C CNN
F 1 "Conn_01x03" H 4568 3626 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 4650 3400 50  0001 C CNN
F 3 "~" H 4650 3400 50  0001 C CNN
	1    4650 3400
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J1
U 1 1 609FDE39
P 6600 3100
F 0 "J1" H 6518 2775 50  0000 C CNN
F 1 "Conn_01x03" H 6518 2866 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 6600 3100 50  0001 C CNN
F 3 "~" H 6600 3100 50  0001 C CNN
	1    6600 3100
	1    0    0    1   
$EndComp
Wire Wire Line
	5300 3000 6400 3000
Wire Wire Line
	5300 3000 5300 3200
Wire Wire Line
	5900 3200 6400 3200
NoConn ~ 6400 3100
Wire Wire Line
	5300 3350 5050 3350
Wire Wire Line
	5050 3350 5050 3300
Wire Wire Line
	5050 3300 4850 3300
Wire Wire Line
	5300 3450 5050 3450
Wire Wire Line
	5050 3450 5050 3500
Wire Wire Line
	5050 3500 4850 3500
NoConn ~ 4850 3400
$EndSCHEMATC
