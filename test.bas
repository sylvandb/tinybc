200 REM Shooting Stars, ported from 68000 Tiny BASIC
210 REM Modified by my clumsy fingers
220 
230 @(1) = -23, -3, -19, -11, 2, -5, -13, -7, -17
240 @(10) = 1518, 1311, 570, 3289, 2310, 1615, 2002, 1547, 1190
250 REM DO - Randomize stars and black holes
260 I = I + 1
270 IF RND(3200) > 2000 THEN @(I) = -@(I)
280 IF I < 9 GOTO 250
290 GOSUB 680
300 
310 REM DO - Game loop
320 REM DO
330 REM DO
340 PRINT "Your shot";
350 INPUT N
360 IF N = 0 PRINT "Press any key to return to command prompt...";
370 IF N = 0 END
380 IF (N < 1) + (N > 9) PRINT "Enter a number from 1 to 9, Q to quit."
390 IF (N < 1) + (N > 9) GOTO 330
400 IF @(N) <= 0 PRINT "You can only shoot stars."
410 C = C + 1
420 IF @(N) <= 0 GOTO 320
430 
440 B = 0
450 I = 1
460 GOSUB 600
470 REM DO - Check score
480 B = B + (@(I) < 0)
490 I = I + 1
500 IF I <= 9 GOTO 470
510 GOSUB 680
520 IF B = 1 PRINT "Sorry, you lost."
530 IF B = 1 END
540 REM Or was it win?
550 IF B < 9 GOTO 310
560 PRINT "You win!"
570 PRINT "You fired", C, "shots."
580 END
590 
600 REM SUB (N) - Inverts some stars and black holes
610 J = 1
620 REM DO
630 IF @(N + 9) / @(J) * @(J) = @(N + 9) THEN @(J) = -@(J)
640 J = J + 1
650 IF J <= 9 GOTO 620
660 RETURN
670 
680 REM SUB - Prints out the galaxy
690 J = 1
700 REM DO
710 IF @(J) < 0 PRINT "   .",
720 IF @(J) > 0 PRINT "   *",
730 IF J / 3 * 3 <> J GOTO 760
740 PRINT
750 PRINT
760 REM END IF
770 J = J + 1
780 IF J <= 9 GOTO 700
790 RETURN
