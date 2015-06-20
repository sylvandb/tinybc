10 REM Shooting Stars, ported from 68000 Tiny BASIC
20 REM Modified by my clumsy fingers
30 
40 @(1) = -23
50 @(2) = -3
60 @(3) = -19
70 @(4) = -11
80 @(5) = 2
90 @(6) = -5
100 @(7) = -13
110 @(8) = -7
120 @(9) = -17
130 @(10) = 1518
140 @(11) = 1311
150 @(12) = 570
160 @(13) = 3289
170 @(14) = 2310
180 @(15) = 1615
190 @(16) = 2002
200 @(17) = 1547
210 @(18) = 1190
220 
230 REM DO - Randomize stars and black holes
240 I = I + 1
250 IF RND(3200) > 2000 THEN @(I) = -@(I)
260 IF I < 9 GOTO 230
270 GOSUB 660
280 
290 REM DO - Game loop
300 REM DO
310 REM DO
320 PRINT "Your shot";
330 INPUT N
340 IF (N < 1) + (N > 9) PRINT "You must enter a number from 1 to 9."
350 IF (N < 1) + (N > 9) GOTO 310
360 IF @(N) <= 0 PRINT "You can only shoot stars."
370 C = C + 1
380 IF @(N) <= 0 GOTO 300
390 
400 H = 0
410 I = 1
420 B = 0
430 GOSUB 580
440 REM DO - Check score
450 H = H + (@(I) < 0)
460 B = B + @(I)
470 I = I + 1
480 IF I <= 9 GOTO 440
490 GOSUB 660
500 IF B = 96 PRINT "Sorry, you lost."
510 IF B = 96 END
520 IF H < 9 GOTO 290
530 
540 PRINT "You win!"
550 PRINT "You fired", C, "shots."
560 END
570 
580 REM Subroutine (N) - Inverts some stars and black holes
590 J = 1
600 REM DO
610 IF @(N + 9) / @(J) * @(J) = @(N + 9) THEN @(J) = -@(J)
620 J = J + 1
630 IF J <= 9 GOTO 600
640 RETURN
650 
660 REM Subroutine - Prints out the galaxy
670 J = 1
680 REM DO
690 IF @(J) < 0 PRINT "   .",
700 IF @(J) > 0 PRINT "   *",
710 IF J / 3 * 3 <> J GOTO 740
720 PRINT
730 PRINT
740 REM END IF
750 J = J + 1
760 IF J <= 9 GOTO 680
770 RETURN

