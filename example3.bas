10 REM Shooting Stars, ported from 68000 Tiny BASIC
20 REM Modified by my clumsy fingers
30 
40 @(1) = -23, -3, -19, -11, 2, -5, -13, -7, -17
50 @(10) = 1518, 1311, 570, 3289, 2310, 1615, 2002, 1547, 1190
60 REM DO - Randomize stars and black holes
70 I = I + 1
80 IF RND(3200) > 2000 THEN @(I) = -@(I)
90 IF I < 9 GOTO 60
100 GOSUB 510
110 
120 REM DO - Game loop
130 REM DO
140 REM DO
150 PRINT "Your shot";
160 INPUT N
170 IF N = 0 PRINT "Press any key to return to command prompt...";
180 IF N = 0 END
190 IF (N < 1) + (N > 9) PRINT "Enter a number from 1 to 9, Q to quit."
200 IF (N < 1) + (N > 9) GOTO 140
210 IF @(N) <= 0 PRINT "You can only shoot stars."
220 C = C + 1
230 IF @(N) <= 0 GOTO 130
240 
250 H = 0
260 I = 1
270 B = 0
280 GOSUB 430
290 REM DO - Check score
300 H = H + (@(I) < 0)
310 B = B + @(I)
320 I = I + 1
330 IF I <= 9 GOTO 290
340 GOSUB 510
350 IF B = 96 PRINT "Sorry, you lost."
360 IF B = 96 END
370 IF H < 9 GOTO 120
380 
390 PRINT "You win!"
400 PRINT "You fired", C, "shots."
410 END
420 
430 REM SUB (N) - Inverts some stars and black holes
440 J = 1
450 REM DO
460 IF @(N + 9) / @(J) * @(J) = @(N + 9) THEN @(J) = -@(J)
470 J = J + 1
480 IF J <= 9 GOTO 450
490 RETURN
500 
510 REM SUB - Prints out the galaxy
520 J = 1
530 REM DO
540 IF @(J) < 0 PRINT "   .",
550 IF @(J) > 0 PRINT "   *",
560 IF J / 3 * 3 <> J GOTO 590
570 PRINT
580 PRINT
590 REM END IF
600 J = J + 1
610 IF J <= 9 GOTO 530
620 RETURN

