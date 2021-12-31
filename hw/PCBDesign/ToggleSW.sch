EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 10
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
L Switch:SW_SPDT_MSM SW?
U 1 1 60455283
P 1400 1650
AR Path="/60445E97/60455283" Ref="SW?"  Part="1" 
AR Path="/60445E97/60452796/60455283" Ref="SW3"  Part="1" 
F 0 "SW3" H 1400 1935 50  0000 C CNN
F 1 "PitchTrim" H 1400 1844 50  0000 C CNN
F 2 "" H 1400 1650 50  0001 C CNN
F 3 "~" H 1400 1650 50  0001 C CNN
	1    1400 1650
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPDT SW?
U 1 1 6045529B
P 2150 3550
AR Path="/60445E97/6045529B" Ref="SW?"  Part="1" 
AR Path="/60445E97/60452796/6045529B" Ref="SW4"  Part="1" 
F 0 "SW4" H 2150 3835 50  0000 C CNN
F 1 "UserSwitchA" H 2150 3744 50  0000 C CNN
F 2 "" H 2150 3550 50  0001 C CNN
F 3 "~" H 2150 3550 50  0001 C CNN
	1    2150 3550
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R15
U 1 1 6048B645
P 1700 1300
F 0 "R15" H 1768 1346 50  0000 L CNN
F 1 "10k" H 1768 1255 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 1740 1290 50  0001 C CNN
F 3 "~" H 1700 1300 50  0001 C CNN
F 4 "C25744" H 1700 1300 50  0001 C CNN "LCSC"
	1    1700 1300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C10
U 1 1 6048BDB6
P 1700 2000
F 0 "C10" H 1815 2046 50  0000 L CNN
F 1 "100n" H 1815 1955 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 1738 1850 50  0001 C CNN
F 3 "~" H 1700 2000 50  0001 C CNN
F 4 "C1525" H 1700 2000 50  0001 C CNN "LCSC"
	1    1700 2000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C12
U 1 1 6048C751
P 2100 2000
F 0 "C12" H 2215 2046 50  0000 L CNN
F 1 "100n" H 2215 1955 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 2138 1850 50  0001 C CNN
F 3 "~" H 2100 2000 50  0001 C CNN
F 4 "C1525" H 2100 2000 50  0001 C CNN "LCSC"
	1    2100 2000
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R17
U 1 1 6048CDDB
P 2100 1300
F 0 "R17" H 2168 1346 50  0000 L CNN
F 1 "10k" H 2168 1255 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 2140 1290 50  0001 C CNN
F 3 "~" H 2100 1300 50  0001 C CNN
F 4 "C25744" H 2100 1300 50  0001 C CNN "LCSC"
	1    2100 1300
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R18
U 1 1 6048EA80
P 2400 1550
F 0 "R18" V 2195 1550 50  0000 C CNN
F 1 "1k" V 2286 1550 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 2440 1540 50  0001 C CNN
F 3 "~" H 2400 1550 50  0001 C CNN
F 4 "C11702" H 2400 1550 50  0001 C CNN "LCSC"
	1    2400 1550
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R19
U 1 1 6048F64C
P 2400 1750
F 0 "R19" V 2200 1750 50  0000 C CNN
F 1 "1k" V 2300 1750 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 2440 1740 50  0001 C CNN
F 3 "~" H 2400 1750 50  0001 C CNN
F 4 "C11702" H 2400 1750 50  0001 C CNN "LCSC"
	1    2400 1750
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR029
U 1 1 60490E9B
P 1150 1750
F 0 "#PWR029" H 1150 1500 50  0001 C CNN
F 1 "GND" H 1155 1577 50  0000 C CNN
F 2 "" H 1150 1750 50  0001 C CNN
F 3 "" H 1150 1750 50  0001 C CNN
	1    1150 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 1750 1150 1650
Wire Wire Line
	1150 1650 1200 1650
Text HLabel 1700 1050 1    50   Input ~ 0
V+
Text HLabel 2100 1050 1    50   Input ~ 0
V+
$Comp
L power:GND #PWR030
U 1 1 60491780
P 1700 2250
F 0 "#PWR030" H 1700 2000 50  0001 C CNN
F 1 "GND" H 1705 2077 50  0000 C CNN
F 2 "" H 1700 2250 50  0001 C CNN
F 3 "" H 1700 2250 50  0001 C CNN
	1    1700 2250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR032
U 1 1 60491B22
P 2100 2250
F 0 "#PWR032" H 2100 2000 50  0001 C CNN
F 1 "GND" H 2105 2077 50  0000 C CNN
F 2 "" H 2100 2250 50  0001 C CNN
F 3 "" H 2100 2250 50  0001 C CNN
	1    2100 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 1450 1700 1550
Wire Wire Line
	2100 1850 2100 1750
Wire Wire Line
	2100 2150 2100 2250
Wire Wire Line
	1700 2250 1700 2150
Connection ~ 2100 1750
Wire Wire Line
	2100 1750 2100 1450
Wire Wire Line
	2250 1750 2100 1750
Wire Wire Line
	1600 1550 1700 1550
Connection ~ 1700 1550
Wire Wire Line
	2100 1150 2100 1050
Wire Wire Line
	1700 1150 1700 1050
Wire Wire Line
	1700 1550 1800 1550
Text HLabel 2650 1550 2    50   Output ~ 0
dPitch_Trim_Up
Text HLabel 2650 1750 2    50   Output ~ 0
dPitch_Trim_Down
Wire Wire Line
	2650 1550 2550 1550
Wire Wire Line
	2650 1750 2550 1750
$Comp
L Switch:SW_SPDT_MSM SW?
U 1 1 6049D71B
P 3900 1650
AR Path="/60445E97/6049D71B" Ref="SW?"  Part="1" 
AR Path="/60445E97/60452796/6049D71B" Ref="SW5"  Part="1" 
F 0 "SW5" H 3900 1935 50  0000 C CNN
F 1 "RollTrim" H 3900 1844 50  0000 C CNN
F 2 "" H 3900 1650 50  0001 C CNN
F 3 "~" H 3900 1650 50  0001 C CNN
	1    3900 1650
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R22
U 1 1 6049D721
P 4200 1300
F 0 "R22" H 4268 1346 50  0000 L CNN
F 1 "10k" H 4268 1255 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 4240 1290 50  0001 C CNN
F 3 "~" H 4200 1300 50  0001 C CNN
F 4 "C25744" H 4200 1300 50  0001 C CNN "LCSC"
	1    4200 1300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C13
U 1 1 6049D727
P 4200 2000
F 0 "C13" H 4315 2046 50  0000 L CNN
F 1 "100n" H 4315 1955 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 4238 1850 50  0001 C CNN
F 3 "~" H 4200 2000 50  0001 C CNN
F 4 "C1525" H 4200 2000 50  0001 C CNN "LCSC"
	1    4200 2000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C15
U 1 1 6049D72D
P 4600 2000
F 0 "C15" H 4715 2046 50  0000 L CNN
F 1 "100n" H 4715 1955 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 4638 1850 50  0001 C CNN
F 3 "~" H 4600 2000 50  0001 C CNN
F 4 "C1525" H 4600 2000 50  0001 C CNN "LCSC"
	1    4600 2000
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R23
U 1 1 6049D733
P 4600 1300
F 0 "R23" H 4668 1346 50  0000 L CNN
F 1 "10k" H 4668 1255 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 4640 1290 50  0001 C CNN
F 3 "~" H 4600 1300 50  0001 C CNN
F 4 "C25744" H 4600 1300 50  0001 C CNN "LCSC"
	1    4600 1300
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R25
U 1 1 6049D739
P 4900 1550
F 0 "R25" V 4695 1550 50  0000 C CNN
F 1 "1k" V 4786 1550 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 4940 1540 50  0001 C CNN
F 3 "~" H 4900 1550 50  0001 C CNN
F 4 "C11702" H 4900 1550 50  0001 C CNN "LCSC"
	1    4900 1550
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R26
U 1 1 6049D73F
P 4900 1750
F 0 "R26" V 4700 1750 50  0000 C CNN
F 1 "1k" V 4800 1750 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 4940 1740 50  0001 C CNN
F 3 "~" H 4900 1750 50  0001 C CNN
F 4 "C11702" H 4900 1750 50  0001 C CNN "LCSC"
	1    4900 1750
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR034
U 1 1 6049D745
P 3650 1750
F 0 "#PWR034" H 3650 1500 50  0001 C CNN
F 1 "GND" H 3655 1577 50  0000 C CNN
F 2 "" H 3650 1750 50  0001 C CNN
F 3 "" H 3650 1750 50  0001 C CNN
	1    3650 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 1750 3650 1650
Wire Wire Line
	3650 1650 3700 1650
Text HLabel 4200 1050 1    50   Input ~ 0
V+
Text HLabel 4600 1050 1    50   Input ~ 0
V+
$Comp
L power:GND #PWR035
U 1 1 6049D74F
P 4200 2250
F 0 "#PWR035" H 4200 2000 50  0001 C CNN
F 1 "GND" H 4205 2077 50  0000 C CNN
F 2 "" H 4200 2250 50  0001 C CNN
F 3 "" H 4200 2250 50  0001 C CNN
	1    4200 2250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR037
U 1 1 6049D755
P 4600 2250
F 0 "#PWR037" H 4600 2000 50  0001 C CNN
F 1 "GND" H 4605 2077 50  0000 C CNN
F 2 "" H 4600 2250 50  0001 C CNN
F 3 "" H 4600 2250 50  0001 C CNN
	1    4600 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 1450 4200 1550
Wire Wire Line
	4600 1850 4600 1750
Wire Wire Line
	4600 2150 4600 2250
Wire Wire Line
	4200 2250 4200 2150
Wire Wire Line
	4100 1750 4500 1750
Connection ~ 4600 1750
Wire Wire Line
	4600 1750 4600 1450
Wire Wire Line
	4750 1750 4600 1750
Wire Wire Line
	4100 1550 4200 1550
Connection ~ 4200 1550
Wire Wire Line
	4200 1550 4200 1850
Wire Wire Line
	4600 1150 4600 1050
Wire Wire Line
	4200 1150 4200 1050
Wire Wire Line
	4200 1550 4300 1550
Text HLabel 5150 1550 2    50   Output ~ 0
dRoll_Trim_Up
Text HLabel 5150 1750 2    50   Output ~ 0
dRoll_Trim_Down
Wire Wire Line
	5150 1550 5050 1550
Wire Wire Line
	5150 1750 5050 1750
$Comp
L Switch:SW_SPDT_MSM SW?
U 1 1 604A13C6
P 6350 1650
AR Path="/60445E97/604A13C6" Ref="SW?"  Part="1" 
AR Path="/60445E97/60452796/604A13C6" Ref="SW7"  Part="1" 
F 0 "SW7" H 6350 1935 50  0000 C CNN
F 1 "YawTrim" H 6350 1844 50  0000 C CNN
F 2 "" H 6350 1650 50  0001 C CNN
F 3 "~" H 6350 1650 50  0001 C CNN
	1    6350 1650
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R28
U 1 1 604A13CC
P 6650 1300
F 0 "R28" H 6718 1346 50  0000 L CNN
F 1 "10k" H 6718 1255 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 6690 1290 50  0001 C CNN
F 3 "~" H 6650 1300 50  0001 C CNN
F 4 "C25744" H 6650 1300 50  0001 C CNN "LCSC"
	1    6650 1300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C16
U 1 1 604A13D2
P 6650 2000
F 0 "C16" H 6765 2046 50  0000 L CNN
F 1 "100n" H 6765 1955 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 6688 1850 50  0001 C CNN
F 3 "~" H 6650 2000 50  0001 C CNN
F 4 "C1525" H 6650 2000 50  0001 C CNN "LCSC"
	1    6650 2000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C18
U 1 1 604A13D8
P 7050 2000
F 0 "C18" H 7165 2046 50  0000 L CNN
F 1 "100n" H 7165 1955 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 7088 1850 50  0001 C CNN
F 3 "~" H 7050 2000 50  0001 C CNN
F 4 "C1525" H 7050 2000 50  0001 C CNN "LCSC"
	1    7050 2000
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R29
U 1 1 604A13DE
P 7050 1300
F 0 "R29" H 7118 1346 50  0000 L CNN
F 1 "10k" H 7118 1255 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 7090 1290 50  0001 C CNN
F 3 "~" H 7050 1300 50  0001 C CNN
F 4 "C25744" H 7050 1300 50  0001 C CNN "LCSC"
	1    7050 1300
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R31
U 1 1 604A13E4
P 7350 1550
F 0 "R31" V 7145 1550 50  0000 C CNN
F 1 "1k" V 7236 1550 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 7390 1540 50  0001 C CNN
F 3 "~" H 7350 1550 50  0001 C CNN
F 4 "C11702" H 7350 1550 50  0001 C CNN "LCSC"
	1    7350 1550
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R32
U 1 1 604A13EA
P 7350 1750
F 0 "R32" V 7150 1750 50  0000 C CNN
F 1 "1k" V 7250 1750 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 7390 1740 50  0001 C CNN
F 3 "~" H 7350 1750 50  0001 C CNN
F 4 "C11702" H 7350 1750 50  0001 C CNN "LCSC"
	1    7350 1750
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR039
U 1 1 604A13F0
P 6100 1750
F 0 "#PWR039" H 6100 1500 50  0001 C CNN
F 1 "GND" H 6105 1577 50  0000 C CNN
F 2 "" H 6100 1750 50  0001 C CNN
F 3 "" H 6100 1750 50  0001 C CNN
	1    6100 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 1750 6100 1650
Wire Wire Line
	6100 1650 6150 1650
Text HLabel 6650 1050 1    50   Input ~ 0
V+
Text HLabel 7050 1050 1    50   Input ~ 0
V+
$Comp
L power:GND #PWR040
U 1 1 604A13FA
P 6650 2250
F 0 "#PWR040" H 6650 2000 50  0001 C CNN
F 1 "GND" H 6655 2077 50  0000 C CNN
F 2 "" H 6650 2250 50  0001 C CNN
F 3 "" H 6650 2250 50  0001 C CNN
	1    6650 2250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR042
U 1 1 604A1400
P 7050 2250
F 0 "#PWR042" H 7050 2000 50  0001 C CNN
F 1 "GND" H 7055 2077 50  0000 C CNN
F 2 "" H 7050 2250 50  0001 C CNN
F 3 "" H 7050 2250 50  0001 C CNN
	1    7050 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 1450 6650 1550
Wire Wire Line
	7050 1850 7050 1750
Wire Wire Line
	7050 2150 7050 2250
Wire Wire Line
	6650 2250 6650 2150
Wire Wire Line
	6550 1750 6950 1750
Connection ~ 7050 1750
Wire Wire Line
	7050 1750 7050 1450
Wire Wire Line
	7200 1750 7050 1750
Wire Wire Line
	6550 1550 6650 1550
Connection ~ 6650 1550
Wire Wire Line
	6650 1550 6650 1850
Wire Wire Line
	7050 1150 7050 1050
Wire Wire Line
	6650 1150 6650 1050
Wire Wire Line
	6650 1550 6750 1550
Text HLabel 7600 1550 2    50   Output ~ 0
dYaw_Trim_Up
Text HLabel 7600 1750 2    50   Output ~ 0
dYaw_Trim_Down
Wire Wire Line
	7600 1550 7500 1550
Wire Wire Line
	7600 1750 7500 1750
$Comp
L Switch:SW_SPDT_MSM SW?
U 1 1 604A9A3D
P 8800 1650
AR Path="/60445E97/604A9A3D" Ref="SW?"  Part="1" 
AR Path="/60445E97/60452796/604A9A3D" Ref="SW9"  Part="1" 
F 0 "SW9" H 8800 1935 50  0000 C CNN
F 1 "ThrottleTrim" H 8800 1844 50  0000 C CNN
F 2 "" H 8800 1650 50  0001 C CNN
F 3 "~" H 8800 1650 50  0001 C CNN
	1    8800 1650
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R34
U 1 1 604A9A43
P 9100 1300
F 0 "R34" H 9168 1346 50  0000 L CNN
F 1 "10k" H 9168 1255 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 9140 1290 50  0001 C CNN
F 3 "~" H 9100 1300 50  0001 C CNN
F 4 "C25744" H 9100 1300 50  0001 C CNN "LCSC"
	1    9100 1300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C19
U 1 1 604A9A49
P 9100 2000
F 0 "C19" H 9215 2046 50  0000 L CNN
F 1 "100n" H 9215 1955 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 9138 1850 50  0001 C CNN
F 3 "~" H 9100 2000 50  0001 C CNN
F 4 "C1525" H 9100 2000 50  0001 C CNN "LCSC"
	1    9100 2000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C21
U 1 1 604A9A4F
P 9500 2000
F 0 "C21" H 9615 2046 50  0000 L CNN
F 1 "100n" H 9615 1955 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 9538 1850 50  0001 C CNN
F 3 "~" H 9500 2000 50  0001 C CNN
F 4 "C1525" H 9500 2000 50  0001 C CNN "LCSC"
	1    9500 2000
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R35
U 1 1 604A9A55
P 9500 1300
F 0 "R35" H 9568 1346 50  0000 L CNN
F 1 "10k" H 9568 1255 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 9540 1290 50  0001 C CNN
F 3 "~" H 9500 1300 50  0001 C CNN
F 4 "C25744" H 9500 1300 50  0001 C CNN "LCSC"
	1    9500 1300
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R37
U 1 1 604A9A5B
P 9800 1550
F 0 "R37" V 9595 1550 50  0000 C CNN
F 1 "1k" V 9686 1550 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 9840 1540 50  0001 C CNN
F 3 "~" H 9800 1550 50  0001 C CNN
F 4 "C11702" H 9800 1550 50  0001 C CNN "LCSC"
	1    9800 1550
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R38
U 1 1 604A9A61
P 9800 1750
F 0 "R38" V 9600 1750 50  0000 C CNN
F 1 "1k" V 9700 1750 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 9840 1740 50  0001 C CNN
F 3 "~" H 9800 1750 50  0001 C CNN
F 4 "C11702" H 9800 1750 50  0001 C CNN "LCSC"
	1    9800 1750
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR044
U 1 1 604A9A67
P 8550 1750
F 0 "#PWR044" H 8550 1500 50  0001 C CNN
F 1 "GND" H 8555 1577 50  0000 C CNN
F 2 "" H 8550 1750 50  0001 C CNN
F 3 "" H 8550 1750 50  0001 C CNN
	1    8550 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 1750 8550 1650
Wire Wire Line
	8550 1650 8600 1650
Text HLabel 9100 1050 1    50   Input ~ 0
V+
Text HLabel 9500 1050 1    50   Input ~ 0
V+
$Comp
L power:GND #PWR045
U 1 1 604A9A71
P 9100 2250
F 0 "#PWR045" H 9100 2000 50  0001 C CNN
F 1 "GND" H 9105 2077 50  0000 C CNN
F 2 "" H 9100 2250 50  0001 C CNN
F 3 "" H 9100 2250 50  0001 C CNN
	1    9100 2250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR047
U 1 1 604A9A77
P 9500 2250
F 0 "#PWR047" H 9500 2000 50  0001 C CNN
F 1 "GND" H 9505 2077 50  0000 C CNN
F 2 "" H 9500 2250 50  0001 C CNN
F 3 "" H 9500 2250 50  0001 C CNN
	1    9500 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 1450 9100 1550
Wire Wire Line
	9500 1850 9500 1750
Wire Wire Line
	9500 2150 9500 2250
Wire Wire Line
	9100 2250 9100 2150
Wire Wire Line
	9000 1750 9400 1750
Connection ~ 9500 1750
Wire Wire Line
	9500 1750 9500 1450
Wire Wire Line
	9650 1750 9500 1750
Wire Wire Line
	9000 1550 9100 1550
Connection ~ 9100 1550
Wire Wire Line
	9100 1550 9100 1850
Wire Wire Line
	9500 1150 9500 1050
Wire Wire Line
	9100 1150 9100 1050
Wire Wire Line
	9100 1550 9200 1550
Text HLabel 10050 1550 2    50   Output ~ 0
dThrottle_Trim_Up
Text HLabel 10050 1750 2    50   Output ~ 0
dThrottle_Trim_Down
Wire Wire Line
	10050 1550 9950 1550
Wire Wire Line
	10050 1750 9950 1750
$Comp
L Device:R_US R20
U 1 1 604AC686
P 2400 3200
F 0 "R20" H 2468 3246 50  0000 L CNN
F 1 "10k" H 2468 3155 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 2440 3190 50  0001 C CNN
F 3 "~" H 2400 3200 50  0001 C CNN
F 4 "C25744" H 2400 3200 50  0001 C CNN "LCSC"
	1    2400 3200
	1    0    0    -1  
$EndComp
$Comp
L Device:C C11
U 1 1 604AC68C
P 1900 3750
F 0 "C11" H 2015 3796 50  0000 L CNN
F 1 "100n" H 2015 3705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 1938 3600 50  0001 C CNN
F 3 "~" H 1900 3750 50  0001 C CNN
F 4 "C1525" H 1900 3750 50  0001 C CNN "LCSC"
	1    1900 3750
	1    0    0    -1  
$EndComp
Text HLabel 2400 2950 1    50   Input ~ 0
V+
$Comp
L power:GND #PWR031
U 1 1 604AC693
P 1900 4000
F 0 "#PWR031" H 1900 3750 50  0001 C CNN
F 1 "GND" H 1905 3827 50  0000 C CNN
F 2 "" H 1900 4000 50  0001 C CNN
F 3 "" H 1900 4000 50  0001 C CNN
	1    1900 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 3350 2400 3450
Wire Wire Line
	1900 4000 1900 3900
Wire Wire Line
	2400 3050 2400 2950
Wire Wire Line
	2400 3450 2350 3450
Wire Wire Line
	1900 3550 1900 3600
$Comp
L Device:R_US R16
U 1 1 604B5229
P 1700 3550
F 0 "R16" V 1495 3550 50  0000 C CNN
F 1 "1k" V 1586 3550 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 1740 3540 50  0001 C CNN
F 3 "~" H 1700 3550 50  0001 C CNN
F 4 "C11702" H 1700 3550 50  0001 C CNN "LCSC"
	1    1700 3550
	0    1    1    0   
$EndComp
Wire Wire Line
	1850 3550 1900 3550
$Comp
L power:GND #PWR033
U 1 1 604B6F36
P 2400 3700
F 0 "#PWR033" H 2400 3450 50  0001 C CNN
F 1 "GND" H 2405 3527 50  0000 C CNN
F 2 "" H 2400 3700 50  0001 C CNN
F 3 "" H 2400 3700 50  0001 C CNN
	1    2400 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 3650 2400 3650
Wire Wire Line
	2400 3650 2400 3700
Wire Wire Line
	1950 3550 1900 3550
Connection ~ 1900 3550
Text HLabel 1450 3550 0    50   Output ~ 0
UserSwitchA
Wire Wire Line
	1450 3550 1550 3550
$Comp
L Switch:SW_SPDT SW?
U 1 1 604C6BE8
P 4550 3550
AR Path="/60445E97/604C6BE8" Ref="SW?"  Part="1" 
AR Path="/60445E97/60452796/604C6BE8" Ref="SW6"  Part="1" 
F 0 "SW6" H 4550 3835 50  0000 C CNN
F 1 "UserSwitchB" H 4550 3744 50  0000 C CNN
F 2 "" H 4550 3550 50  0001 C CNN
F 3 "~" H 4550 3550 50  0001 C CNN
	1    4550 3550
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R24
U 1 1 604C6BEE
P 4800 3200
F 0 "R24" H 4868 3246 50  0000 L CNN
F 1 "10k" H 4868 3155 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 4840 3190 50  0001 C CNN
F 3 "~" H 4800 3200 50  0001 C CNN
F 4 "C25744" H 4800 3200 50  0001 C CNN "LCSC"
	1    4800 3200
	1    0    0    -1  
$EndComp
$Comp
L Device:C C14
U 1 1 604C6BF4
P 4300 3750
F 0 "C14" H 4415 3796 50  0000 L CNN
F 1 "100n" H 4415 3705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 4338 3600 50  0001 C CNN
F 3 "~" H 4300 3750 50  0001 C CNN
F 4 "C1525" H 4300 3750 50  0001 C CNN "LCSC"
	1    4300 3750
	1    0    0    -1  
$EndComp
Text HLabel 4800 2950 1    50   Input ~ 0
V+
$Comp
L power:GND #PWR036
U 1 1 604C6BFB
P 4300 4000
F 0 "#PWR036" H 4300 3750 50  0001 C CNN
F 1 "GND" H 4305 3827 50  0000 C CNN
F 2 "" H 4300 4000 50  0001 C CNN
F 3 "" H 4300 4000 50  0001 C CNN
	1    4300 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 3350 4800 3450
Wire Wire Line
	4300 4000 4300 3900
Wire Wire Line
	4800 3050 4800 2950
Wire Wire Line
	4800 3450 4750 3450
Wire Wire Line
	4300 3550 4300 3600
$Comp
L Device:R_US R21
U 1 1 604C6C06
P 4100 3550
F 0 "R21" V 3895 3550 50  0000 C CNN
F 1 "1k" V 3986 3550 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 4140 3540 50  0001 C CNN
F 3 "~" H 4100 3550 50  0001 C CNN
F 4 "C11702" H 4100 3550 50  0001 C CNN "LCSC"
	1    4100 3550
	0    1    1    0   
$EndComp
Wire Wire Line
	4250 3550 4300 3550
$Comp
L power:GND #PWR038
U 1 1 604C6C0D
P 4800 3700
F 0 "#PWR038" H 4800 3450 50  0001 C CNN
F 1 "GND" H 4805 3527 50  0000 C CNN
F 2 "" H 4800 3700 50  0001 C CNN
F 3 "" H 4800 3700 50  0001 C CNN
	1    4800 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 3650 4800 3650
Wire Wire Line
	4800 3650 4800 3700
Wire Wire Line
	4350 3550 4300 3550
Connection ~ 4300 3550
Text HLabel 3850 3550 0    50   Output ~ 0
UserSwitchB
Wire Wire Line
	3850 3550 3950 3550
$Comp
L Switch:SW_SPDT SW?
U 1 1 604CC6E0
P 7000 3550
AR Path="/60445E97/604CC6E0" Ref="SW?"  Part="1" 
AR Path="/60445E97/60452796/604CC6E0" Ref="SW8"  Part="1" 
F 0 "SW8" H 7000 3835 50  0000 C CNN
F 1 "UserSwitchC" H 7000 3744 50  0000 C CNN
F 2 "" H 7000 3550 50  0001 C CNN
F 3 "~" H 7000 3550 50  0001 C CNN
	1    7000 3550
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R30
U 1 1 604CC6E6
P 7250 3200
F 0 "R30" H 7318 3246 50  0000 L CNN
F 1 "10k" H 7318 3155 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 7290 3190 50  0001 C CNN
F 3 "~" H 7250 3200 50  0001 C CNN
F 4 "C25744" H 7250 3200 50  0001 C CNN "LCSC"
	1    7250 3200
	1    0    0    -1  
$EndComp
$Comp
L Device:C C17
U 1 1 604CC6EC
P 6750 3750
F 0 "C17" H 6865 3796 50  0000 L CNN
F 1 "100n" H 6865 3705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 6788 3600 50  0001 C CNN
F 3 "~" H 6750 3750 50  0001 C CNN
F 4 "C1525" H 6750 3750 50  0001 C CNN "LCSC"
	1    6750 3750
	1    0    0    -1  
$EndComp
Text HLabel 7250 2950 1    50   Input ~ 0
V+
$Comp
L power:GND #PWR041
U 1 1 604CC6F3
P 6750 4000
F 0 "#PWR041" H 6750 3750 50  0001 C CNN
F 1 "GND" H 6755 3827 50  0000 C CNN
F 2 "" H 6750 4000 50  0001 C CNN
F 3 "" H 6750 4000 50  0001 C CNN
	1    6750 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 3350 7250 3450
Wire Wire Line
	6750 4000 6750 3900
Wire Wire Line
	7250 3050 7250 2950
Wire Wire Line
	7250 3450 7200 3450
Wire Wire Line
	6750 3550 6750 3600
$Comp
L Device:R_US R27
U 1 1 604CC6FE
P 6550 3550
F 0 "R27" V 6345 3550 50  0000 C CNN
F 1 "1k" V 6436 3550 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 6590 3540 50  0001 C CNN
F 3 "~" H 6550 3550 50  0001 C CNN
F 4 "C11702" H 6550 3550 50  0001 C CNN "LCSC"
	1    6550 3550
	0    1    1    0   
$EndComp
Wire Wire Line
	6700 3550 6750 3550
$Comp
L power:GND #PWR043
U 1 1 604CC705
P 7250 3700
F 0 "#PWR043" H 7250 3450 50  0001 C CNN
F 1 "GND" H 7255 3527 50  0000 C CNN
F 2 "" H 7250 3700 50  0001 C CNN
F 3 "" H 7250 3700 50  0001 C CNN
	1    7250 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 3650 7250 3650
Wire Wire Line
	7250 3650 7250 3700
Wire Wire Line
	6800 3550 6750 3550
Connection ~ 6750 3550
Text HLabel 6300 3550 0    50   Output ~ 0
UserSwitchC
Wire Wire Line
	6300 3550 6400 3550
$Comp
L Switch:SW_SPDT SW?
U 1 1 604D1862
P 9500 3550
AR Path="/60445E97/604D1862" Ref="SW?"  Part="1" 
AR Path="/60445E97/60452796/604D1862" Ref="SW10"  Part="1" 
F 0 "SW10" H 9500 3835 50  0000 C CNN
F 1 "UserSwitchD" H 9500 3744 50  0000 C CNN
F 2 "" H 9500 3550 50  0001 C CNN
F 3 "~" H 9500 3550 50  0001 C CNN
	1    9500 3550
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R36
U 1 1 604D1868
P 9750 3200
F 0 "R36" H 9818 3246 50  0000 L CNN
F 1 "10k" H 9818 3155 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 9790 3190 50  0001 C CNN
F 3 "~" H 9750 3200 50  0001 C CNN
F 4 "C25744" H 9750 3200 50  0001 C CNN "LCSC"
	1    9750 3200
	1    0    0    -1  
$EndComp
$Comp
L Device:C C20
U 1 1 604D186E
P 9250 3750
F 0 "C20" H 9365 3796 50  0000 L CNN
F 1 "100n" H 9365 3705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 9288 3600 50  0001 C CNN
F 3 "~" H 9250 3750 50  0001 C CNN
F 4 "C1525" H 9250 3750 50  0001 C CNN "LCSC"
	1    9250 3750
	1    0    0    -1  
$EndComp
Text HLabel 9750 2950 1    50   Input ~ 0
V+
$Comp
L power:GND #PWR046
U 1 1 604D1875
P 9250 4000
F 0 "#PWR046" H 9250 3750 50  0001 C CNN
F 1 "GND" H 9255 3827 50  0000 C CNN
F 2 "" H 9250 4000 50  0001 C CNN
F 3 "" H 9250 4000 50  0001 C CNN
	1    9250 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	9750 3350 9750 3450
Wire Wire Line
	9250 4000 9250 3900
Wire Wire Line
	9750 3050 9750 2950
Wire Wire Line
	9750 3450 9700 3450
Wire Wire Line
	9250 3550 9250 3600
$Comp
L Device:R_US R33
U 1 1 604D1880
P 9050 3550
F 0 "R33" V 8845 3550 50  0000 C CNN
F 1 "1k" V 8936 3550 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 9090 3540 50  0001 C CNN
F 3 "~" H 9050 3550 50  0001 C CNN
F 4 "C11702" H 9050 3550 50  0001 C CNN "LCSC"
	1    9050 3550
	0    1    1    0   
$EndComp
Wire Wire Line
	9200 3550 9250 3550
$Comp
L power:GND #PWR048
U 1 1 604D1887
P 9750 3700
F 0 "#PWR048" H 9750 3450 50  0001 C CNN
F 1 "GND" H 9755 3527 50  0000 C CNN
F 2 "" H 9750 3700 50  0001 C CNN
F 3 "" H 9750 3700 50  0001 C CNN
	1    9750 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	9700 3650 9750 3650
Wire Wire Line
	9750 3650 9750 3700
Wire Wire Line
	9300 3550 9250 3550
Connection ~ 9250 3550
Text HLabel 8800 3550 0    50   Output ~ 0
UserSwitchD
Wire Wire Line
	8800 3550 8900 3550
Text Notes 5200 900  0    50   ~ 0
Momentary Toggle Switches
Text Notes 5250 2850 0    50   ~ 0
Latched Toggle Switches
$Comp
L Connector_Generic:Conn_01x03 J14
U 1 1 60504500
P 9950 3550
F 0 "J14" H 10030 3592 50  0000 L CNN
F 1 "SW_D" H 10030 3501 50  0000 L CNN
F 2 "Connector_Molex:Molex_PicoBlade_53261-0371_1x03-1MP_P1.25mm_Horizontal" H 9950 3550 50  0001 C CNN
F 3 "~" H 9950 3550 50  0001 C CNN
F 4 "WM7621CT-ND" H 9950 3550 50  0001 C CNN "DigiKey"
	1    9950 3550
	1    0    0    -1  
$EndComp
Connection ~ 9750 3450
Connection ~ 9750 3650
$Comp
L Connector_Generic:Conn_01x03 J12
U 1 1 60504AA7
P 7450 3550
F 0 "J12" H 7530 3592 50  0000 L CNN
F 1 "SW_C" H 7530 3501 50  0000 L CNN
F 2 "Connector_Molex:Molex_PicoBlade_53261-0371_1x03-1MP_P1.25mm_Horizontal" H 7450 3550 50  0001 C CNN
F 3 "~" H 7450 3550 50  0001 C CNN
F 4 "WM7621CT-ND" H 7450 3550 50  0001 C CNN "DigiKey"
	1    7450 3550
	1    0    0    -1  
$EndComp
Connection ~ 7250 3450
Connection ~ 7250 3650
$Comp
L Connector_Generic:Conn_01x03 J10
U 1 1 6050532B
P 5000 3550
F 0 "J10" H 5080 3592 50  0000 L CNN
F 1 "SW_B" H 5080 3501 50  0000 L CNN
F 2 "Connector_Molex:Molex_PicoBlade_53261-0371_1x03-1MP_P1.25mm_Horizontal" H 5000 3550 50  0001 C CNN
F 3 "~" H 5000 3550 50  0001 C CNN
F 4 "WM7621CT-ND" H 5000 3550 50  0001 C CNN "DigiKey"
	1    5000 3550
	1    0    0    -1  
$EndComp
Connection ~ 4800 3450
Connection ~ 4800 3650
$Comp
L Connector_Generic:Conn_01x03 J8
U 1 1 60505773
P 2600 3550
F 0 "J8" H 2680 3592 50  0000 L CNN
F 1 "SW_A" H 2680 3501 50  0000 L CNN
F 2 "Connector_Molex:Molex_PicoBlade_53261-0371_1x03-1MP_P1.25mm_Horizontal" H 2600 3550 50  0001 C CNN
F 3 "~" H 2600 3550 50  0001 C CNN
F 4 "WM7621CT-ND" H 2600 3550 50  0001 C CNN "DigiKey"
	1    2600 3550
	1    0    0    -1  
$EndComp
Connection ~ 2400 3450
Connection ~ 2400 3650
$Comp
L Connector_Generic:Conn_01x03 J7
U 1 1 60505E31
P 1900 750
F 0 "J7" V 1864 930 50  0000 L CNN
F 1 "PTrim" V 1773 930 50  0000 L CNN
F 2 "Connector_Molex:Molex_PicoBlade_53261-0371_1x03-1MP_P1.25mm_Horizontal" H 1900 750 50  0001 C CNN
F 3 "~" H 1900 750 50  0001 C CNN
F 4 "WM7621CT-ND" H 1900 750 50  0001 C CNN "DigiKey"
F 5 "WM7621CT-ND" H 1900 750 50  0001 C CNN "Digikey"
	1    1900 750 
	0    1    -1   0   
$EndComp
Wire Wire Line
	1700 1550 1700 1850
Wire Wire Line
	1600 1750 2000 1750
Wire Wire Line
	1800 950  1800 1550
Connection ~ 1800 1550
Wire Wire Line
	1800 1550 2250 1550
Wire Wire Line
	2000 950  2000 1750
Connection ~ 2000 1750
Wire Wire Line
	2000 1750 2100 1750
$Comp
L power:GND #PWR0108
U 1 1 60511C21
P 1900 950
F 0 "#PWR0108" H 1900 700 50  0001 C CNN
F 1 "GND" H 1905 777 50  0000 C CNN
F 2 "" H 1900 950 50  0001 C CNN
F 3 "" H 1900 950 50  0001 C CNN
	1    1900 950 
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J9
U 1 1 605133C1
P 4400 750
F 0 "J9" V 4364 930 50  0000 L CNN
F 1 "RTrim" V 4273 930 50  0000 L CNN
F 2 "Connector_Molex:Molex_PicoBlade_53261-0371_1x03-1MP_P1.25mm_Horizontal" H 4400 750 50  0001 C CNN
F 3 "~" H 4400 750 50  0001 C CNN
F 4 "WM7621CT-ND" H 4400 750 50  0001 C CNN "DigiKey"
	1    4400 750 
	0    1    -1   0   
$EndComp
Wire Wire Line
	4300 950  4300 1550
Wire Wire Line
	4500 950  4500 1750
$Comp
L power:GND #PWR0109
U 1 1 605133C9
P 4400 950
F 0 "#PWR0109" H 4400 700 50  0001 C CNN
F 1 "GND" H 4405 777 50  0000 C CNN
F 2 "" H 4400 950 50  0001 C CNN
F 3 "" H 4400 950 50  0001 C CNN
	1    4400 950 
	1    0    0    -1  
$EndComp
Connection ~ 4300 1550
Wire Wire Line
	4300 1550 4750 1550
Connection ~ 4500 1750
Wire Wire Line
	4500 1750 4600 1750
$Comp
L Connector_Generic:Conn_01x03 J11
U 1 1 605173C4
P 6850 750
F 0 "J11" V 6814 930 50  0000 L CNN
F 1 "YTrim" V 6723 930 50  0000 L CNN
F 2 "Connector_Molex:Molex_PicoBlade_53261-0371_1x03-1MP_P1.25mm_Horizontal" H 6850 750 50  0001 C CNN
F 3 "~" H 6850 750 50  0001 C CNN
F 4 "WM7621CT-ND" H 6850 750 50  0001 C CNN "DigiKey"
	1    6850 750 
	0    1    -1   0   
$EndComp
Wire Wire Line
	6750 950  6750 1550
Wire Wire Line
	6950 950  6950 1750
$Comp
L power:GND #PWR0110
U 1 1 605173CC
P 6850 950
F 0 "#PWR0110" H 6850 700 50  0001 C CNN
F 1 "GND" H 6855 777 50  0000 C CNN
F 2 "" H 6850 950 50  0001 C CNN
F 3 "" H 6850 950 50  0001 C CNN
	1    6850 950 
	1    0    0    -1  
$EndComp
Connection ~ 6950 1750
Wire Wire Line
	6950 1750 7050 1750
Connection ~ 6750 1550
Wire Wire Line
	6750 1550 7200 1550
$Comp
L Connector_Generic:Conn_01x03 J13
U 1 1 6051B9CA
P 9300 750
F 0 "J13" V 9264 930 50  0000 L CNN
F 1 "TTrim" V 9173 930 50  0000 L CNN
F 2 "Connector_Molex:Molex_PicoBlade_53261-0371_1x03-1MP_P1.25mm_Horizontal" H 9300 750 50  0001 C CNN
F 3 "~" H 9300 750 50  0001 C CNN
F 4 "WM7621CT-ND" H 9300 750 50  0001 C CNN "DigiKey"
	1    9300 750 
	0    1    -1   0   
$EndComp
Wire Wire Line
	9200 950  9200 1550
Wire Wire Line
	9400 950  9400 1750
$Comp
L power:GND #PWR0111
U 1 1 6051B9D2
P 9300 950
F 0 "#PWR0111" H 9300 700 50  0001 C CNN
F 1 "GND" H 9305 777 50  0000 C CNN
F 2 "" H 9300 950 50  0001 C CNN
F 3 "" H 9300 950 50  0001 C CNN
	1    9300 950 
	1    0    0    -1  
$EndComp
Connection ~ 9200 1550
Wire Wire Line
	9200 1550 9650 1550
Connection ~ 9400 1750
Wire Wire Line
	9400 1750 9500 1750
Wire Wire Line
	9750 3550 9300 3550
Connection ~ 9300 3550
Wire Wire Line
	6800 3550 7250 3550
Connection ~ 6800 3550
Wire Wire Line
	4800 3550 4350 3550
Connection ~ 4350 3550
Wire Wire Line
	2400 3550 1950 3550
Connection ~ 1950 3550
$EndSCHEMATC
