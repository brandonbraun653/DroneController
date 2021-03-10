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
P 8100 2900
F 0 "U?" H 8100 3600 50  0000 C CNN
F 1 "STM32F446RETx" H 8100 3450 50  0000 C CNN
F 2 "Package_QFP:LQFP-64_10x10mm_P0.5mm" H 7500 1200 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00141306.pdf" H 8100 2900 50  0001 C CNN
F 4 "C69336" H 8100 2900 50  0001 C CNN "LCSC"
	1    8100 2900
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_ARM_JTAG_SWD_10 J?
U 1 1 6047637A
P 10200 5650
F 0 "J?" H 9900 6250 50  0000 R CNN
F 1 "Conn_ARM_JTAG_SWD_10" V 9750 6100 50  0000 R CNN
F 2 "" H 10200 5650 50  0001 C CNN
F 3 "http://infocenter.arm.com/help/topic/com.arm.doc.ddi0314h/DDI0314H_coresight_components_trm.pdf" V 9850 4400 50  0001 C CNN
	1    10200 5650
	1    0    0    -1  
$EndComp
Text HLabel 8800 2600 2    50   BiDi ~ 0
USB_D+
Text HLabel 8800 2500 2    50   BiDi ~ 0
USB_D-
Text HLabel 550  3300 2    50   Input ~ 0
nBatt_Pwr_Good
Text HLabel 550  3400 2    50   Input ~ 0
nBatt_Chg_Good
Text HLabel 8800 1400 2    50   Input ~ 0
vBatt_Sense
Text HLabel 1350 3300 2    50   Output ~ 0
nBattChgEn
Text HLabel 1350 3100 2    50   Output ~ 0
BattChgCfg0
Text HLabel 1350 3200 2    50   Output ~ 0
BattChgCfg1
Text HLabel 7400 3700 0    50   Input ~ 0
BT_UART_RX
Text HLabel 7400 3600 0    50   Output ~ 0
BT_UART_TX
Text HLabel 1350 3400 2    50   Output ~ 0
BT_nWakeup
Text HLabel 1350 3500 2    50   Output ~ 0
BT_nPowerUp
Text HLabel 7400 3800 0    50   Input ~ 0
BT_IRQ
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
Text HLabel 8800 1500 2    50   Input ~ 0
VSense_Digital
Text HLabel 8800 1600 2    50   Input ~ 0
VSense_Radio
Text HLabel 8800 1700 2    50   Input ~ 0
VSense_Analog
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
Text HLabel 2250 3400 2    50   Output ~ 0
KEY_nCS
Text HLabel 2250 3500 2    50   Output ~ 0
KEY_nSAMPLE
Text HLabel 7400 2800 0    50   Input ~ 0
ENCODER0_A
Text HLabel 7400 4200 0    50   Input ~ 0
ENCODER0_B
Text HLabel 8800 2400 2    50   Input ~ 0
ENCODER1_A
Text HLabel 8800 2300 2    50   Input ~ 0
ENCODER1_B
Text HLabel 7400 3000 0    50   Input ~ 0
ANALOG_IN_VPITCH
Text HLabel 7400 3100 0    50   Input ~ 0
ANALOG_IN_VROLL
Text HLabel 7400 3200 0    50   Input ~ 0
ANALOG_IN_VYAW
Text HLabel 7400 3300 0    50   Input ~ 0
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
L power:GND #PWR?
U 1 1 605AD389
P 10200 6350
F 0 "#PWR?" H 10200 6100 50  0001 C CNN
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
$Comp
L power:GND #PWR?
U 1 1 605ADCEE
P 8100 4800
F 0 "#PWR?" H 8100 4550 50  0001 C CNN
F 1 "GND" H 8105 4627 50  0000 C CNN
F 2 "" H 8100 4800 50  0001 C CNN
F 3 "" H 8100 4800 50  0001 C CNN
	1    8100 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	8100 4700 8100 4750
Wire Wire Line
	8100 4750 8200 4750
Wire Wire Line
	8200 4750 8200 4700
Connection ~ 8100 4750
Wire Wire Line
	8100 4750 8100 4800
Wire Wire Line
	8200 4750 8300 4750
Wire Wire Line
	8300 4750 8300 4700
Connection ~ 8200 4750
Wire Wire Line
	8100 4750 8000 4750
Wire Wire Line
	8000 4750 8000 4700
Wire Wire Line
	8000 4750 7900 4750
Wire Wire Line
	7900 4750 7900 4700
Connection ~ 8000 4750
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
Wire Wire Line
	8400 1100 8400 1200
$Comp
L Device:R_US R?
U 1 1 605B24E0
P 7200 1600
F 0 "R?" V 7100 1600 50  0000 C CNN
F 1 "10k" V 7300 1600 50  0000 C CNN
F 2 "" V 7240 1590 50  0001 C CNN
F 3 "~" H 7200 1600 50  0001 C CNN
	1    7200 1600
	0    1    1    0   
$EndComp
Wire Wire Line
	7350 1600 7400 1600
$Comp
L power:GND #PWR?
U 1 1 605B3866
P 7050 1600
F 0 "#PWR?" H 7050 1350 50  0001 C CNN
F 1 "GND" V 7055 1472 50  0000 R CNN
F 2 "" H 7050 1600 50  0001 C CNN
F 3 "" H 7050 1600 50  0001 C CNN
	1    7050 1600
	0    1    1    0   
$EndComp
$Comp
L Device:C C?
U 1 1 605B4044
P 7300 2000
F 0 "C?" H 7186 1954 50  0000 R CNN
F 1 "2.2uF" H 7186 2045 50  0000 R CNN
F 2 "" H 7338 1850 50  0001 C CNN
F 3 "~" H 7300 2000 50  0001 C CNN
	1    7300 2000
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 605B4752
P 7300 2150
F 0 "#PWR?" H 7300 1900 50  0001 C CNN
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
L Device:R_US R?
U 1 1 605B572A
P 7300 1150
F 0 "R?" V 7200 1150 50  0000 C CNN
F 1 "10k" V 7400 1150 50  0000 C CNN
F 2 "" V 7340 1140 50  0001 C CNN
F 3 "~" H 7300 1150 50  0001 C CNN
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
Text Notes 5900 2600 0    50   ~ 0
If not hurting for pins, use resonator
Text Notes 3200 3000 0    50   ~ 0
Input Interrupts (4)
Text Notes 2100 3000 0    50   ~ 0
Fast Outputs (5)
Text HLabel 8800 4100 2    50   Output ~ 0
DBG_UART_TX
Text HLabel 7400 3500 0    50   Input ~ 0
DBG_UART_RX
Text Notes 1450 1950 0    50   ~ 0
Place the discrete outputs on the same SPI bus as the discrete inputs.
Text Notes 1450 1550 0    50   ~ 0
Have the discrete interrupt inputs be AND-ed together. Need to invert to the same logic.\nHonestly it might be good to have them sampled along with the keys.\nAre any of the interrupts super short such that a sample couldn't be made?
Text Notes 1450 2150 0    50   ~ 0
Might need to use BT paired with a phone app instead of a screen.
Text Notes 550  3000 0    50   ~ 0
Discrete Inputs
Text Notes 1300 3000 0    50   ~ 0
Slow Outputs (5)
Text Notes 1700 4100 0    50   ~ 0
PCB Checklist:\n1. Ensure serial lines are correct for each device
Text Notes 9800 1350 0    50   ~ 0
Device Mapping:\nSPI1 - RF24 Radio\nSPI2 - NOR Flash\nSPI3 - GPIO Shift Registers
Text Notes 1450 2600 0    50   ~ 0
Need some leds on the output for debugging as well.
$EndSCHEMATC
