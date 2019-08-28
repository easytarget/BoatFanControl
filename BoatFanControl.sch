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
P 4500 2450
F 0 "#PWR06" H 4500 2300 50  0001 C CNN
F 1 "+BATT" V 4515 2577 50  0000 L CNN
F 2 "" H 4500 2450 50  0001 C CNN
F 3 "" H 4500 2450 50  0001 C CNN
	1    4500 2450
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR07
U 1 1 5D59C261
P 5000 3400
F 0 "#PWR07" H 5000 3150 50  0001 C CNN
F 1 "GND" H 5005 3227 50  0000 C CNN
F 2 "" H 5000 3400 50  0001 C CNN
F 3 "" H 5000 3400 50  0001 C CNN
	1    5000 3400
	1    0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR03
U 1 1 5D59FB25
P 2350 950
F 0 "#PWR03" H 2350 800 50  0001 C CNN
F 1 "+BATT" V 2365 1078 50  0000 L CNN
F 2 "" H 2350 950 50  0001 C CNN
F 3 "" H 2350 950 50  0001 C CNN
	1    2350 950 
	0    1    1    0   
$EndComp
$Comp
L Diode:1N4007 D1
U 1 1 5D5A1A0C
P 2100 950
F 0 "D1" H 2100 734 50  0000 C CNN
F 1 "1N4007" H 2100 825 50  0000 C CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 2100 775 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 2100 950 50  0001 C CNN
	1    2100 950 
	-1   0    0    1   
$EndComp
Wire Wire Line
	4500 2450 4500 2650
Wire Wire Line
	4850 3400 5000 3400
$Comp
L power:GND #PWR01
U 1 1 5D5A3EF7
P 1550 1150
F 0 "#PWR01" H 1550 900 50  0001 C CNN
F 1 "GND" H 1555 977 50  0000 C CNN
F 2 "" H 1550 1150 50  0001 C CNN
F 3 "" H 1550 1150 50  0001 C CNN
	1    1550 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 1150 1550 1150
Text GLabel 5750 2200 0    50   Input ~ 0
Vin
$Comp
L Device:R R1
U 1 1 5D5A4BFD
P 6150 2400
F 0 "R1" H 6220 2446 50  0000 L CNN
F 1 "10K" H 6220 2355 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 6080 2400 50  0001 C CNN
F 3 "~" H 6150 2400 50  0001 C CNN
	1    6150 2400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5D5A53AE
P 6150 2850
F 0 "R2" H 6220 2896 50  0000 L CNN
F 1 "1K" H 6220 2805 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 6080 2850 50  0001 C CNN
F 3 "~" H 6150 2850 50  0001 C CNN
	1    6150 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 2200 6150 2200
Wire Wire Line
	6150 2200 6150 2250
$Comp
L power:GND #PWR02
U 1 1 5D5A5B52
P 6150 3150
F 0 "#PWR02" H 6150 2900 50  0001 C CNN
F 1 "GND" H 6155 2977 50  0000 C CNN
F 2 "" H 6150 3150 50  0001 C CNN
F 3 "" H 6150 3150 50  0001 C CNN
	1    6150 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 3000 6150 3150
Wire Wire Line
	6150 2550 6150 2650
Text GLabel 6300 2650 2    50   Output ~ 0
Vin-sense
Wire Wire Line
	6300 2650 6150 2650
Connection ~ 6150 2650
Wire Wire Line
	6150 2650 6150 2700
Text GLabel 3600 3100 0    50   Input ~ 0
Vin-sense
Text GLabel 1550 1050 2    50   Output ~ 0
FAN-gnd
Text GLabel 3400 1200 0    50   Input ~ 0
LED
$Comp
L Transistor_FET:IRLIZ44N Q1
U 1 1 5D5A8AD6
P 4350 1200
F 0 "Q1" H 4556 1246 50  0000 L CNN
F 1 "IRLZ14" H 4556 1155 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220F-3_Horizontal_TabDown" H 4600 1125 50  0001 L CIN
F 3 "http://www.irf.com/product-info/datasheets/data/irliz44n.pdf" H 4350 1200 50  0001 L CNN
	1    4350 1200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 5D5A9882
P 3800 1200
F 0 "R3" V 4000 1200 50  0000 C CNN
F 1 "220R" V 3900 1200 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P5.08mm_Vertical" V 3730 1200 50  0001 C CNN
F 3 "~" H 3800 1200 50  0001 C CNN
	1    3800 1200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3400 1200 3650 1200
Wire Wire Line
	3950 1200 4000 1200
$Comp
L power:GND #PWR05
U 1 1 5D5AA0DC
P 4250 1800
F 0 "#PWR05" H 4250 1550 50  0001 C CNN
F 1 "GND" H 4255 1627 50  0000 C CNN
F 2 "" H 4250 1800 50  0001 C CNN
F 3 "" H 4250 1800 50  0001 C CNN
	1    4250 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 1400 4450 1700
Text GLabel 4700 850  2    50   Output ~ 0
FAN-gnd
Wire Wire Line
	4450 1000 4450 850 
Wire Wire Line
	4450 850  4700 850 
Text GLabel 3600 2900 0    50   Output ~ 0
LED
$Comp
L Switch:SW_Push SW1
U 1 1 5D5AB785
P 6050 1300
F 0 "SW1" V 6096 1252 50  0000 R CNN
F 1 "SW_Push" V 6005 1252 50  0000 R CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm" H 6050 1500 50  0001 C CNN
F 3 "~" H 6050 1500 50  0001 C CNN
	1    6050 1300
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR04
U 1 1 5D5AD0E1
P 6050 1650
F 0 "#PWR04" H 6050 1400 50  0001 C CNN
F 1 "GND" H 6055 1477 50  0000 C CNN
F 2 "" H 6050 1650 50  0001 C CNN
F 3 "" H 6050 1650 50  0001 C CNN
	1    6050 1650
	1    0    0    -1  
$EndComp
Text GLabel 5900 900  0    50   Input ~ 0
button
Text GLabel 3600 3200 0    50   Input ~ 0
button
Wire Wire Line
	5900 900  6050 900 
Wire Wire Line
	6050 900  6050 1100
Wire Wire Line
	6050 1500 6050 1650
Wire Wire Line
	3600 2900 3850 2900
Wire Wire Line
	3600 3100 3850 3100
Wire Wire Line
	3600 3200 3850 3200
NoConn ~ 3850 3300
$Comp
L Mechanical:MountingHole H1
U 1 1 5D5C84B3
P 2350 4900
F 0 "H1" H 2450 4946 50  0000 L CNN
F 1 "MountingHole" H 2450 4855 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 2350 4900 50  0001 C CNN
F 3 "~" H 2350 4900 50  0001 C CNN
	1    2350 4900
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 5D5C8A88
P 2350 5150
F 0 "H2" H 2450 5196 50  0000 L CNN
F 1 "MountingHole" H 2450 5105 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 2350 5150 50  0001 C CNN
F 3 "~" H 2350 5150 50  0001 C CNN
	1    2350 5150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 5D655ED0
P 4000 1450
F 0 "R4" H 4070 1496 50  0000 L CNN
F 1 "10K" H 4070 1405 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P5.08mm_Vertical" V 3930 1450 50  0001 C CNN
F 3 "~" H 4000 1450 50  0001 C CNN
	1    4000 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 1300 4000 1200
Connection ~ 4000 1200
Wire Wire Line
	4000 1200 4150 1200
Wire Wire Line
	4000 1600 4000 1700
Wire Wire Line
	4000 1700 4250 1700
Wire Wire Line
	4250 1800 4250 1700
Connection ~ 4250 1700
Wire Wire Line
	4250 1700 4450 1700
Text GLabel 3600 3000 0    50   BiDi ~ 0
DHT11
Wire Wire Line
	3850 3000 3600 3000
$Comp
L SW-Digistump:Digispark U1
U 1 1 5D599E15
P 4350 3150
F 0 "U1" H 4350 2769 60  0000 C CNN
F 1 "Digispark" H 4350 2663 60  0000 C CNN
F 2 "digi:Digispark" H 4400 4250 60  0001 C CNN
F 3 "" H 4650 3150 60  0001 C CNN
F 4 "0.00@0" H 4400 4350 60  0001 C CNN "Pricing"
F 5 "Digispark Microcontroller" H 4500 4100 60  0001 C CNN "Description"
F 6 "Digistump" H 4350 4200 60  0001 C CNN "Manufacturer"
	1    4350 3150
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x03 J1
U 1 1 5D59DE5B
P 1200 1050
F 0 "J1" H 1200 700 50  0000 C CNN
F 1 "Batt" H 1200 800 50  0000 C CNN
F 2 "TerminalBlock_MetzConnect:TerminalBlock_MetzConnect_Type073_RT02603HBLU_1x03_P5.08mm_Horizontal" H 1200 1050 50  0001 C CNN
F 3 "~" H 1200 1050 50  0001 C CNN
	1    1200 1050
	-1   0    0    1   
$EndComp
Text GLabel 1650 850  2    50   Input ~ 0
Vin
Wire Wire Line
	1400 950  1600 950 
Wire Wire Line
	1650 850  1600 850 
Wire Wire Line
	1600 850  1600 950 
Wire Wire Line
	2250 950  2350 950 
Wire Wire Line
	1950 950  1600 950 
Connection ~ 1600 950 
$Comp
L power:+5V #PWR0101
U 1 1 5D662260
P 4600 2450
F 0 "#PWR0101" H 4600 2300 50  0001 C CNN
F 1 "+5V" V 4615 2578 50  0000 L CNN
F 2 "" H 4600 2450 50  0001 C CNN
F 3 "" H 4600 2450 50  0001 C CNN
	1    4600 2450
	0    1    1    0   
$EndComp
Wire Wire Line
	4600 2650 4600 2450
Wire Wire Line
	1400 1050 1550 1050
$Comp
L power:+5V #PWR0103
U 1 1 5D66C79F
P 1550 2800
F 0 "#PWR0103" H 1550 2650 50  0001 C CNN
F 1 "+5V" H 1450 3000 50  0000 L CNN
F 2 "" H 1550 2800 50  0001 C CNN
F 3 "" H 1550 2800 50  0001 C CNN
	1    1550 2800
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 5D66D2B4
P 1750 2800
F 0 "#PWR0104" H 1750 2550 50  0001 C CNN
F 1 "GND" H 1755 2627 50  0000 C CNN
F 2 "" H 1750 2800 50  0001 C CNN
F 3 "" H 1750 2800 50  0001 C CNN
	1    1750 2800
	0    -1   1    0   
$EndComp
Wire Wire Line
	1750 2750 1750 2800
Wire Wire Line
	1650 2750 1650 3000
Wire Wire Line
	1550 2800 1550 2750
$Comp
L sensors:DHT11_Temperature_Humidity_II TH1
U 1 1 5D665FCE
P 1650 2750
F 0 "TH1" H 2000 3400 60  0000 L CNN
F 1 "DHT11" H 1950 3250 60  0000 L CNN
F 2 "sensors:DHT11_Temperature_Humidity" H 1750 4050 60  0001 C CNN
F 3 "" H 1650 2750 60  0000 C CNN
	1    1650 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 3000 1800 3000
Text GLabel 1800 3000 2    50   BiDi ~ 0
DHT11
Text GLabel 3600 3400 0    50   Input ~ 0
Reset
Wire Wire Line
	3600 3400 3850 3400
Text GLabel 2000 3700 2    50   Input ~ 0
Reset
$Comp
L Connector_Generic:Conn_01x01 J2
U 1 1 5D666371
P 1650 3700
F 0 "J2" H 1568 3475 50  0000 C CNN
F 1 "Reset" H 1568 3566 50  0000 C CNN
F 2 "Connector_PinHeader_1.00mm:PinHeader_1x01_P1.00mm_Vertical" H 1650 3700 50  0001 C CNN
F 3 "~" H 1650 3700 50  0001 C CNN
	1    1650 3700
	-1   0    0    1   
$EndComp
Wire Wire Line
	1850 3700 2000 3700
$EndSCHEMATC
