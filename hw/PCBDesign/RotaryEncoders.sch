EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 11
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
L Device:Rotary_Encoder_Switch SW?
U 1 1 60451ED3
P 5550 4650
AR Path="/60445E97/60451ED3" Ref="SW?"  Part="1" 
AR Path="/60445E97/6044E41E/60451ED3" Ref="SW?"  Part="1" 
F 0 "SW?" H 5550 5017 50  0000 C CNN
F 1 "Encoder0" H 5550 4926 50  0000 C CNN
F 2 "" H 5400 4810 50  0001 C CNN
F 3 "~" H 5550 4910 50  0001 C CNN
	1    5550 4650
	1    0    0    -1  
$EndComp
$Comp
L Device:Rotary_Encoder_Switch SW?
U 1 1 60451ED9
P 5550 2650
AR Path="/60445E97/60451ED9" Ref="SW?"  Part="1" 
AR Path="/60445E97/6044E41E/60451ED9" Ref="SW?"  Part="1" 
F 0 "SW?" H 5550 3017 50  0000 C CNN
F 1 "Encoder1" H 5550 2926 50  0000 C CNN
F 2 "" H 5400 2810 50  0001 C CNN
F 3 "~" H 5550 2910 50  0001 C CNN
	1    5550 2650
	1    0    0    -1  
$EndComp
Text HLabel 5900 1700 1    50   Input ~ 0
V+
Text HLabel 6600 4250 2    50   Output ~ 0
ENC0_nBTN
Text HLabel 4300 4550 0    50   Output ~ 0
ENC0_A
Text HLabel 4300 4750 0    50   Output ~ 0
ENC0_B
Text HLabel 6600 2250 2    50   Output ~ 0
ENC1_nBTN
Text HLabel 4350 2550 0    50   Output ~ 0
ENC1_A
Text HLabel 4350 2750 0    50   Output ~ 0
ENC1_B
$Comp
L power:GND #PWR?
U 1 1 60675BE5
P 5900 2850
F 0 "#PWR?" H 5900 2600 50  0001 C CNN
F 1 "GND" H 5905 2677 50  0000 C CNN
F 2 "" H 5900 2850 50  0001 C CNN
F 3 "" H 5900 2850 50  0001 C CNN
	1    5900 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 2850 5900 2750
Wire Wire Line
	5900 2750 5850 2750
$Comp
L Device:R_US R?
U 1 1 60676526
P 5900 2000
F 0 "R?" H 5968 2046 50  0000 L CNN
F 1 "10k" H 5968 1955 50  0000 L CNN
F 2 "" V 5940 1990 50  0001 C CNN
F 3 "~" H 5900 2000 50  0001 C CNN
	1    5900 2000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 60677146
P 6100 2500
F 0 "C?" H 6215 2546 50  0000 L CNN
F 1 "10n" H 6215 2455 50  0000 L CNN
F 2 "" H 6138 2350 50  0001 C CNN
F 3 "~" H 6100 2500 50  0001 C CNN
	1    6100 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 2650 6100 2750
Wire Wire Line
	6100 2750 5900 2750
Connection ~ 5900 2750
Wire Wire Line
	5850 2550 5900 2550
Wire Wire Line
	5900 2550 5900 2250
Wire Wire Line
	6100 2350 6100 2250
Wire Wire Line
	6100 2250 5900 2250
Connection ~ 5900 2250
Wire Wire Line
	5900 2250 5900 2150
Wire Wire Line
	5900 1700 5900 1850
$Comp
L Device:R_US R?
U 1 1 60677E80
P 6350 2250
F 0 "R?" V 6145 2250 50  0000 C CNN
F 1 "1k" V 6236 2250 50  0000 C CNN
F 2 "" V 6390 2240 50  0001 C CNN
F 3 "~" H 6350 2250 50  0001 C CNN
	1    6350 2250
	0    1    1    0   
$EndComp
Wire Wire Line
	6200 2250 6100 2250
Connection ~ 6100 2250
$Comp
L power:GND #PWR?
U 1 1 6067927C
P 5250 2650
F 0 "#PWR?" H 5250 2400 50  0001 C CNN
F 1 "GND" V 5255 2522 50  0000 R CNN
F 2 "" H 5250 2650 50  0001 C CNN
F 3 "" H 5250 2650 50  0001 C CNN
	1    5250 2650
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 60679819
P 5150 2250
F 0 "R?" H 5218 2296 50  0000 L CNN
F 1 "10k" H 5218 2205 50  0000 L CNN
F 2 "" V 5190 2240 50  0001 C CNN
F 3 "~" H 5150 2250 50  0001 C CNN
	1    5150 2250
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R?
U 1 1 6067A90F
P 5150 3050
F 0 "R?" H 5218 3096 50  0000 L CNN
F 1 "10k" H 5218 3005 50  0000 L CNN
F 2 "" V 5190 3040 50  0001 C CNN
F 3 "~" H 5150 3050 50  0001 C CNN
	1    5150 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 2900 5150 2750
Wire Wire Line
	5150 2750 5250 2750
Wire Wire Line
	5150 2400 5150 2550
Wire Wire Line
	5150 2550 5250 2550
$Comp
L Device:R_US R?
U 1 1 6067B493
P 4600 2550
F 0 "R?" V 4395 2550 50  0000 C CNN
F 1 "1k" V 4486 2550 50  0000 C CNN
F 2 "" V 4640 2540 50  0001 C CNN
F 3 "~" H 4600 2550 50  0001 C CNN
	1    4600 2550
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 6067BA67
P 4600 2750
F 0 "R?" V 4800 2750 50  0000 C CNN
F 1 "1k" V 4700 2750 50  0000 C CNN
F 2 "" V 4640 2740 50  0001 C CNN
F 3 "~" H 4600 2750 50  0001 C CNN
	1    4600 2750
	0    1    1    0   
$EndComp
Connection ~ 5150 2550
Connection ~ 5150 2750
Text HLabel 5150 2000 1    50   Input ~ 0
V+
Text HLabel 5150 3300 3    50   Input ~ 0
V+
Wire Wire Line
	5150 3300 5150 3200
Wire Wire Line
	5150 2000 5150 2100
$Comp
L Device:C C?
U 1 1 6067D16B
P 4850 3050
F 0 "C?" H 4965 3096 50  0000 L CNN
F 1 "10n" H 4965 3005 50  0000 L CNN
F 2 "" H 4888 2900 50  0001 C CNN
F 3 "~" H 4850 3050 50  0001 C CNN
	1    4850 3050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6067DEB4
P 4850 3250
F 0 "#PWR?" H 4850 3000 50  0001 C CNN
F 1 "GND" H 4855 3077 50  0000 C CNN
F 2 "" H 4850 3250 50  0001 C CNN
F 3 "" H 4850 3250 50  0001 C CNN
	1    4850 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 3250 4850 3200
$Comp
L Device:C C?
U 1 1 6067ECD5
P 4850 2250
F 0 "C?" H 4965 2296 50  0000 L CNN
F 1 "10n" H 4965 2205 50  0000 L CNN
F 2 "" H 4888 2100 50  0001 C CNN
F 3 "~" H 4850 2250 50  0001 C CNN
	1    4850 2250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6067F45A
P 4850 2050
F 0 "#PWR?" H 4850 1800 50  0001 C CNN
F 1 "GND" H 4855 1877 50  0000 C CNN
F 2 "" H 4850 2050 50  0001 C CNN
F 3 "" H 4850 2050 50  0001 C CNN
	1    4850 2050
	-1   0    0    1   
$EndComp
Wire Wire Line
	4850 2050 4850 2100
Wire Wire Line
	4750 2550 4850 2550
Wire Wire Line
	4750 2750 4850 2750
Wire Wire Line
	4850 2900 4850 2750
Connection ~ 4850 2750
Wire Wire Line
	4850 2750 5150 2750
Wire Wire Line
	4850 2400 4850 2550
Connection ~ 4850 2550
Wire Wire Line
	4850 2550 5150 2550
Text HLabel 5900 3700 1    50   Input ~ 0
V+
$Comp
L power:GND #PWR?
U 1 1 60685F7C
P 5900 4850
F 0 "#PWR?" H 5900 4600 50  0001 C CNN
F 1 "GND" H 5905 4677 50  0000 C CNN
F 2 "" H 5900 4850 50  0001 C CNN
F 3 "" H 5900 4850 50  0001 C CNN
	1    5900 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 4850 5900 4750
Wire Wire Line
	5900 4750 5850 4750
$Comp
L Device:R_US R?
U 1 1 60685F84
P 5900 4000
F 0 "R?" H 5968 4046 50  0000 L CNN
F 1 "10k" H 5968 3955 50  0000 L CNN
F 2 "" V 5940 3990 50  0001 C CNN
F 3 "~" H 5900 4000 50  0001 C CNN
	1    5900 4000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 60685F8A
P 6100 4500
F 0 "C?" H 6215 4546 50  0000 L CNN
F 1 "10n" H 6215 4455 50  0000 L CNN
F 2 "" H 6138 4350 50  0001 C CNN
F 3 "~" H 6100 4500 50  0001 C CNN
	1    6100 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 4650 6100 4750
Wire Wire Line
	6100 4750 5900 4750
Connection ~ 5900 4750
Wire Wire Line
	5850 4550 5900 4550
Wire Wire Line
	5900 4550 5900 4250
Wire Wire Line
	6100 4350 6100 4250
Wire Wire Line
	6100 4250 5900 4250
Connection ~ 5900 4250
Wire Wire Line
	5900 4250 5900 4150
Wire Wire Line
	5900 3700 5900 3850
$Comp
L Device:R_US R?
U 1 1 60685F9A
P 6350 4250
F 0 "R?" V 6145 4250 50  0000 C CNN
F 1 "1k" V 6236 4250 50  0000 C CNN
F 2 "" V 6390 4240 50  0001 C CNN
F 3 "~" H 6350 4250 50  0001 C CNN
	1    6350 4250
	0    1    1    0   
$EndComp
Wire Wire Line
	6200 4250 6100 4250
Connection ~ 6100 4250
$Comp
L power:GND #PWR?
U 1 1 60685FA2
P 5250 4650
F 0 "#PWR?" H 5250 4400 50  0001 C CNN
F 1 "GND" V 5255 4522 50  0000 R CNN
F 2 "" H 5250 4650 50  0001 C CNN
F 3 "" H 5250 4650 50  0001 C CNN
	1    5250 4650
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 60685FA8
P 5150 4250
F 0 "R?" H 5218 4296 50  0000 L CNN
F 1 "10k" H 5218 4205 50  0000 L CNN
F 2 "" V 5190 4240 50  0001 C CNN
F 3 "~" H 5150 4250 50  0001 C CNN
	1    5150 4250
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R?
U 1 1 60685FAE
P 5150 5050
F 0 "R?" H 5218 5096 50  0000 L CNN
F 1 "10k" H 5218 5005 50  0000 L CNN
F 2 "" V 5190 5040 50  0001 C CNN
F 3 "~" H 5150 5050 50  0001 C CNN
	1    5150 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 4900 5150 4750
Wire Wire Line
	5150 4750 5250 4750
Wire Wire Line
	5150 4400 5150 4550
Wire Wire Line
	5150 4550 5250 4550
$Comp
L Device:R_US R?
U 1 1 60685FB8
P 4600 4550
F 0 "R?" V 4395 4550 50  0000 C CNN
F 1 "1k" V 4486 4550 50  0000 C CNN
F 2 "" V 4640 4540 50  0001 C CNN
F 3 "~" H 4600 4550 50  0001 C CNN
	1    4600 4550
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 60685FBE
P 4600 4750
F 0 "R?" V 4800 4750 50  0000 C CNN
F 1 "1k" V 4700 4750 50  0000 C CNN
F 2 "" V 4640 4740 50  0001 C CNN
F 3 "~" H 4600 4750 50  0001 C CNN
	1    4600 4750
	0    1    1    0   
$EndComp
Connection ~ 5150 4550
Connection ~ 5150 4750
Text HLabel 5150 4000 1    50   Input ~ 0
V+
Text HLabel 5150 5300 3    50   Input ~ 0
V+
Wire Wire Line
	5150 5300 5150 5200
Wire Wire Line
	5150 4000 5150 4100
$Comp
L Device:C C?
U 1 1 60685FCA
P 4850 5050
F 0 "C?" H 4965 5096 50  0000 L CNN
F 1 "10n" H 4965 5005 50  0000 L CNN
F 2 "" H 4888 4900 50  0001 C CNN
F 3 "~" H 4850 5050 50  0001 C CNN
	1    4850 5050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60685FD0
P 4850 5250
F 0 "#PWR?" H 4850 5000 50  0001 C CNN
F 1 "GND" H 4855 5077 50  0000 C CNN
F 2 "" H 4850 5250 50  0001 C CNN
F 3 "" H 4850 5250 50  0001 C CNN
	1    4850 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 5250 4850 5200
$Comp
L Device:C C?
U 1 1 60685FD7
P 4850 4250
F 0 "C?" H 4965 4296 50  0000 L CNN
F 1 "10n" H 4965 4205 50  0000 L CNN
F 2 "" H 4888 4100 50  0001 C CNN
F 3 "~" H 4850 4250 50  0001 C CNN
	1    4850 4250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60685FDD
P 4850 4050
F 0 "#PWR?" H 4850 3800 50  0001 C CNN
F 1 "GND" H 4855 3877 50  0000 C CNN
F 2 "" H 4850 4050 50  0001 C CNN
F 3 "" H 4850 4050 50  0001 C CNN
	1    4850 4050
	-1   0    0    1   
$EndComp
Wire Wire Line
	4850 4050 4850 4100
Wire Wire Line
	4750 4550 4850 4550
Wire Wire Line
	4750 4750 4850 4750
Wire Wire Line
	4850 4900 4850 4750
Connection ~ 4850 4750
Wire Wire Line
	4850 4750 5150 4750
Wire Wire Line
	4850 4400 4850 4550
Connection ~ 4850 4550
Wire Wire Line
	4850 4550 5150 4550
Wire Wire Line
	6600 2250 6500 2250
Wire Wire Line
	4350 2550 4450 2550
Wire Wire Line
	4350 2750 4450 2750
Wire Wire Line
	6600 4250 6500 4250
Wire Wire Line
	4300 4550 4450 4550
Wire Wire Line
	4300 4750 4450 4750
$EndSCHEMATC