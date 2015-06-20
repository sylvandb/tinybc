CC     = gcc
# DBFLAGS = -DDEBUG

all: tinybc
 
tinybc: tokenize.c tinybc.c main.c tokenize.h tinybc.h
	$(CC) $(DBFLAGS) -o $@ tokenize.c tinybc.c main.c -lcurses
 
tinybc.exe: tee.c cat.c tokenize.c tinybc.c main.c tokenize.h tinybc.h
	$(CC) $(DBFLAGS) -DBGR -I. -o $@ tokenize.c tinybc.c main.c -L. -lpdcurses
	$(CC) $(DBFLAGS) -o tee.exe tee.c
	$(CC) $(DBFLAGS) -o cat.exe cat.c

dos: tee.c cat.c tokenize.c tinybc.c main.c tokenize.h tinybc.h
	$(CC) $(DBFLAGS) -DBGR -I\pdcurses -o tinybc.exe tokenize.c tinybc.c main.c c:\pdcurses\dos\pdcurses.a
	$(CC) $(DBFLAGS) -o tee.exe tee.c
	$(CC) $(DBFLAGS) -o cat.exe cat.c

clean:
	rm -f tinybc tinybc.exe
 
.PHONY: clean

install:
	install tinybc /usr/bin
	install tinybc.1.gz /usr/share/man/man1
	install -d /usr/share/doc/tinybc
	install -m 0644 README /usr/share/doc/tinybc
	install -m 0644 LICENSE /usr/share/doc/tinybc
	install -m 0644 *.bas /usr/share/doc/tinybc
	install -m 0644 tinybctut.txt /usr/share/doc/tinybc

.PHONY: install

remove:
	rm -f /usr/bin/tinybc
	rm -f /usr/share/man/man1/tinybc.1.gz
	rm -rf /usr/share/doc/tinybc

.PHONY: remove

