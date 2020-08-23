EESchema Schematic File Version 4
LIBS:10knobs-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L bluepill_breakouts:BluePill_STM32F103C U2
U 1 1 5D04FCF5
P 8050 4000
F 0 "U2" V 8029 2572 50  0000 R CNN
F 1 "BluePill_STM32F103C" V 8120 2572 50  0000 R CNN
F 2 "BluePill_breakouts:BluePill_STM32F103C" H 8100 2400 50  0001 C CNN
F 3 "www.rogerclark.net" H 8050 2500 50  0001 C CNN
	1    8050 4000
	0    1    1    0   
$EndComp
Wire Wire Line
	8650 4900 8650 5000
Wire Wire Line
	8750 5050 8750 4900
$Comp
L Device:R_POT RV8
U 1 1 5D05046E
P 8750 2150
F 0 "RV8" H 8680 2196 50  0000 R CNN
F 1 "10K" H 8680 2105 50  0000 R CNN
F 2 "Potentiometer_THT:Potentiometer_Alps_RK09K_Single_Vertical" H 8750 2150 50  0001 C CNN
F 3 "~" H 8750 2150 50  0001 C CNN
	1    8750 2150
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT RV7
U 1 1 5D050582
P 10150 5800
F 0 "RV7" H 10080 5846 50  0000 R CNN
F 1 "10K" H 10080 5755 50  0000 R CNN
F 2 "Potentiometer_THT:Potentiometer_Alps_RK09K_Single_Vertical" H 10150 5800 50  0001 C CNN
F 3 "~" H 10150 5800 50  0001 C CNN
	1    10150 5800
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT RV6
U 1 1 5D05062D
P 8500 2400
F 0 "RV6" H 8430 2446 50  0000 R CNN
F 1 "10K" H 8430 2355 50  0000 R CNN
F 2 "Potentiometer_THT:Potentiometer_Alps_RK09K_Single_Vertical" H 8500 2400 50  0001 C CNN
F 3 "~" H 8500 2400 50  0001 C CNN
	1    8500 2400
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT RV5
U 1 1 5D050634
P 8250 2150
F 0 "RV5" H 8180 2196 50  0000 R CNN
F 1 "10K" H 8180 2105 50  0000 R CNN
F 2 "Potentiometer_THT:Potentiometer_Alps_RK09K_Single_Vertical" H 8250 2150 50  0001 C CNN
F 3 "~" H 8250 2150 50  0001 C CNN
	1    8250 2150
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT RV4
U 1 1 5D050747
P 8050 2400
F 0 "RV4" H 7980 2446 50  0000 R CNN
F 1 "10K" H 7980 2355 50  0000 R CNN
F 2 "Potentiometer_THT:Potentiometer_Alps_RK09K_Single_Vertical" H 8050 2400 50  0001 C CNN
F 3 "~" H 8050 2400 50  0001 C CNN
	1    8050 2400
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT RV3
U 1 1 5D05074E
P 7800 2150
F 0 "RV3" H 7730 2196 50  0000 R CNN
F 1 "10K" H 7730 2105 50  0000 R CNN
F 2 "Potentiometer_THT:Potentiometer_Alps_RK09K_Single_Vertical" H 7800 2150 50  0001 C CNN
F 3 "~" H 7800 2150 50  0001 C CNN
	1    7800 2150
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT RV2
U 1 1 5D050755
P 7600 2400
F 0 "RV2" H 7530 2446 50  0000 R CNN
F 1 "10K" H 7530 2355 50  0000 R CNN
F 2 "Potentiometer_THT:Potentiometer_Alps_RK09K_Single_Vertical" H 7600 2400 50  0001 C CNN
F 3 "~" H 7600 2400 50  0001 C CNN
	1    7600 2400
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT RV1
U 1 1 5D05075C
P 7350 2150
F 0 "RV1" H 7280 2196 50  0000 R CNN
F 1 "10K" H 7280 2105 50  0000 R CNN
F 2 "Potentiometer_THT:Potentiometer_Alps_RK09K_Single_Vertical" H 7350 2150 50  0001 C CNN
F 3 "~" H 7350 2150 50  0001 C CNN
	1    7350 2150
	1    0    0    -1  
$EndComp
Connection ~ 7800 2000
Wire Wire Line
	7800 2000 7600 2000
Connection ~ 8250 2000
Wire Wire Line
	8250 2000 8050 2000
Wire Wire Line
	8500 2000 8500 2250
Connection ~ 8500 2000
Wire Wire Line
	8500 2000 8250 2000
Wire Wire Line
	8050 2000 8050 2250
Connection ~ 8050 2000
Wire Wire Line
	8050 2000 7800 2000
Wire Wire Line
	7600 2250 7600 2000
Connection ~ 7600 2000
Connection ~ 8050 2550
Wire Wire Line
	8050 2550 7800 2550
Wire Wire Line
	7350 2550 7350 2300
Connection ~ 7600 2550
Wire Wire Line
	7800 2300 7800 2550
Connection ~ 7800 2550
Wire Wire Line
	7800 2550 7600 2550
Wire Wire Line
	8250 2300 8250 2550
Connection ~ 8250 2550
Wire Wire Line
	8250 2550 8050 2550
$Comp
L Connector:TestPoint TP7
U 1 1 5D05C5F5
P 8450 6400
F 0 "TP7" V 8645 6474 50  0000 C CNN
F 1 "out1" V 8554 6474 50  0000 C CNN
F 2 "TestPoint:TestPoint_THTPad_2.5x2.5mm_Drill1.2mm" H 8650 6400 50  0001 C CNN
F 3 "~" H 8650 6400 50  0001 C CNN
	1    8450 6400
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N914 D1
U 1 1 5D0624B1
P 3600 3000
F 0 "D1" V 3554 3079 50  0000 L CNN
F 1 "1N914" V 3645 3079 50  0000 L CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 3600 2825 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 3600 3000 50  0001 C CNN
	1    3600 3000
	0    1    1    0   
$EndComp
Wire Wire Line
	3600 2850 4100 2850
Wire Wire Line
	3600 3150 3900 3150
Wire Wire Line
	7250 3150 7250 2700
Wire Wire Line
	7250 2700 6050 2700
$Comp
L Connector:TestPoint TP6
U 1 1 5D074B90
P 6200 3100
F 0 "TP6" H 6142 3127 50  0000 R CNN
F 1 "IN2" H 6142 3218 50  0000 R CNN
F 2 "TestPoint:TestPoint_THTPad_2.5x2.5mm_Drill1.2mm" H 6400 3100 50  0001 C CNN
F 3 "~" H 6400 3100 50  0001 C CNN
	1    6200 3100
	-1   0    0    1   
$EndComp
$Comp
L Connector:TestPoint TP5
U 1 1 5D074C58
P 4100 2550
F 0 "TP5" H 4158 2670 50  0000 L CNN
F 1 "IN4" H 4158 2579 50  0000 L CNN
F 2 "TestPoint:TestPoint_THTPad_2.5x2.5mm_Drill1.2mm" H 4300 2550 50  0001 C CNN
F 3 "~" H 4300 2550 50  0001 C CNN
	1    4100 2550
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP4
U 1 1 5D074CBF
P 3900 3150
F 0 "TP4" H 3842 3177 50  0000 R CNN
F 1 "IN5" H 3842 3268 50  0000 R CNN
F 2 "TestPoint:TestPoint_THTPad_2.5x2.5mm_Drill1.2mm" H 4100 3150 50  0001 C CNN
F 3 "~" H 4100 3150 50  0001 C CNN
	1    3900 3150
	-1   0    0    1   
$EndComp
Connection ~ 3900 3150
$Comp
L Device:R R3
U 1 1 5D07F846
P 4100 2700
F 0 "R3" H 4170 2746 50  0000 L CNN
F 1 "220" H 4170 2655 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 4030 2700 50  0001 C CNN
F 3 "~" H 4100 2700 50  0001 C CNN
	1    4100 2700
	1    0    0    -1  
$EndComp
Connection ~ 4100 2850
Connection ~ 6200 3100
$Comp
L Connector:TestPoint TP1
U 1 1 5D082A8E
P 2100 5300
F 0 "TP1" V 2295 5374 50  0000 C CNN
F 1 "T4" V 2204 5374 50  0000 C CNN
F 2 "TestPoint:TestPoint_THTPad_2.5x2.5mm_Drill1.2mm" H 2300 5300 50  0001 C CNN
F 3 "~" H 2300 5300 50  0001 C CNN
	1    2100 5300
	0    -1   -1   0   
$EndComp
$Comp
L Connector:TestPoint TP2
U 1 1 5D082B9F
P 2100 5550
F 0 "TP2" V 2295 5624 50  0000 C CNN
F 1 "T2" V 2204 5624 50  0000 C CNN
F 2 "TestPoint:TestPoint_THTPad_2.5x2.5mm_Drill1.2mm" H 2300 5550 50  0001 C CNN
F 3 "~" H 2300 5550 50  0001 C CNN
	1    2100 5550
	0    -1   -1   0   
$EndComp
$Comp
L Connector:TestPoint TP3
U 1 1 5D082C66
P 2100 5850
F 0 "TP3" V 2295 5924 50  0000 C CNN
F 1 "T5" V 2204 5924 50  0000 C CNN
F 2 "TestPoint:TestPoint_THTPad_2.5x2.5mm_Drill1.2mm" H 2300 5850 50  0001 C CNN
F 3 "~" H 2300 5850 50  0001 C CNN
	1    2100 5850
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5D085ED7
P 5900 3100
F 0 "#PWR0101" H 5900 2850 50  0001 C CNN
F 1 "GND" H 5905 2927 50  0000 C CNN
F 2 "" H 5900 3100 50  0001 C CNN
F 3 "" H 5900 3100 50  0001 C CNN
	1    5900 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 3100 6200 3100
$Comp
L power:+3.3V #PWR0102
U 1 1 5D086156
P 8900 2000
F 0 "#PWR0102" H 8900 1850 50  0001 C CNN
F 1 "+3.3V" H 8915 2173 50  0000 C CNN
F 2 "" H 8900 2000 50  0001 C CNN
F 3 "" H 8900 2000 50  0001 C CNN
	1    8900 2000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 5D086250
P 2150 5550
F 0 "#PWR0103" H 2150 5300 50  0001 C CNN
F 1 "GND" V 2155 5422 50  0000 R CNN
F 2 "" H 2150 5550 50  0001 C CNN
F 3 "" H 2150 5550 50  0001 C CNN
	1    2150 5550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2150 5550 2100 5550
$Comp
L Device:R R1
U 1 1 5D089794
P 2250 5850
F 0 "R1" V 2457 5850 50  0000 C CNN
F 1 "10" V 2366 5850 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 2180 5850 50  0001 C CNN
F 3 "~" H 2250 5850 50  0001 C CNN
	1    2250 5850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2400 5850 6050 5850
$Comp
L power:GND #PWR0104
U 1 1 5D08D8D9
P 10500 6150
F 0 "#PWR0104" H 10500 5900 50  0001 C CNN
F 1 "GND" H 10505 5977 50  0000 C CNN
F 2 "" H 10500 6150 50  0001 C CNN
F 3 "" H 10500 6150 50  0001 C CNN
	1    10500 6150
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D2
U 1 1 5D0950C7
P 7400 5750
F 0 "D2" H 7391 5966 50  0000 C CNN
F 1 "LED" H 7391 5875 50  0000 C CNN
F 2 "LED_THT:LED_D3.0mm" H 7400 5750 50  0001 C CNN
F 3 "~" H 7400 5750 50  0001 C CNN
	1    7400 5750
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R5
U 1 1 5D095175
P 7400 6050
F 0 "R5" V 7193 6050 50  0000 C CNN
F 1 "220" V 7284 6050 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 7330 6050 50  0001 C CNN
F 3 "~" H 7400 6050 50  0001 C CNN
	1    7400 6050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 5D0952A1
P 7400 6200
F 0 "#PWR0106" H 7400 5950 50  0001 C CNN
F 1 "GND" V 7405 6072 50  0000 R CNN
F 2 "" H 7400 6200 50  0001 C CNN
F 3 "" H 7400 6200 50  0001 C CNN
	1    7400 6200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 4900 7250 5000
Wire Wire Line
	7250 5000 7100 5000
Wire Wire Line
	6950 3150 6850 3150
NoConn ~ 7150 3150
NoConn ~ 7350 3150
NoConn ~ 8450 3150
NoConn ~ 8550 3150
NoConn ~ 8650 3150
NoConn ~ 9950 3950
NoConn ~ 9950 4050
NoConn ~ 8250 4900
NoConn ~ 8150 4900
NoConn ~ 8050 4900
NoConn ~ 7950 4900
NoConn ~ 7850 4900
NoConn ~ 7750 4900
NoConn ~ 7650 4900
NoConn ~ 7550 4900
NoConn ~ 7050 4900
$Comp
L Connector:TestPoint TP9
U 1 1 5D0FBCB8
P 9500 2900
F 0 "TP9" H 9558 3020 50  0000 L CNN
F 1 "Batt+" H 9558 2929 50  0000 L CNN
F 2 "TestPoint:TestPoint_THTPad_2.5x2.5mm_Drill1.2mm" H 9700 2900 50  0001 C CNN
F 3 "~" H 9700 2900 50  0001 C CNN
	1    9500 2900
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP10
U 1 1 5D0FFE2B
P 9900 3150
F 0 "TP10" H 9958 3270 50  0000 L CNN
F 1 "Batt-" H 9958 3179 50  0000 L CNN
F 2 "TestPoint:TestPoint_THTPad_2.5x2.5mm_Drill1.2mm" H 10100 3150 50  0001 C CNN
F 3 "~" H 10100 3150 50  0001 C CNN
	1    9900 3150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 5D0FFF08
P 9900 3150
F 0 "#PWR0107" H 9900 2900 50  0001 C CNN
F 1 "GND" H 9905 2977 50  0000 C CNN
F 2 "" H 9900 3150 50  0001 C CNN
F 3 "" H 9900 3150 50  0001 C CNN
	1    9900 3150
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP11
U 1 1 5D101022
P 10250 6100
F 0 "TP11" V 10204 6287 50  0000 L CNN
F 1 "GND" V 10295 6287 50  0000 L CNN
F 2 "TestPoint:TestPoint_THTPad_2.5x2.5mm_Drill1.2mm" H 10450 6100 50  0001 C CNN
F 3 "~" H 10450 6100 50  0001 C CNN
	1    10250 6100
	-1   0    0    1   
$EndComp
Wire Wire Line
	10400 5650 10150 5650
$Comp
L Device:R R8
U 1 1 5D0A7FC4
P 9750 5950
F 0 "R8" H 9820 5996 50  0000 L CNN
F 1 "1k" H 9820 5905 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 9680 5950 50  0001 C CNN
F 3 "~" H 9750 5950 50  0001 C CNN
	1    9750 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	10150 5950 10150 6100
Wire Wire Line
	10150 6100 10250 6100
Wire Wire Line
	10500 6100 10500 6150
Connection ~ 10150 6100
Connection ~ 10250 6100
Wire Wire Line
	10250 6100 10500 6100
Wire Wire Line
	9750 6100 10150 6100
Wire Wire Line
	9750 5800 10000 5800
Wire Wire Line
	10000 5800 10000 6000
Wire Wire Line
	10000 6000 10300 6000
Wire Wire Line
	10300 6000 10300 5800
Wire Wire Line
	8750 2550 8750 2300
Wire Wire Line
	8250 2550 8500 2550
Wire Wire Line
	8500 2550 8750 2550
NoConn ~ 8450 4900
NoConn ~ 8750 3150
Wire Wire Line
	10800 2900 10800 4900
Wire Wire Line
	9500 2900 9750 2900
Wire Wire Line
	10800 4900 9050 4900
Wire Wire Line
	9050 4900 9050 5200
Wire Wire Line
	9050 5200 8700 5200
Wire Wire Line
	8550 5200 8550 4900
Text GLabel 10400 5650 2    50   Input ~ 0
DAC_out
NoConn ~ 8350 4900
Connection ~ 8500 2550
Connection ~ 8750 2000
Wire Wire Line
	8750 2000 8900 2000
Wire Wire Line
	8500 2000 8750 2000
Wire Wire Line
	7350 2000 7600 2000
$Comp
L Device:R_POT RV11
U 1 1 5F40125E
P 7150 2400
F 0 "RV11" H 7080 2446 50  0000 R CNN
F 1 "10K" H 7080 2355 50  0000 R CNN
F 2 "Potentiometer_THT:Potentiometer_Alps_RK09K_Single_Vertical" H 7150 2400 50  0001 C CNN
F 3 "~" H 7150 2400 50  0001 C CNN
	1    7150 2400
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT RV10
U 1 1 5F401265
P 6900 2150
F 0 "RV10" H 6830 2196 50  0000 R CNN
F 1 "10K" H 6830 2105 50  0000 R CNN
F 2 "Potentiometer_THT:Potentiometer_Alps_RK09K_Single_Vertical" H 6900 2150 50  0001 C CNN
F 3 "~" H 6900 2150 50  0001 C CNN
	1    6900 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7350 2000 7150 2000
Wire Wire Line
	7150 2250 7150 2000
Connection ~ 7150 2000
Wire Wire Line
	6900 2550 6900 2300
Wire Wire Line
	6900 2000 7150 2000
Wire Wire Line
	6900 2550 7150 2550
Connection ~ 7150 2550
Wire Wire Line
	7150 2550 7350 2550
Connection ~ 7350 2550
Wire Wire Line
	7350 2550 7600 2550
Wire Wire Line
	7050 2650 7450 2650
Wire Wire Line
	7450 2650 7450 3150
Wire Wire Line
	7050 2150 7050 2650
Wire Wire Line
	7300 2400 7300 2600
Wire Wire Line
	7300 2600 7550 2600
Wire Wire Line
	7550 2600 7550 3150
Wire Wire Line
	7500 2850 7650 2850
Wire Wire Line
	7500 2150 7500 2850
Wire Wire Line
	7650 2850 7650 3150
Wire Wire Line
	7750 2400 7750 3150
Wire Wire Line
	7950 2150 7950 2600
Wire Wire Line
	7950 2600 7850 2600
Wire Wire Line
	7850 2600 7850 3150
Wire Wire Line
	8200 2400 8200 2650
Wire Wire Line
	8200 2650 7950 2650
Wire Wire Line
	7950 2650 7950 3150
Wire Wire Line
	8400 2150 8400 2700
Wire Wire Line
	8400 2700 8050 2700
Wire Wire Line
	8050 2700 8050 3150
Wire Wire Line
	8650 2400 8650 2800
Wire Wire Line
	8650 2800 8150 2800
Wire Wire Line
	8150 2800 8150 3150
Wire Wire Line
	8900 2150 8900 2900
Wire Wire Line
	8900 2900 8250 2900
Wire Wire Line
	8250 2900 8250 3150
$Comp
L power:GND #PWR0105
U 1 1 5F43569A
P 6900 2550
F 0 "#PWR0105" H 6900 2300 50  0001 C CNN
F 1 "GND" V 6905 2422 50  0000 R CNN
F 2 "" H 6900 2550 50  0001 C CNN
F 3 "" H 6900 2550 50  0001 C CNN
	1    6900 2550
	0    1    1    0   
$EndComp
Connection ~ 6900 2550
Wire Wire Line
	6050 2700 6050 3000
$Comp
L Analog_DAC:MCP4822 U1
U 1 1 5F435FFF
P 4450 6800
F 0 "U1" H 4450 7378 50  0000 C CNN
F 1 "MCP4822" H 4450 7287 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 5250 6500 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/20002249B.pdf" H 5250 6500 50  0001 C CNN
	1    4450 6800
	1    0    0    -1  
$EndComp
Wire Wire Line
	8700 5200 8700 5950
Wire Wire Line
	8700 5950 4850 5950
Connection ~ 8700 5200
Wire Wire Line
	8700 5200 8550 5200
$Comp
L power:GND #PWR0108
U 1 1 5F43EAC5
P 4450 7300
F 0 "#PWR0108" H 4450 7050 50  0001 C CNN
F 1 "GND" H 4455 7127 50  0000 C CNN
F 2 "" H 4450 7300 50  0001 C CNN
F 3 "" H 4450 7300 50  0001 C CNN
	1    4450 7300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 6800 3750 6800
Wire Wire Line
	3750 6800 3750 7300
Wire Wire Line
	3750 7300 4450 7300
Connection ~ 4450 7300
Wire Wire Line
	3950 6900 3500 6900
Wire Wire Line
	3500 6900 3500 6150
Wire Wire Line
	3500 6150 6950 6150
Wire Wire Line
	7100 5600 7400 5600
Wire Wire Line
	7100 5000 7100 5600
Wire Wire Line
	7150 4900 7150 5700
Wire Wire Line
	7150 5700 6950 5700
Wire Wire Line
	6950 5700 6950 6150
Wire Wire Line
	6850 4900 6850 7550
Wire Wire Line
	6850 7550 3950 7550
Wire Wire Line
	3950 7550 3950 7000
Wire Wire Line
	6950 4900 6950 5300
Wire Wire Line
	6950 5300 3950 5300
Wire Wire Line
	3950 5300 3950 6700
Text GLabel 6600 6950 1    50   Input ~ 0
DAC_out
$Comp
L Device:R R6
U 1 1 5F45FFDD
P 5400 6700
F 0 "R6" H 5470 6746 50  0000 L CNN
F 1 "470k" H 5470 6655 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 5330 6700 50  0001 C CNN
F 3 "~" H 5400 6700 50  0001 C CNN
	1    5400 6700
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R2
U 1 1 5F464815
P 5400 7350
F 0 "R2" V 5193 7350 50  0000 C CNN
F 1 "220" V 5284 7350 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 5330 7350 50  0001 C CNN
F 3 "~" H 5400 7350 50  0001 C CNN
	1    5400 7350
	0    1    1    0   
$EndComp
$Comp
L Device:R_POT_TRIM RV9
U 1 1 5F464A40
P 5400 7000
F 0 "RV9" V 5286 7000 50  0000 C CNN
F 1 "1k_Trim" V 5195 7000 50  0000 C CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3266Y_Vertical" H 5400 7000 50  0001 C CNN
F 3 "~" H 5400 7000 50  0001 C CNN
	1    5400 7000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5400 6850 5550 6850
Wire Wire Line
	5550 6850 5550 7000
Wire Wire Line
	5550 7000 5900 7000
Wire Wire Line
	5900 7000 5900 6900
Connection ~ 5550 7000
Wire Wire Line
	5900 6900 6000 6900
$Comp
L power:GND #PWR0109
U 1 1 5F477E85
P 4900 6350
F 0 "#PWR0109" H 4900 6100 50  0001 C CNN
F 1 "GND" V 4905 6222 50  0000 R CNN
F 2 "" H 4900 6350 50  0001 C CNN
F 3 "" H 4900 6350 50  0001 C CNN
	1    4900 6350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4750 6350 4850 6350
$Comp
L Device:CP C2
U 1 1 5F481DCA
P 4850 6100
F 0 "C2" H 4968 6146 50  0000 L CNN
F 1 "0.1micro_tantale" H 4968 6055 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 4888 5950 50  0001 C CNN
F 3 "~" H 4850 6100 50  0001 C CNN
	1    4850 6100
	1    0    0    -1  
$EndComp
Connection ~ 4850 5950
Wire Wire Line
	4850 5950 4450 5950
Wire Wire Line
	4850 6250 4850 6350
Connection ~ 4850 6350
Wire Wire Line
	4850 6350 4900 6350
Wire Wire Line
	6850 3100 6850 3150
Connection ~ 6850 3150
Wire Wire Line
	7050 3150 7050 2800
$Comp
L Isolator:6N138 U3
U 1 1 5F491E25
P 4650 3000
F 0 "U3" H 4650 3467 50  0000 C CNN
F 1 "6N138" H 4650 3376 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 4940 2700 50  0001 C CNN
F 3 "http://www.onsemi.com/pub/Collateral/HCPL2731-D.pdf" H 4940 2700 50  0001 C CNN
	1    4650 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 2850 4350 2900
Wire Wire Line
	4100 2850 4350 2850
Wire Wire Line
	4350 3100 4350 3150
Wire Wire Line
	3900 3150 4350 3150
Wire Wire Line
	4950 2800 5200 2800
Wire Wire Line
	4950 3200 4950 3400
Wire Wire Line
	4950 3400 5800 3400
Wire Wire Line
	5800 3400 5800 3100
Wire Wire Line
	5800 3100 5900 3100
Connection ~ 5900 3100
$Comp
L Device:R R4
U 1 1 5F4B39BE
P 5200 2950
F 0 "R4" H 5270 2996 50  0000 L CNN
F 1 "220" H 5270 2905 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 5130 2950 50  0001 C CNN
F 3 "~" H 5200 2950 50  0001 C CNN
	1    5200 2950
	1    0    0    -1  
$EndComp
Connection ~ 5200 2800
Wire Wire Line
	4950 3100 5200 3100
Wire Wire Line
	6050 3000 5500 3000
Wire Wire Line
	5500 3000 5500 3100
Wire Wire Line
	5500 3100 5200 3100
Connection ~ 6050 3000
Wire Wire Line
	6050 3000 6050 5850
Connection ~ 5200 3100
NoConn ~ 4950 2900
$Comp
L Connector:Conn_01x06_Female J1
U 1 1 5F4CDA37
P 7650 5450
F 0 "J1" V 7497 5698 50  0000 L CNN
F 1 "Conn_01x06_Female" V 7588 5698 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 7650 5450 50  0001 C CNN
F 3 "~" H 7650 5450 50  0001 C CNN
	1    7650 5450
	0    1    1    0   
$EndComp
Wire Wire Line
	8650 5000 7850 5000
Wire Wire Line
	7850 5000 7850 5250
NoConn ~ 7750 5250
Wire Wire Line
	7650 5050 7650 5250
Wire Wire Line
	7650 5050 8750 5050
Wire Wire Line
	7450 5050 7550 5050
Wire Wire Line
	7550 5050 7550 5250
Wire Wire Line
	7450 4900 7450 5050
Wire Wire Line
	7350 4900 7350 5100
Wire Wire Line
	7350 5100 7450 5100
Wire Wire Line
	7450 5100 7450 5250
NoConn ~ 7350 5250
$Comp
L Device:R R7
U 1 1 5F4FA085
P 2350 5150
F 0 "R7" H 2420 5196 50  0000 L CNN
F 1 "33" H 2420 5105 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 2280 5150 50  0001 C CNN
F 3 "~" H 2350 5150 50  0001 C CNN
	1    2350 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 5300 2350 5300
$Comp
L power:+3.3V #PWR0110
U 1 1 5F50094D
P 2350 5000
F 0 "#PWR0110" H 2350 4850 50  0001 C CNN
F 1 "+3.3V" H 2365 5173 50  0000 C CNN
F 2 "" H 2350 5000 50  0001 C CNN
F 3 "" H 2350 5000 50  0001 C CNN
	1    2350 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 7000 5250 7350
Wire Wire Line
	5250 7000 4950 7000
Connection ~ 5250 7000
Wire Wire Line
	5550 7350 5550 7000
Wire Wire Line
	4950 6700 5250 6700
Wire Wire Line
	5550 6700 5900 6700
Wire Wire Line
	5900 6700 5900 6900
Connection ~ 5900 6900
$Comp
L Amplifier_Operational:LM358 U4
U 1 1 5F44FFCF
P 6300 7000
F 0 "U4" H 6300 7367 50  0000 C CNN
F 1 "LM358" H 6300 7276 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 6300 7000 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2904-n.pdf" H 6300 7000 50  0001 C CNN
	1    6300 7000
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:LM358 U4
U 2 1 5F4500E6
P 9350 5650
F 0 "U4" H 9350 5283 50  0000 C CNN
F 1 "LM358" H 9350 5374 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 9350 5650 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2904-n.pdf" H 9350 5650 50  0001 C CNN
	2    9350 5650
	-1   0    0    1   
$EndComp
$Comp
L Amplifier_Operational:LM358 U4
U 3 1 5F4501F5
P 10150 2200
F 0 "U4" H 10108 2246 50  0000 L CNN
F 1 "LM358" H 10108 2155 50  0000 L CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 10150 2200 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2904-n.pdf" H 10150 2200 50  0001 C CNN
	3    10150 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	10050 1900 9750 1900
Wire Wire Line
	9750 1900 9750 2900
Connection ~ 9750 2900
Wire Wire Line
	9750 2900 10800 2900
Wire Wire Line
	8750 2550 10050 2550
Wire Wire Line
	10050 2550 10050 2500
Connection ~ 8750 2550
Wire Wire Line
	6600 6950 6600 7000
Wire Wire Line
	6600 7000 6600 7300
Wire Wire Line
	6600 7300 6000 7300
Wire Wire Line
	6000 7300 6000 7100
Connection ~ 6600 7000
Wire Wire Line
	9750 5800 9650 5800
Wire Wire Line
	9650 5800 9650 5750
Connection ~ 9750 5800
Wire Wire Line
	9650 5550 9650 5350
Wire Wire Line
	9650 5350 9050 5350
Wire Wire Line
	9050 5800 9000 5800
Connection ~ 9050 5650
Wire Wire Line
	9050 5650 9050 5800
Wire Wire Line
	9050 5350 9050 5650
$Comp
L Device:CP C4
U 1 1 5F4FA1AF
P 9000 5950
F 0 "C4" H 9118 5996 50  0000 L CNN
F 1 "10m" H 9118 5905 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 9038 5800 50  0001 C CNN
F 3 "~" H 9000 5950 50  0001 C CNN
	1    9000 5950
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C5
U 1 1 5F4FA2CD
P 9000 6250
F 0 "C5" H 8882 6204 50  0000 R CNN
F 1 "10m" H 8882 6295 50  0000 R CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 9038 6100 50  0001 C CNN
F 3 "~" H 9000 6250 50  0001 C CNN
	1    9000 6250
	-1   0    0    1   
$EndComp
$Comp
L Device:R R9
U 1 1 5F502147
P 8600 6400
F 0 "R9" V 8393 6400 50  0000 C CNN
F 1 "100R" V 8484 6400 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 8530 6400 50  0001 C CNN
F 3 "~" H 8600 6400 50  0001 C CNN
	1    8600 6400
	0    1    1    0   
$EndComp
Wire Wire Line
	8750 6400 9000 6400
Wire Wire Line
	4450 5950 4450 6350
$Comp
L Device:CP C1
U 1 1 5F521F06
P 4600 6350
F 0 "C1" V 4855 6350 50  0000 C CNN
F 1 "10m_chem" V 4764 6350 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 4638 6200 50  0001 C CNN
F 3 "~" H 4600 6350 50  0001 C CNN
	1    4600 6350
	0    -1   -1   0   
$EndComp
Connection ~ 4450 6350
Wire Wire Line
	4450 6350 4450 6400
Wire Wire Line
	5200 2800 6750 2800
Wire Wire Line
	6200 3100 6750 3100
$Comp
L Device:CP C3
U 1 1 5F52256D
P 6750 2950
F 0 "C3" H 6868 2996 50  0000 L CNN
F 1 "100n_tant" H 6868 2905 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 6788 2800 50  0001 C CNN
F 3 "~" H 6750 2950 50  0001 C CNN
	1    6750 2950
	1    0    0    -1  
$EndComp
Connection ~ 6750 2800
Wire Wire Line
	6750 2800 7050 2800
Connection ~ 6750 3100
Wire Wire Line
	6750 3100 6850 3100
$Comp
L Device:R R10
U 1 1 5F41B0F0
P 9500 3050
F 0 "R10" H 9570 3096 50  0000 L CNN
F 1 "22k" H 9570 3005 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 9430 3050 50  0001 C CNN
F 3 "~" H 9500 3050 50  0001 C CNN
	1    9500 3050
	1    0    0    -1  
$EndComp
Connection ~ 9500 2900
$Comp
L Device:R R11
U 1 1 5F41B1C3
P 9650 3200
F 0 "R11" V 9443 3200 50  0000 C CNN
F 1 "22k" V 9534 3200 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 9580 3200 50  0001 C CNN
F 3 "~" H 9650 3200 50  0001 C CNN
	1    9650 3200
	0    1    1    0   
$EndComp
Wire Wire Line
	9900 3100 9800 3100
Wire Wire Line
	9800 3100 9800 3200
Wire Wire Line
	9900 3150 9900 3100
Connection ~ 9900 3150
Wire Wire Line
	9500 3200 8950 3200
Wire Wire Line
	8950 3200 8950 3000
Wire Wire Line
	8950 3000 8350 3000
Wire Wire Line
	8350 3000 8350 3150
Connection ~ 9500 3200
$EndSCHEMATC
