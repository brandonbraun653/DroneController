EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 9 11
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
L RF:NRF24L01_Breakout U?
U 1 1 60458E2E
P 6300 1700
F 0 "U?" H 6650 2300 50  0000 L CNN
F 1 "NRF24L01_Breakout" H 6350 2200 50  0000 L CNN
F 2 "RF_Module:nRF24L01_Breakout" H 6450 2300 50  0001 L CIN
F 3 "http://www.nordicsemi.com/eng/content/download/2730/34105/file/nRF24L01_Product_Specification_v2_0.pdf" H 6300 1600 50  0001 C CNN
	1    6300 1700
	1    0    0    -1  
$EndComp
Text Notes 4100 2850 0    50   ~ 0
Need to add symbol for the HM-BT4502 bluetooth radio
Text HLabel 4550 3000 2    50   Output ~ 0
BT_INT_REQ
Text HLabel 4550 3100 2    50   Input ~ 0
nBT_WAKEUP
Text HLabel 4550 3200 2    50   Input ~ 0
nBT_PWR_UP
Text HLabel 4550 3300 2    50   Input ~ 0
BT_RX
Text HLabel 4550 3400 2    50   Output ~ 0
BT_TX
Text HLabel 5650 1400 0    50   Input ~ 0
RF24_SPI_MOSI
Text HLabel 5650 1500 0    50   Output ~ 0
RF24_SPI_MISO
Text HLabel 5650 1600 0    50   Input ~ 0
RF24_SPI_SCK
Text HLabel 5650 1700 0    50   Input ~ 0
nRF24_SPI_CS
Text HLabel 5650 1900 0    50   Input ~ 0
RF24_CE
Text HLabel 5650 2000 0    50   Output ~ 0
nRF24_IRQ
$Comp
L power:GND #PWR?
U 1 1 60625E14
P 6300 2300
F 0 "#PWR?" H 6300 2050 50  0001 C CNN
F 1 "GND" H 6305 2127 50  0000 C CNN
F 2 "" H 6300 2300 50  0001 C CNN
F 3 "" H 6300 2300 50  0001 C CNN
	1    6300 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 1400 5800 1400
Wire Wire Line
	5650 1500 5800 1500
Wire Wire Line
	5650 1600 5800 1600
Wire Wire Line
	5650 1700 5800 1700
Wire Wire Line
	5650 1900 5800 1900
Wire Wire Line
	5650 2000 5800 2000
Text HLabel 7400 1800 0    50   Output ~ 0
nRF24_IRQ
$Comp
L Device:C C?
U 1 1 606288B3
P 8300 1750
F 0 "C?" H 8415 1796 50  0000 L CNN
F 1 "10uF" H 8415 1705 50  0000 L CNN
F 2 "" H 8338 1600 50  0001 C CNN
F 3 "~" H 8300 1750 50  0001 C CNN
	1    8300 1750
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 60628CEA
P 8700 1750
F 0 "C?" H 8815 1796 50  0000 L CNN
F 1 "100nF" H 8815 1705 50  0000 L CNN
F 2 "" H 8738 1600 50  0001 C CNN
F 3 "~" H 8700 1750 50  0001 C CNN
	1    8700 1750
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R?
U 1 1 60628F56
P 7750 1800
F 0 "R?" H 7818 1846 50  0000 L CNN
F 1 "10k" H 7818 1755 50  0000 L CNN
F 2 "" V 7790 1790 50  0001 C CNN
F 3 "~" H 7750 1800 50  0001 C CNN
	1    7750 1800
	0    1    1    0   
$EndComp
Wire Wire Line
	8300 1600 8300 1500
$Comp
L power:GND #PWR?
U 1 1 60629A72
P 8300 1900
F 0 "#PWR?" H 8300 1650 50  0001 C CNN
F 1 "GND" H 8305 1727 50  0000 C CNN
F 2 "" H 8300 1900 50  0001 C CNN
F 3 "" H 8300 1900 50  0001 C CNN
	1    8300 1900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60629F1D
P 8700 1900
F 0 "#PWR?" H 8700 1650 50  0001 C CNN
F 1 "GND" H 8705 1727 50  0000 C CNN
F 2 "" H 8700 1900 50  0001 C CNN
F 3 "" H 8700 1900 50  0001 C CNN
	1    8700 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	8300 1500 8700 1500
Wire Wire Line
	8700 1500 8700 1600
Text Notes 9550 1450 2    50   ~ 0
The 10uF cap must be ceramic
Wire Wire Line
	7600 1800 7400 1800
$Comp
L Device:R_US R?
U 1 1 6062A636
P 7750 1500
F 0 "R?" H 7818 1546 50  0000 L CNN
F 1 "10k" H 7818 1455 50  0000 L CNN
F 2 "" V 7790 1490 50  0001 C CNN
F 3 "~" H 7750 1500 50  0001 C CNN
	1    7750 1500
	0    1    1    0   
$EndComp
Text HLabel 7400 1500 0    50   Input ~ 0
nRF24_SPI_CS
Wire Wire Line
	7600 1500 7400 1500
Wire Wire Line
	7900 1800 8000 1800
Wire Wire Line
	8000 1800 8000 1500
Connection ~ 8000 1500
Wire Wire Line
	8000 1500 8000 1300
Wire Wire Line
	7900 1500 8000 1500
Connection ~ 8300 1500
Wire Wire Line
	8300 1300 8300 1500
Text HLabel 8000 1300 1    50   Input ~ 0
V+
Text HLabel 8300 1300 1    50   Input ~ 0
V+
Text HLabel 6300 1100 1    50   Input ~ 0
V+
Text HLabel 4550 3600 2    50   Input ~ 0
BT_VCC_EN
Text HLabel 4200 1000 0    50   Input ~ 0
RF24_VCC_EN
$EndSCHEMATC
