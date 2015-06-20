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

#include "tokenizer.h"

struct pstr {
	int token;
	char *pattern;
};

/* Keywords of the new statements must be added here */
static const struct pstr patterns[] = {
	{TOKEN_CLS, "CLS"}, /* Added */
	{TOKEN_COLOR, "COLOR"}, /* Added */
	{TOKEN_END, "END"},
	{TOKEN_GOSUB, "GOSUB"},
	{TOKEN_GOTO, "GOTO"},
	{TOKEN_IF, "IF"},
	{TOKEN_INCHAR, "INCHAR"}, /* Added */
	{TOKEN_INKEY, "INKEY"}, /* Added */
	{TOKEN_INPUT, "INPUT"},
	{TOKEN_LET, "LET"},
	{TOKEN_LOCATE, "LOCATE"}, /* Added */
	{TOKEN_NAP, "NAP"}, /* Added */
	{TOKEN_PRINT, "PRINT"},
	{TOKEN_PRINT, "PR"},
	{TOKEN_REM, "REM"}, /* Added */
	{TOKEN_RETURN, "RETURN"},
	{TOKEN_RND, "RND"}, /* Added */
	{TOKEN_SIZE, "SIZE"},
	{TOKEN_THEN, "THEN"},
	{TOKEN_NONE, NULL}
};

static int specialchar(struct ttype *t)
{
	switch (*t->ptr) {
	case '\n': return TOKEN_LF;
	case '*': return TOKEN_ASTR;
	case '@': return TOKEN_AT;
	case ',': return TOKEN_COMMA;
	case '=': return TOKEN_EQ;
	case '>': return TOKEN_GT;
	case '(': return TOKEN_LPAREN;
	case '<': return TOKEN_LT;
	case '-': return TOKEN_MINUS;
	case '+': return TOKEN_PLUS;
	case ')': return TOKEN_RPAREN;
	case ';': return TOKEN_SEMICOLON;
	case '/': return TOKEN_SLASH;
	}
	return 0;
}

static int get_type(struct ttype *t)
{
	const struct pstr *pt;
	const char *p;
	long int slen;

#ifdef DEBUG
	char str[20];
	strncpy(str, t->ptr, 20);
	str[20] = 0;
	fprintf(lg, "get: text '%s'\n", str);
#endif
	if (*t->ptr == 0) {
		t->ended = 1;
		return TOKEN_NONE;
	}
	if (isdigit(*t->ptr)) {
		if (strspn(t->ptr, "0123456789") <= MAX_NUMLEN) {
			t->next = t->ptr + strspn(t->ptr, "0123456789");
			return TOKEN_NUMBER;
		}
		PDEBUG(lg, "get: too long number\n");
		t->ended = 1;
		return TOKEN_NONE;
	}
	if (specialchar(t)) {
		if (!strncmp(t->ptr, "<>", 2)) {
			t->next = t->ptr + 2;
			return TOKEN_NOTEQ;
		}
		if (!strncmp(t->ptr, "<=", 2)) {
			t->next = t->ptr + 2;
			return TOKEN_LE;
		}
		if (!strncmp(t->ptr, ">=", 2)) {
			t->next = t->ptr + 2;
			return TOKEN_GE;
		}
		t->next = t->ptr + 1;
		return specialchar(t);
	}
	if (*t->ptr == '"') {
		slen = 0;
		for (p = t->ptr + 1; *p != '\"'; p++) slen++;
		t->next = t->ptr + slen + 2;
		return TOKEN_STRING;
	}
	for (pt = patterns; pt->pattern; pt++)
		if (!strncmp(t->ptr, pt->pattern, strlen(pt->pattern))) {
			if (!strcmp(pt->pattern, "REM"))
				t->next = t->ptr + strcspn(t->ptr, "\n");
			else
				t->next = t->ptr + strlen(pt->pattern);
			return pt->token;
		}
	if (*t->ptr >= 'A' && *t->ptr <= 'Z') {
		t->next = t->ptr + 1;
		return TOKEN_VARIABLE;
	}
	return TOKEN_NONE;
}

long int t_currline(struct ttype *t)
{
	return t->currentline;
}

void t_currline_set(struct ttype *t, long int currline)
{
	t->currentline = currline;
}

long int *t_data(struct ttype *t)
{
	return t->data;
}

void t_end(struct ttype *t)
{
	t->ended = 1;
}

int t_ended(struct ttype *t)
{
	return t->ended == 1;
}

int t_expr_type(struct ttype *t)
{
	if (t->currtype == TOKEN_VARIABLE ||
		t->currtype == TOKEN_NUMBER ||
		t->currtype == TOKEN_MINUS ||
		t->currtype == TOKEN_RND ||
		t->currtype == TOKEN_SIZE ||
		t->currtype == TOKEN_AT ||
		t->currtype == TOKEN_LPAREN)
		return 1;
	return 0;
}

void t_jump(struct ttype *t, long int line)
{
	if (t_ended(t)) return;
	if (line >= ARRSIZE ||
		(!t->numbers[line] && line != t->firstline)) {
		PDEBUG(lg, "jump: jump to wrong line\n");
		t->ended = 1;
		return;
	}
	t->ptr = t->program + t->numbers[line];
	PDEBUG(lg, "jump: jumped to line %d\n", line);
	t->currtype = get_type(t);
}

void t_init(struct ttype *t, char *program, long int *numbers)
{
#ifdef DEBUG
	lg = fopen("log.txt", "w");
#endif
	t->program = program;
	t->numbers = numbers;
}

void t_next(struct ttype *t)
{
	if (t_ended(t)) return;
	t->ptr = t->next;
	if (*t->ptr) t->ptr += strspn(t->ptr, " ");
	t->currtype = get_type(t);
	PDEBUG(lg, "next: current type %d\n", t->currtype);
	return;
}

void t_next_line(struct ttype *t)
{
	if (t_ended(t)) return;
	if (*t->ptr) t->ptr += strcspn(t->ptr, "\n");
	if (*t->ptr) t->ptr++;
	t->currtype = get_type(t);
	return;
}

long int t_number(struct ttype *t)
{
	return atoi(t->ptr);
}

long int t_size(struct ttype *t)
{
	return t->size;
}

void t_start(struct ttype *t)
{
	long int n, i;
	char *p;

	t->ended = 0;
	t->ptr = t->program;
	t->firstline = atoi(t->ptr);
	for (i = 0; i < ARRSIZE; i++) t->numbers[i] = 0;

	for (i = 0; i < BUFSIZE && *(t->ptr + i); i++);
	n = i + 1;
	t->data = (long int *) t->ptr + n;
	t->size = BUFSIZE - n;
	for (i = n; i < BUFSIZE; i++) {
		p = (char *) t->ptr + i;
		*p = 0;
	}

	for (i = 0; *(t->ptr + i) && !t->ended; ) {
		if (i >= ARRSIZE) t->ended = 1;
		if ((n = atoi(t->ptr + i)) < ARRSIZE) 
			t->numbers[n] = i;
		else
			t->ended = 1;
		i += strcspn(t->ptr + i, "\n");
		if (t->ptr + i) i++;
	}
	t->ptr = t->program;
	t->currtype = get_type(t);
}

void t_string(struct ttype *t, char *dest, long int len)
{
	const char *sptr, *p;
	char shex[3], *dptr;
	unsigned int n;
	long int slen;
	
	if (t_type(t) != TOKEN_STRING) return;
	slen = 0;
	for (p = t->ptr + 1; *p && *p != '\"' && slen < MAX_STRLEN; p++)
		slen++;
	if (*p != '\"') return;
	if (len < slen) slen = len;
	dptr = dest;
	*dptr = 0;
	for (sptr = t->ptr + 1; sptr < t->ptr + 1 + slen; dptr++)
		if (*sptr == '\\' && strlen(sptr) >= 4) {
			strncpy(shex, sptr + 2, 2);
			n = 0;
			shex[2] = 0;
			sscanf(shex, "%x", &n);
			*dptr = (char) n;
			*(dptr + 1) = 0;
			sptr += 4;
		} else {
			*dptr = *sptr++;
			*(dptr + 1) = 0;
		}
}

void t_take(struct ttype *t, int expected)
{
	if (expected != t->currtype) {
		printw("Token type not what was expected (expected %d, "
			"got %d), line %d\n", expected, t_type(t),
			t->currentline);
		t->ended = 1;
	}
	PDEBUG(lg, "take: expected type %d, got it\n", expected);
	t_next(t);
}

int t_toolong(struct ttype *t)
{
	if (strcspn(t->ptr, "\n") >= MAX_STRLEN - 1) return 1;
	return 0;
}

int t_type(struct ttype *t)
{
	return t->currtype;
}

int t_variable(struct ttype *t)
{
	if (*t->ptr == 0) return 0;
	return *t->ptr - 'A';
}

