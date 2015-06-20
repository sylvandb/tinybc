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

install:
	install tinybc /usr/bin
	install tinybc.1.gz /usr/share/man/man1
	install -d /usr/share/doc/tinybc
	install -m 0644 README /usr/share/doc/tinybc
	install -m 0644 LICENSE /usr/share/doc/tinybc
	install -m 0644 ex* /usr/share/doc/tinybc

.PHONY: install

remove:
	rm -f /usr/bin/tinybc
	rm -f /usr/share/man/man1/tinybc.1.gz
	rm -rf /usr/share/doc/tinybc

.PHONY: remove

