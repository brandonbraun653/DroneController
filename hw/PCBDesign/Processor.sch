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
Text HLabel 8100 5600 2    50   Input ~ 0
nBatt_Pwr_Good
Text HLabel 8100 5700 2    50   Input ~ 0
nBatt_Chg_Good
Text HLabel 8800 1400 2    50   Input ~ 0
vBatt_Sense
Text HLabel 3350 2100 2    50   Output ~ 0
nBattChgEn
Text HLabel 3350 1900 2    50   Output ~ 0
BattChgCfg0
Text HLabel 3350 2000 2    50   Output ~ 0
BattChgCfg1
Text HLabel 7400 3700 0    50   Input ~ 0
BT_UART_RX
Text HLabel 7400 3600 0    50   Output ~ 0
BT_UART_TX
Text HLabel 3350 2200 2    50   Output ~ 0
BT_nWakeup
Text HLabel 3350 2300 2    50   Output ~ 0
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
Text HLabel 8800 4000 2    50   Output ~ 0
KEY_nCS
Text HLabel 8800 3900 2    50   Output ~ 0
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
Text HLabel 8800 4100 2    50   Output ~ 0
DBG_UART_TX
Text HLabel 7400 3500 0    50   Input ~ 0
DBG_UART_RX
Text Notes 1250 1100 0    50   ~ 0
PCB Checklist: \n    https://github.com/azonenberg/pcb-checklist\n1. Ensure serial lines are correct for each device\n2. Verify the shift register connections match the pin names\n3. Verify interrupt lines are all separated and can fire individually.
Text Notes 9800 1350 0    50   ~ 0
Device Mapping:\nSPI1 - RF24 Radio\nSPI2 - NOR Flash\nSPI3 - GPIO Shift Registers
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
L 74xx:74HC595 U?
U 1 1 60495CB2
P 2950 2300
F 0 "U?" H 3200 2950 50  0000 C CNN
F 1 "74HC595" H 3200 2850 50  0000 C CNN
F 2 "" H 2950 2300 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/sn74hc595.pdf" H 2950 2300 50  0001 C CNN
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
L power:GND #PWR?
U 1 1 60499345
P 2950 3000
F 0 "#PWR?" H 2950 2750 50  0001 C CNN
F 1 "GND" H 2955 2827 50  0000 C CNN
F 2 "" H 2950 3000 50  0001 C CNN
F 3 "" H 2950 3000 50  0001 C CNN
	1    2950 3000
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R?
U 1 1 604995B9
P 2450 2700
F 0 "R?" V 2350 2700 50  0000 C CNN
F 1 "10k" V 2550 2700 50  0000 C CNN
F 2 "" V 2490 2690 50  0001 C CNN
F 3 "~" H 2450 2700 50  0001 C CNN
	1    2450 2700
	-1   0    0    1   
$EndComp
Wire Wire Line
	2450 2550 2450 2500
Wire Wire Line
	2450 2500 2550 2500
$Comp
L power:GND #PWR?
U 1 1 6049ABC8
P 2450 2850
F 0 "#PWR?" H 2450 2600 50  0001 C CNN
F 1 "GND" H 2455 2677 50  0000 C CNN
F 2 "" H 2450 2850 50  0001 C CNN
F 3 "" H 2450 2850 50  0001 C CNN
	1    2450 2850
	1    0    0    -1  
$EndComp
Text HLabel 2950 1700 1    50   Input ~ 0
V+
$Comp
L Device:C C?
U 1 1 6049BFC2
P 1650 2750
F 0 "C?" H 1765 2796 50  0000 L CNN
F 1 "100n" H 1765 2705 50  0000 L CNN
F 2 "" H 1688 2600 50  0001 C CNN
F 3 "~" H 1650 2750 50  0001 C CNN
	1    1650 2750
	1    0    0    -1  
$EndComp
Text HLabel 1650 2600 1    50   Input ~ 0
V+
$Comp
L power:GND #PWR?
U 1 1 6049C901
P 1650 2900
F 0 "#PWR?" H 1650 2650 50  0001 C CNN
F 1 "GND" H 1655 2727 50  0000 C CNN
F 2 "" H 1650 2900 50  0001 C CNN
F 3 "" H 1650 2900 50  0001 C CNN
	1    1650 2900
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R?
U 1 1 6049EC7C
P 1850 1950
F 0 "R?" V 1750 1950 50  0000 C CNN
F 1 "10k" V 1950 1950 50  0000 C CNN
F 2 "" V 1890 1940 50  0001 C CNN
F 3 "~" H 1850 1950 50  0001 C CNN
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
$Comp
L 74xx:74HC595 U?
U 1 1 604A3733
P 2950 4150
F 0 "U?" H 3200 4800 50  0000 C CNN
F 1 "74HC595" H 3200 4700 50  0000 C CNN
F 2 "" H 2950 4150 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/sn74hc595.pdf" H 2950 4150 50  0001 C CNN
	1    2950 4150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 604A5ADA
P 2950 4850
F 0 "#PWR?" H 2950 4600 50  0001 C CNN
F 1 "GND" H 2955 4677 50  0000 C CNN
F 2 "" H 2950 4850 50  0001 C CNN
F 3 "" H 2950 4850 50  0001 C CNN
	1    2950 4850
	1    0    0    -1  
$EndComp
Text HLabel 2950 3550 1    50   Input ~ 0
V+
$Comp
L Device:C C?
U 1 1 604A7BC3
P 1700 4600
F 0 "C?" H 1815 4646 50  0000 L CNN
F 1 "100n" H 1815 4555 50  0000 L CNN
F 2 "" H 1738 4450 50  0001 C CNN
F 3 "~" H 1700 4600 50  0001 C CNN
	1    1700 4600
	1    0    0    -1  
$EndComp
Text HLabel 1700 4450 1    50   Input ~ 0
V+
$Comp
L power:GND #PWR?
U 1 1 604A7BCA
P 1700 4750
F 0 "#PWR?" H 1700 4500 50  0001 C CNN
F 1 "GND" H 1705 4577 50  0000 C CNN
F 2 "" H 1700 4750 50  0001 C CNN
F 3 "" H 1700 4750 50  0001 C CNN
	1    1700 4750
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R?
U 1 1 604A8914
P 2450 4550
F 0 "R?" V 2350 4550 50  0000 C CNN
F 1 "10k" V 2550 4550 50  0000 C CNN
F 2 "" V 2490 4540 50  0001 C CNN
F 3 "~" H 2450 4550 50  0001 C CNN
	1    2450 4550
	-1   0    0    1   
$EndComp
Wire Wire Line
	2450 4400 2450 4350
Wire Wire Line
	2450 4350 2550 4350
$Comp
L power:GND #PWR?
U 1 1 604AA63F
P 2450 4700
F 0 "#PWR?" H 2450 4450 50  0001 C CNN
F 1 "GND" H 2455 4527 50  0000 C CNN
F 2 "" H 2450 4700 50  0001 C CNN
F 3 "" H 2450 4700 50  0001 C CNN
	1    2450 4700
	1    0    0    -1  
$EndComp
Text HLabel 2550 3950 0    50   Output ~ 0
KEY_SCK
$Comp
L Device:R_US R?
U 1 1 604AB457
P 1850 3750
F 0 "R?" V 1750 3750 50  0000 C CNN
F 1 "10k" V 1950 3750 50  0000 C CNN
F 2 "" V 1890 3740 50  0001 C CNN
F 3 "~" H 1850 3750 50  0001 C CNN
	1    1850 3750
	-1   0    0    1   
$EndComp
Text HLabel 1850 3500 1    50   Input ~ 0
V+
Wire Wire Line
	1850 3500 1850 3600
Wire Wire Line
	1850 4050 2550 4050
Wire Wire Line
	1850 3900 1850 4050
Wire Wire Line
	2550 4250 2000 4250
Text Label 2000 4250 0    50   ~ 0
KeyOut_nCS
NoConn ~ 3350 2800
NoConn ~ 3350 4650
Wire Wire Line
	2550 3750 2250 3750
Wire Wire Line
	2250 3750 2250 3300
Wire Wire Line
	2250 3300 3500 3300
Wire Wire Line
	3500 3300 3500 2600
Wire Wire Line
	3500 2600 3350 2600
Text Notes 2700 1400 0    50   ~ 0
GPIO Outputs
$Comp
L Device:R_US R?
U 1 1 604BBD6A
P 3550 4700
F 0 "R?" H 3482 4654 50  0000 R CNN
F 1 "560" H 3482 4745 50  0000 R CNN
F 2 "" V 3590 4690 50  0001 C CNN
F 3 "~" H 3550 4700 50  0001 C CNN
	1    3550 4700
	-1   0    0    1   
$EndComp
$Comp
L Device:R_US R?
U 1 1 604BDD22
P 3850 4700
F 0 "R?" H 3782 4654 50  0000 R CNN
F 1 "560" H 3782 4745 50  0000 R CNN
F 2 "" V 3890 4690 50  0001 C CNN
F 3 "~" H 3850 4700 50  0001 C CNN
	1    3850 4700
	-1   0    0    1   
$EndComp
$Comp
L Device:R_US R?
U 1 1 604BE3A0
P 4150 4700
F 0 "R?" H 4082 4654 50  0000 R CNN
F 1 "560" H 4082 4745 50  0000 R CNN
F 2 "" V 4190 4690 50  0001 C CNN
F 3 "~" H 4150 4700 50  0001 C CNN
	1    4150 4700
	-1   0    0    1   
$EndComp
$Comp
L Device:R_US R?
U 1 1 604BE882
P 4450 4700
F 0 "R?" H 4382 4654 50  0000 R CNN
F 1 "560" H 4382 4745 50  0000 R CNN
F 2 "" V 4490 4690 50  0001 C CNN
F 3 "~" H 4450 4700 50  0001 C CNN
	1    4450 4700
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D?
U 1 1 604BF32A
P 3550 5100
F 0 "D?" V 3589 4982 50  0000 R CNN
F 1 "LED" V 3498 4982 50  0000 R CNN
F 2 "" H 3550 5100 50  0001 C CNN
F 3 "~" H 3550 5100 50  0001 C CNN
	1    3550 5100
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D?
U 1 1 604BFA89
P 3850 5100
F 0 "D?" V 3889 4982 50  0000 R CNN
F 1 "LED" V 3798 4982 50  0000 R CNN
F 2 "" H 3850 5100 50  0001 C CNN
F 3 "~" H 3850 5100 50  0001 C CNN
	1    3850 5100
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D?
U 1 1 604C00A7
P 4150 5100
F 0 "D?" V 4189 4982 50  0000 R CNN
F 1 "LED" V 4098 4982 50  0000 R CNN
F 2 "" H 4150 5100 50  0001 C CNN
F 3 "~" H 4150 5100 50  0001 C CNN
	1    4150 5100
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D?
U 1 1 604C059C
P 4450 5100
F 0 "D?" V 4489 4982 50  0000 R CNN
F 1 "LED" V 4398 4982 50  0000 R CNN
F 2 "" H 4450 5100 50  0001 C CNN
F 3 "~" H 4450 5100 50  0001 C CNN
	1    4450 5100
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 604C0A44
P 3550 5250
F 0 "#PWR?" H 3550 5000 50  0001 C CNN
F 1 "GND" H 3555 5077 50  0000 C CNN
F 2 "" H 3550 5250 50  0001 C CNN
F 3 "" H 3550 5250 50  0001 C CNN
	1    3550 5250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 604C0FC2
P 3850 5250
F 0 "#PWR?" H 3850 5000 50  0001 C CNN
F 1 "GND" H 3855 5077 50  0000 C CNN
F 2 "" H 3850 5250 50  0001 C CNN
F 3 "" H 3850 5250 50  0001 C CNN
	1    3850 5250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 604C131D
P 4150 5250
F 0 "#PWR?" H 4150 5000 50  0001 C CNN
F 1 "GND" H 4155 5077 50  0000 C CNN
F 2 "" H 4150 5250 50  0001 C CNN
F 3 "" H 4150 5250 50  0001 C CNN
	1    4150 5250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 604C1680
P 4450 5250
F 0 "#PWR?" H 4450 5000 50  0001 C CNN
F 1 "GND" H 4455 5077 50  0000 C CNN
F 2 "" H 4450 5250 50  0001 C CNN
F 3 "" H 4450 5250 50  0001 C CNN
	1    4450 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 4850 3550 4950
Wire Wire Line
	3850 4850 3850 4950
Wire Wire Line
	4150 4850 4150 4950
Wire Wire Line
	4450 4850 4450 4950
Wire Wire Line
	3550 4550 3550 4450
Wire Wire Line
	3550 4450 3350 4450
Wire Wire Line
	3850 4550 3850 4350
Wire Wire Line
	3850 4350 3350 4350
Wire Wire Line
	4150 4550 4150 4250
Wire Wire Line
	4150 4250 3350 4250
Wire Wire Line
	4450 4550 4450 4150
Wire Wire Line
	4450 4150 3350 4150
NoConn ~ 3350 4050
NoConn ~ 3350 3950
NoConn ~ 3350 3850
NoConn ~ 3350 3750
$Comp
L Device:Crystal Y?
U 1 1 604DCFCD
P 6400 2500
F 0 "Y?" V 6354 2631 50  0000 L CNN
F 1 "8MHz Crystal" V 6445 2631 50  0000 L CNN
F 2 "" H 6400 2500 50  0001 C CNN
F 3 "~" H 6400 2500 50  0001 C CNN
F 4 "C115962" V 6400 2500 50  0001 C CNN "LCSC"
	1    6400 2500
	0    1    1    0   
$EndComp
$Comp
L Device:C 1.5pF
U 1 1 604DDB41
P 6150 2300
F 0 "1.5pF" V 6300 2300 50  0000 C CNN
F 1 "C" V 5989 2300 50  0000 C CNN
F 2 "" H 6188 2150 50  0001 C CNN
F 3 "~" H 6150 2300 50  0001 C CNN
	1    6150 2300
	0    1    1    0   
$EndComp
$Comp
L Device:C 1.5pF
U 1 1 604DE10D
P 6150 2700
F 0 "1.5pF" V 6300 2700 50  0000 C CNN
F 1 "C" V 5989 2700 50  0000 C CNN
F 2 "" H 6188 2550 50  0001 C CNN
F 3 "~" H 6150 2700 50  0001 C CNN
	1    6150 2700
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 604DE54A
P 6000 2700
F 0 "#PWR?" H 6000 2450 50  0001 C CNN
F 1 "GND" V 6005 2572 50  0000 R CNN
F 2 "" H 6000 2700 50  0001 C CNN
F 3 "" H 6000 2700 50  0001 C CNN
	1    6000 2700
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 604DED19
P 6000 2300
F 0 "#PWR?" H 6000 2050 50  0001 C CNN
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
Text HLabel 3350 2400 2    50   Output ~ 0
BT_VCC_EN
Text HLabel 3350 2500 2    50   Output ~ 0
RF24_VCC_EN
Text Notes 3800 5600 0    50   ~ 0
Debug LEDs
$EndSCHEMATC
