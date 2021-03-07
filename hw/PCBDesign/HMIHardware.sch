EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 11
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
L 74xx:74HC165 U?
U 1 1 60465132
P 1900 3400
F 0 "U?" H 1650 4350 50  0000 C CNN
F 1 "74HC165" H 1650 4200 50  0000 C CNN
F 2 "Package_SO:SOIC-16_3.9x9.9mm_P1.27mm" H 1900 3400 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/74HC_HCT165.pdf" H 1900 3400 50  0001 C CNN
F 4 "C5613" H 1900 3400 50  0001 C CNN "LCSC"
	1    1900 3400
	-1   0    0    -1  
$EndComp
$Comp
L 74xx:74HC165 U?
U 1 1 6046592A
P 1900 5800
F 0 "U?" H 1650 6750 50  0000 C CNN
F 1 "74HC165" H 1650 6600 50  0000 C CNN
F 2 "Package_SO:SOIC-16_3.9x9.9mm_P1.27mm" H 1900 5800 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/74HC_HCT165.pdf" H 1900 5800 50  0001 C CNN
F 4 "C5613" H 1900 5800 50  0001 C CNN "LCSC"
	1    1900 5800
	-1   0    0    -1  
$EndComp
$Sheet
S 5600 1350 900  600 
U 6044E41E
F0 "Rotary Encoder" 50
F1 "RotaryEncoders.sch" 50
F2 "V+" I L 5600 1450 50 
F3 "ENC0_nBTN" O L 5600 1600 50 
F4 "ENC0_A" O R 6500 1450 50 
F5 "ENC0_B" O R 6500 1550 50 
F6 "ENC1_nBTN" O L 5600 1700 50 
F7 "ENC1_A" O R 6500 1750 50 
F8 "ENC1_B" O R 6500 1850 50 
$EndSheet
$Sheet
S 5600 3550 900  1200
U 60452796
F0 "Toggle Switches" 50
F1 "ToggleSW.sch" 50
$EndSheet
$Sheet
S 8350 1200 900  1000
U 60452A36
F0 "Joy Stick Inputs" 50
F1 "JoyStick.sch" 50
$EndSheet
$Sheet
S 8600 3800 1000 1000
U 60452CE3
F0 "Audio Output" 50
F1 "AudioOut.sch" 50
$EndSheet
$Sheet
S 5600 2250 900  1050
U 60456C21
F0 "Button Input" 50
F1 "ButtonInput.sch" 50
F2 "V+" I L 5600 2350 50 
F3 "KeyLeft" O L 5600 2500 50 
F4 "KeyRight" O L 5600 2600 50 
F5 "KeyUp" O L 5600 2700 50 
F6 "KeyDown" O L 5600 2800 50 
F7 "KeyEnter" O L 5600 2900 50 
F8 "KeyEscape" O L 5600 3000 50 
F9 "KeyReset" O L 5600 3100 50 
F10 "KeyBoot" O L 5600 3200 50 
$EndSheet
Text HLabel 7650 3700 2    50   Input ~ 0
PWM_Buzzer
Text HLabel 7650 4200 2    50   Input ~ 0
KEY_MOSI
Text HLabel 1250 5200 0    50   Output ~ 0
KEY_MISO
Text HLabel 7650 4500 2    50   Output ~ 0
KEY_SCK
Text HLabel 7650 4650 2    50   Output ~ 0
KEY_nCS
Text HLabel 7650 4800 2    50   Output ~ 0
KEY_nSAMPLE
Text HLabel 6650 1450 2    50   Output ~ 0
ENC0_A
Text HLabel 6650 1550 2    50   Output ~ 0
ENC0_B
Text HLabel 6650 1750 2    50   Output ~ 0
ENC1_A
Text HLabel 6650 1850 2    50   Output ~ 0
ENC1_B
Text HLabel 8500 2900 2    50   Output ~ 0
JS_VP
Text HLabel 8500 3000 2    50   Output ~ 0
JS_VR
Text HLabel 8500 3100 2    50   Output ~ 0
JS_VY
Text HLabel 8500 3200 2    50   Output ~ 0
JS_VT
Text HLabel 5450 2350 0    50   Input ~ 0
V+
Text HLabel 5500 3200 0    50   Output ~ 0
nBOOT
Text HLabel 5500 3100 0    50   Output ~ 0
nRESET
$Comp
L power:GND #PWR?
U 1 1 6066FFA2
P 1900 4400
F 0 "#PWR?" H 1900 4150 50  0001 C CNN
F 1 "GND" H 1905 4227 50  0000 C CNN
F 2 "" H 1900 4400 50  0001 C CNN
F 3 "" H 1900 4400 50  0001 C CNN
	1    1900 4400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 606707FE
P 1900 6800
F 0 "#PWR?" H 1900 6550 50  0001 C CNN
F 1 "GND" H 1905 6627 50  0000 C CNN
F 2 "" H 1900 6800 50  0001 C CNN
F 3 "" H 1900 6800 50  0001 C CNN
	1    1900 6800
	1    0    0    -1  
$EndComp
Text HLabel 1900 2500 1    50   Input ~ 0
V+
Text HLabel 1900 4900 1    50   Input ~ 0
V+
Text HLabel 2500 3800 2    50   Output ~ 0
KEY_nSAMPLE
Text HLabel 2500 6200 2    50   Output ~ 0
KEY_nSAMPLE
Text HLabel 2500 4100 2    50   Output ~ 0
KEY_nCS
Text HLabel 2500 4000 2    50   Output ~ 0
KEY_SCK
Text HLabel 2500 6400 2    50   Output ~ 0
KEY_SCK
Text HLabel 2500 6500 2    50   Output ~ 0
KEY_nCS
Wire Wire Line
	1400 2800 1250 2800
Wire Wire Line
	1250 2800 1250 4750
Wire Wire Line
	1250 4750 2500 4750
Wire Wire Line
	2500 4750 2500 5200
Wire Wire Line
	2500 5200 2400 5200
NoConn ~ 1400 2900
NoConn ~ 1400 5300
$Comp
L Device:R_US R?
U 1 1 60672EC3
P 2750 2800
F 0 "R?" V 2955 2800 50  0000 C CNN
F 1 "10k" V 2864 2800 50  0000 C CNN
F 2 "" V 2790 2790 50  0001 C CNN
F 3 "~" H 2750 2800 50  0001 C CNN
	1    2750 2800
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60672ECA
P 3000 2800
F 0 "#PWR?" H 3000 2550 50  0001 C CNN
F 1 "GND" H 3005 2627 50  0000 C CNN
F 2 "" H 3000 2800 50  0001 C CNN
F 3 "" H 3000 2800 50  0001 C CNN
	1    3000 2800
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2900 2800 3000 2800
Wire Wire Line
	2400 2800 2600 2800
Wire Wire Line
	1250 5200 1400 5200
Wire Wire Line
	2500 6200 2400 6200
Wire Wire Line
	2500 6400 2400 6400
Wire Wire Line
	2500 6500 2400 6500
Wire Wire Line
	2400 3800 2500 3800
Wire Wire Line
	2400 4000 2500 4000
Wire Wire Line
	2400 4100 2500 4100
Text HLabel 800  3100 1    50   Output ~ 0
V+
$Comp
L Device:C C?
U 1 1 60673CDD
P 800 3250
F 0 "C?" H 915 3296 50  0000 L CNN
F 1 "100n" H 915 3205 50  0000 L CNN
F 2 "" H 838 3100 50  0001 C CNN
F 3 "~" H 800 3250 50  0001 C CNN
	1    800  3250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6067404D
P 800 3400
F 0 "#PWR?" H 800 3150 50  0001 C CNN
F 1 "GND" H 805 3227 50  0000 C CNN
F 2 "" H 800 3400 50  0001 C CNN
F 3 "" H 800 3400 50  0001 C CNN
	1    800  3400
	1    0    0    -1  
$EndComp
Text HLabel 800  5750 1    50   Output ~ 0
V+
$Comp
L Device:C C?
U 1 1 6067545F
P 800 5900
F 0 "C?" H 915 5946 50  0000 L CNN
F 1 "100n" H 915 5855 50  0000 L CNN
F 2 "" H 838 5750 50  0001 C CNN
F 3 "~" H 800 5900 50  0001 C CNN
	1    800  5900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60675465
P 800 6050
F 0 "#PWR?" H 800 5800 50  0001 C CNN
F 1 "GND" H 805 5877 50  0000 C CNN
F 2 "" H 800 6050 50  0001 C CNN
F 3 "" H 800 6050 50  0001 C CNN
	1    800  6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 1850 6650 1850
Wire Wire Line
	6500 1750 6650 1750
Wire Wire Line
	6500 1550 6650 1550
Wire Wire Line
	6500 1450 6650 1450
Text HLabel 5450 1450 0    50   Input ~ 0
V+
Wire Wire Line
	5450 1450 5600 1450
Wire Wire Line
	5450 2350 5600 2350
Wire Wire Line
	5500 3200 5600 3200
Wire Wire Line
	5500 3100 5600 3100
$EndSCHEMATC
