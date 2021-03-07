EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 5
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
L Device:Battery BT?
U 1 1 60472F21
P 2000 3500
F 0 "BT?" H 2108 3546 50  0000 L CNN
F 1 "Battery" H 2108 3455 50  0000 L CNN
F 2 "" V 2000 3560 50  0001 C CNN
F 3 "~" V 2000 3560 50  0001 C CNN
	1    2000 3500
	1    0    0    -1  
$EndComp
$Comp
L Battery_Management:BQ24074RGT U?
U 1 1 60473B5A
P 4350 3250
F 0 "U?" H 4350 4031 50  0000 C CNN
F 1 "BQ24074RGT" H 4350 3940 50  0000 C CNN
F 2 "Package_DFN_QFN:VQFN-16-1EP_3x3mm_P0.5mm_EP1.6x1.6mm" H 4650 2700 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/bq24074.pdf" H 4650 3450 50  0001 C CNN
F 4 "C54313" H 4350 3250 50  0001 C CNN "LCSC"
	1    4350 3250
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:IFX27001TFV U?
U 1 1 6047951C
P 6850 2600
F 0 "U?" H 6850 2867 50  0000 C CNN
F 1 "IFX27001TFV" H 6850 2776 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:TO-252-3_TabPin2" H 6850 2550 50  0001 C CNN
F 3 "https://static6.arrow.com/aropdfconversion/dc75757ae45a88e5f69bdce3f2a651a5fe0ca07d/ifx27001_ds_10.pdf" H 6850 2550 50  0001 C CNN
	1    6850 2600
	1    0    0    -1  
$EndComp
Text Notes 6350 2150 0    50   ~ 0
Change to LCSC C5446. This is a totally different package.\nThis is for the digital power supply.
$Comp
L Regulator_Linear:IFX27001TFV U?
U 1 1 604799F8
P 6800 3800
F 0 "U?" H 6800 4067 50  0000 C CNN
F 1 "IFX27001TFV" H 6800 3976 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:TO-252-3_TabPin2" H 6800 3750 50  0001 C CNN
F 3 "https://static6.arrow.com/aropdfconversion/dc75757ae45a88e5f69bdce3f2a651a5fe0ca07d/ifx27001_ds_10.pdf" H 6800 3750 50  0001 C CNN
	1    6800 3800
	1    0    0    -1  
$EndComp
Text Notes 6350 3400 0    50   ~ 0
Same as digital, but extra filtering for analog
Text Notes 6400 4750 0    50   ~ 0
Need to select power supply for radio
$EndSCHEMATC
