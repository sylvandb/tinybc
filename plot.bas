10 REM 3D Plot
20 REM
30 I = 4
40 X = -3000
50 REM DO
60 N = 90000 - X * X / 100
70 GOSUB 330
80 V = S * 10 / 500 * 500
90 Y = V
100 REM DO
110 N = X * X / 100 + Y * Y / 100
120 GOSUB 330
130 S = S * 10
140 REM Change the sine argument here
150 N = S / 10
160 N = N * 5728 / 10000
170 N = N - N / 360 * 360
180 GOSUB 430
190 S = S / 100
200 REM Change the formula here
210 J = 30 * S
220 J = (2500 + J - 70 * Y / 100) / 100
230 GOSUB 570
240 Y = Y - 500
250 IF Y >= -V GOTO 100
260 REM LOOP
270 I = I + 1
280 X = X + 150
290 NAP 1
300 IF X <= 3000 GOTO 50
310 REM LOOP
320 END
330 REM SUBROUTINE square root
340 S = 1
350 K = 0
360 REM DO
370 S = (S + N / S) / 2
380 K = K + 1
390 IF (K < 100) * S GOTO 360
400 REM LOOP
410 RETURN
420 REM
430 REM SUBROUTINE sine
440 C = 10000
450 S = 0
460 K = 1
470 REM DO
480 IF K > N GOTO 540
490 U = S * 9998 / 10000 + C * 175 / 10000
500 C = C * 9998 / 10000 - S * 175 / 10000
510 S = U
520 K = K + 1
530 GOTO 470
540 REM LOOP
550 RETURN
560 REM
570 REM SUBROUTINE pixel
580 LOCATE I / 2, J
590 P = I - I / 2 * 2
600 INCHAR Z
610 IF (P = 0) * (Z = 32) OUT 223
620 IF (P = 0) * (Z = 220) OUT 219
630 IF P * (Z = 32) OUT 220
640 IF P * (Z = 223) OUT 219
650 RETURN

