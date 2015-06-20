10 REM Shooting Stars, ported from 68000 Tiny BASIC
20 REM Modified by my clumsy fingers
30 
40 @(1) = -23, -3, -19, -11, 2, -5, -13, -7, -17
50 @(10) = 1518, 1311, 570, 3289, 2310, 1615, 2002, 1547, 1190
60 REM DO - Randomize stars and black holes
70 I = I + 1
80 IF RND(3200) > 2000 THEN @(I) = -@(I)
90 IF I < 9 GOTO 60
100 GOSUB 490
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
250 B = 0
260 I = 1
270 GOSUB 410
280 REM DO - Check score
290 B = B + (@(I) < 0)
300 I = I + 1
310 IF I <= 9 GOTO 280
320 GOSUB 490
330 IF B = 1 PRINT "Sorry, you lost."
340 IF B = 1 END
350 REM Or was it win?
360 IF B < 9 GOTO 120
370 PRINT "You win!"
380 PRINT "You fired", C, "shots."
390 END
400 
410 REM SUB (N) - Inverts some stars and black holes
420 J = 1
430 REM DO
440 IF @(N + 9) / @(J) * @(J) = @(N + 9) THEN @(J) = -@(J)
450 J = J + 1
460 IF J <= 9 GOTO 430
470 RETURN
480 
490 REM SUB - Prints out the galaxy
500 J = 1
510 REM DO
520 IF @(J) < 0 PRINT "   .",
530 IF @(J) > 0 PRINT "   *",
540 IF J / 3 * 3 <> J GOTO 570
550 PRINT
560 PRINT
570 REM END IF
580 J = J + 1
590 IF J <= 9 GOTO 510
600 RETURN

