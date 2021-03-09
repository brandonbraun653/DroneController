EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
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
L MCU_ST_STM32F4:STM32F446RETx U?
U 1 1 6047114C
P 5450 3350
F 0 "U?" H 5450 4050 50  0000 C CNN
F 1 "STM32F446RETx" H 5450 3900 50  0000 C CNN
F 2 "Package_QFP:LQFP-64_10x10mm_P0.5mm" H 4850 1650 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00141306.pdf" H 5450 3350 50  0001 C CNN
F 4 "C69336" H 5450 3350 50  0001 C CNN "LCSC"
	1    5450 3350
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_ARM_JTAG_SWD_10 J?
U 1 1 6047637A
P 8400 1750
F 0 "J?" H 7957 1796 50  0000 R CNN
F 1 "Conn_ARM_JTAG_SWD_10" H 7957 1705 50  0000 R CNN
F 2 "" H 8400 1750 50  0001 C CNN
F 3 "http://infocenter.arm.com/help/topic/com.arm.doc.ddi0314h/DDI0314H_coresight_components_trm.pdf" V 8050 500 50  0001 C CNN
	1    8400 1750
	1    0    0    -1  
$EndComp
Text HLabel 2650 2050 2    50   BiDi ~ 0
USB_D+
Text HLabel 2650 2200 2    50   BiDi ~ 0
USB_D-
Text HLabel 2650 2550 2    50   Input ~ 0
nBatt_Pwr_Good
Text HLabel 2650 2700 2    50   Input ~ 0
nBatt_Chg_Good
Text HLabel 2650 2800 2    50   Input ~ 0
vBatt_Sense
Text HLabel 2650 3050 2    50   Output ~ 0
nBattChgEn
Text HLabel 2650 3150 2    50   Output ~ 0
BattChgCfg0
Text HLabel 2650 3250 2    50   Output ~ 0
BattChgCfg1
Text HLabel 2600 4000 2    50   Input ~ 0
BT_UART_RX
Text HLabel 2600 4150 2    50   Output ~ 0
BT_UART_TX
Text HLabel 2600 4350 2    50   Output ~ 0
BT_nWakeup
Text HLabel 2600 4450 2    50   Output ~ 0
BT_nPowerUp
Text HLabel 2600 4550 2    50   Input ~ 0
BT_IRQ
Text HLabel 2600 5050 2    50   Output ~ 0
RF24_MOSI
Text HLabel 2600 5150 2    50   Input ~ 0
RF24_MISO
Text HLabel 2600 5250 2    50   Output ~ 0
RF24_SCK
Text HLabel 2600 5350 2    50   Output ~ 0
RF24_nCS
Text HLabel 2600 5450 2    50   Output ~ 0
RF24_CE
Text HLabel 2600 5550 2    50   Input ~ 0
RF24_nIRQ
Text HLabel 7050 3150 2    50   Output ~ 0
NOR_MOSI
Text HLabel 7050 3250 2    50   Input ~ 0
NOR_MISO
Text HLabel 7050 3400 2    50   Output ~ 0
NOR_SCK
Text HLabel 7050 3500 2    50   Output ~ 0
NOR_nCS
Text HLabel 7000 3900 2    50   BiDi ~ 0
EEPROM_SDA
Text HLabel 7000 4050 2    50   Output ~ 0
EEPROM_SCL
Text HLabel 7450 4600 2    50   Input ~ 0
VSense_USB
Text HLabel 7450 4750 2    50   Input ~ 0
VSense_Digital
Text HLabel 7450 4900 2    50   Input ~ 0
VSense_Radio
Text HLabel 7450 5050 2    50   Input ~ 0
VSense_Analog
Text HLabel 5450 1550 1    50   Input ~ 0
V+
Text HLabel 4550 1850 0    50   Input ~ 0
nRESET
Text HLabel 8600 2950 2    50   Input ~ 0
nBOOT
Text HLabel 9700 2750 2    50   Output ~ 0
PWM_Buzzer
Text HLabel 9700 3150 2    50   Output ~ 0
KEY_MOSI
Text HLabel 9700 3250 2    50   Input ~ 0
KEY_MISO
Text HLabel 9700 3350 2    50   Output ~ 0
KEY_SCK
Text HLabel 9700 3450 2    50   Output ~ 0
KEY_nCS
Text HLabel 9700 3550 2    50   Output ~ 0
KEY_nSAMPLE
Text HLabel 9700 3750 2    50   Input ~ 0
ENCODER0_A
Text HLabel 9700 3850 2    50   Input ~ 0
ENCODER0_B
Text HLabel 9700 3950 2    50   Input ~ 0
ENCODER1_A
Text HLabel 9700 4050 2    50   Input ~ 0
ENCODER1_B
Text HLabel 9700 4250 2    50   Input ~ 0
ANALOG_IN_VPITCH
Text HLabel 9700 4350 2    50   Input ~ 0
ANALOG_IN_VROLL
Text HLabel 9700 4450 2    50   Input ~ 0
ANALOG_IN_VYAW
Text HLabel 9700 4550 2    50   Input ~ 0
ANALOG_IN_VTHROTTLE
Wire Wire Line
	8900 1450 9250 1450
Wire Wire Line
	8900 1650 9250 1650
Wire Wire Line
	8900 1750 9250 1750
Wire Wire Line
	8900 1850 9250 1850
Wire Wire Line
	8900 1950 9250 1950
Text HLabel 8400 1150 1    50   Input ~ 0
V+
$Comp
L power:GND #PWR?
U 1 1 605AD389
P 8400 2450
F 0 "#PWR?" H 8400 2200 50  0001 C CNN
F 1 "GND" H 8405 2277 50  0000 C CNN
F 2 "" H 8400 2450 50  0001 C CNN
F 3 "" H 8400 2450 50  0001 C CNN
	1    8400 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	8400 2350 8400 2400
Wire Wire Line
	8300 2350 8300 2400
Wire Wire Line
	8300 2400 8400 2400
Connection ~ 8400 2400
Wire Wire Line
	8400 2400 8400 2450
$Comp
L power:GND #PWR?
U 1 1 605ADCEE
P 5450 5250
F 0 "#PWR?" H 5450 5000 50  0001 C CNN
F 1 "GND" H 5455 5077 50  0000 C CNN
F 2 "" H 5450 5250 50  0001 C CNN
F 3 "" H 5450 5250 50  0001 C CNN
	1    5450 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 5150 5450 5200
Wire Wire Line
	5450 5200 5550 5200
Wire Wire Line
	5550 5200 5550 5150
Connection ~ 5450 5200
Wire Wire Line
	5450 5200 5450 5250
Wire Wire Line
	5550 5200 5650 5200
Wire Wire Line
	5650 5200 5650 5150
Connection ~ 5550 5200
Wire Wire Line
	5450 5200 5350 5200
Wire Wire Line
	5350 5200 5350 5150
Wire Wire Line
	5350 5200 5250 5200
Wire Wire Line
	5250 5200 5250 5150
Connection ~ 5350 5200
Text Label 8950 1450 0    50   ~ 0
JT_nRST
Text Label 8950 1650 0    50   ~ 0
JT_TCK
Text Label 8950 1750 0    50   ~ 0
JT_TMS
Text Label 8950 1850 0    50   ~ 0
JT_TDO
Text Label 8950 1950 0    50   ~ 0
JT_TDI
Text Label 6200 3950 0    50   ~ 0
JT_nRST
Wire Wire Line
	5450 1550 5450 1600
Wire Wire Line
	5550 1650 5550 1600
Wire Wire Line
	5550 1600 5450 1600
Connection ~ 5450 1600
Wire Wire Line
	5450 1600 5450 1650
Wire Wire Line
	5650 1650 5650 1600
Wire Wire Line
	5650 1600 5550 1600
Connection ~ 5550 1600
Wire Wire Line
	5350 1650 5350 1600
Wire Wire Line
	5350 1600 5450 1600
Wire Wire Line
	5250 1650 5250 1600
Wire Wire Line
	5250 1600 5350 1600
Connection ~ 5350 1600
Text HLabel 5750 1550 1    50   Input ~ 0
VDDA
Wire Wire Line
	5750 1550 5750 1650
$Comp
L Device:R_US R?
U 1 1 605B24E0
P 4550 2050
F 0 "R?" V 4450 2050 50  0000 C CNN
F 1 "10k" V 4650 2050 50  0000 C CNN
F 2 "" V 4590 2040 50  0001 C CNN
F 3 "~" H 4550 2050 50  0001 C CNN
	1    4550 2050
	0    1    1    0   
$EndComp
Wire Wire Line
	4700 2050 4750 2050
$Comp
L power:GND #PWR?
U 1 1 605B3866
P 4400 2050
F 0 "#PWR?" H 4400 1800 50  0001 C CNN
F 1 "GND" V 4405 1922 50  0000 R CNN
F 2 "" H 4400 2050 50  0001 C CNN
F 3 "" H 4400 2050 50  0001 C CNN
	1    4400 2050
	0    1    1    0   
$EndComp
$Comp
L Device:C C?
U 1 1 605B4044
P 4650 2450
F 0 "C?" H 4536 2404 50  0000 R CNN
F 1 "2.2uF" H 4536 2495 50  0000 R CNN
F 2 "" H 4688 2300 50  0001 C CNN
F 3 "~" H 4650 2450 50  0001 C CNN
	1    4650 2450
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 605B4752
P 4650 2600
F 0 "#PWR?" H 4650 2350 50  0001 C CNN
F 1 "GND" H 4655 2427 50  0000 C CNN
F 2 "" H 4650 2600 50  0001 C CNN
F 3 "" H 4650 2600 50  0001 C CNN
	1    4650 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 2300 4650 2250
Wire Wire Line
	4650 2250 4750 2250
Text Notes 3900 2600 0    50   ~ 0
Ceramic Low-ESR
$Comp
L Device:R_US R?
U 1 1 605B572A
P 4650 1600
F 0 "R?" V 4550 1600 50  0000 C CNN
F 1 "10k" V 4750 1600 50  0000 C CNN
F 2 "" V 4690 1590 50  0001 C CNN
F 3 "~" H 4650 1600 50  0001 C CNN
	1    4650 1600
	-1   0    0    1   
$EndComp
Wire Wire Line
	4650 1750 4650 1850
Text HLabel 4650 1350 1    50   Input ~ 0
V+
Wire Wire Line
	4650 1350 4650 1450
Wire Wire Line
	6150 3850 6450 3850
Text Label 6200 3850 0    50   ~ 0
JT_TDO
Wire Wire Line
	6150 3950 6450 3950
Wire Wire Line
	4650 1850 4750 1850
Wire Wire Line
	4550 1850 4650 1850
Connection ~ 4650 1850
Wire Wire Line
	6150 3350 6450 3350
Text Label 6200 3350 0    50   ~ 0
JT_TDI
Wire Wire Line
	6150 3250 6450 3250
Text Label 6200 3250 0    50   ~ 0
JT_TCK
Wire Wire Line
	6150 3150 6450 3150
Text Label 6200 3150 0    50   ~ 0
JT_TMS
Text Notes 3250 3050 0    50   ~ 0
If not hurting for pins, use resonator
$EndSCHEMATC
