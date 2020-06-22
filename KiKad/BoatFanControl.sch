EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr User 7874 5906
encoding utf-8
Sheet 1 1
Title "DigiSpark Fan Controller for Boats"
Date "2020-06-22"
Rev "1.0"
Comp "Owen Carter"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:GND #PWR07
U 1 1 5D59C261
P 4950 3650
F 0 "#PWR07" H 4950 3400 50  0001 C CNN
F 1 "GND" H 4955 3477 50  0000 C CNN
F 2 "" H 4950 3650 50  0001 C CNN
F 3 "" H 4950 3650 50  0001 C CNN
	1    4950 3650
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4007 D1
U 1 1 5D5A1A0C
P 2100 2700
F 0 "D1" H 2100 2484 50  0000 C CNN
F 1 "1N4007" H 2100 2575 50  0000 C CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 2100 2525 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 2100 2700 50  0001 C CNN
	1    2100 2700
	-1   0    0    1   
$EndComp
Wire Wire Line
	4450 2700 4450 2900
Wire Wire Line
	4800 3650 4950 3650
$Comp
L power:GND #PWR01
U 1 1 5D5A3EF7
P 1550 2900
F 0 "#PWR01" H 1550 2650 50  0001 C CNN
F 1 "GND" H 1555 2727 50  0000 C CNN
F 2 "" H 1550 2900 50  0001 C CNN
F 3 "" H 1550 2900 50  0001 C CNN
	1    1550 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 2900 1550 2900
Text GLabel 5750 2200 0    50   Input ~ 0
Vbatt
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
Vsense
Wire Wire Line
	6300 2650 6150 2650
Connection ~ 6150 2650
Wire Wire Line
	6150 2650 6150 2700
Text GLabel 3550 3350 0    50   Input ~ 0
Vsense
Text GLabel 1550 2800 2    50   Output ~ 0
FAN-GND
Text GLabel 3400 1550 0    50   Input ~ 0
fan-pwm
$Comp
L Transistor_FET:IRLIZ44N Q1
U 1 1 5D5A8AD6
P 4350 1550
F 0 "Q1" H 4556 1596 50  0000 L CNN
F 1 "IRLZ14" H 4556 1505 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220F-3_Horizontal_TabDown" H 4600 1475 50  0001 L CIN
F 3 "http://www.irf.com/product-info/datasheets/data/irliz44n.pdf" H 4350 1550 50  0001 L CNN
	1    4350 1550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 5D5A9882
P 3800 1550
F 0 "R3" V 4000 1550 50  0000 C CNN
F 1 "220R" V 3900 1550 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3730 1550 50  0001 C CNN
F 3 "~" H 3800 1550 50  0001 C CNN
	1    3800 1550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3400 1550 3650 1550
Wire Wire Line
	3950 1550 4000 1550
$Comp
L power:GND #PWR05
U 1 1 5D5AA0DC
P 4250 2150
F 0 "#PWR05" H 4250 1900 50  0001 C CNN
F 1 "GND" H 4255 1977 50  0000 C CNN
F 2 "" H 4250 2150 50  0001 C CNN
F 3 "" H 4250 2150 50  0001 C CNN
	1    4250 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 1750 4450 2050
Text GLabel 4700 1200 2    50   Output ~ 0
FAN-GND
Wire Wire Line
	4450 1350 4450 1200
Wire Wire Line
	4450 1200 4700 1200
Text GLabel 3550 3150 0    50   Output ~ 0
fan-pwm
$Comp
L Switch:SW_Push SW1
U 1 1 5D5AB785
P 6150 1350
F 0 "SW1" V 6196 1302 50  0000 R CNN
F 1 "SW_Push" V 6105 1302 50  0000 R CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm" H 6150 1550 50  0001 C CNN
F 3 "~" H 6150 1550 50  0001 C CNN
	1    6150 1350
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR04
U 1 1 5D5AD0E1
P 6150 1700
F 0 "#PWR04" H 6150 1450 50  0001 C CNN
F 1 "GND" H 6155 1527 50  0000 C CNN
F 2 "" H 6150 1700 50  0001 C CNN
F 3 "" H 6150 1700 50  0001 C CNN
	1    6150 1700
	1    0    0    -1  
$EndComp
Text GLabel 6300 1000 2    50   Output ~ 0
button
Text GLabel 3550 3450 0    50   Input ~ 0
button
Wire Wire Line
	6300 1000 6150 1000
Wire Wire Line
	6150 1000 6150 1150
Wire Wire Line
	6150 1550 6150 1700
Wire Wire Line
	3550 3150 3800 3150
Wire Wire Line
	3550 3350 3800 3350
Wire Wire Line
	3550 3450 3800 3450
NoConn ~ 3800 3550
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
P 4000 1800
F 0 "R4" H 4070 1846 50  0000 L CNN
F 1 "10K" H 4070 1755 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3930 1800 50  0001 C CNN
F 3 "~" H 4000 1800 50  0001 C CNN
	1    4000 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 1650 4000 1550
Connection ~ 4000 1550
Wire Wire Line
	4000 1550 4150 1550
Wire Wire Line
	4000 1950 4000 2050
Wire Wire Line
	4000 2050 4250 2050
Wire Wire Line
	4250 2150 4250 2050
Connection ~ 4250 2050
Wire Wire Line
	4250 2050 4450 2050
Text GLabel 3550 3250 0    50   BiDi ~ 0
DHT11
Wire Wire Line
	3800 3250 3550 3250
$Comp
L mcuz:Digispark U1
U 1 1 5D599E15
P 4300 3400
F 0 "U1" H 4300 3019 60  0000 C CNN
F 1 "Digispark" H 4300 2913 60  0000 C CNN
F 2 "mcuz:Digispark" H 4350 4500 60  0001 C CNN
F 3 "" H 4600 3400 60  0001 C CNN
F 4 "0.00@0" H 4350 4600 60  0001 C CNN "Pricing"
F 5 "Digispark Microcontroller" H 4450 4350 60  0001 C CNN "Description"
F 6 "Digistump" H 4300 4450 60  0001 C CNN "Manufacturer"
	1    4300 3400
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x03 J1
U 1 1 5D59DE5B
P 1200 2800
F 0 "J1" H 1200 2450 50  0000 C CNN
F 1 "Batt" H 1200 2550 50  0000 C CNN
F 2 "TerminalBlock_MetzConnect:TerminalBlock_MetzConnect_Type073_RT02603HBLU_1x03_P5.08mm_Horizontal" H 1200 2800 50  0001 C CNN
F 3 "~" H 1200 2800 50  0001 C CNN
	1    1200 2800
	-1   0    0    1   
$EndComp
Text GLabel 1650 2600 2    50   Output ~ 0
Vbatt
Wire Wire Line
	1400 2700 1600 2700
Wire Wire Line
	1650 2600 1600 2600
Wire Wire Line
	1600 2600 1600 2700
Wire Wire Line
	2250 2700 2350 2700
Wire Wire Line
	1950 2700 1600 2700
Connection ~ 1600 2700
$Comp
L power:+5V #PWR0101
U 1 1 5D662260
P 4550 2700
F 0 "#PWR0101" H 4550 2550 50  0001 C CNN
F 1 "+5V" V 4565 2828 50  0000 L CNN
F 2 "" H 4550 2700 50  0001 C CNN
F 3 "" H 4550 2700 50  0001 C CNN
	1    4550 2700
	0    1    1    0   
$EndComp
Wire Wire Line
	4550 2900 4550 2700
Wire Wire Line
	1400 2800 1550 2800
$Comp
L power:+5V #PWR0103
U 1 1 5D66C79F
P 1500 1700
F 0 "#PWR0103" H 1500 1550 50  0001 C CNN
F 1 "+5V" H 1400 1900 50  0000 L CNN
F 2 "" H 1500 1700 50  0001 C CNN
F 3 "" H 1500 1700 50  0001 C CNN
	1    1500 1700
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 5D66D2B4
P 1700 1700
F 0 "#PWR0104" H 1700 1450 50  0001 C CNN
F 1 "GND" H 1705 1527 50  0000 C CNN
F 2 "" H 1700 1700 50  0001 C CNN
F 3 "" H 1700 1700 50  0001 C CNN
	1    1700 1700
	0    -1   1    0   
$EndComp
Wire Wire Line
	1700 1650 1700 1700
Wire Wire Line
	1600 1650 1600 1900
Wire Wire Line
	1500 1700 1500 1650
$Comp
L sensorz:DHT11_Temperature_Humidity TH1
U 1 1 5D665FCE
P 1600 1650
F 0 "TH1" H 1950 2300 60  0000 L CNN
F 1 "DHT11" H 1900 2150 60  0000 L CNN
F 2 "sensorz:DHT11_Temperature_Humidity" H 1700 2950 60  0001 C CNN
F 3 "" H 1600 1650 60  0000 C CNN
	1    1600 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 1900 1750 1900
Text GLabel 1750 1900 2    50   BiDi ~ 0
DHT11
Text GLabel 3550 3650 0    50   Input ~ 0
Reset
Wire Wire Line
	3550 3650 3800 3650
Text GLabel 6400 3850 2    50   Output ~ 0
Reset
$Comp
L Connector_Generic:Conn_01x01 J2
U 1 1 5D666371
P 6050 3850
F 0 "J2" H 5968 3625 50  0000 C CNN
F 1 "Reset" H 5968 3716 50  0000 C CNN
F 2 "Connector_PinHeader_1.00mm:PinHeader_1x01_P1.00mm_Vertical" H 6050 3850 50  0001 C CNN
F 3 "~" H 6050 3850 50  0001 C CNN
	1    6050 3850
	-1   0    0    1   
$EndComp
Wire Wire Line
	6250 3850 6400 3850
$Comp
L Diode:1N4007 D2
U 1 1 5EF13D6F
P 4450 1000
F 0 "D2" V 4500 1350 50  0000 C CNN
F 1 "1N4007" V 4400 1250 50  0000 C CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 4450 825 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 4450 1000 50  0001 C CNN
	1    4450 1000
	0    -1   -1   0   
$EndComp
Text GLabel 4350 750  0    50   Input ~ 0
Vbatt
Wire Wire Line
	4350 750  4450 750 
Wire Wire Line
	4450 750  4450 850 
Wire Wire Line
	4450 1150 4450 1200
Connection ~ 4450 1200
Text Notes 4550 1050 0    50   ~ 0
Flyback\nDiode \n(optional, ish)
Text GLabel 2350 2700 2    50   Input ~ 0
Vin
Text GLabel 4350 2700 0    50   Input ~ 0
Vin
Wire Wire Line
	4350 2700 4450 2700
$Comp
L Device:LED #D3
U 1 1 5EF2E235
P 1300 4050
F 0 "#D3" V 1339 4130 50  0000 L CNN
F 1 "LED" V 1248 4130 50  0000 L CNN
F 2 "LED_THT:LED_D5.0mm" H 1300 4050 50  0001 C CNN
F 3 "~" H 1300 4050 50  0001 C CNN
	1    1300 4050
	0    -1   -1   0   
$EndComp
$Comp
L Device:R #R5
U 1 1 5EF30A15
P 1300 3650
F 0 "#R5" H 1231 3696 50  0000 R CNN
F 1 "330R" H 1231 3605 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P5.08mm_Vertical" V 1230 3650 50  0001 C CNN
F 3 "~" H 1300 3650 50  0001 C CNN
	1    1300 3650
	1    0    0    -1  
$EndComp
Text GLabel 1450 3400 2    50   Input ~ 0
DHT11
Wire Wire Line
	1300 3500 1300 3400
Wire Wire Line
	1300 3400 1450 3400
Wire Wire Line
	1300 3800 1300 3900
$Comp
L power:GND #PWR03
U 1 1 5EF33FC0
P 1300 4300
F 0 "#PWR03" H 1300 4050 50  0001 C CNN
F 1 "GND" H 1305 4127 50  0000 C CNN
F 2 "" H 1300 4300 50  0001 C CNN
F 3 "" H 1300 4300 50  0001 C CNN
	1    1300 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 4300 1300 4200
Wire Notes Line
	2650 3250 2650 4600
Wire Notes Line
	2650 4600 1000 4600
Wire Notes Line
	1000 4600 1000 3250
Wire Notes Line
	1000 3250 2650 3250
Text Notes 2150 3400 0    63   ~ 13
Optional
Text Notes 1700 4550 0    43   ~ 0
For v2 genuine DigiKey's\nthe on-board LED is on \nP1, not P2.\n\nThis LED will replace that.\n\nYou also need to cut the \non-board track to disable \nthe onboard led, or leave \nit as a fan level indicator.\n\nFor clone digisparks this\nwill not be needed, they\nare all clones of the v1 \ndesign
$EndSCHEMATC
