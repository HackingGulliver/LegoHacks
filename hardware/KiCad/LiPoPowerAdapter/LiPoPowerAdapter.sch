EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:legohacks
LIBS:LiPoPowerAdapter-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Lego LiPo Power Adapter"
Date "2016-03-25"
Rev "0.1"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L CONN_01X04 P1
U 1 1 56F525B1
P 1500 2950
F 0 "P1" H 1500 3200 50  0000 C CNN
F 1 "CONN_01X04" V 1600 2950 50  0000 C CNN
F 2 "JST-Connectors:JST_XH_S04B-XH-A_04x2.50mm_Angled" H 1600 2600 50  0001 C CNN
F 3 "" H 1500 2950 50  0000 C CNN
	1    1500 2950
	-1   0    0    1   
$EndComp
$Comp
L LiPo_Warner LiPoWarn1
U 1 1 56F52C0F
P 4100 2950
F 0 "LiPoWarn1" H 4100 2550 60  0000 C CNN
F 1 "LiPo_Warner" H 4100 3400 60  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04" H 3700 2950 60  0001 C CNN
F 3 "" H 3700 2950 60  0000 C CNN
	1    4100 2950
	1    0    0    -1  
$EndComp
$Comp
L SWITCH_INV SW1
U 1 1 56F52CB7
P 2700 3300
F 0 "SW1" H 2500 3450 50  0000 C CNN
F 1 "SWITCH_INV" H 2550 3150 50  0000 C CNN
F 2 "Lego Hacks:AS500APC-Kippschalter" H 2700 3300 50  0001 C CNN
F 3 "" H 2700 3300 50  0000 C CNN
	1    2700 3300
	1    0    0    -1  
$EndComp
$Comp
L FUSE F1
U 1 1 56F52D66
P 2400 2800
F 0 "F1" H 2500 2850 50  0000 C CNN
F 1 "FUSE" H 2300 2750 50  0000 C CNN
F 2 "Lego Hacks:FKS-Halter" H 2400 2800 50  0001 C CNN
F 3 "" H 2400 2800 50  0000 C CNN
	1    2400 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 2800 2150 2800
Wire Wire Line
	1700 3100 2200 3100
Wire Wire Line
	2200 3100 2200 3300
Wire Wire Line
	1700 3000 3450 3000
Wire Wire Line
	3200 3200 3300 3200
Wire Wire Line
	3300 3200 3300 3100
Wire Wire Line
	3300 3100 3450 3100
Wire Wire Line
	1700 2900 3450 2900
Wire Wire Line
	2650 2800 3450 2800
$Comp
L CONN_01X03 P2
U 1 1 56F531D1
P 6800 2900
F 0 "P2" H 6800 3100 50  0000 C CNN
F 1 "CONN_01X03" V 6900 2900 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Angled_1x03" H 6800 2900 50  0001 C CNN
F 3 "" H 6800 2900 50  0000 C CNN
	1    6800 2900
	1    0    0    -1  
$EndComp
Connection ~ 3350 3100
Wire Wire Line
	3350 3100 3350 3450
Wire Wire Line
	3350 3450 4800 3450
Wire Wire Line
	4800 3450 4800 3000
$Comp
L LM2596 LM25961
U 1 1 56F53490
P 5350 2950
F 0 "LM25961" H 5350 2800 60  0000 C CNN
F 1 "LM2596" H 5350 3100 60  0000 C CNN
F 2 "Lego Hacks:LM2596" H 5350 2950 60  0001 C CNN
F 3 "" H 5350 2950 60  0001 C CNN
	1    5350 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 3000 6600 3000
Wire Wire Line
	5900 2900 6600 2900
Connection ~ 3350 2800
Wire Wire Line
	3350 2800 3350 2400
Wire Wire Line
	3350 2400 6150 2400
Wire Wire Line
	4800 2400 4800 2900
Connection ~ 4800 2400
Wire Wire Line
	6150 2400 6150 2800
Wire Wire Line
	6150 2800 6600 2800
$Comp
L GND #PWR01
U 1 1 56F5363E
P 1800 3700
F 0 "#PWR01" H 1800 3450 50  0001 C CNN
F 1 "GND" H 1800 3550 50  0000 C CNN
F 2 "" H 1800 3700 50  0000 C CNN
F 3 "" H 1800 3700 50  0000 C CNN
	1    1800 3700
	1    0    0    -1  
$EndComp
Connection ~ 1800 3100
Wire Wire Line
	1800 3100 1800 3700
$Comp
L VCC #PWR02
U 1 1 56F53693
P 1800 2450
F 0 "#PWR02" H 1800 2300 50  0001 C CNN
F 1 "VCC" H 1800 2600 50  0000 C CNN
F 2 "" H 1800 2450 50  0000 C CNN
F 3 "" H 1800 2450 50  0000 C CNN
	1    1800 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 2450 1800 2800
Connection ~ 1800 2800
Text Label 1850 2800 0    60   ~ 0
VCC
Text Label 1850 3200 0    60   ~ 0
GND
$Comp
L +5V #PWR03
U 1 1 56F53B81
P 6000 2900
F 0 "#PWR03" H 6000 2750 50  0001 C CNN
F 1 "+5V" H 6000 3040 50  0000 C CNN
F 2 "" H 6000 2900 50  0000 C CNN
F 3 "" H 6000 2900 50  0000 C CNN
	1    6000 2900
	1    0    0    -1  
$EndComp
Connection ~ 6000 2900
Text Label 2550 3000 0    60   ~ 0
BAT1
Text Label 2850 2900 0    60   ~ 0
BAT2
Text Label 3450 3450 0    60   ~ 0
GND_SWITCHED
Text Label 5000 2400 0    60   ~ 0
VCC_FUSED
Text Label 5950 3000 0    60   ~ 0
GND_SWITCHED
$Comp
L PWR_FLAG #FLG04
U 1 1 56F90E21
P 1550 2600
F 0 "#FLG04" H 1550 2695 50  0001 C CNN
F 1 "PWR_FLAG" H 1550 2780 50  0000 C CNN
F 2 "" H 1550 2600 50  0000 C CNN
F 3 "" H 1550 2600 50  0000 C CNN
	1    1550 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1550 2650 1550 2600
Wire Wire Line
	1550 2650 1800 2650
Connection ~ 1800 2650
$Comp
L PWR_FLAG #FLG05
U 1 1 56F90F10
P 1550 3500
F 0 "#FLG05" H 1550 3595 50  0001 C CNN
F 1 "PWR_FLAG" H 1550 3680 50  0000 C CNN
F 2 "" H 1550 3500 50  0000 C CNN
F 3 "" H 1550 3500 50  0000 C CNN
	1    1550 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1550 3500 1550 3600
Wire Wire Line
	1550 3600 1800 3600
Connection ~ 1800 3600
NoConn ~ 3200 3400
$Comp
L PWR_FLAG #FLG06
U 1 1 56F910A6
P 4550 2350
F 0 "#FLG06" H 4550 2445 50  0001 C CNN
F 1 "PWR_FLAG" H 4550 2530 50  0000 C CNN
F 2 "" H 4550 2350 50  0000 C CNN
F 3 "" H 4550 2350 50  0000 C CNN
	1    4550 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 2350 4550 2400
Connection ~ 4550 2400
$EndSCHEMATC
