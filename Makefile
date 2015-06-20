CC     = gcc
# DBFLAGS = -DDEBUG

all: tinybc
 
tinybc: tokenizer.c tinybc.c main.c tokenizer.h tinybc.h
	$(CC) $(DBFLAGS) -o $@ tokenizer.c tinybc.c main.c -lcurses
 
tinybc.exe: tokenizer.c tinybc.c main.c tokenizer.h tinybc.h
	$(CC) $(DBFLAGS) -I. -o $@ tokenizer.c tinybc.c main.c -L. -lpdcurses

clean:
	rm -f tinybc tinybc.exe
 
.PHONY: clean

