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
LIBS:SerialDriver-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Serial Driver"
Date "2016-03-31"
Rev "0.1"
Comp ""
Comment1 "Ansteuerung eines Treibers über ein Shift-Register"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L 74HC595 U1
U 1 1 56FD9D98
P 3800 3250
F 0 "U1" H 3950 3850 50  0000 C CNN
F 1 "74HC595" H 3800 2650 50  0000 C CNN
F 2 "Housings_SOIC:SOIC-16_3.9x9.9mm_Pitch1.27mm" H 3800 3250 50  0001 C CNN
F 3 "" H 3800 3250 50  0000 C CNN
	1    3800 3250
	1    0    0    -1  
$EndComp
$Comp
L ULN2803 U2
U 1 1 56FDACD1
P 5700 3200
F 0 "U2" H 5700 3300 50  0000 C CNN
F 1 "ULN2803" H 5700 3100 50  0000 C CNN
F 2 "Housings_SOIC:SOIC-18_7.5x11.6mm_Pitch1.27mm" H 5650 3200 50  0001 C CNN
F 3 "" H 5650 3200 50  0000 C CNN
	1    5700 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 2800 5000 2800
Wire Wire Line
	4500 2900 5000 2900
Wire Wire Line
	4500 3000 5000 3000
Wire Wire Line
	4500 3100 5000 3100
Wire Wire Line
	4500 3200 5000 3200
Wire Wire Line
	4500 3300 5000 3300
Wire Wire Line
	4500 3400 5000 3400
Wire Wire Line
	4500 3500 5000 3500
$EndSCHEMATC
