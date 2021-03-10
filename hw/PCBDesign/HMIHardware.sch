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
P 6450 2500
F 0 "U?" H 6200 3450 50  0000 C CNN
F 1 "74HC165" H 6200 3300 50  0000 C CNN
F 2 "Package_SO:SOIC-16_3.9x9.9mm_P1.27mm" H 6450 2500 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/74HC_HCT165.pdf" H 6450 2500 50  0001 C CNN
F 4 "C5613" H 6450 2500 50  0001 C CNN "LCSC"
	1    6450 2500
	-1   0    0    -1  
$EndComp
$Sheet
S 9600 750  900  600 
U 6044E41E
F0 "Rotary Encoder" 50
F1 "RotaryEncoders.sch" 50
F2 "V+" I L 9600 850 50 
F3 "ENC0_nBTN" O L 9600 1000 50 
F4 "ENC0_A" O R 10500 850 50 
F5 "ENC0_B" O R 10500 950 50 
F6 "ENC1_nBTN" O L 9600 1100 50 
F7 "ENC1_A" O R 10500 1150 50 
F8 "ENC1_B" O R 10500 1250 50 
$EndSheet
$Sheet
S 9600 2950 900  1500
U 60452796
F0 "Toggle Switches" 50
F1 "ToggleSW.sch" 50
F2 "V+" I L 9600 3050 50 
F3 "dPitch_Trim_Up" O L 9600 3200 50 
F4 "dPitch_Trim_Down" O L 9600 3300 50 
F5 "dRoll_Trim_Up" O L 9600 3400 50 
F6 "dRoll_Trim_Down" O L 9600 3500 50 
F7 "dYaw_Trim_Up" O L 9600 3600 50 
F8 "dYaw_Trim_Down" O L 9600 3700 50 
F9 "dThrottle_Trim_Up" O L 9600 3800 50 
F10 "dThrottle_Trim_Down" O L 9600 3900 50 
F11 "UserSwitchA" O L 9600 4050 50 
F12 "UserSwitchB" O L 9600 4150 50 
F13 "UserSwitchC" O L 9600 4250 50 
F14 "UserSwitchD" O L 9600 4350 50 
$EndSheet
$Sheet
S 9600 4700 900  750 
U 60452A36
F0 "Joy Stick Inputs" 50
F1 "JoyStick.sch" 50
F2 "AnalogRef" I L 9600 4800 50 
F3 "vPitch" O L 9600 5050 50 
F4 "vRoll" O L 9600 5150 50 
F5 "vThrottle" O L 9600 5350 50 
F6 "vYaw" O L 9600 5250 50 
$EndSheet
$Sheet
S 9600 5700 900  450 
U 60452CE3
F0 "Audio Output" 50
F1 "AudioOut.sch" 50
F2 "V+" I L 9600 5850 50 
F3 "PWM_In" I L 9600 6000 50 
$EndSheet
$Sheet
S 9600 1650 900  1050
U 60456C21
F0 "Button Input" 50
F1 "ButtonInput.sch" 50
F2 "V+" I L 9600 1750 50 
F3 "KeyLeft" O L 9600 1900 50 
F4 "KeyRight" O L 9600 2000 50 
F5 "KeyUp" O L 9600 2100 50 
F6 "KeyDown" O L 9600 2200 50 
F7 "KeyEnter" O L 9600 2300 50 
F8 "KeyEscape" O L 9600 2400 50 
F9 "KeyReset" O L 9600 2500 50 
F10 "KeyBoot" O L 9600 2600 50 
$EndSheet
Text HLabel 9550 6000 0    50   Input ~ 0
PWM_Buzzer
Text HLabel 10650 850  2    50   Output ~ 0
ENC0_A
Text HLabel 10650 950  2    50   Output ~ 0
ENC0_B
Text HLabel 10650 1150 2    50   Output ~ 0
ENC1_A
Text HLabel 10650 1250 2    50   Output ~ 0
ENC1_B
Text HLabel 9500 5050 0    50   Output ~ 0
JS_VP
Text HLabel 9500 5150 0    50   Output ~ 0
JS_VR
Text HLabel 9500 5250 0    50   Output ~ 0
JS_VY
Text HLabel 9500 5350 0    50   Output ~ 0
JS_VT
Text HLabel 9450 1750 0    50   Input ~ 0
V+
Text HLabel 9500 2600 0    50   Output ~ 0
nBOOT
Text HLabel 9500 2500 0    50   Output ~ 0
nRESET
$Comp
L power:GND #PWR?
U 1 1 6066FFA2
P 6450 3500
F 0 "#PWR?" H 6450 3250 50  0001 C CNN
F 1 "GND" H 6455 3327 50  0000 C CNN
F 2 "" H 6450 3500 50  0001 C CNN
F 3 "" H 6450 3500 50  0001 C CNN
	1    6450 3500
	1    0    0    -1  
$EndComp
Text HLabel 6450 1600 1    50   Input ~ 0
V+
Text HLabel 7050 2900 2    50   Output ~ 0
KEY_nSAMPLE
Text HLabel 7050 3200 2    50   Output ~ 0
KEY_nCS
Text HLabel 7050 3100 2    50   Output ~ 0
KEY_SCK
NoConn ~ 5950 2000
$Comp
L Device:R_US R?
U 1 1 60672EC3
P 7300 1900
F 0 "R?" V 7505 1900 50  0000 C CNN
F 1 "10k" V 7414 1900 50  0000 C CNN
F 2 "" V 7340 1890 50  0001 C CNN
F 3 "~" H 7300 1900 50  0001 C CNN
	1    7300 1900
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60672ECA
P 7550 1900
F 0 "#PWR?" H 7550 1650 50  0001 C CNN
F 1 "GND" H 7555 1727 50  0000 C CNN
F 2 "" H 7550 1900 50  0001 C CNN
F 3 "" H 7550 1900 50  0001 C CNN
	1    7550 1900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7450 1900 7550 1900
Wire Wire Line
	6950 1900 7150 1900
Wire Wire Line
	6950 2900 7050 2900
Wire Wire Line
	6950 3100 7050 3100
Wire Wire Line
	6950 3200 7050 3200
Text HLabel 5800 2350 1    50   Output ~ 0
V+
$Comp
L Device:C C?
U 1 1 60673CDD
P 5800 2500
F 0 "C?" H 5915 2546 50  0000 L CNN
F 1 "100n" H 5915 2455 50  0000 L CNN
F 2 "" H 5838 2350 50  0001 C CNN
F 3 "~" H 5800 2500 50  0001 C CNN
	1    5800 2500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6067404D
P 5800 2650
F 0 "#PWR?" H 5800 2400 50  0001 C CNN
F 1 "GND" H 5805 2477 50  0000 C CNN
F 2 "" H 5800 2650 50  0001 C CNN
F 3 "" H 5800 2650 50  0001 C CNN
	1    5800 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	10500 1250 10650 1250
Wire Wire Line
	10500 1150 10650 1150
Wire Wire Line
	10500 950  10650 950 
Wire Wire Line
	10500 850  10650 850 
Text HLabel 9450 850  0    50   Input ~ 0
V+
Wire Wire Line
	9450 850  9600 850 
Wire Wire Line
	9450 1750 9600 1750
Wire Wire Line
	9500 2600 9600 2600
Wire Wire Line
	9500 2500 9600 2500
Text HLabel 9500 4800 0    50   Input ~ 0
VAnalogRef
Wire Wire Line
	9500 5050 9600 5050
Wire Wire Line
	9500 5150 9600 5150
Wire Wire Line
	9500 5250 9600 5250
Wire Wire Line
	9500 5350 9600 5350
Wire Wire Line
	9500 4800 9600 4800
Text HLabel 9550 5850 0    50   Input ~ 0
V+
Wire Wire Line
	9550 6000 9600 6000
Wire Wire Line
	9550 5850 9600 5850
Text HLabel 9450 3050 0    50   Input ~ 0
V+
Wire Wire Line
	9450 3050 9600 3050
$Comp
L power:GND #PWR?
U 1 1 60675465
P 1550 2750
F 0 "#PWR?" H 1550 2500 50  0001 C CNN
F 1 "GND" H 1555 2577 50  0000 C CNN
F 2 "" H 1550 2750 50  0001 C CNN
F 3 "" H 1550 2750 50  0001 C CNN
	1    1550 2750
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 6067545F
P 1550 2600
F 0 "C?" H 1665 2646 50  0000 L CNN
F 1 "100n" H 1665 2555 50  0000 L CNN
F 2 "" H 1588 2450 50  0001 C CNN
F 3 "~" H 1550 2600 50  0001 C CNN
	1    1550 2600
	1    0    0    -1  
$EndComp
Text HLabel 1550 2450 1    50   Output ~ 0
V+
Wire Wire Line
	2800 3200 2700 3200
Wire Wire Line
	2800 3100 2700 3100
Wire Wire Line
	2800 2900 2700 2900
Wire Wire Line
	1550 1900 1700 1900
NoConn ~ 1700 2000
Text HLabel 2800 3200 2    50   Output ~ 0
KEY_nCS
Text HLabel 2800 3100 2    50   Output ~ 0
KEY_SCK
Text HLabel 2800 2900 2    50   Output ~ 0
KEY_nSAMPLE
Text HLabel 2200 1600 1    50   Input ~ 0
V+
$Comp
L power:GND #PWR?
U 1 1 606707FE
P 2200 3500
F 0 "#PWR?" H 2200 3250 50  0001 C CNN
F 1 "GND" H 2205 3327 50  0000 C CNN
F 2 "" H 2200 3500 50  0001 C CNN
F 3 "" H 2200 3500 50  0001 C CNN
	1    2200 3500
	1    0    0    -1  
$EndComp
Text HLabel 1550 1900 0    50   Output ~ 0
KEY_MISO
$Comp
L 74xx:74HC165 U?
U 1 1 6046592A
P 2200 2500
F 0 "U?" H 1950 3450 50  0000 C CNN
F 1 "74HC165" H 1950 3300 50  0000 C CNN
F 2 "Package_SO:SOIC-16_3.9x9.9mm_P1.27mm" H 2200 2500 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/74HC_HCT165.pdf" H 2200 2500 50  0001 C CNN
F 4 "C5613" H 2200 2500 50  0001 C CNN "LCSC"
	1    2200 2500
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60500016
P 3750 2750
F 0 "#PWR?" H 3750 2500 50  0001 C CNN
F 1 "GND" H 3755 2577 50  0000 C CNN
F 2 "" H 3750 2750 50  0001 C CNN
F 3 "" H 3750 2750 50  0001 C CNN
	1    3750 2750
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 6050001C
P 3750 2600
F 0 "C?" H 3865 2646 50  0000 L CNN
F 1 "100n" H 3865 2555 50  0000 L CNN
F 2 "" H 3788 2450 50  0001 C CNN
F 3 "~" H 3750 2600 50  0001 C CNN
	1    3750 2600
	1    0    0    -1  
$EndComp
Text HLabel 3750 2450 1    50   Output ~ 0
V+
Wire Wire Line
	5000 3200 4900 3200
Wire Wire Line
	5000 3100 4900 3100
Wire Wire Line
	5000 2900 4900 2900
NoConn ~ 3900 2000
Text HLabel 5000 3200 2    50   Output ~ 0
KEY_nCS
Text HLabel 5000 3100 2    50   Output ~ 0
KEY_SCK
Text HLabel 5000 2900 2    50   Output ~ 0
KEY_nSAMPLE
Text HLabel 4400 1600 1    50   Input ~ 0
V+
$Comp
L power:GND #PWR?
U 1 1 6050002C
P 4400 3500
F 0 "#PWR?" H 4400 3250 50  0001 C CNN
F 1 "GND" H 4405 3327 50  0000 C CNN
F 2 "" H 4400 3500 50  0001 C CNN
F 3 "" H 4400 3500 50  0001 C CNN
	1    4400 3500
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74HC165 U?
U 1 1 60500034
P 4400 2500
F 0 "U?" H 4150 3450 50  0000 C CNN
F 1 "74HC165" H 4150 3300 50  0000 C CNN
F 2 "Package_SO:SOIC-16_3.9x9.9mm_P1.27mm" H 4400 2500 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/74HC_HCT165.pdf" H 4400 2500 50  0001 C CNN
F 4 "C5613" H 4400 2500 50  0001 C CNN "LCSC"
	1    4400 2500
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2700 1900 3900 1900
Wire Wire Line
	4900 1900 5950 1900
Wire Wire Line
	6950 2000 7150 2000
Wire Wire Line
	6950 2100 7150 2100
Wire Wire Line
	6950 2200 7150 2200
Wire Wire Line
	6950 2300 7150 2300
Wire Wire Line
	6950 2400 7150 2400
Wire Wire Line
	6950 2500 7150 2500
Wire Wire Line
	6950 2600 7150 2600
Wire Wire Line
	6950 2700 7150 2700
Entry Wire Line
	7150 2000 7250 2100
Entry Wire Line
	7150 2100 7250 2200
Entry Wire Line
	7150 2200 7250 2300
Entry Wire Line
	7150 2300 7250 2400
Entry Wire Line
	7150 2400 7250 2500
Entry Wire Line
	7150 2500 7250 2600
Entry Wire Line
	7150 2600 7250 2700
Entry Wire Line
	7150 2700 7250 2800
Wire Wire Line
	9600 1000 9200 1000
Wire Wire Line
	9600 1100 9200 1100
Wire Wire Line
	9600 1900 9200 1900
Wire Wire Line
	9600 2000 9200 2000
Wire Wire Line
	9600 2100 9200 2100
Wire Wire Line
	9600 2200 9200 2200
Wire Wire Line
	9600 2300 9200 2300
Wire Wire Line
	9600 2400 9200 2400
Wire Bus Line
	7250 2800 9100 2800
Entry Wire Line
	9100 900  9200 1000
Entry Wire Line
	9100 1000 9200 1100
Entry Wire Line
	9100 1800 9200 1900
Entry Wire Line
	9100 1900 9200 2000
Entry Wire Line
	9100 2000 9200 2100
Entry Wire Line
	9100 2100 9200 2200
Entry Wire Line
	9100 2200 9200 2300
Entry Wire Line
	9100 2300 9200 2400
Text Label 7000 2000 0    50   ~ 0
d0
Text Label 7000 2100 0    50   ~ 0
d1
Text Label 7000 2200 0    50   ~ 0
d2
Text Label 7000 2300 0    50   ~ 0
d3
Text Label 7000 2400 0    50   ~ 0
d4
Text Label 7000 2500 0    50   ~ 0
d5
Text Label 7000 2600 0    50   ~ 0
d6
Text Label 7000 2700 0    50   ~ 0
d7
Text Label 9300 1000 0    50   ~ 0
d0
Text Label 9300 1100 0    50   ~ 0
d1
Text Label 9300 1900 0    50   ~ 0
d2
Text Label 9300 2000 0    50   ~ 0
d3
Text Label 9300 2100 0    50   ~ 0
d4
Text Label 9300 2200 0    50   ~ 0
d5
Text Label 9300 2300 0    50   ~ 0
d6
Text Label 9300 2400 0    50   ~ 0
d7
Wire Wire Line
	4900 2000 5100 2000
Wire Wire Line
	4900 2100 5100 2100
Wire Wire Line
	4900 2200 5100 2200
Wire Wire Line
	4900 2300 5100 2300
Wire Wire Line
	4900 2400 5100 2400
Wire Wire Line
	4900 2500 5100 2500
Wire Wire Line
	4900 2600 5100 2600
Wire Wire Line
	4900 2700 5100 2700
Entry Wire Line
	5100 2000 5200 2100
Entry Wire Line
	5100 2100 5200 2200
Entry Wire Line
	5100 2200 5200 2300
Entry Wire Line
	5100 2300 5200 2400
Entry Wire Line
	5100 2400 5200 2500
Entry Wire Line
	5100 2500 5200 2600
Entry Wire Line
	5100 2600 5200 2700
Entry Wire Line
	5100 2700 5200 2800
Wire Wire Line
	9600 3200 9200 3200
Wire Wire Line
	9600 3300 9200 3300
Wire Wire Line
	9600 3400 9200 3400
Wire Wire Line
	9600 3500 9200 3500
Wire Wire Line
	9600 3600 9200 3600
Wire Wire Line
	9600 3700 9200 3700
Wire Wire Line
	9600 3800 9200 3800
Wire Wire Line
	9600 3900 9200 3900
Wire Wire Line
	9600 4050 9200 4050
Wire Wire Line
	9600 4150 9200 4150
Wire Wire Line
	9600 4250 9200 4250
Wire Wire Line
	9600 4350 9200 4350
Entry Wire Line
	9100 3100 9200 3200
Entry Wire Line
	9100 3300 9200 3400
Entry Wire Line
	9100 3200 9200 3300
Entry Wire Line
	9100 3400 9200 3500
Entry Wire Line
	9100 3600 9200 3700
Entry Wire Line
	9100 3700 9200 3800
Entry Wire Line
	9100 3500 9200 3600
Entry Wire Line
	9100 3800 9200 3900
Wire Bus Line
	5200 2800 5650 2800
Text Label 4950 2000 0    50   ~ 0
d8
Text Label 4950 2100 0    50   ~ 0
d9
Text Label 4950 2200 0    50   ~ 0
d10
Text Label 4950 2300 0    50   ~ 0
d11
Text Label 4950 2400 0    50   ~ 0
d12
Text Label 4950 2500 0    50   ~ 0
d13
Text Label 4950 2600 0    50   ~ 0
d14
Text Label 4950 2700 0    50   ~ 0
d15
Text Label 9300 3200 0    50   ~ 0
d8
Text Label 9300 3300 0    50   ~ 0
d9
Text Label 9300 3400 0    50   ~ 0
d10
Text Label 9300 3500 0    50   ~ 0
d11
Text Label 9300 3600 0    50   ~ 0
d12
Text Label 9300 3700 0    50   ~ 0
d13
Text Label 9300 3800 0    50   ~ 0
d14
Text Label 9300 3900 0    50   ~ 0
d15
Wire Bus Line
	9100 3800 5650 3800
Wire Bus Line
	5650 2800 5650 3800
Entry Wire Line
	9100 3950 9200 4050
Entry Wire Line
	9100 4050 9200 4150
Entry Wire Line
	9100 4150 9200 4250
Entry Wire Line
	9100 4250 9200 4350
Text Label 9300 4050 0    50   ~ 0
d16
Text Label 9300 4150 0    50   ~ 0
d17
Text Label 9300 4250 0    50   ~ 0
d18
Text Label 9300 4350 0    50   ~ 0
d19
Wire Wire Line
	2700 2000 2900 2000
Wire Wire Line
	2700 2100 2900 2100
Wire Wire Line
	2700 2200 2900 2200
Wire Wire Line
	2700 2300 2900 2300
Wire Wire Line
	2700 2400 2900 2400
Wire Wire Line
	2700 2500 2900 2500
Wire Wire Line
	2700 2600 2900 2600
Wire Wire Line
	2700 2700 2900 2700
Entry Wire Line
	2900 2000 3000 2100
Entry Wire Line
	2900 2100 3000 2200
Entry Wire Line
	2900 2200 3000 2300
Entry Wire Line
	2900 2300 3000 2400
Wire Bus Line
	3000 2800 3500 2800
Wire Bus Line
	3500 2800 3500 4250
Text Label 2750 2000 0    50   ~ 0
d16
Text Label 2750 2100 0    50   ~ 0
d17
Text Label 2750 2200 0    50   ~ 0
d18
Text Label 2750 2300 0    50   ~ 0
d19
Text Label 2750 2400 0    50   ~ 0
d20
Text Label 2750 2500 0    50   ~ 0
d21
Text Label 2750 2600 0    50   ~ 0
d22
Text Label 2750 2700 0    50   ~ 0
d23
Entry Wire Line
	2900 2700 3000 2800
Entry Wire Line
	2900 2600 3000 2700
Entry Wire Line
	2900 2500 3000 2600
Entry Wire Line
	2900 2400 3000 2500
$Comp
L Device:R_US R?
U 1 1 6058828C
P 8100 4650
F 0 "R?" H 8168 4696 50  0000 L CNN
F 1 "10k" H 8168 4605 50  0000 L CNN
F 2 "" V 8140 4640 50  0001 C CNN
F 3 "~" H 8100 4650 50  0001 C CNN
	1    8100 4650
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R?
U 1 1 60588674
P 8400 4650
F 0 "R?" H 8468 4696 50  0000 L CNN
F 1 "10k" H 8468 4605 50  0000 L CNN
F 2 "" V 8440 4640 50  0001 C CNN
F 3 "~" H 8400 4650 50  0001 C CNN
	1    8400 4650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60589895
P 8100 4800
F 0 "#PWR?" H 8100 4550 50  0001 C CNN
F 1 "GND" H 8105 4627 50  0000 C CNN
F 2 "" H 8100 4800 50  0001 C CNN
F 3 "" H 8100 4800 50  0001 C CNN
	1    8100 4800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60589A9A
P 8400 4800
F 0 "#PWR?" H 8400 4550 50  0001 C CNN
F 1 "GND" H 8405 4627 50  0000 C CNN
F 2 "" H 8400 4800 50  0001 C CNN
F 3 "" H 8400 4800 50  0001 C CNN
	1    8400 4800
	1    0    0    -1  
$EndComp
Entry Wire Line
	7400 4250 7500 4350
Entry Wire Line
	7700 4250 7800 4350
Entry Wire Line
	8000 4250 8100 4350
Entry Wire Line
	8300 4250 8400 4350
Wire Wire Line
	8400 4500 8400 4350
Wire Wire Line
	8100 4500 8100 4350
Wire Wire Line
	7800 4500 7800 4350
Wire Wire Line
	7500 4500 7500 4350
Text Label 7500 4400 0    50   ~ 0
d20
Text Label 7800 4400 0    50   ~ 0
d21
Text Label 8100 4400 0    50   ~ 0
d22
Text Label 8400 4400 0    50   ~ 0
d23
Text Notes 8700 5550 1    50   ~ 0
These inputs currently unused
Text GLabel 7500 4500 3    50   Output ~ 0
nBatteryPowerGood
Text GLabel 7800 4500 3    50   Output ~ 0
nBatteryChargeGood
Wire Bus Line
	9100 3950 9100 4250
Wire Bus Line
	3500 4250 9100 4250
Wire Bus Line
	7250 2100 7250 2800
Wire Bus Line
	5200 2100 5200 2800
Wire Bus Line
	9100 3100 9100 3800
Wire Bus Line
	3000 2100 3000 2800
Wire Bus Line
	9100 900  9100 2800
$EndSCHEMATC
