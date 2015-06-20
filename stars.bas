10 REM Shooting Stars, ported from 68000 Tiny BASIC
20 REM Modified by my clumsy fingers
30 REM
40 @(1) = -23, -3, -19, -11, 2, -5, -13, -7, -17
50 @(10) = 1518, 1311, 570, 3289, 2310, 1615, 2002, 1547, 1190
60 REM DO
70 I = I + 1
80 IF RND(3200) > 2000 @(I) = -@(I)
90 IF I < 9 GOTO 60
100 REM LOOP
110 GOSUB 520
120 REM DO
130 REM DO
140 REM DO
150 PRINT "Your shot";
160 INPUT N
170 IF N = 0 PRINT "Press any key to return to command prompt...";
180 IF N = 0 END
190 IF (N < 1) + (N > 9) PRINT "Enter a number from 1 to 9, Q to quit."
200 IF (N < 1) + (N > 9) GOTO 140
210 REM LOOP
220 IF @(N) <= 0 PRINT "You can only shoot stars."
230 C = C + 1
240 IF @(N) <= 0 GOTO 130
250 REM LOOP
260 B = 0
270 I = 1
280 GOSUB 430
290 REM DO
300 B = B + (@(I) < 0)
310 I = I + 1
320 IF I <= 9 GOTO 290
330 REM LOOP
340 GOSUB 520
350 REM Or was it win?
360 IF B = 1 PRINT "Sorry, you lost."
370 IF B = 1 END
380 IF B < 9 GOTO 120
390 REM LOOP
400 PRINT "You win!"
410 PRINT "You fired", C, "shots."
420 END
430 REM SUBROUTINE invert some stars and black holes
440 K = 1
450 REM DO
460 IF @(N + 9) / @(K) * @(K) = @(N + 9) @(K) = -@(K)
470 K = K + 1
480 IF K <= 9 GOTO 450
490 REM LOOP
500 RETURN
510 REM
520 REM SUBROUTINE print out the galaxy
530 K = 1
540 REM DO
550 IF @(K) < 0 PRINT "   .",
560 IF @(K) > 0 PRINT "   *",
570 IF K / 3 * 3 <> K GOTO 600
580 PRINT
590 PRINT
600 REM END IF
610 K = K + 1
620 IF K <= 9 GOTO 540
630 REM LOOP
640 RETURN

