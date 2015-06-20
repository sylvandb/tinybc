/*
 * Tiny BASIC for Curses
 *
 * Copyright (c) 2011, Tarvo Korrovits
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA  02110-1301  USA
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <curses.h>
#include "tinybc.h"

#define MAX_STRLEN FILENAME_MAX
/* Make a large buffer */
#define BUFSIZE 1000000
#define ARRSIZE 100000

struct mttype {
	char program[BUFSIZE];
	long int numbers[ARRSIZE];
	struct cttype *ct;
};

static void list(struct mttype *mt, long int m, long int n)
{
	char buffer[FILENAME_MAX], *p;
	long int exit, i, k;

	p = mt->program;
	while (*p && m && atoi(p) != m) {
		p += strcspn(p, "\n");
		p += strspn(p, "\n");
	}
	if (!(*p)) return;
	i = 0;
	exit = 0;
	do {
		if (strcspn(p, "\n") >= FILENAME_MAX - 1) break;
		strncpy(buffer, p, strcspn(p, "\n"));
		buffer[strcspn(p, "\n")] = 0;
		printw("%s\n", buffer);
		if (i++ == LINES - 3) {
			i = 0;
			printw("=== Press any key, ESC to break ===\n");
			interactive(1);
			while ((k = getch()) == -1) napms(10);
			interactive(0);
			if (k == 27) exit = 1;
		}
		p += strcspn(p, "\n");
		if (*p) p++;
		if (m && m == n) break;
	} while (*p && (!m || atoi(p) <= n) && !exit);
}

static void insert(struct mttype *mt, char *buffer)
{
	char *p, *p1;
	long int n;

	n = atoi(buffer);
	if (!n) return;
	p = mt->program;
	if (strlen(mt->program) + strlen(buffer) >= BUFSIZE) return;
	if (atoi(p) < n)
		while (*p && n && atoi(p) < n) {
			p += strcspn(p, "\n");
			p += strspn(p, "\n");
		}
	p1 = buffer;
	p1 += strcspn(p1, " ");
	p1 += strspn(p1, " ");
	if (atoi(p) == n) {
		memmove(p, p + strcspn(p, "\n") + 1, strlen(p) -
			strcspn(p, "\n")+ 1);
		if (!(*p1))
			if (*p == '\n')
				memmove(p, p + strspn(p, "\n"),
					strlen(p) - strspn(p, "\n") + 1);
	}
	if (!(*p1)) return;
	sprintf(buffer, "%s\n", buffer);
	memmove(p + strlen(buffer), p, strlen(p) + 1);
	memmove(p, buffer, strlen(buffer));
}

static void help(void)
{
	printw("\nCommand line: tinybc [options] [filename]\n");
	printw("Options: -number renumber, -i run interactively\n");
	printw("CLEAR -- Delete program\n");
	printw("LIST line1-line2 -- List program from line1 to line2\n");
	printw("QUIT -- Exit\n");
	printw("RUN -- Run program\n");
	printw("SAVE filename -- Save program\n");
	printw("HELP -- This help\n\n");
}

static void intro(void)
{
	printw("Tiny BASIC for Curses, version 0.6.0\n");
	printw("Type HELP if you need help\n\n");
}

static void run(struct mttype *mt)
{
	tinybc_start(mt->ct);
	while (!tinybc_ended(mt->ct)) tinybc_statement(mt->ct);
}

int main(int argc, char **argv)
{
	char buffer[MAX_STRLEN], *result, *p, *p1;
	long int pos, fileind, lastnum, exit, m, n;
	struct mttype *mt;
	FILE *f;

	mt = (struct mttype *) malloc(sizeof(struct mttype));
	mt->ct = (struct cttype *) malloc(sizeof(struct cttype));
	tinybc_init(mt->ct, mt->program, mt->numbers);
	exit = 0;
	fileind = 1;
	if (argc == 3) fileind = 2;
	if (argc > 1) {
		f = fopen(argv[fileind], "r");
		if (!f) {
			printf("tinybc: cannot open the file\n");
			return 1;
		}
		result = buffer;
		for (pos = 0; pos + MAX_STRLEN < BUFSIZE && result; ) {
			strcpy(buffer, "");
			result = fgets(buffer, MAX_STRLEN, f);
			strcpy(mt->program + pos, buffer);
			pos += strlen(buffer);
		}
		fclose(f);
	}

	if (argc == 1 || (argc == 3 && argv[1][1] == 'i')) {
		intro();
		while (!exit) {
			printw("tinybc: ");
			strcpy(buffer, "");
			getnstr(buffer, MAX_STRLEN - 1);
			p = buffer;
			if (isdigit(buffer[0])) {
				insert(mt, buffer);
				continue;
			}
			switch (buffer[0]) {
			case 'C':
				strcpy(mt->program, "");
				break;
			case 'L':
				p += strcspn(p, " ");
				p += strspn(p, " ");
				m = atoi(p);
				p += strcspn(p, "-");
				p += strspn(p, "-");
				n = atoi(p);
				if (!n) n = m;
				list(mt, m, n);
				break;
			case 'Q':
				tinybc_close(mt->ct);
				return 0;
			case 'R':
				run(mt);
				intro();
				break;
			case 'S':
				p += strcspn(p, " ");
				p += strspn(p, " ");
				f = fopen(p, "w");
				fputs(mt->program, f);
				fclose(f);
				break;
			case 'H':
				help();
				break;
			}

		}
		tinybc_close(mt->ct);
		return 0;
	}

	if (argc == 2) {
		run(mt);
		tinybc_close(mt->ct);
		return 0;
	}

	if (argc != 3 || !isdigit(argv[1][1])) {
		tinybc_close(mt->ct);
		return 1;
	}

	tinybc_close(mt->ct);
	lastnum = atoi(argv[1] + 1);
	for (p = mt->program; *p; p++) {
		if (lastnum + 10 >= ARRSIZE || atoi(p) >= ARRSIZE) {
			fclose(f);
			return 1;
		}
		n = atoi(p);
		mt->numbers[n] = lastnum;
		lastnum += 10;
		p += strcspn(p, "\n");
	}
	lastnum = atoi(argv[1] + 1);
	f = fopen(argv[fileind], "w");
	for (p = mt->program; *p; p++) {
		if (*p != '\n')	fprintf(f, "%d ", lastnum);
		if (*p != '\n') p += strcspn(p, " \n");
		p += strspn(p, " ");
		lastnum += 10;
		while (*p && *p != '\n')
			if (!strncmp(p, "GOTO", strlen("GOTO"))) {
				p1 = p;
				p1 += strcspn(p1, " ");
				p1 += strspn(p1, " ");
				n = atoi(p1);
				if (n >= ARRSIZE) return 1;
				p1 += strcspn(p1, " \n");
				p1 += strspn(p1, " ");
				if (*p1 == '\n') {
					fprintf(f, "GOTO %d",
						mt->numbers[n]);
					p += strcspn(p, "\n");
				} else if (*p)
					fputc(*p++, f);
			} else if (!strncmp(p, "GOSUB", strlen("GOSUB"))) {
				p1 = p;
				p1 += strcspn(p1, " ");
				p1 += strspn(p1, " ");
				n = atoi(p1);
				if (n >= ARRSIZE) return 1;
				p1 += strcspn(p1, " \n");
				p1 += strspn(p1, " ");
				if (*p1 == '\n') {
					fprintf(f, "GOSUB %d",
						mt->numbers[n]);
					p += strcspn(p, "\n");
				} else if (*p)
					fputc(*p++, f);
			} else
				fputc(*p++, f);
		fprintf(f, "\n");
	}
	fclose(f);
	return 0;
}

