EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 4
Title "PCM Player"
Date "2020-05-07"
Rev "0"
Comp "Sergey Pershin <sergey.pershin at hotmail.com>"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Amplifier_Audio:TDA7297 U4
U 1 1 5F12A17B
P 3000 3000
F 0 "U4" H 3000 2725 50  0000 C CNN
F 1 "TDA7297" H 3000 2634 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-15_P2.54x2.54mm_StaggerOdd_Lead4.58mm_Vertical" H 3000 3000 50  0001 C CIN
F 3 "http://www.st.com/resource/en/datasheet/tda7297.pdf" H 3000 3000 50  0001 C CNN
	1    3000 3000
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Audio:TDA7297 U4
U 2 1 5F12A5D9
P 3000 3900
F 0 "U4" H 3000 4267 50  0000 C CNN
F 1 "TDA7297" H 3000 4176 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-15_P2.54x2.54mm_StaggerOdd_Lead4.58mm_Vertical" H 3000 3900 50  0001 C CIN
F 3 "http://www.st.com/resource/en/datasheet/tda7297.pdf" H 3000 3900 50  0001 C CNN
	2    3000 3900
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Audio:TDA7297 U4
U 3 1 5F12AE4A
P 3000 4800
F 0 "U4" H 3053 4846 50  0000 L CNN
F 1 "TDA7297" H 3053 4755 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-15_P2.54x2.54mm_StaggerOdd_Lead4.58mm_Vertical" H 3000 4800 50  0001 C CIN
F 3 "http://www.st.com/resource/en/datasheet/tda7297.pdf" H 3000 4800 50  0001 C CNN
	3    3000 4800
	1    0    0    -1  
$EndComp
$Comp
L Device:C C7
U 1 1 5F12D586
P 2450 3000
F 0 "C7" V 2702 3000 50  0000 C CNN
F 1 "2.2uF" V 2611 3000 50  0000 C CNN
F 2 "" H 2488 2850 50  0001 C CNN
F 3 "~" H 2450 3000 50  0001 C CNN
	1    2450 3000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2700 3000 2600 3000
$Comp
L Device:C C8
U 1 1 5F12DE99
P 2450 3900
F 0 "C8" V 2702 3900 50  0000 C CNN
F 1 "2.2uF" V 2611 3900 50  0000 C CNN
F 2 "" H 2488 3750 50  0001 C CNN
F 3 "~" H 2450 3900 50  0001 C CNN
	1    2450 3900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2700 3900 2600 3900
$Comp
L Device:Speaker LS1
U 1 1 5F12E4C7
P 3700 2950
F 0 "LS1" H 3870 2946 50  0000 L CNN
F 1 "Speaker" H 3870 2855 50  0000 L CNN
F 2 "" H 3700 2750 50  0001 C CNN
F 3 "~" H 3690 2900 50  0001 C CNN
	1    3700 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 2900 3400 2900
Wire Wire Line
	3400 2900 3400 2950
Wire Wire Line
	3400 2950 3500 2950
Wire Wire Line
	3300 3100 3400 3100
Wire Wire Line
	3400 3100 3400 3050
Wire Wire Line
	3400 3050 3500 3050
$Comp
L Device:Speaker LS2
U 1 1 5F12F9C6
P 3700 3850
F 0 "LS2" H 3870 3846 50  0000 L CNN
F 1 "Speaker" H 3870 3755 50  0000 L CNN
F 2 "" H 3700 3650 50  0001 C CNN
F 3 "~" H 3690 3800 50  0001 C CNN
	1    3700 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 3800 3400 3800
Wire Wire Line
	3400 3800 3400 3850
Wire Wire Line
	3400 3850 3500 3850
Wire Wire Line
	3300 4000 3400 4000
Wire Wire Line
	3400 4000 3400 3950
Wire Wire Line
	3400 3950 3500 3950
$Comp
L power:GND #PWR0110
U 1 1 5F1301E8
P 3000 5200
F 0 "#PWR0110" H 3000 4950 50  0001 C CNN
F 1 "GND" H 3005 5027 50  0000 C CNN
F 2 "" H 3000 5200 50  0001 C CNN
F 3 "" H 3000 5200 50  0001 C CNN
	1    3000 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 5100 3000 5200
$Comp
L power:VCC #PWR0111
U 1 1 5F1316FD
P 2900 4400
F 0 "#PWR0111" H 2900 4250 50  0001 C CNN
F 1 "VCC" H 2915 4573 50  0000 C CNN
F 2 "" H 2900 4400 50  0001 C CNN
F 3 "" H 2900 4400 50  0001 C CNN
	1    2900 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 4400 2900 4500
Text HLabel 2200 3000 0    50   Input ~ 0
LIN
Wire Wire Line
	2200 3000 2300 3000
Text HLabel 2200 3900 0    50   Input ~ 0
RIN
Wire Wire Line
	2200 3900 2300 3900
Text HLabel 2800 5200 0    50   Input ~ 0
INGND
Wire Wire Line
	2900 5100 2900 5200
Wire Wire Line
	2900 5200 2800 5200
$Comp
L Device:C C11
U 1 1 5F13E9D2
P 3750 4750
F 0 "C11" H 3865 4796 50  0000 L CNN
F 1 "100nF" H 3865 4705 50  0000 L CNN
F 2 "" H 3788 4600 50  0001 C CNN
F 3 "~" H 3750 4750 50  0001 C CNN
	1    3750 4750
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C12
U 1 1 5F13EAD5
P 4250 4750
F 0 "C12" H 4368 4796 50  0000 L CNN
F 1 "2200uF" H 4368 4705 50  0000 L CNN
F 2 "" H 4288 4600 50  0001 C CNN
F 3 "~" H 4250 4750 50  0001 C CNN
	1    4250 4750
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR03
U 1 1 5F13F202
P 4000 4400
F 0 "#PWR03" H 4000 4250 50  0001 C CNN
F 1 "VCC" H 4015 4573 50  0000 C CNN
F 2 "" H 4000 4400 50  0001 C CNN
F 3 "" H 4000 4400 50  0001 C CNN
	1    4000 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 4400 4000 4500
Wire Wire Line
	3750 4600 3750 4500
Wire Wire Line
	3750 4500 4000 4500
Wire Wire Line
	4000 4500 4250 4500
Wire Wire Line
	4250 4500 4250 4600
Connection ~ 4000 4500
Wire Wire Line
	3750 4900 3750 5000
Wire Wire Line
	3750 5000 4000 5000
Wire Wire Line
	4250 5000 4250 4900
$Comp
L power:GND #PWR04
U 1 1 5F142398
P 4000 5100
F 0 "#PWR04" H 4000 4850 50  0001 C CNN
F 1 "GND" H 4005 4927 50  0000 C CNN
F 2 "" H 4000 5100 50  0001 C CNN
F 3 "" H 4000 5100 50  0001 C CNN
	1    4000 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 5000 4000 5100
Connection ~ 4000 5000
Wire Wire Line
	4000 5000 4250 5000
$Comp
L Device:CP C9
U 1 1 5F145AC2
P 2450 1150
F 0 "C9" H 2568 1196 50  0000 L CNN
F 1 "10uF" H 2568 1105 50  0000 L CNN
F 2 "" H 2488 1000 50  0001 C CNN
F 3 "~" H 2450 1150 50  0001 C CNN
	1    2450 1150
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C10
U 1 1 5F145CC9
P 2450 2100
F 0 "C10" H 2568 2146 50  0000 L CNN
F 1 "1uF" H 2568 2055 50  0000 L CNN
F 2 "" H 2488 1950 50  0001 C CNN
F 3 "~" H 2450 2100 50  0001 C CNN
	1    2450 2100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5F14607B
P 2200 900
F 0 "R1" V 2407 900 50  0000 C CNN
F 1 "10K" V 2316 900 50  0000 C CNN
F 2 "" V 2130 900 50  0001 C CNN
F 3 "~" H 2200 900 50  0001 C CNN
	1    2200 900 
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R2
U 1 1 5F1463D4
P 2200 1850
F 0 "R2" V 2407 1850 50  0000 C CNN
F 1 "10K" V 2316 1850 50  0000 C CNN
F 2 "" V 2130 1850 50  0001 C CNN
F 3 "~" H 2200 1850 50  0001 C CNN
	1    2200 1850
	0    -1   -1   0   
$EndComp
Text HLabel 1950 900  0    50   Input ~ 0
ST-BY
$Comp
L power:GND #PWR01
U 1 1 5F147B7D
P 2450 1400
F 0 "#PWR01" H 2450 1150 50  0001 C CNN
F 1 "GND" H 2455 1227 50  0000 C CNN
F 2 "" H 2450 1400 50  0001 C CNN
F 3 "" H 2450 1400 50  0001 C CNN
	1    2450 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 1300 2450 1400
Wire Wire Line
	2350 900  2450 900 
Wire Wire Line
	2450 900  2450 1000
Wire Wire Line
	2050 900  1950 900 
Wire Wire Line
	2350 1850 2450 1850
Wire Wire Line
	2450 1850 2450 1950
$Comp
L power:GND #PWR02
U 1 1 5F14A6C2
P 2450 2350
F 0 "#PWR02" H 2450 2100 50  0001 C CNN
F 1 "GND" H 2455 2177 50  0000 C CNN
F 2 "" H 2450 2350 50  0001 C CNN
F 3 "" H 2450 2350 50  0001 C CNN
	1    2450 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 2250 2450 2350
Text HLabel 1950 1850 0    50   Input ~ 0
MUTE
Wire Wire Line
	1950 1850 2050 1850
Wire Wire Line
	2450 900  3100 900 
Wire Wire Line
	3100 900  3100 2700
Connection ~ 2450 900 
Wire Wire Line
	3000 2700 3000 1850
Wire Wire Line
	3000 1850 2450 1850
Connection ~ 2450 1850
$EndSCHEMATC
