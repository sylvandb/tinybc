10 REM Circles
20 COLOR 7, 1
30 CLS
40 A = 56
50 B = 22
60 R = 20
70 GOSUB 1000
80 A = 25
90 B = 32
100 R = 19
110 GOSUB 1000
120 A = 18
130 B = 18
140 R = 15
150 GOSUB 1000
160 LOCATE 5, 14
170 COLOR 7, 3
180 PRINT "  T i n y  B A S I C  ";
190 LOCATE 19, 46
200 COLOR 7, 5
210 PRINT "  f o r  C u r s e s  ";
220 END
230
1000 REM Draw a circle
1050 F = 1 - R
1060 D = 1
1070 E = -2 * R
1080 X = 0
1090 Y = R
1100 M = A
1110 N = B + R
1120 GOSUB 2000
1130 M = A
1140 N = B - R
1150 GOSUB 2000
1160 M = A + R
1170 N = B
1180 GOSUB 2000
1190 M = A - R
1200 N = B
1210 GOSUB 2000
1220 IF F < 0 GOTO 1260
1230 Y = Y - 1
1240 E = E + 2
1250 F = F + E
1260 X = X + 1
1270 D = D + 2
1280 F = F + D
1290 M = A + X
1300 N = B + Y
1310 GOSUB 2000
1320 M = A - X
1330 N = B + Y
1340 GOSUB 2000
1350 M = A + X
1360 N = B - Y
1370 GOSUB 2000
1380 M = A - X
1390 N = B - Y
1400 GOSUB 2000
1410 M = A + Y
1420 N = B + X
1430 GOSUB 2000
1440 M = A - Y
1450 N = B + X
1460 GOSUB 2000
1470 M = A + Y
1480 N = B - X
1490 GOSUB 2000
1500 M = A - Y
1510 N = B - X
1520 GOSUB 2000
1530 IF X < Y GOTO 1220
1540 RETURN
1550
2000 REM Draw a pixel
2010 LOCATE 25 - N / 2, M
2020 P = N - N / 2 * 2
2030 INCHAR C
2040 IF P = 1 GOSUB 2200
2050 IF P = 0 GOSUB 2400
2060 RETURN
2200 IF C < 219 PRINT "\xdf";
2210 IF C = 220 PRINT "\xdb";
2220 RETURN
2400 IF C < 219 PRINT "\xdc";
2410 IF C = 223 PRINT "\xdb";
2420 RETURN
