10 REM Star Trek
20 REM
30 REM Global variables:
40 REM A - command, C - casualties, D - days left, E - energy,
50 REM F - torpedoes, H - Klingons destroyed, K - Klingons, O - docked,
60 REM U, V - quadrant, X, Y - sector
70 REM Array offsets:
80 REM 0 - Galaxy map 8 x 8 (+/-100*Klingons+10*Starbases+stars)
90 REM 64 - Days to repair (SR, map, LR, phaser, warp, torpedo, shield)
100 REM 71 - Quadrant map 8 x 8 (1-Klingon, 2-base, 3-star, 4-Enterprise)
110 REM 135 - Klingons data 3 x 6 (energies, X, Y)
120 REM DO
130 PRINT "Do you want a difficult game (y or n)?";
140 GOSUB 5830
150 Z = (A <> 121) * 2999 + (A = 121) * 999
160 PRINT "Stardate 3200: your mission is",
170 REM DO
180 B = 0
190 I = 0
200 K = 0
210 REM DO
220 M = RND(Z) + 1
230 M = (M < 209) + (M < 99) + (M < 49) + (M < 24) + (M < 9) + (M < 2)
240 K = K + M
250 N = RND(99) < 4
260 B = B + N
270 @(I) = -100 * M - 10 * N - RND(8) - 1
280 I = I + 1
290 IF I <= 63 GOTO 210
300 REM LOOP
310 IF (B < 2) + (K < 4) GOTO 170
320 REM LOOP
330 PRINT "to destroy", K, "Klingons in 30 stardates."
340 PRINT "There are", B, "Starbases."
350 C = 0
360 D = 30
370 H = K
380 GOSUB 1140
390 GOSUB 5400
400 GOSUB 5470
410 GOSUB 950
420 GOSUB 2770
430 REM DO
440 REM DO
450 PRINT "r = Report       s = SR sensor    l = LR sensor"
460 PRINT "g = Galaxy map   p = Phaser       t = Torpedo"
470 PRINT "w = Warp engine  ***Please use these commands***"
480 PRINT "Captain?";
490 GOSUB 5830
500 IF A = 103 GOSUB 1340
510 IF A = 108 GOSUB 1590
520 IF A = 115 GOSUB 1840
530 IF A = 112 GOSUB 2130
540 IF A = 114 GOSUB 3350
550 IF A = 119 GOSUB 3740
560 IF A = 116 GOSUB 4590
570 IF (A = 113) + (A = 27) A = -A
580 IF A > 0 GOTO 440
590 REM LOOP
600 IF A < 0 GOTO 870
610 GOSUB 950
620 GOSUB 2770
630 IF K GOTO 760
640 PRINT "Mission accomplished."
650 IF D < 6 PRINT "Boy, you barely made it."
660 IF (D > 5) * (D < 10) PRINT "Good work..."
670 IF (D > 9) * (D < 14) PRINT "Fantastic!"
680 IF D > 13 PRINT "Unbelievable!"
690 D = 30 - D
700 L = H * 100 / D * 10
710 PRINT H, "Klingons were destroyed in", D, "stardates ("; L; ")."
720 M = 100 * (C = 0) - 5 * C
730 PRINT C, "casualties incurred ("; M; ")."
740 PRINT "Your score:", L + M
750 GOTO 870
760 REM END IF
770 IF D >= 0 GOTO 800
780 PRINT "It's too late, the federation has been conquered."
790 GOTO 870
800 REM END IF
810 IF E >= 0 GOTO 850
820 PRINT "Enterprise destroyed"
830 IF H - K > 9 PRINT "But you were a good man"
840 GOTO 870
850 REM END IF
860 GOTO 430
870 REM LOOP
880 PRINT
890 PRINT "Another game (y or n)?";
900 GOSUB 5830
910 IF A = 121 GOTO 120
920 REM LOOP
930 PRINT "Good bye."
940 END
950 REM SUBROUTINE docking
960 I = X - (X > 0)
970 REM DO
980 J = Y - (Y > 0)
990 REM DO
1000 IF @(71 + 8 * I + J) <> 2 GOTO 1040
1010 IF O = 0 PRINT "Sulu: 'Captain, we are docked at Starbase.'"
1020 GOSUB 1140
1030 RETURN
1040 REM END IF
1050 J = J + 1
1060 IF J <= Y + (Y < 7) GOTO 990
1070 REM LOOP
1080 I = I + 1
1090 IF I <= X + (X < 7) GOTO 970
1100 REM LOOP
1110 O = 0
1120 RETURN
1130 REM
1140 REM SUBROUTINE restore and repair
1150 E = 4000
1160 F = 10
1170 O = 1
1180 @(64) = 0, 0, 0, 0, 0, 0, 0
1190 RETURN
1200 REM
1210 REM SUBROUTINE assign random sector
1220 REM DO
1230 S = RND(8)
1240 T = RND(8)
1250 IF @(71 + 8 * S + T) GOTO 1220
1260 REM LOOP
1270 @(71 + 8 * S + T) = N
1280 RETURN
1290 REM
1300 REM SUBROUTINE location
1310 PRINT "Enterprise in q-", U + 1; ","; V + 1, "s-", X + 1; ","; Y + 1
1320 RETURN
1330 REM
1340 REM SUBROUTINE map
1350 GOSUB 1300
1360 M = 1
1370 GOSUB 3230
1380 IF @(64 + M) RETURN
1390 PRINT "of galaxy map";
1400 I = 0
1410 REM DO
1420 PRINT
1430 PRINT I + 1; ":",
1440 J = 0
1450 REM DO
1460 M = (@(8 * I + J) > 0) * @(8 * I + J)
1470 PRINT M / 100; M / 10 - M / 100 * 10; M - M / 10 * 10,
1480 J = J + 1
1490 IF J <= 7 GOTO 1450
1500 REM LOOP
1510 I = I + 1
1520 IF I <= 7 GOTO 1410
1530 REM LOOP
1540 PRINT
1550 PRINT "   ... ... ... ... ... ... ... ..."
1560 PRINT "    1   2   3   4   5   6   7   8 "
1570 RETURN
1580 REM
1590 REM SUBROUTINE lr
1600 GOSUB 1300
1610 M = 2
1620 GOSUB 3230
1630 IF @(64 + M) RETURN
1640 PRINT
1650 I = U - 1
1660 REM DO
1670 J = V - 1
1680 REM DO
1690 M = 8 * I + J
1700 Z = 0
1710 IF (I >= 0) * (I < 8) * (J >= 0) * (J < 8) Z = @(M)
1720 Z = (2 * (Z > 0) - 1) * Z
1730 IF Z @(M) = Z
1740 PRINT Z / 100; Z / 10 - Z / 100 * 10; Z - Z / 10 * 10,
1750 J = J + 1
1760 IF J <= V + 1 GOTO 1680
1770 REM LOOP
1780 PRINT
1790 I = I + 1
1800 IF I <= U + 1 GOTO 1660
1810 REM LOOP
1820 RETURN
1830 REM
1840 REM SUBROUTINE sr
1850 GOSUB 1300
1860 M = 0
1870 GOSUB 3230
1880 IF @(64 + M) RETURN
1890 M = 8 * U + V
1900 @(M) = (2 * (@(M) > 0) - 1) * @(M)
1910 PRINT
1920 I = 0
1930 REM DO
1940 PRINT I + 1,
1950 J = 0
1960 REM DO
1970 M = @(71 + 8 * I + J)
1980 IF M = 0 PRINT " .",
1990 IF M = 1 PRINT " K",
2000 IF M = 2 PRINT " B",
2010 IF M = 3 PRINT " *",
2020 IF M = 4 PRINT " E",
2030 J = J + 1
2040 IF J <= 7 GOTO 1960
2050 REM LOOP
2060 PRINT
2070 I = I + 1
2080 IF I <= 7 GOTO 1930
2090 REM LOOP
2100 PRINT "   1  2  3  4  5  6  7  8"
2110 RETURN
2120 REM
2130 REM SUBROUTINE phaser
2140 M = 3
2150 GOSUB 3230
2160 IF @(64 + M) RETURN
2170 PRINT "energized"
2180 PRINT "Units to fire";
2190 Z = 0
2200 INPUT Z
2210 IF Z < 1 RETURN
2220 IF Z <= E GOTO 2250
2230 PRINT "Spock: 'We have only", E, "units.'"
2240 RETURN
2250 REM END IF
2260 E = E - Z
2270 IF @(8 * U + V) / 100 GOTO 2310
2280 PRINT "Phaser fired at empty space."
2290 A = 0
2300 RETURN
2310 REM END IF
2320 N = @(8 * U + V) / 100
2330 Z = (2 * (N > 0) - 1) * Z / N
2340 N = 135
2350 REM DO
2360 IF N > 140 GOTO 2460
2370 IF @(N) GOTO 2400
2380 N = N + 1
2390 GOTO 2350
2400 REM END IF
2410 GOSUB 2500
2420 PRINT S, "units hit",
2430 GOSUB 2630
2440 N = N + 1
2450 GOTO 2350
2460 REM LOOP
2470 A = 0
2480 RETURN
2490 REM
2500 REM SUBROUTINE energy to hit
2510 IF Z < 1091 GOTO 2570
2520 PRINT "...overloaded..."
2530 @(67) = 1
2540 Z = 9
2550 M = 3
2560 GOSUB 3230
2570 REM END IF
2580 I = @(N + 6) - X - 1
2590 J = @(N + 12) - Y - 1
2600 S = Z * 30 / (30 + I * I + J * J) + 1
2610 RETURN
2620 REM
2630 REM SUBROUTINE hit klingon
2640 PRINT "Klingon at s-", @(N + 6) + 1; ","; @(N + 12) + 1,
2650 @(N) = @(N) - S
2660 IF @(N) > 0 PRINT "**damaged**"
2670 IF @(N) > 0 RETURN
2680 PRINT "***destroyed***"
2690 @(N) = 0
2700 I = 8 * U + V
2710 J = (@(I) > 0) - (@(I) < 0)
2720 @(I) = @(I) - 100 * J
2730 @(71 + 8 * @(N + 6) + @(N + 12)) = 0
2740 K = K - 1
2750 RETURN
2760 REM
2770 REM SUBROUTINE klingon attack
2780 IF @(8 * U + V) / 100 = 0 RETURN
2790 PRINT "Klingon attack"
2800 IF O PRINT "Starbase protects Enterprise"
2810 IF O RETURN
2820 T = 0
2830 M = 135
2840 REM DO
2850 IF M > 140 GOTO 2970
2860 IF @(M) GOTO 2890
2870 M = M + 1
2880 GOTO 2840
2890 REM END IF
2900 Z = (@(M) + RND(@(M)) + 1) / 2
2910 GOSUB 2500
2920 T = T + S
2930 PRINT S, "units hit from Klingon at s-",
2940 PRINT @(M + 6) + 1; ","; @(M + 12) + 1
2950 M = M + 1
2960 GOTO 2840
2970 REM LOOP
2980 E = E - T
2990 IF E > 0 GOTO 3030
3000 PRINT "*** Bang ***"
3010 A = 0
3020 RETURN
3030 REM END IF
3040 PRINT E, "units of energy left."
3050 IF RND(E / 4) < T GOSUB 3080
3060 RETURN
3070 REM
3080 REM SUBROUTINE random damages
3090 IF @(70) GOTO 3140
3100 @(70) = RND(T / 50 + 1) + 1
3110 M = 6
3120 GOSUB 3230
3130 RETURN
3140 REM END IF
3150 M = RND(6)
3160 @(64 + M) = @(64 + M) + RND(T / 99 + 1) + 1
3170 GOSUB 3230
3180 I = RND(8) + 1
3190 PRINT "McCoy: 'Sickbay to bridge, we suffered", I, "casualties.'"
3200 C = C + I
3210 RETURN
3220 REM
3230 REM SUBROUTINE print damage
3240 IF M = 0 PRINT "Short range sensor",
3250 IF M = 1 PRINT "Computer display",
3260 IF M = 2 PRINT "Long range sensor",
3270 IF M = 3 PRINT "Phaser",
3280 IF M = 4 PRINT "Warp engine",
3290 IF M = 5 PRINT "Photon torpedo tubes",
3300 IF M = 6 PRINT "Shield",
3310 IF @(64 + M) = 0 RETURN
3320 PRINT "damaged,", @(64 + M), "stardates estimated for repair"
3330 RETURN
3340 REM
3350 REM SUBROUTINE report
3360 PRINT "Status report:"
3370 PRINT "Stardate", 3230 - D
3380 PRINT "Time left", D
3390 PRINT "Condition     ",
3400 IF O = 0 GOTO 3430
3410 PRINT "Docked"
3420 GOTO 3530
3430 REM ELSE
3440 IF @(8 * U + V) / 100 = 0 GOTO 3470
3450 PRINT "Red"
3460 GOTO 3530
3470 REM ELSE
3480 IF E >= 999 GOTO 3510
3490 PRINT "Yellow"
3500 GOTO 3530
3510 REM ELSE
3520 PRINT "Green"
3530 REM END IF
3540 PRINT "Position       q-", U + 1; ","; V + 1, "s-", X + 1; ","; Y + 1
3550 PRINT "Energy", E
3560 PRINT "Torpedoes", F
3570 PRINT "Klingons left", K
3580 I = 0
3590 J = 0
3600 REM DO
3610 J = J + (2 * (@(I) > 0) - 1) * (@(I) - @(I) / 100 * 100) / 10
3620 I = I + 1
3630 IF I <= 63 GOTO 3600
3640 REM LOOP
3650 PRINT "Starbases", J
3660 M = 0
3670 REM DO
3680 IF @(64 + M) GOSUB 3230
3690 M = M + 1
3700 IF M <= 6 GOTO 3670
3710 REM LOOP
3720 RETURN
3730 REM
3740 REM SUBROUTINE warp
3750 M = 4
3760 GOSUB 3230
3770 I = @(64 + M)
3780 IF I = 0 PRINT
3790 REM DO
3800 PRINT "Sector distance";
3810 M = 0
3820 INPUT M
3830 IF M <= 0 RETURN
3840 IF (M > 2) * I = 0 GOTO 3870
3850 PRINT "Chekov: 'We can try 2 at most, sir.'"
3860 GOTO 3790
3870 REM END IF
3880 REM LOOP
3890 IF M <= 64 GOTO 3920
3900 PRINT "Spock: 'Are you sure, Captain?'"
3910 M = 64
3920 REM END IF
3930 IF E >= M * M / 2 GOTO 3960
3940 PRINT "Scotty: 'Sir, we do not have the energy.'"
3950 RETURN
3960 REM END IF
3970 GOSUB 5260
3980 IF R = 0 RETURN
3990 D = D - 1
4000 E = E - M * M / 2
4010 @(71 + 8 * X + Y) = 0
4020 N = 64
4030 REM DO
4040 @(N) = (@(N) > 0) * (@(N) - 1) 
4050 N = N + 1
4060 IF N <= 70 GOTO 4030
4070 REM LOOP
4080 B = 45 * (X + 1) + 22
4090 G = 45 * (Y + 1) + 22
4100 M = 45 * M
4110 REM DO
4120 M = M - R
4130 IF M >= -22 GOTO 4180
4140 @(71 + 8 * X + Y) = 4
4150 A = 0
4160 GOSUB 1300
4170 RETURN
4180 REM END IF
4190 B = B + S
4200 G = G + T
4210 I = B / 45 - 1
4220 J = G / 45 - 1
4230 IF (I < 0) + (I > 7) + (J < 0) + (J > 7) GOTO 4350
4240 IF @(71 + 8 * I + J) = 0 GOTO 4310
4250 PRINT "**Emergency stop**"
4260 PRINT "Spock: 'To err is human.'"
4270 @(71 + 8 * X + Y) = 4
4280 GOSUB 1300
4290 A = 0
4300 RETURN
4310 REM END IF
4320 X = I
4330 Y = J
4340 GOTO 4110
4350 REM LOOP
4360 B = (U + 1) * 72 + B / 5 + M / 5 * S / R - 9
4370 G = (V + 1) * 72 + G / 5 + M / 5 * T / R - 9
4380 U = B / 72 - 1
4390 V = G / 72 - 1
4400 IF RND(9) GOTO 4440
4410 PRINT "***Space storm***"
4420 T = 100
4430 GOSUB 3080
4440 REM END IF
4450 IF (U < 0) + (U > 7) + (V < 0) + (V > 7) GOTO 4510
4460 X = (B + 9 - 72 * (U + 1)) / 9 - 1
4470 Y = (G + 9 - 72 * (V + 1)) / 9 - 1
4480 GOSUB 5470
4490 A = 0
4500 RETURN
4510 REM END IF
4520 PRINT "**You wandered outside the galaxy**"
4530 PRINT "On board computer takes over, and saved your life"
4540 GOSUB 5400
4550 GOSUB 5470
4560 A = 0
4570 RETURN
4580 REM
4590 REM SUBROUTINE torpedo
4600 M = 5
4610 GOSUB 3230
4620 IF @(64 + M) RETURN
4630 IF F GOTO 4660
4640 PRINT "empty"
4650 RETURN
4660 REM END IF
4670 PRINT "loaded"
4680 GOSUB 5260
4690 IF R = 0 RETURN
4700 F = F - 1
4710 PRINT "Torpedo track",
4720 B = 45 * (X + 1) + 22
4730 G = 45 * (Y + 1) + 22
4740 REM DO
4750 B = B + S
4760 G = G + T
4770 I = B / 45 - 1
4780 J = G / 45 - 1
4790 IF (I < 0) + (I > 7) + (J < 0) + (J > 7) GOTO 5210
4800 PRINT I + 1; ","; J + 1,
4810 L = 71 + 8 * I + J
4820 M = 8 * U + V
4830 Z = (@(M) > 0) - (@(M) < 0)
4840 A = 0
4850 IF @(L) = 0 GOTO 4740
4860 IF @(L) <> 1 GOTO 4950
4870 S = RND(99) + 281
4880 N = 135
4890 REM DO
4900 IF (@(N + 6) = I) * (@(N + 12) = J) GOSUB 2630
4910 N = N + 1
4920 IF N <= 140 GOTO 4890
4930 REM LOOP
4940 RETURN
4950 REM END IF
4960 IF @(L) <> 2 GOTO 5020
4970 @(L) = 0
4980 @(M) = @(M) - 10 * Z
4990 PRINT "Starbase destroyed"
5000 PRINT "Spock: 'I often find human behaviour fascinating.'"
5010 RETURN
5020 REM END IF
5030 IF @(L) <> 3 GOTO 5190
5040 PRINT "Hit a star"
5050 IF RND(9) > 1 GOTO 5080
5060 PRINT "Torpedo absorbed"
5070 RETURN
5080 REM END IF
5090 @(L) = 0
5100 @(M) = @(M) - Z
5110 IF RND(9) > 4 GOTO 5140
5120 PRINT "Star destroyed"
5130 RETURN
5140 REM END IF
5150 T = 300
5160 PRINT "It novas ***radiation alarm***"
5170 GOSUB 3080
5180 RETURN
5190 REM END IF
5200 GOTO 4740
5210 REM LOOP
5220 PRINT "...missed"
5230 A = 0
5240 RETURN
5250 REM
5260 REM SUBRROUTINE course
5270 PRINT "Course (0-360)";
5280 N = -1
5290 INPUT N
5300 R = 0
5310 IF (N < 0) + (N > 360) RETURN
5320 S = (N + 45) / 90
5330 N = N - S * 90
5340 R = (45 + N * N) / 110 + 45
5350 Z = (S < 4) * S
5360 S = (Z = 0) * -45 + (Z = 1) * N + (Z = 2) * 45 + (Z = 3) * -N
5370 T = (Z = 0) * N + (Z = 1) * 45 + (Z = 2) * -N + (Z = 3) * -45
5380 RETURN
5390 REM
5400 REM SUBROUTINE random location
5410 U = RND(8)
5420 V = RND(8)
5430 X = RND(8)
5440 Y = RND(8)
5450 RETURN
5460 REM
5470 REM SUBROUTINE init quadrant
5480 I = 71
5490 REM DO
5500 @(I) = 0
5510 I = I + 1
5520 IF I <= 152 GOTO 5490
5530 REM LOOP
5540 @(71 + 8 * X + Y) = 4
5550 M = @(8 * U + V)
5560 M = (2 * (M > 0) - 1) * M
5570 N = 1
5580 I = 1
5590 REM DO
5600 IF I > M / 100 GOTO 5670
5610 GOSUB 1210
5620 @(135 + I - 1) = 300
5630 @(141 + I - 1) = S
5640 @(147 + I - 1) = T
5650 I = I + 1
5660 GOTO 5590
5670 REM LOOP
5680 GOSUB 1300
5690 M = M - M / 100 * 100
5700 N = 2
5710 IF M / 10 GOSUB 1210
5720 M = M - M / 10 * 10
5730 N = 3
5740 I = 1
5750 REM DO
5760 IF I > M GOTO 5800
5770 GOSUB 1210
5780 I = I + 1
5790 GOTO 5750
5800 REM LOOP
5810 RETURN
5820 REM
5830 REM SUBROUTINE input
5840 REM DO
5850 INKEY A
5860 NAP 10
5870 IF A < 0 GOTO 5840
5880 REM LOOP
5890 PRINT
5900 RETURN

