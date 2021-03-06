EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 11 11
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
L Connector:Conn_ARM_JTAG_SWD_10 J4
U 1 1 6047637A
P 10200 5650
F 0 "J4" H 9900 6250 50  0000 R CNN
F 1 "Conn_ARM_JTAG_SWD_10" V 9750 6100 50  0000 R CNN
F 2 "Connector_PinHeader_1.27mm:PinHeader_2x05_P1.27mm_Vertical_SMD" H 10200 5650 50  0001 C CNN
F 3 "http://infocenter.arm.com/help/topic/com.arm.doc.ddi0314h/DDI0314H_coresight_components_trm.pdf" V 9850 4400 50  0001 C CNN
	1    10200 5650
	1    0    0    -1  
$EndComp
Text HLabel 10050 2700 2    50   BiDi ~ 0
USB_D+
Text HLabel 10050 2400 2    50   BiDi ~ 0
USB_D-
Text HLabel 8100 5600 2    50   Input ~ 0
nBatt_Pwr_Good
Text HLabel 8100 5700 2    50   Input ~ 0
nBatt_Chg_Good
Text HLabel 3350 2300 2    50   Output ~ 0
nBattChgEn
Text HLabel 7400 3700 0    50   Input ~ 0
BT_UART_RX
Text HLabel 7400 3600 0    50   Output ~ 0
BT_UART_TX
Text HLabel 8800 2100 2    50   Output ~ 0
RF24_MOSI
Text HLabel 8800 2000 2    50   Input ~ 0
RF24_MISO
Text HLabel 8800 1900 2    50   Output ~ 0
RF24_SCK
Text HLabel 7400 3400 0    50   Output ~ 0
RF24_nCS
Text HLabel 8800 1800 2    50   Output ~ 0
RF24_CE
Text HLabel 8800 3200 2    50   Input ~ 0
RF24_nIRQ
Text HLabel 8800 4500 2    50   Output ~ 0
NOR_MOSI
Text HLabel 8800 4400 2    50   Input ~ 0
NOR_MISO
Text HLabel 8800 4300 2    50   Output ~ 0
NOR_SCK
Text HLabel 8800 4200 2    50   Output ~ 0
NOR_nCS
Text HLabel 7400 3900 0    50   BiDi ~ 0
EEPROM_SDA
Text HLabel 8800 2200 2    50   Output ~ 0
EEPROM_SCL
Text HLabel 9100 1400 2    50   Input ~ 0
VSense_Batt
Text HLabel 8100 1100 1    50   Input ~ 0
V+
Text HLabel 7200 1400 0    50   Input ~ 0
nRESET
Text HLabel 8800 3700 2    50   Output ~ 0
PWM_Buzzer
Text HLabel 8800 3100 2    50   Output ~ 0
KEY_MOSI
Text HLabel 7400 4100 0    50   Input ~ 0
KEY_MISO
Text HLabel 7400 4000 0    50   Output ~ 0
KEY_SCK
Text HLabel 8800 4000 2    50   Output ~ 0
KEY_nCS
Text HLabel 8800 3900 2    50   Output ~ 0
KEY_nSAMPLE
Text HLabel 7400 4200 0    50   Input ~ 0
ENCODER0_A
Text HLabel 7400 4300 0    50   Input ~ 0
ENCODER0_B
Text HLabel 8800 2300 2    50   Input ~ 0
ENCODER1_A
Text HLabel 8800 2400 2    50   Input ~ 0
ENCODER1_B
Text HLabel 7400 3100 0    50   Input ~ 0
ANALOG_IN_VPITCH
Text HLabel 7400 3000 0    50   Input ~ 0
ANALOG_IN_VROLL
Text HLabel 7400 3300 0    50   Input ~ 0
ANALOG_IN_VYAW
Text HLabel 7400 3200 0    50   Input ~ 0
ANALOG_IN_VTHROTTLE
Wire Wire Line
	10700 5350 11050 5350
Wire Wire Line
	10700 5550 11050 5550
Wire Wire Line
	10700 5650 11050 5650
Wire Wire Line
	10700 5750 11050 5750
Wire Wire Line
	10700 5850 11050 5850
Text HLabel 10200 5050 1    50   Input ~ 0
V+
$Comp
L power:GND #PWR0107
U 1 1 605AD389
P 10200 6350
F 0 "#PWR0107" H 10200 6100 50  0001 C CNN
F 1 "GND" H 10205 6177 50  0000 C CNN
F 2 "" H 10200 6350 50  0001 C CNN
F 3 "" H 10200 6350 50  0001 C CNN
	1    10200 6350
	1    0    0    -1  
$EndComp
Wire Wire Line
	10200 6250 10200 6300
Wire Wire Line
	10100 6250 10100 6300
Wire Wire Line
	10100 6300 10200 6300
Connection ~ 10200 6300
Wire Wire Line
	10200 6300 10200 6350
Text Label 10750 5350 0    50   ~ 0
JT_nRST
Text Label 10750 5550 0    50   ~ 0
JT_TCK
Text Label 10750 5650 0    50   ~ 0
JT_TMS
Text Label 10750 5750 0    50   ~ 0
JT_TDO
Text Label 10750 5850 0    50   ~ 0
JT_TDI
Text Label 8850 3500 0    50   ~ 0
JT_nRST
Wire Wire Line
	8100 1100 8100 1150
Wire Wire Line
	8200 1200 8200 1150
Wire Wire Line
	8200 1150 8100 1150
Connection ~ 8100 1150
Wire Wire Line
	8100 1150 8100 1200
Wire Wire Line
	8300 1200 8300 1150
Wire Wire Line
	8300 1150 8200 1150
Connection ~ 8200 1150
Wire Wire Line
	8000 1200 8000 1150
Wire Wire Line
	8000 1150 8100 1150
Wire Wire Line
	7900 1200 7900 1150
Wire Wire Line
	7900 1150 8000 1150
Connection ~ 8000 1150
Text HLabel 8400 1100 1    50   Input ~ 0
VDDA
$Comp
L Device:R_US R96
U 1 1 605B24E0
P 7200 1600
F 0 "R96" V 7100 1600 50  0000 C CNN
F 1 "10k" V 7300 1600 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 7240 1590 50  0001 C CNN
F 3 "~" H 7200 1600 50  0001 C CNN
F 4 "C25744" H 7200 1600 50  0001 C CNN "LCSC"
	1    7200 1600
	0    1    1    0   
$EndComp
Wire Wire Line
	7350 1600 7400 1600
$Comp
L power:GND #PWR0104
U 1 1 605B3866
P 7050 1600
F 0 "#PWR0104" H 7050 1350 50  0001 C CNN
F 1 "GND" V 7055 1472 50  0000 R CNN
F 2 "" H 7050 1600 50  0001 C CNN
F 3 "" H 7050 1600 50  0001 C CNN
	1    7050 1600
	0    1    1    0   
$EndComp
$Comp
L Device:C C52
U 1 1 605B4044
P 7300 2000
F 0 "C52" H 7186 1954 50  0000 R CNN
F 1 "2.2uF" H 7186 2045 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 7338 1850 50  0001 C CNN
F 3 "~" H 7300 2000 50  0001 C CNN
F 4 "C49217" H 7300 2000 50  0001 C CNN "LCSC"
	1    7300 2000
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 605B4752
P 7300 2150
F 0 "#PWR0105" H 7300 1900 50  0001 C CNN
F 1 "GND" H 7305 1977 50  0000 C CNN
F 2 "" H 7300 2150 50  0001 C CNN
F 3 "" H 7300 2150 50  0001 C CNN
	1    7300 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 1850 7300 1800
Wire Wire Line
	7300 1800 7400 1800
Text Notes 6550 2150 0    50   ~ 0
Ceramic Low-ESR
$Comp
L Device:R_US R97
U 1 1 605B572A
P 7300 1150
F 0 "R97" V 7200 1150 50  0000 C CNN
F 1 "10k" V 7400 1150 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 7340 1140 50  0001 C CNN
F 3 "~" H 7300 1150 50  0001 C CNN
F 4 "C25744" H 7300 1150 50  0001 C CNN "LCSC"
	1    7300 1150
	-1   0    0    1   
$EndComp
Wire Wire Line
	7300 1300 7300 1400
Text HLabel 7300 900  1    50   Input ~ 0
V+
Wire Wire Line
	7300 900  7300 1000
Wire Wire Line
	8800 3400 9100 3400
Text Label 8850 3400 0    50   ~ 0
JT_TDO
Wire Wire Line
	8800 3500 9100 3500
Wire Wire Line
	7300 1400 7400 1400
Wire Wire Line
	7200 1400 7300 1400
Connection ~ 7300 1400
Wire Wire Line
	8800 2900 9100 2900
Text Label 8850 2900 0    50   ~ 0
JT_TDI
Wire Wire Line
	8800 2800 9100 2800
Text Label 8850 2800 0    50   ~ 0
JT_TCK
Wire Wire Line
	8800 2700 9100 2700
Text Label 8850 2700 0    50   ~ 0
JT_TMS
Text HLabel 10050 4100 2    50   Output ~ 0
DBG_UART_TX
Text HLabel 6150 3500 0    50   Input ~ 0
DBG_UART_RX
Text GLabel 7900 5600 0    50   Output ~ 0
nBatteryPowerGood
Text GLabel 7900 5700 0    50   Output ~ 0
nBatteryChargeGood
Wire Wire Line
	7900 5700 8100 5700
Wire Wire Line
	7900 5600 8100 5600
Text Notes 7000 5500 0    50   ~ 0
Pipe this out to the shift registers for the moment...
$Comp
L 74xx:74HC595 U11
U 1 1 60495CB2
P 2950 2300
F 0 "U11" H 3200 2950 50  0000 C CNN
F 1 "74HC595" H 3200 2850 50  0000 C CNN
F 2 "Package_SO:SO-16_3.9x9.9mm_P1.27mm" H 2950 2300 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/sn74hc595.pdf" H 2950 2300 50  0001 C CNN
F 4 "C5947" H 2950 2300 50  0001 C CNN "LCSC"
	1    2950 2300
	1    0    0    -1  
$EndComp
Text HLabel 2550 2100 0    50   Output ~ 0
KEY_SCK
Text HLabel 2550 1900 0    50   Output ~ 0
KEY_MOSI
Text Label 1950 2400 0    50   ~ 0
KeyOut_nCS
Wire Wire Line
	1950 2400 2550 2400
$Comp
L power:GND #PWR096
U 1 1 60499345
P 2950 3000
F 0 "#PWR096" H 2950 2750 50  0001 C CNN
F 1 "GND" H 2955 2827 50  0000 C CNN
F 2 "" H 2950 3000 50  0001 C CNN
F 3 "" H 2950 3000 50  0001 C CNN
	1    2950 3000
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R90
U 1 1 604995B9
P 2450 2700
F 0 "R90" V 2350 2700 50  0000 C CNN
F 1 "10k" V 2550 2700 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 2490 2690 50  0001 C CNN
F 3 "~" H 2450 2700 50  0001 C CNN
F 4 "C25744" H 2450 2700 50  0001 C CNN "LCSC"
	1    2450 2700
	-1   0    0    1   
$EndComp
Wire Wire Line
	2450 2550 2450 2500
Wire Wire Line
	2450 2500 2550 2500
$Comp
L power:GND #PWR094
U 1 1 6049ABC8
P 2450 2850
F 0 "#PWR094" H 2450 2600 50  0001 C CNN
F 1 "GND" H 2455 2677 50  0000 C CNN
F 2 "" H 2450 2850 50  0001 C CNN
F 3 "" H 2450 2850 50  0001 C CNN
	1    2450 2850
	1    0    0    -1  
$EndComp
Text HLabel 2950 1700 1    50   Input ~ 0
V+
$Comp
L Device:C C50
U 1 1 6049BFC2
P 1650 2750
F 0 "C50" H 1765 2796 50  0000 L CNN
F 1 "100n" H 1765 2705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 1688 2600 50  0001 C CNN
F 3 "~" H 1650 2750 50  0001 C CNN
F 4 "C1525" H 1650 2750 50  0001 C CNN "LCSC"
	1    1650 2750
	1    0    0    -1  
$EndComp
Text HLabel 1650 2600 1    50   Input ~ 0
V+
$Comp
L power:GND #PWR092
U 1 1 6049C901
P 1650 2900
F 0 "#PWR092" H 1650 2650 50  0001 C CNN
F 1 "GND" H 1655 2727 50  0000 C CNN
F 2 "" H 1650 2900 50  0001 C CNN
F 3 "" H 1650 2900 50  0001 C CNN
	1    1650 2900
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R88
U 1 1 6049EC7C
P 1850 1950
F 0 "R88" V 1750 1950 50  0000 C CNN
F 1 "10k" V 1950 1950 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 1890 1940 50  0001 C CNN
F 3 "~" H 1850 1950 50  0001 C CNN
F 4 "C25744" H 1850 1950 50  0001 C CNN "LCSC"
	1    1850 1950
	-1   0    0    1   
$EndComp
Wire Wire Line
	1850 2100 1850 2200
Wire Wire Line
	1850 2200 2550 2200
Text HLabel 1850 1700 1    50   Input ~ 0
V+
Wire Wire Line
	1850 1700 1850 1800
Wire Wire Line
	8800 3600 9100 3600
Text Label 8850 3600 0    50   ~ 0
KeyOut_nCS
NoConn ~ 3350 2800
Text Notes 2700 1400 0    50   ~ 0
GPIO Outputs
$Comp
L Device:R_US R93
U 1 1 604BDD22
P 3850 2950
F 0 "R93" H 3782 2904 50  0000 R CNN
F 1 "560" H 3782 2995 50  0000 R CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 3890 2940 50  0001 C CNN
F 3 "~" H 3850 2950 50  0001 C CNN
F 4 "C11702" H 3850 2950 50  0001 C CNN "LCSC"
	1    3850 2950
	-1   0    0    1   
$EndComp
$Comp
L Device:R_US R94
U 1 1 604BE3A0
P 4150 2950
F 0 "R94" H 4082 2904 50  0000 R CNN
F 1 "560" H 4082 2995 50  0000 R CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 4190 2940 50  0001 C CNN
F 3 "~" H 4150 2950 50  0001 C CNN
F 4 "C11702" H 4150 2950 50  0001 C CNN "LCSC"
	1    4150 2950
	-1   0    0    1   
$EndComp
$Comp
L Device:R_US R95
U 1 1 604BE882
P 4450 2950
F 0 "R95" H 4382 2904 50  0000 R CNN
F 1 "560" H 4382 2995 50  0000 R CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 4490 2940 50  0001 C CNN
F 3 "~" H 4450 2950 50  0001 C CNN
F 4 "C11702" H 4450 2950 50  0001 C CNN "LCSC"
	1    4450 2950
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D4
U 1 1 604BFA89
P 3850 3350
F 0 "D4" V 3950 3350 50  0000 R CNN
F 1 "DBG_LED_2" H 4050 3450 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 3850 3350 50  0001 C CNN
F 3 "~" H 3850 3350 50  0001 C CNN
F 4 "C72041" H 3850 3350 50  0001 C CNN "LCSC"
	1    3850 3350
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D5
U 1 1 604C00A7
P 4150 3350
F 0 "D5" V 4250 3350 50  0000 R CNN
F 1 "DBG_LED_1" H 4350 3450 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 4150 3350 50  0001 C CNN
F 3 "~" H 4150 3350 50  0001 C CNN
F 4 "C72041" H 4150 3350 50  0001 C CNN "LCSC"
	1    4150 3350
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D6
U 1 1 604C059C
P 4450 3350
F 0 "D6" V 4550 3350 50  0000 R CNN
F 1 "DBG_LED_0" H 4650 3450 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 4450 3350 50  0001 C CNN
F 3 "~" H 4450 3350 50  0001 C CNN
F 4 "C72041" H 4450 3350 50  0001 C CNN "LCSC"
	1    4450 3350
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR099
U 1 1 604C0FC2
P 3850 3500
F 0 "#PWR099" H 3850 3250 50  0001 C CNN
F 1 "GND" H 3855 3327 50  0000 C CNN
F 2 "" H 3850 3500 50  0001 C CNN
F 3 "" H 3850 3500 50  0001 C CNN
	1    3850 3500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0100
U 1 1 604C131D
P 4150 3500
F 0 "#PWR0100" H 4150 3250 50  0001 C CNN
F 1 "GND" H 4155 3327 50  0000 C CNN
F 2 "" H 4150 3500 50  0001 C CNN
F 3 "" H 4150 3500 50  0001 C CNN
	1    4150 3500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 604C1680
P 4450 3500
F 0 "#PWR0101" H 4450 3250 50  0001 C CNN
F 1 "GND" H 4455 3327 50  0000 C CNN
F 2 "" H 4450 3500 50  0001 C CNN
F 3 "" H 4450 3500 50  0001 C CNN
	1    4450 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 3100 3850 3200
Wire Wire Line
	4150 3100 4150 3200
Wire Wire Line
	4450 3100 4450 3200
Wire Wire Line
	3850 2800 3850 2600
Wire Wire Line
	3850 2600 3350 2600
Wire Wire Line
	4150 2800 4150 2500
Wire Wire Line
	4150 2500 3350 2500
Wire Wire Line
	4450 2800 4450 2400
Wire Wire Line
	4450 2400 3350 2400
$Comp
L Device:Crystal Y1
U 1 1 604DCFCD
P 6400 2500
F 0 "Y1" V 6354 2631 50  0000 L CNN
F 1 "8MHz Crystal" V 6445 2631 50  0000 L CNN
F 2 "Crystal:Crystal_SMD_5032-2Pin_5.0x3.2mm" H 6400 2500 50  0001 C CNN
F 3 "~" H 6400 2500 50  0001 C CNN
F 4 "C115962" V 6400 2500 50  0001 C CNN "LCSC"
	1    6400 2500
	0    1    1    0   
$EndComp
$Comp
L Device:C C53
U 1 1 604DDB41
P 6150 2300
F 0 "C53" V 6300 2300 50  0000 C CNN
F 1 "1.5pF" V 5989 2300 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 6188 2150 50  0001 C CNN
F 3 "~" H 6150 2300 50  0001 C CNN
F 4 "C1552" H 6150 2300 50  0001 C CNN "LCSC"
	1    6150 2300
	0    1    1    0   
$EndComp
$Comp
L Device:C C54
U 1 1 604DE10D
P 6150 2700
F 0 "C54" V 6300 2700 50  0000 C CNN
F 1 "1.5pF" V 5989 2700 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 6188 2550 50  0001 C CNN
F 3 "~" H 6150 2700 50  0001 C CNN
F 4 "C1552" H 6150 2700 50  0001 C CNN "LCSC"
	1    6150 2700
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 604DE54A
P 6000 2700
F 0 "#PWR0103" H 6000 2450 50  0001 C CNN
F 1 "GND" V 6005 2572 50  0000 R CNN
F 2 "" H 6000 2700 50  0001 C CNN
F 3 "" H 6000 2700 50  0001 C CNN
	1    6000 2700
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 604DED19
P 6000 2300
F 0 "#PWR0102" H 6000 2050 50  0001 C CNN
F 1 "GND" V 6005 2172 50  0000 R CNN
F 2 "" H 6000 2300 50  0001 C CNN
F 3 "" H 6000 2300 50  0001 C CNN
	1    6000 2300
	0    1    1    0   
$EndComp
Wire Wire Line
	6300 2300 6400 2300
Wire Wire Line
	6400 2300 6400 2350
Wire Wire Line
	7400 2500 6850 2500
Wire Wire Line
	6850 2500 6850 2300
Wire Wire Line
	6850 2300 6400 2300
Connection ~ 6400 2300
Wire Wire Line
	7400 2600 6850 2600
Wire Wire Line
	6300 2700 6400 2700
Wire Wire Line
	6400 2700 6400 2650
Wire Wire Line
	6400 2700 6850 2700
Wire Wire Line
	6850 2700 6850 2600
Connection ~ 6400 2700
Text HLabel 3350 2000 2    50   Output ~ 0
BT_VCC_EN
Text HLabel 3350 1900 2    50   Output ~ 0
RF24_VCC_EN
Text Notes 3800 3850 0    50   ~ 0
Debug LEDs
$Comp
L Device:R_US R52
U 1 1 605FAE0B
P 9900 2400
F 0 "R52" V 9800 2400 50  0000 C CNN
F 1 "33" V 10000 2400 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 9940 2390 50  0001 C CNN
F 3 "~" H 9900 2400 50  0001 C CNN
F 4 "C25105" H 9900 2400 50  0001 C CNN "LCSC"
	1    9900 2400
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R54
U 1 1 605FB594
P 9900 2700
F 0 "R54" V 9800 2700 50  0000 C CNN
F 1 "33" V 10000 2700 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 9940 2690 50  0001 C CNN
F 3 "~" H 9900 2700 50  0001 C CNN
F 4 "C25105" H 9900 2700 50  0001 C CNN "LCSC"
	1    9900 2700
	0    1    1    0   
$EndComp
Wire Wire Line
	9750 2700 9400 2700
Wire Wire Line
	9400 2700 9400 2600
Wire Wire Line
	9400 2600 8800 2600
Wire Wire Line
	9750 2400 9400 2400
Wire Wire Line
	9400 2400 9400 2500
Wire Wire Line
	9400 2500 8800 2500
NoConn ~ 7400 4400
NoConn ~ 8800 3800
NoConn ~ 8800 3300
$Comp
L Device:C C55
U 1 1 6065388D
P 5500 1300
F 0 "C55" H 5615 1346 50  0000 L CNN
F 1 "100n" H 5615 1255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 5538 1150 50  0001 C CNN
F 3 "~" H 5500 1300 50  0001 C CNN
F 4 "C1525" H 5500 1300 50  0001 C CNN "LCSC"
	1    5500 1300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C56
U 1 1 606541DA
P 5900 1300
F 0 "C56" H 6015 1346 50  0000 L CNN
F 1 "100n" H 6015 1255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 5938 1150 50  0001 C CNN
F 3 "~" H 5900 1300 50  0001 C CNN
F 4 "C1525" H 5900 1300 50  0001 C CNN "LCSC"
	1    5900 1300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C57
U 1 1 6065440B
P 6300 1300
F 0 "C57" H 6415 1346 50  0000 L CNN
F 1 "100n" H 6415 1255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 6338 1150 50  0001 C CNN
F 3 "~" H 6300 1300 50  0001 C CNN
F 4 "C1525" H 6300 1300 50  0001 C CNN "LCSC"
	1    6300 1300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C33
U 1 1 60654852
P 5100 1300
F 0 "C33" H 5215 1346 50  0000 L CNN
F 1 "100n" H 5215 1255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 5138 1150 50  0001 C CNN
F 3 "~" H 5100 1300 50  0001 C CNN
F 4 "C1525" H 5100 1300 50  0001 C CNN "LCSC"
	1    5100 1300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C31
U 1 1 60654BAF
P 4700 1300
F 0 "C31" H 4815 1346 50  0000 L CNN
F 1 "100n" H 4815 1255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 4738 1150 50  0001 C CNN
F 3 "~" H 4700 1300 50  0001 C CNN
F 4 "C1525" H 4700 1300 50  0001 C CNN "LCSC"
	1    4700 1300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C29
U 1 1 606550A4
P 4300 1300
F 0 "C29" H 4415 1346 50  0000 L CNN
F 1 "100n" H 4415 1255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 4338 1150 50  0001 C CNN
F 3 "~" H 4300 1300 50  0001 C CNN
F 4 "C1525" H 4300 1300 50  0001 C CNN "LCSC"
	1    4300 1300
	1    0    0    -1  
$EndComp
Text HLabel 5900 1150 1    50   Input ~ 0
V+
Text HLabel 5500 1150 1    50   Input ~ 0
V+
Text HLabel 5100 1150 1    50   Input ~ 0
V+
Text HLabel 4700 1150 1    50   Input ~ 0
V+
Text HLabel 4300 1150 1    50   Input ~ 0
V+
$Comp
L power:GND #PWR0122
U 1 1 60655583
P 6300 1450
F 0 "#PWR0122" H 6300 1200 50  0001 C CNN
F 1 "GND" H 6305 1277 50  0000 C CNN
F 2 "" H 6300 1450 50  0001 C CNN
F 3 "" H 6300 1450 50  0001 C CNN
	1    6300 1450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0123
U 1 1 60655871
P 5900 1450
F 0 "#PWR0123" H 5900 1200 50  0001 C CNN
F 1 "GND" H 5905 1277 50  0000 C CNN
F 2 "" H 5900 1450 50  0001 C CNN
F 3 "" H 5900 1450 50  0001 C CNN
	1    5900 1450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0124
U 1 1 606559F7
P 5500 1450
F 0 "#PWR0124" H 5500 1200 50  0001 C CNN
F 1 "GND" H 5505 1277 50  0000 C CNN
F 2 "" H 5500 1450 50  0001 C CNN
F 3 "" H 5500 1450 50  0001 C CNN
	1    5500 1450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0125
U 1 1 60655C44
P 5100 1450
F 0 "#PWR0125" H 5100 1200 50  0001 C CNN
F 1 "GND" H 5105 1277 50  0000 C CNN
F 2 "" H 5100 1450 50  0001 C CNN
F 3 "" H 5100 1450 50  0001 C CNN
	1    5100 1450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0126
U 1 1 60655DFB
P 4700 1450
F 0 "#PWR0126" H 4700 1200 50  0001 C CNN
F 1 "GND" H 4705 1277 50  0000 C CNN
F 2 "" H 4700 1450 50  0001 C CNN
F 3 "" H 4700 1450 50  0001 C CNN
	1    4700 1450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0127
U 1 1 6065602B
P 4300 1450
F 0 "#PWR0127" H 4300 1200 50  0001 C CNN
F 1 "GND" H 4305 1277 50  0000 C CNN
F 2 "" H 4300 1450 50  0001 C CNN
F 3 "" H 4300 1450 50  0001 C CNN
	1    4300 1450
	1    0    0    -1  
$EndComp
Text HLabel 6300 1150 1    50   Input ~ 0
VDDA
NoConn ~ 8800 1600
NoConn ~ 8800 1700
NoConn ~ 8800 1500
$Comp
L Device:R_US R65
U 1 1 605A69C7
P 8950 1400
F 0 "R65" V 8850 1400 50  0000 C CNN
F 1 "10k" V 9050 1400 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 8990 1390 50  0001 C CNN
F 3 "~" H 8950 1400 50  0001 C CNN
F 4 "C25744" H 8950 1400 50  0001 C CNN "LCSC"
	1    8950 1400
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R91
U 1 1 605B2DF4
P 9900 4100
F 0 "R91" V 9800 4100 50  0000 C CNN
F 1 "10k" V 10000 4100 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 9940 4090 50  0001 C CNN
F 3 "~" H 9900 4100 50  0001 C CNN
F 4 "C25744" H 9900 4100 50  0001 C CNN "LCSC"
	1    9900 4100
	0    1    1    0   
$EndComp
Wire Wire Line
	9750 4100 8800 4100
$Comp
L Device:R_US R89
U 1 1 605B77B2
P 6300 3500
F 0 "R89" V 6200 3500 50  0000 C CNN
F 1 "10k" V 6400 3500 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 6340 3490 50  0001 C CNN
F 3 "~" H 6300 3500 50  0001 C CNN
F 4 "C25744" H 6300 3500 50  0001 C CNN "LCSC"
	1    6300 3500
	0    1    1    0   
$EndComp
NoConn ~ 7400 2800
Wire Wire Line
	6450 3500 7400 3500
$Comp
L Connector:TestPoint TP?
U 1 1 605CFE2B
P 3500 5500
AR Path="/6045890B/605CFE2B" Ref="TP?"  Part="1" 
AR Path="/604707FB/605CFE2B" Ref="TP18"  Part="1" 
F 0 "TP18" H 3558 5618 50  0000 L CNN
F 1 "TestPoint" H 3558 5527 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_2.5x2.5mm" H 3700 5500 50  0001 C CNN
F 3 "~" H 3700 5500 50  0001 C CNN
	1    3500 5500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR09
U 1 1 605D1BD5
P 3500 5500
F 0 "#PWR09" H 3500 5250 50  0001 C CNN
F 1 "GND" H 3505 5327 50  0000 C CNN
F 2 "" H 3500 5500 50  0001 C CNN
F 3 "" H 3500 5500 50  0001 C CNN
	1    3500 5500
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP?
U 1 1 605D1DEB
P 4000 5500
AR Path="/6045890B/605D1DEB" Ref="TP?"  Part="1" 
AR Path="/604707FB/605D1DEB" Ref="TP15"  Part="1" 
F 0 "TP15" H 4058 5618 50  0000 L CNN
F 1 "TestPoint" H 4058 5527 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_2.5x2.5mm" H 4200 5500 50  0001 C CNN
F 3 "~" H 4200 5500 50  0001 C CNN
	1    4000 5500
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP?
U 1 1 605D20E0
P 4500 5500
AR Path="/6045890B/605D20E0" Ref="TP?"  Part="1" 
AR Path="/604707FB/605D20E0" Ref="TP16"  Part="1" 
F 0 "TP16" H 4558 5618 50  0000 L CNN
F 1 "TestPoint" H 4558 5527 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_2.5x2.5mm" H 4700 5500 50  0001 C CNN
F 3 "~" H 4700 5500 50  0001 C CNN
	1    4500 5500
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP?
U 1 1 605D227A
P 5000 5500
AR Path="/6045890B/605D227A" Ref="TP?"  Part="1" 
AR Path="/604707FB/605D227A" Ref="TP17"  Part="1" 
F 0 "TP17" H 5058 5618 50  0000 L CNN
F 1 "TestPoint" H 5058 5527 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_2.5x2.5mm" H 5200 5500 50  0001 C CNN
F 3 "~" H 5200 5500 50  0001 C CNN
	1    5000 5500
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP?
U 1 1 605D23A2
P 5500 5500
AR Path="/6045890B/605D23A2" Ref="TP?"  Part="1" 
AR Path="/604707FB/605D23A2" Ref="TP19"  Part="1" 
F 0 "TP19" H 5558 5618 50  0000 L CNN
F 1 "TestPoint" H 5558 5527 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_2.5x2.5mm" H 5700 5500 50  0001 C CNN
F 3 "~" H 5700 5500 50  0001 C CNN
	1    5500 5500
	1    0    0    -1  
$EndComp
Text HLabel 4500 5500 3    50   Output ~ 0
KEY_MOSI
Text HLabel 5000 5500 3    50   Input ~ 0
KEY_MISO
Text HLabel 4000 5500 3    50   Output ~ 0
KEY_SCK
Text Label 5500 5500 3    50   ~ 0
KeyOut_nCS
Wire Wire Line
	5500 5500 5500 5800
$Comp
L Connector:TestPoint TP?
U 1 1 605D756E
P 6000 5500
AR Path="/6045890B/605D756E" Ref="TP?"  Part="1" 
AR Path="/604707FB/605D756E" Ref="TP20"  Part="1" 
F 0 "TP20" H 6058 5618 50  0000 L CNN
F 1 "TestPoint" H 6058 5527 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_2.5x2.5mm" H 6200 5500 50  0001 C CNN
F 3 "~" H 6200 5500 50  0001 C CNN
	1    6000 5500
	1    0    0    -1  
$EndComp
Text HLabel 6000 5500 3    50   Output ~ 0
KEY_nSAMPLE
$Comp
L Connector:TestPoint TP?
U 1 1 605D9B3F
P 6500 5500
AR Path="/6045890B/605D9B3F" Ref="TP?"  Part="1" 
AR Path="/604707FB/605D9B3F" Ref="TP21"  Part="1" 
F 0 "TP21" H 6558 5618 50  0000 L CNN
F 1 "TestPoint" H 6558 5527 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_2.5x2.5mm" H 6700 5500 50  0001 C CNN
F 3 "~" H 6700 5500 50  0001 C CNN
	1    6500 5500
	1    0    0    -1  
$EndComp
Text HLabel 6500 5500 3    50   Output ~ 0
KEY_nCS
$Comp
L Connector:TestPoint TP?
U 1 1 605E052A
P 6150 3150
AR Path="/6045890B/605E052A" Ref="TP?"  Part="1" 
AR Path="/604707FB/605E052A" Ref="TP22"  Part="1" 
F 0 "TP22" H 6208 3268 50  0000 L CNN
F 1 "TestPoint" H 6208 3177 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_2.5x2.5mm" H 6350 3150 50  0001 C CNN
F 3 "~" H 6350 3150 50  0001 C CNN
	1    6150 3150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR012
U 1 1 605E0530
P 6150 3150
F 0 "#PWR012" H 6150 2900 50  0001 C CNN
F 1 "GND" H 6155 2977 50  0000 C CNN
F 2 "" H 6150 3150 50  0001 C CNN
F 3 "" H 6150 3150 50  0001 C CNN
	1    6150 3150
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D3
U 1 1 6066A05B
P 6400 4550
F 0 "D3" V 6500 4550 50  0000 R CNN
F 1 "STATUS_LED" H 6600 4650 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 6400 4550 50  0001 C CNN
F 3 "~" H 6400 4550 50  0001 C CNN
F 4 "C72041" H 6400 4550 50  0001 C CNN "LCSC"
	1    6400 4550
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR090
U 1 1 6066A061
P 6400 4700
F 0 "#PWR090" H 6400 4450 50  0001 C CNN
F 1 "GND" H 6405 4527 50  0000 C CNN
F 2 "" H 6400 4700 50  0001 C CNN
F 3 "" H 6400 4700 50  0001 C CNN
	1    6400 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6400 4300 6400 4400
$Comp
L Device:R_US R92
U 1 1 6066A054
P 6400 4150
F 0 "R92" H 6332 4104 50  0000 R CNN
F 1 "560" H 6332 4195 50  0000 R CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 6440 4140 50  0001 C CNN
F 3 "~" H 6400 4150 50  0001 C CNN
F 4 "C11702" H 6400 4150 50  0001 C CNN "LCSC"
	1    6400 4150
	-1   0    0    1   
$EndComp
Wire Wire Line
	7400 3800 6400 3800
Wire Wire Line
	6400 3800 6400 4000
NoConn ~ 3350 2200
NoConn ~ 3350 2100
Wire Wire Line
	8400 1100 8400 1200
NoConn ~ 7400 4500
Connection ~ 8000 4750
Wire Wire Line
	7900 4750 7900 4700
Wire Wire Line
	8000 4750 7900 4750
Wire Wire Line
	8000 4750 8000 4700
Wire Wire Line
	8100 4750 8000 4750
Connection ~ 8200 4750
Wire Wire Line
	8300 4750 8300 4700
Wire Wire Line
	8200 4750 8300 4750
Wire Wire Line
	8100 4750 8100 4800
Connection ~ 8100 4750
Wire Wire Line
	8200 4750 8200 4700
Wire Wire Line
	8100 4750 8200 4750
Wire Wire Line
	8100 4700 8100 4750
$Comp
L power:GND #PWR0106
U 1 1 605ADCEE
P 8100 4800
F 0 "#PWR0106" H 8100 4550 50  0001 C CNN
F 1 "GND" H 8105 4627 50  0000 C CNN
F 2 "" H 8100 4800 50  0001 C CNN
F 3 "" H 8100 4800 50  0001 C CNN
	1    8100 4800
	1    0    0    -1  
$EndComp
$Comp
L MCU_ST_STM32F4:STM32F446RETx U13
U 1 1 6047114C
P 8100 2900
F 0 "U13" H 8100 3600 50  0000 C CNN
F 1 "STM32F446RETx" H 8100 3450 50  0000 C CNN
F 2 "Package_QFP:LQFP-64_10x10mm_P0.5mm" H 7500 1200 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00141306.pdf" H 8100 2900 50  0001 C CNN
F 4 "C69336" H 8100 2900 50  0001 C CNN "LCSC"
	1    8100 2900
	1    0    0    -1  
$EndComp
Text Notes 10550 2650 0    50   ~ 0
BMB: 07/11/21\n-- Need to add VBUS and ID lines to USB (PA10, 9)\n-- Need re-enumeration circuit to enable FS with 1.5k pullup. See nucleo.\n-- Move encoder 1A/B to PA2/3
Text Notes 1600 3450 0    50   ~ 0
BMB: 07/11/21\nUse smaller shift registers if JLC allows it.
$EndSCHEMATC
