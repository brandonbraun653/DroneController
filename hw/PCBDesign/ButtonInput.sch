EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 7 11
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
L Switch:SW_Push SW?
U 1 1 60457CFD
P 3500 2350
AR Path="/60445E97/60457CFD" Ref="SW?"  Part="1" 
AR Path="/60445E97/60456C21/60457CFD" Ref="SW11"  Part="1" 
F 0 "SW11" V 3454 2498 50  0000 L CNN
F 1 "Key_Left" V 3545 2498 50  0000 L CNN
F 2 "" H 3500 2550 50  0001 C CNN
F 3 "~" H 3500 2550 50  0001 C CNN
	1    3500 2350
	0    1    1    0   
$EndComp
Text HLabel 3500 1650 1    50   Input ~ 0
V+
$Comp
L Device:C C26
U 1 1 60692C1F
P 3250 2350
F 0 "C26" H 3135 2304 50  0000 R CNN
F 1 "100n" H 3135 2395 50  0000 R CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 3288 2200 50  0001 C CNN
F 3 "~" H 3250 2350 50  0001 C CNN
F 4 "C1525" H 3250 2350 50  0001 C CNN "LCSC"
	1    3250 2350
	1    0    0    1   
$EndComp
$Comp
L Device:R_US R46
U 1 1 60692F65
P 3500 1900
F 0 "R46" H 3568 1946 50  0000 L CNN
F 1 "10k" H 3568 1855 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 3540 1890 50  0001 C CNN
F 3 "~" H 3500 1900 50  0001 C CNN
F 4 "C25744" H 3500 1900 50  0001 C CNN "LCSC"
	1    3500 1900
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R45
U 1 1 606932DF
P 3000 2100
F 0 "R45" V 2795 2100 50  0000 C CNN
F 1 "1k" V 2886 2100 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 3040 2090 50  0001 C CNN
F 3 "~" H 3000 2100 50  0001 C CNN
F 4 "C11702" H 3000 2100 50  0001 C CNN "LCSC"
	1    3000 2100
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR057
U 1 1 60693DD4
P 3500 2550
F 0 "#PWR057" H 3500 2300 50  0001 C CNN
F 1 "GND" H 3505 2377 50  0000 C CNN
F 2 "" H 3500 2550 50  0001 C CNN
F 3 "" H 3500 2550 50  0001 C CNN
	1    3500 2550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR056
U 1 1 606948BE
P 3250 2500
F 0 "#PWR056" H 3250 2250 50  0001 C CNN
F 1 "GND" H 3255 2327 50  0000 C CNN
F 2 "" H 3250 2500 50  0001 C CNN
F 3 "" H 3250 2500 50  0001 C CNN
	1    3250 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 1650 3500 1750
Wire Wire Line
	3500 2050 3500 2100
Wire Wire Line
	3150 2100 3250 2100
Connection ~ 3500 2100
Wire Wire Line
	3500 2100 3500 2150
Wire Wire Line
	3250 2200 3250 2100
Connection ~ 3250 2100
Wire Wire Line
	3250 2100 3500 2100
$Comp
L Switch:SW_Push SW?
U 1 1 60698428
P 5000 2350
AR Path="/60445E97/60698428" Ref="SW?"  Part="1" 
AR Path="/60445E97/60456C21/60698428" Ref="SW12"  Part="1" 
F 0 "SW12" V 4954 2498 50  0000 L CNN
F 1 "Key_Right" V 5045 2498 50  0000 L CNN
F 2 "" H 5000 2550 50  0001 C CNN
F 3 "~" H 5000 2550 50  0001 C CNN
	1    5000 2350
	0    1    1    0   
$EndComp
Text HLabel 5000 1650 1    50   Input ~ 0
V+
$Comp
L Device:C C27
U 1 1 6069842F
P 4750 2350
F 0 "C27" H 4635 2304 50  0000 R CNN
F 1 "100n" H 4635 2395 50  0000 R CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 4788 2200 50  0001 C CNN
F 3 "~" H 4750 2350 50  0001 C CNN
F 4 "C1525" H 4750 2350 50  0001 C CNN "LCSC"
	1    4750 2350
	1    0    0    1   
$EndComp
$Comp
L Device:R_US R49
U 1 1 60698435
P 5000 1900
F 0 "R49" H 5068 1946 50  0000 L CNN
F 1 "10k" H 5068 1855 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 5040 1890 50  0001 C CNN
F 3 "~" H 5000 1900 50  0001 C CNN
F 4 "C25744" H 5000 1900 50  0001 C CNN "LCSC"
	1    5000 1900
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R47
U 1 1 6069843B
P 4500 2100
F 0 "R47" V 4295 2100 50  0000 C CNN
F 1 "1k" V 4386 2100 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 4540 2090 50  0001 C CNN
F 3 "~" H 4500 2100 50  0001 C CNN
F 4 "C11702" H 4500 2100 50  0001 C CNN "LCSC"
	1    4500 2100
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR060
U 1 1 60698441
P 5000 2550
F 0 "#PWR060" H 5000 2300 50  0001 C CNN
F 1 "GND" H 5005 2377 50  0000 C CNN
F 2 "" H 5000 2550 50  0001 C CNN
F 3 "" H 5000 2550 50  0001 C CNN
	1    5000 2550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR058
U 1 1 60698447
P 4750 2500
F 0 "#PWR058" H 4750 2250 50  0001 C CNN
F 1 "GND" H 4755 2327 50  0000 C CNN
F 2 "" H 4750 2500 50  0001 C CNN
F 3 "" H 4750 2500 50  0001 C CNN
	1    4750 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 1650 5000 1750
Wire Wire Line
	5000 2050 5000 2100
Wire Wire Line
	4650 2100 4750 2100
Connection ~ 5000 2100
Wire Wire Line
	5000 2100 5000 2150
Wire Wire Line
	4750 2200 4750 2100
Connection ~ 4750 2100
Wire Wire Line
	4750 2100 5000 2100
$Comp
L Switch:SW_Push SW?
U 1 1 6069E920
P 6500 2350
AR Path="/60445E97/6069E920" Ref="SW?"  Part="1" 
AR Path="/60445E97/60456C21/6069E920" Ref="SW14"  Part="1" 
F 0 "SW14" V 6454 2498 50  0000 L CNN
F 1 "Key_Up" V 6545 2498 50  0000 L CNN
F 2 "" H 6500 2550 50  0001 C CNN
F 3 "~" H 6500 2550 50  0001 C CNN
	1    6500 2350
	0    1    1    0   
$EndComp
Text HLabel 6500 1650 1    50   Input ~ 0
V+
$Comp
L Device:C C29
U 1 1 6069E927
P 6250 2350
F 0 "C29" H 6135 2304 50  0000 R CNN
F 1 "100n" H 6135 2395 50  0000 R CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 6288 2200 50  0001 C CNN
F 3 "~" H 6250 2350 50  0001 C CNN
F 4 "C1525" H 6250 2350 50  0001 C CNN "LCSC"
	1    6250 2350
	1    0    0    1   
$EndComp
$Comp
L Device:R_US R52
U 1 1 6069E92D
P 6500 1900
F 0 "R52" H 6568 1946 50  0000 L CNN
F 1 "10k" H 6568 1855 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 6540 1890 50  0001 C CNN
F 3 "~" H 6500 1900 50  0001 C CNN
F 4 "C25744" H 6500 1900 50  0001 C CNN "LCSC"
	1    6500 1900
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R51
U 1 1 6069E933
P 6000 2100
F 0 "R51" V 5795 2100 50  0000 C CNN
F 1 "1k" V 5886 2100 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 6040 2090 50  0001 C CNN
F 3 "~" H 6000 2100 50  0001 C CNN
F 4 "C11702" H 6000 2100 50  0001 C CNN "LCSC"
	1    6000 2100
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR064
U 1 1 6069E939
P 6500 2550
F 0 "#PWR064" H 6500 2300 50  0001 C CNN
F 1 "GND" H 6505 2377 50  0000 C CNN
F 2 "" H 6500 2550 50  0001 C CNN
F 3 "" H 6500 2550 50  0001 C CNN
	1    6500 2550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR062
U 1 1 6069E93F
P 6250 2500
F 0 "#PWR062" H 6250 2250 50  0001 C CNN
F 1 "GND" H 6255 2327 50  0000 C CNN
F 2 "" H 6250 2500 50  0001 C CNN
F 3 "" H 6250 2500 50  0001 C CNN
	1    6250 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 1650 6500 1750
Wire Wire Line
	6500 2050 6500 2100
Wire Wire Line
	6150 2100 6250 2100
Connection ~ 6500 2100
Wire Wire Line
	6500 2100 6500 2150
Wire Wire Line
	6250 2200 6250 2100
Connection ~ 6250 2100
Wire Wire Line
	6250 2100 6500 2100
$Comp
L Switch:SW_Push SW?
U 1 1 606A0B5C
P 8000 2350
AR Path="/60445E97/606A0B5C" Ref="SW?"  Part="1" 
AR Path="/60445E97/60456C21/606A0B5C" Ref="SW16"  Part="1" 
F 0 "SW16" V 7954 2498 50  0000 L CNN
F 1 "Key_Down" V 8045 2498 50  0000 L CNN
F 2 "" H 8000 2550 50  0001 C CNN
F 3 "~" H 8000 2550 50  0001 C CNN
	1    8000 2350
	0    1    1    0   
$EndComp
Text HLabel 8000 1650 1    50   Input ~ 0
V+
$Comp
L Device:C C31
U 1 1 606A0B63
P 7750 2350
F 0 "C31" H 7635 2304 50  0000 R CNN
F 1 "100n" H 7635 2395 50  0000 R CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 7788 2200 50  0001 C CNN
F 3 "~" H 7750 2350 50  0001 C CNN
F 4 "C1525" H 7750 2350 50  0001 C CNN "LCSC"
	1    7750 2350
	1    0    0    1   
$EndComp
$Comp
L Device:R_US R56
U 1 1 606A0B69
P 8000 1900
F 0 "R56" H 8068 1946 50  0000 L CNN
F 1 "10k" H 8068 1855 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 8040 1890 50  0001 C CNN
F 3 "~" H 8000 1900 50  0001 C CNN
F 4 "C25744" H 8000 1900 50  0001 C CNN "LCSC"
	1    8000 1900
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R54
U 1 1 606A0B6F
P 7500 2100
F 0 "R54" V 7295 2100 50  0000 C CNN
F 1 "1k" V 7386 2100 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 7540 2090 50  0001 C CNN
F 3 "~" H 7500 2100 50  0001 C CNN
F 4 "C11702" H 7500 2100 50  0001 C CNN "LCSC"
	1    7500 2100
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR068
U 1 1 606A0B75
P 8000 2550
F 0 "#PWR068" H 8000 2300 50  0001 C CNN
F 1 "GND" H 8005 2377 50  0000 C CNN
F 2 "" H 8000 2550 50  0001 C CNN
F 3 "" H 8000 2550 50  0001 C CNN
	1    8000 2550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR066
U 1 1 606A0B7B
P 7750 2500
F 0 "#PWR066" H 7750 2250 50  0001 C CNN
F 1 "GND" H 7755 2327 50  0000 C CNN
F 2 "" H 7750 2500 50  0001 C CNN
F 3 "" H 7750 2500 50  0001 C CNN
	1    7750 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	8000 1650 8000 1750
Wire Wire Line
	8000 2050 8000 2100
Wire Wire Line
	7650 2100 7750 2100
Connection ~ 8000 2100
Wire Wire Line
	8000 2100 8000 2150
Wire Wire Line
	7750 2200 7750 2100
Connection ~ 7750 2100
Wire Wire Line
	7750 2100 8000 2100
$Comp
L Switch:SW_Push SW?
U 1 1 606A1D51
P 9500 2350
AR Path="/60445E97/606A1D51" Ref="SW?"  Part="1" 
AR Path="/60445E97/60456C21/606A1D51" Ref="SW18"  Part="1" 
F 0 "SW18" V 9454 2498 50  0000 L CNN
F 1 "Key_Enter" V 9545 2498 50  0000 L CNN
F 2 "" H 9500 2550 50  0001 C CNN
F 3 "~" H 9500 2550 50  0001 C CNN
	1    9500 2350
	0    1    1    0   
$EndComp
Text HLabel 9500 1650 1    50   Input ~ 0
V+
$Comp
L Device:C C33
U 1 1 606A1D58
P 9250 2350
F 0 "C33" H 9135 2304 50  0000 R CNN
F 1 "100n" H 9135 2395 50  0000 R CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 9288 2200 50  0001 C CNN
F 3 "~" H 9250 2350 50  0001 C CNN
F 4 "C1525" H 9250 2350 50  0001 C CNN "LCSC"
	1    9250 2350
	1    0    0    1   
$EndComp
$Comp
L Device:R_US R59
U 1 1 606A1D5E
P 9500 1900
F 0 "R59" H 9568 1946 50  0000 L CNN
F 1 "10k" H 9568 1855 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 9540 1890 50  0001 C CNN
F 3 "~" H 9500 1900 50  0001 C CNN
F 4 "C25744" H 9500 1900 50  0001 C CNN "LCSC"
	1    9500 1900
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R58
U 1 1 606A1D64
P 9000 2100
F 0 "R58" V 8795 2100 50  0000 C CNN
F 1 "1k" V 8886 2100 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 9040 2090 50  0001 C CNN
F 3 "~" H 9000 2100 50  0001 C CNN
F 4 "C11702" H 9000 2100 50  0001 C CNN "LCSC"
	1    9000 2100
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR071
U 1 1 606A1D6A
P 9500 2550
F 0 "#PWR071" H 9500 2300 50  0001 C CNN
F 1 "GND" H 9505 2377 50  0000 C CNN
F 2 "" H 9500 2550 50  0001 C CNN
F 3 "" H 9500 2550 50  0001 C CNN
	1    9500 2550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR070
U 1 1 606A1D70
P 9250 2500
F 0 "#PWR070" H 9250 2250 50  0001 C CNN
F 1 "GND" H 9255 2327 50  0000 C CNN
F 2 "" H 9250 2500 50  0001 C CNN
F 3 "" H 9250 2500 50  0001 C CNN
	1    9250 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	9500 1650 9500 1750
Wire Wire Line
	9500 2050 9500 2100
Wire Wire Line
	9150 2100 9250 2100
Connection ~ 9500 2100
Wire Wire Line
	9500 2100 9500 2150
Wire Wire Line
	9250 2200 9250 2100
Connection ~ 9250 2100
Wire Wire Line
	9250 2100 9500 2100
$Comp
L Switch:SW_Push SW?
U 1 1 606A5CBE
P 5000 3850
AR Path="/60445E97/606A5CBE" Ref="SW?"  Part="1" 
AR Path="/60445E97/60456C21/606A5CBE" Ref="SW13"  Part="1" 
F 0 "SW13" V 4954 3998 50  0000 L CNN
F 1 "Key_Esc" V 5045 3998 50  0000 L CNN
F 2 "" H 5000 4050 50  0001 C CNN
F 3 "~" H 5000 4050 50  0001 C CNN
	1    5000 3850
	0    1    1    0   
$EndComp
Text HLabel 5000 3150 1    50   Input ~ 0
V+
$Comp
L Device:C C28
U 1 1 606A5CC5
P 4750 3850
F 0 "C28" H 4635 3804 50  0000 R CNN
F 1 "100n" H 4635 3895 50  0000 R CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 4788 3700 50  0001 C CNN
F 3 "~" H 4750 3850 50  0001 C CNN
F 4 "C1525" H 4750 3850 50  0001 C CNN "LCSC"
	1    4750 3850
	1    0    0    1   
$EndComp
$Comp
L Device:R_US R50
U 1 1 606A5CCB
P 5000 3400
F 0 "R50" H 5068 3446 50  0000 L CNN
F 1 "10k" H 5068 3355 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 5040 3390 50  0001 C CNN
F 3 "~" H 5000 3400 50  0001 C CNN
F 4 "C25744" H 5000 3400 50  0001 C CNN "LCSC"
	1    5000 3400
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R48
U 1 1 606A5CD1
P 4500 3600
F 0 "R48" V 4295 3600 50  0000 C CNN
F 1 "1k" V 4386 3600 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 4540 3590 50  0001 C CNN
F 3 "~" H 4500 3600 50  0001 C CNN
F 4 "C11702" H 4500 3600 50  0001 C CNN "LCSC"
	1    4500 3600
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR061
U 1 1 606A5CD7
P 5000 4050
F 0 "#PWR061" H 5000 3800 50  0001 C CNN
F 1 "GND" H 5005 3877 50  0000 C CNN
F 2 "" H 5000 4050 50  0001 C CNN
F 3 "" H 5000 4050 50  0001 C CNN
	1    5000 4050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR059
U 1 1 606A5CDD
P 4750 4000
F 0 "#PWR059" H 4750 3750 50  0001 C CNN
F 1 "GND" H 4755 3827 50  0000 C CNN
F 2 "" H 4750 4000 50  0001 C CNN
F 3 "" H 4750 4000 50  0001 C CNN
	1    4750 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 3150 5000 3250
Wire Wire Line
	5000 3550 5000 3600
Wire Wire Line
	4650 3600 4750 3600
Connection ~ 5000 3600
Wire Wire Line
	5000 3600 5000 3650
Wire Wire Line
	4750 3700 4750 3600
Connection ~ 4750 3600
Wire Wire Line
	4750 3600 5000 3600
$Comp
L Switch:SW_Push SW?
U 1 1 606A7634
P 6500 3850
AR Path="/60445E97/606A7634" Ref="SW?"  Part="1" 
AR Path="/60445E97/60456C21/606A7634" Ref="SW15"  Part="1" 
F 0 "SW15" V 6454 3998 50  0000 L CNN
F 1 "Key_nRESET" V 6545 3998 50  0000 L CNN
F 2 "" H 6500 4050 50  0001 C CNN
F 3 "~" H 6500 4050 50  0001 C CNN
	1    6500 3850
	0    1    1    0   
$EndComp
Text HLabel 6500 3150 1    50   Input ~ 0
V+
$Comp
L Device:C C30
U 1 1 606A763B
P 6250 3850
F 0 "C30" H 6135 3804 50  0000 R CNN
F 1 "100n" H 6135 3895 50  0000 R CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 6288 3700 50  0001 C CNN
F 3 "~" H 6250 3850 50  0001 C CNN
F 4 "C1525" H 6250 3850 50  0001 C CNN "LCSC"
	1    6250 3850
	1    0    0    1   
$EndComp
$Comp
L Device:R_US R53
U 1 1 606A7641
P 6500 3400
F 0 "R53" H 6568 3446 50  0000 L CNN
F 1 "10k" H 6568 3355 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 6540 3390 50  0001 C CNN
F 3 "~" H 6500 3400 50  0001 C CNN
F 4 "C25744" H 6500 3400 50  0001 C CNN "LCSC"
	1    6500 3400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR065
U 1 1 606A764D
P 6500 4050
F 0 "#PWR065" H 6500 3800 50  0001 C CNN
F 1 "GND" H 6505 3877 50  0000 C CNN
F 2 "" H 6500 4050 50  0001 C CNN
F 3 "" H 6500 4050 50  0001 C CNN
	1    6500 4050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR063
U 1 1 606A7653
P 6250 4000
F 0 "#PWR063" H 6250 3750 50  0001 C CNN
F 1 "GND" H 6255 3827 50  0000 C CNN
F 2 "" H 6250 4000 50  0001 C CNN
F 3 "" H 6250 4000 50  0001 C CNN
	1    6250 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 3150 6500 3250
Wire Wire Line
	6500 3550 6500 3600
Wire Wire Line
	6150 3600 6250 3600
Connection ~ 6500 3600
Wire Wire Line
	6500 3600 6500 3650
Wire Wire Line
	6250 3700 6250 3600
Connection ~ 6250 3600
Wire Wire Line
	6250 3600 6500 3600
$Comp
L Switch:SW_Push SW?
U 1 1 606A94A7
P 8000 3850
AR Path="/60445E97/606A94A7" Ref="SW?"  Part="1" 
AR Path="/60445E97/60456C21/606A94A7" Ref="SW17"  Part="1" 
F 0 "SW17" V 7954 3998 50  0000 L CNN
F 1 "Key_nBOOT" V 8045 3998 50  0000 L CNN
F 2 "" H 8000 4050 50  0001 C CNN
F 3 "~" H 8000 4050 50  0001 C CNN
	1    8000 3850
	0    1    1    0   
$EndComp
Text HLabel 8000 3150 1    50   Input ~ 0
V+
$Comp
L Device:C C32
U 1 1 606A94AE
P 7750 3850
F 0 "C32" H 7635 3804 50  0000 R CNN
F 1 "100n" H 7635 3895 50  0000 R CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 7788 3700 50  0001 C CNN
F 3 "~" H 7750 3850 50  0001 C CNN
F 4 "C1525" H 7750 3850 50  0001 C CNN "LCSC"
	1    7750 3850
	1    0    0    1   
$EndComp
$Comp
L Device:R_US R57
U 1 1 606A94B4
P 8000 3400
F 0 "R57" H 8068 3446 50  0000 L CNN
F 1 "10k" H 8068 3355 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 8040 3390 50  0001 C CNN
F 3 "~" H 8000 3400 50  0001 C CNN
F 4 "C25744" H 8000 3400 50  0001 C CNN "LCSC"
	1    8000 3400
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R55
U 1 1 606A94BA
P 7500 3600
F 0 "R55" V 7295 3600 50  0000 C CNN
F 1 "1k" V 7386 3600 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 7540 3590 50  0001 C CNN
F 3 "~" H 7500 3600 50  0001 C CNN
F 4 "C11702" H 7500 3600 50  0001 C CNN "LCSC"
	1    7500 3600
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR069
U 1 1 606A94C0
P 8000 4050
F 0 "#PWR069" H 8000 3800 50  0001 C CNN
F 1 "GND" H 8005 3877 50  0000 C CNN
F 2 "" H 8000 4050 50  0001 C CNN
F 3 "" H 8000 4050 50  0001 C CNN
	1    8000 4050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR067
U 1 1 606A94C6
P 7750 4000
F 0 "#PWR067" H 7750 3750 50  0001 C CNN
F 1 "GND" H 7755 3827 50  0000 C CNN
F 2 "" H 7750 4000 50  0001 C CNN
F 3 "" H 7750 4000 50  0001 C CNN
	1    7750 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	8000 3150 8000 3250
Wire Wire Line
	8000 3550 8000 3600
Wire Wire Line
	7650 3600 7750 3600
Connection ~ 8000 3600
Wire Wire Line
	8000 3600 8000 3650
Wire Wire Line
	7750 3700 7750 3600
Connection ~ 7750 3600
Wire Wire Line
	7750 3600 8000 3600
Text HLabel 2850 2100 0    50   Output ~ 0
KeyLeft
Text HLabel 4350 2100 0    50   Output ~ 0
KeyRight
Text HLabel 5850 2100 0    50   Output ~ 0
KeyUp
Text HLabel 7350 2100 0    50   Output ~ 0
KeyDown
Text HLabel 8850 2100 0    50   Output ~ 0
KeyEnter
Text HLabel 4350 3600 0    50   Output ~ 0
KeyEscape
Text HLabel 6150 3600 0    50   Output ~ 0
KeyReset
Text HLabel 7350 3600 0    50   Output ~ 0
KeyBoot
$EndSCHEMATC
