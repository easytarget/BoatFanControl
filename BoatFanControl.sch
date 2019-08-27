EESchema Schematic File Version 4
LIBS:BoatFanControl-cache
EELAYER 30 0
EELAYER END
$Descr User 7874 5906
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
L power:+BATT #PWR06
U 1 1 5D59BE04
P 5200 2150
F 0 "#PWR06" H 5200 2000 50  0001 C CNN
F 1 "+BATT" V 5215 2277 50  0000 L CNN
F 2 "" H 5200 2150 50  0001 C CNN
F 3 "" H 5200 2150 50  0001 C CNN
	1    5200 2150
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR07
U 1 1 5D59C261
P 5700 3100
F 0 "#PWR07" H 5700 2850 50  0001 C CNN
F 1 "GND" H 5705 2927 50  0000 C CNN
F 2 "" H 5700 3100 50  0001 C CNN
F 3 "" H 5700 3100 50  0001 C CNN
	1    5700 3100
	1    0    0    -1  
$EndComp
NoConn ~ 5300 2350
$Comp
L power:+BATT #PWR03
U 1 1 5D59FB25
P 2350 1150
F 0 "#PWR03" H 2350 1000 50  0001 C CNN
F 1 "+BATT" V 2365 1278 50  0000 L CNN
F 2 "" H 2350 1150 50  0001 C CNN
F 3 "" H 2350 1150 50  0001 C CNN
	1    2350 1150
	0    1    1    0   
$EndComp
$Comp
L Diode:1N4007 D1
U 1 1 5D5A1A0C
P 2100 1150
F 0 "D1" H 2100 934 50  0000 C CNN
F 1 "1N4007" H 2100 1025 50  0000 C CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 2100 975 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 2100 1150 50  0001 C CNN
	1    2100 1150
	-1   0    0    1   
$EndComp
Wire Wire Line
	5200 2150 5200 2350
Wire Wire Line
	5550 3100 5700 3100
$Comp
L power:GND #PWR01
U 1 1 5D5A3EF7
P 1550 1450
F 0 "#PWR01" H 1550 1200 50  0001 C CNN
F 1 "GND" H 1555 1277 50  0000 C CNN
F 2 "" H 1550 1450 50  0001 C CNN
F 3 "" H 1550 1450 50  0001 C CNN
	1    1550 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 1450 1550 1450
Text GLabel 1300 2100 0    50   Input ~ 0
Vin
$Comp
L Device:R R1
U 1 1 5D5A4BFD
P 1700 2300
F 0 "R1" H 1770 2346 50  0000 L CNN
F 1 "10K" H 1770 2255 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 1630 2300 50  0001 C CNN
F 3 "~" H 1700 2300 50  0001 C CNN
	1    1700 2300
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5D5A53AE
P 1700 2750
F 0 "R2" H 1770 2796 50  0000 L CNN
F 1 "100R" H 1770 2705 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 1630 2750 50  0001 C CNN
F 3 "~" H 1700 2750 50  0001 C CNN
	1    1700 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 2100 1700 2100
Wire Wire Line
	1700 2100 1700 2150
$Comp
L power:GND #PWR02
U 1 1 5D5A5B52
P 1700 3050
F 0 "#PWR02" H 1700 2800 50  0001 C CNN
F 1 "GND" H 1705 2877 50  0000 C CNN
F 2 "" H 1700 3050 50  0001 C CNN
F 3 "" H 1700 3050 50  0001 C CNN
	1    1700 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 2900 1700 3050
Wire Wire Line
	1700 2450 1700 2550
Text GLabel 1850 2550 2    50   Output ~ 0
Vin-sense
Wire Wire Line
	1850 2550 1700 2550
Connection ~ 1700 2550
Wire Wire Line
	1700 2550 1700 2600
Text GLabel 4300 2800 0    50   Input ~ 0
Vin-sense
NoConn ~ 4550 3100
Text GLabel 1400 1350 2    50   Output ~ 0
FAN-gnd
Text GLabel 1400 1250 2    50   BiDi ~ 0
DHT11
Text GLabel 3950 1100 0    50   Input ~ 0
LED
$Comp
L Transistor_FET:IRLIZ44N Q1
U 1 1 5D5A8AD6
P 4900 1100
F 0 "Q1" H 5106 1146 50  0000 L CNN
F 1 "IRLIZ44N" H 5106 1055 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220F-3_Horizontal_TabDown" H 5150 1025 50  0001 L CIN
F 3 "http://www.irf.com/product-info/datasheets/data/irliz44n.pdf" H 4900 1100 50  0001 L CNN
	1    4900 1100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 5D5A9882
P 4350 1100
F 0 "R3" V 4550 1100 50  0000 C CNN
F 1 "220R" V 4450 1100 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P5.08mm_Vertical" V 4280 1100 50  0001 C CNN
F 3 "~" H 4350 1100 50  0001 C CNN
	1    4350 1100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3950 1100 4200 1100
Wire Wire Line
	4500 1100 4550 1100
$Comp
L power:GND #PWR05
U 1 1 5D5AA0DC
P 4800 1700
F 0 "#PWR05" H 4800 1450 50  0001 C CNN
F 1 "GND" H 4805 1527 50  0000 C CNN
F 2 "" H 4800 1700 50  0001 C CNN
F 3 "" H 4800 1700 50  0001 C CNN
	1    4800 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 1300 5000 1600
Text GLabel 5250 750  2    50   Output ~ 0
FAN-gnd
Wire Wire Line
	5000 900  5000 750 
Wire Wire Line
	5000 750  5250 750 
Text GLabel 4300 2600 0    50   Output ~ 0
LED
$Comp
L Switch:SW_Push SW1
U 1 1 5D5AB785
P 3150 2700
F 0 "SW1" V 3196 2652 50  0000 R CNN
F 1 "SW_Push" V 3105 2652 50  0000 R CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm" H 3150 2900 50  0001 C CNN
F 3 "~" H 3150 2900 50  0001 C CNN
	1    3150 2700
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR04
U 1 1 5D5AD0E1
P 3150 3050
F 0 "#PWR04" H 3150 2800 50  0001 C CNN
F 1 "GND" H 3155 2877 50  0000 C CNN
F 2 "" H 3150 3050 50  0001 C CNN
F 3 "" H 3150 3050 50  0001 C CNN
	1    3150 3050
	1    0    0    -1  
$EndComp
Text GLabel 3000 2300 0    50   Input ~ 0
button
Text GLabel 4300 2900 0    50   Input ~ 0
button
Wire Wire Line
	3000 2300 3150 2300
Wire Wire Line
	3150 2300 3150 2500
Wire Wire Line
	3150 2900 3150 3050
Wire Wire Line
	4300 2600 4550 2600
Wire Wire Line
	4300 2800 4550 2800
Wire Wire Line
	4300 2900 4550 2900
NoConn ~ 4550 3000
$Comp
L Mechanical:MountingHole H1
U 1 1 5D5C84B3
P 6650 3700
F 0 "H1" H 6750 3746 50  0000 L CNN
F 1 "MountingHole" H 6750 3655 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 6650 3700 50  0001 C CNN
F 3 "~" H 6650 3700 50  0001 C CNN
	1    6650 3700
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 5D5C8A88
P 6650 3950
F 0 "H2" H 6750 3996 50  0000 L CNN
F 1 "MountingHole" H 6750 3905 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 6650 3950 50  0001 C CNN
F 3 "~" H 6650 3950 50  0001 C CNN
	1    6650 3950
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 5D655ED0
P 4550 1350
F 0 "R4" H 4620 1396 50  0000 L CNN
F 1 "10K" H 4620 1305 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P5.08mm_Vertical" V 4480 1350 50  0001 C CNN
F 3 "~" H 4550 1350 50  0001 C CNN
	1    4550 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 1200 4550 1100
Connection ~ 4550 1100
Wire Wire Line
	4550 1100 4700 1100
Wire Wire Line
	4550 1500 4550 1600
Wire Wire Line
	4550 1600 4800 1600
Wire Wire Line
	4800 1700 4800 1600
Connection ~ 4800 1600
Wire Wire Line
	4800 1600 5000 1600
Text GLabel 4300 2700 0    50   BiDi ~ 0
DHT11
Wire Wire Line
	4550 2700 4300 2700
$Comp
L SW-Digistump:Digispark U1
U 1 1 5D599E15
P 5050 2850
F 0 "U1" H 5050 2469 60  0000 C CNN
F 1 "Digispark" H 5050 2363 60  0000 C CNN
F 2 "digi:Digispark" H 5100 3950 60  0001 C CNN
F 3 "" H 5350 2850 60  0001 C CNN
F 4 "0.00@0" H 5100 4050 60  0001 C CNN "Pricing"
F 5 "Digispark Microcontroller" H 5200 3800 60  0001 C CNN "Description"
F 6 "Digistump" H 5050 3900 60  0001 C CNN "Manufacturer"
	1    5050 2850
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J1
U 1 1 5D59DE5B
P 1200 1350
F 0 "J1" H 1118 925 50  0000 C CNN
F 1 "Conn_01x04" H 1118 1016 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x04_P5.08mm_Drill1.5mm" H 1200 1350 50  0001 C CNN
F 3 "~" H 1200 1350 50  0001 C CNN
	1    1200 1350
	-1   0    0    1   
$EndComp
Text GLabel 1650 1050 2    50   Input ~ 0
Vin
Wire Wire Line
	1400 1150 1600 1150
Wire Wire Line
	1650 1050 1600 1050
Wire Wire Line
	1600 1050 1600 1150
Wire Wire Line
	2250 1150 2350 1150
Wire Wire Line
	1950 1150 1600 1150
Connection ~ 1600 1150
$EndSCHEMATC
