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
#include "tinybc.h"

static long int expr(struct cttype *ct);
static void stmt(struct cttype *ct);

static long int factor(struct cttype *ct)
{
	long int minus, nind, n;

	if (t_ended(ct->t)) return 0;
	PDEBUG(lg, "factor: token %d\n", t_type(ct->t));
	if (t_type(ct->t) == TOKEN_MINUS) {
		t_take(ct->t, TOKEN_MINUS);
		minus = -1;
		PDEBUG(lg, "factor: minus\n");
	} else
		minus = 1;
	switch (t_type(ct->t)) {
	case TOKEN_RND:
		t_take(ct->t, TOKEN_RND);
		t_take(ct->t, TOKEN_LPAREN);
		n = minus * rand() % expr(ct);
		PDEBUG(lg, "factor: random number %d\n", n);
		t_take(ct->t, TOKEN_RPAREN);
		break;
	case TOKEN_SIZE:
		t_take(ct->t, TOKEN_SIZE);
		n = minus * t_size(ct->t);
		PDEBUG(lg, "factor: size %d\n", n);
		break;
	case TOKEN_NUMBER:
		n = minus * t_number(ct->t);
		PDEBUG(lg, "factor: number %d\n", n);
		t_take(ct->t, TOKEN_NUMBER);
		break;
	case TOKEN_LPAREN:
		t_take(ct->t, TOKEN_LPAREN);
		n = minus * expr(ct);
		PDEBUG(lg, "factor: expression %d\n", n);
		t_take(ct->t, TOKEN_RPAREN);
		break;
	case TOKEN_VARIABLE:
		n = minus * tinybc_get(ct, t_variable(ct->t));
		PDEBUG(lg, "factor: obtaining value %d from "
			"variable number %d\n",
			tinybc_get(ct, t_variable(ct->t)),
			t_variable(ct->t));
		t_take(ct->t, TOKEN_VARIABLE);
		break;
	case TOKEN_AT:
		t_take(ct->t, TOKEN_AT);
		t_take(ct->t, TOKEN_LPAREN);
		nind = expr(ct);
		n = minus * tinybc_get(ct, MAX_VARIND + nind);
		PDEBUG(lg, "factor: obtaining value %d from "
			"array element number %d\n",
			tinybc_get(ct, MAX_VARIND + nind), nind);
		t_take(ct->t, TOKEN_RPAREN);
		break;
	default:
		PDEBUG(lg, "factor: wrong token\n");
		t_end(ct->t);
		return 0;
	}
	return n;
}

static long int term(struct cttype *ct)
{
	long int n1, n2, op;

	if (t_ended(ct->t)) return 0;
	n1 = factor(ct);
	op = t_type(ct->t);
	PDEBUG(lg, "term: token %d\n", op);
	/* Does all multiplications and divisions */
	while (op == TOKEN_ASTR || op == TOKEN_SLASH) {
		t_next(ct->t);
		n2 = factor(ct);
		PDEBUG(lg, "term: %d %d %d\n", n1, op, n2);
		switch (op) {
		case TOKEN_ASTR:
			n1 = n1 * n2;
			break;
		case TOKEN_SLASH:
			n1 = n1 / n2;
			break;
		}
		op = t_type(ct->t);
	}
	PDEBUG(lg, "term: %d\n", n1);
	return n1;
}

static long int component(struct cttype *ct)
{
	long int n1, n2, op;
	
	if (t_ended(ct->t)) return 0;
	n1 = term(ct);
	op = t_type(ct->t);
	PDEBUG(lg, "component: token %d\n", op);
	while (op == TOKEN_PLUS || op == TOKEN_MINUS) {
		t_next(ct->t);
		n2 = term(ct);
		PDEBUG(lg, "component: %d %d %d\n", n1, op, n2);
		switch(op) {
		case TOKEN_PLUS:
			n1 = n1 + n2;
			break;
		case TOKEN_MINUS:
			n1 = n1 - n2;
			break;
		}
		op = t_type(ct->t);
	}
	PDEBUG(lg, "component: %d\n", n1);
	return n1;
}

static long int expr(struct cttype *ct)
{
	long int n1, n2, op;

	if (t_ended(ct->t)) return 0;
	n1 = component(ct);
	op = t_type(ct->t);
	PDEBUG(lg, "expr: token %d\n", op);
	while (op == TOKEN_LT || op == TOKEN_GT ||
		op == TOKEN_EQ || op == TOKEN_NOTEQ ||
		op == TOKEN_LE || op == TOKEN_GE) {
		t_next(ct->t);
		n2 = component(ct);
		PDEBUG(lg, "expr: %d %d %d\n", n1, op, n2);
		switch(op) {
		case TOKEN_LT:
			n1 = n1 < n2;
			break;
		case TOKEN_GT:
			n1 = n1 > n2;
			break;
		case TOKEN_EQ:
			n1 = n1 == n2;
			break;
		case TOKEN_NOTEQ:
			n1 = n1 != n2;
			break;
		case TOKEN_LE:
			n1 = n1 <= n2;
			break;
		case TOKEN_GE:
			n1 = n1 >= n2;
			break;
		}
		op = t_type(ct->t);
	}
	PDEBUG(lg, "expr: %d\n", n1);
	return n1;
}

void interactive(int mode)
{
	if (mode) {
		curs_set(0);
		cbreak();
		noecho();
		nodelay(stdscr, TRUE);
		keypad(stdscr, TRUE);
		scrollok(stdscr, FALSE);
	} else {
		curs_set(1);
		nocbreak();
		echo();
		nodelay(stdscr, FALSE);
		keypad(stdscr, FALSE);
		scrollok(stdscr, TRUE);
	}
}

#if 0
/*
 * Example of a new statement, assigns n2 to n1.
 * To add a new statement, do the following:
 * 1. Add the tokenizer type to the enum in tokenizer.h,
 * 2. Add the keyword to keywords array in tokenizer.c,
 * 3. Add new function to the statement function below,
 * 4. Include a new header file here if necessary,
 * 5. Write the new function below this example
 */
static void assign_stmt(struct cttype *ct)
{
	long int n1ind, n2;

	t_take(ct->t, TOKEN_ASSIGN);
	PDEBUG(lg, "assign:\n");
	if (t_type(ct->t) == TOKEN_VARIABLE) {
		n1ind = t_variable(ct->t);
		t_take(ct->t, TOKEN_VARIABLE);
	} else
		t_take(ct->t, TOKEN_VARIABLE);
	if (t_expr_type(ct)) {
		n2 = expr(ct);
		/* Now we have both parameters, do the operation */
		tinybc_set(ct, n1ind, n2);
	} else
		t_take(ct->t, TOKEN_VARIABLE);
	t_take(ct->t, TOKEN_LF);
}
#endif

static void at_stmt(struct cttype *ct)
{
	long int n1ind;

	t_take(ct->t, TOKEN_AT);
	PDEBUG(lg, "at:\n");
	t_take(ct->t, TOKEN_LPAREN);
	n1ind = expr(ct);
	t_take(ct->t, TOKEN_RPAREN);
	t_take(ct->t, TOKEN_EQ);
	for (; ;)
		if (t_expr_type(ct->t))
			tinybc_set(ct, MAX_VARIND + n1ind++, expr(ct));
		else if (t_type(ct->t) == TOKEN_COMMA)
			t_take(ct->t, TOKEN_COMMA);
		else
			break;
	t_take(ct->t, TOKEN_LF);
}

static void cls_stmt(struct cttype *ct)
{
	t_take(ct->t, TOKEN_CLS);
	PDEBUG(lg, "cls:\n");
	bkgd(COLOR_PAIR(ct->currentcolor[0]));
	clear();
	refresh();
	t_take(ct->t, TOKEN_LF);
}

static void color_stmt(struct cttype *ct)
{
	long int n1, n2;

	t_take(ct->t, TOKEN_COLOR);
	PDEBUG(lg, "color:\n");
	if (t_expr_type(ct->t))
		n1 = expr(ct);
	else
		t_take(ct->t, TOKEN_VARIABLE);
	t_take(ct->t, TOKEN_COMMA);
	if (t_expr_type(ct->t)) {
		n2 = expr(ct);
		/* Only COLOR_PAIRS color pairs are allowed */
		if (ct->colorpairs[n1][n2] && 
			n1 < MAX_COLOR && n2 < MAX_COLOR) {
			ct->currentcolor[0] = ct->colorpairs[n1][n2];
			ct->currentcolor[1] = n1;
			ct->currentcolor[2] = n2;
		} else if (ct->lastpair < COLOR_PAIRS - 1 &&
			n1 < MAX_COLOR && n2 < MAX_COLOR) {
			ct->lastpair++;
			ct->colorpairs[n1][n2] = ct->lastpair;
			ct->currentcolor[0] = ct->lastpair;
			ct->currentcolor[1] = n1;
			ct->currentcolor[2] = n2;
			init_pair(ct->currentcolor[0], n1, n2);
		}
		attrset(COLOR_PAIR(ct->currentcolor[0]));
	} else
		t_take(ct->t, TOKEN_VARIABLE);
	t_take(ct->t, TOKEN_LF);
}

static void end_stmt(struct cttype *ct)
{
	t_take(ct->t, TOKEN_END);
	PDEBUG(lg, "end:t\n");
	t_end(ct->t);
	t_take(ct->t, TOKEN_LF);
}

static void gosub_stmt(struct cttype *ct)
{
	long int linenum;

	t_take(ct->t, TOKEN_GOSUB);
	PDEBUG(lg, "gosub:\n");
	linenum = expr(ct);
	t_take(ct->t, TOKEN_LF);
	if (ct->gosub_stack_ptr < MAX_GOSUB_DEPTH) {
		ct->gosub_stack[ct->gosub_stack_ptr++] = t_number(ct->t);
		t_jump(ct->t, linenum);
	} else {
		printw("Gosub stack exhausted, line %d\n",
			t_currline(ct->t));
		t_end(ct->t);
	}
}

static void goto_stmt(struct cttype *ct)
{
	long int linenum;

	t_take(ct->t, TOKEN_GOTO);
	PDEBUG(lg, "goto:\n");
	linenum = expr(ct);
	t_jump(ct->t, linenum);
}

static void if_stmt(struct cttype *ct)
{
	long int n;
	
	t_take(ct->t, TOKEN_IF);
	n = expr(ct);
	PDEBUG(lg, "if: expression %d\n", n);
	/* THEN not compulsory */
	if (t_type(ct->t) == TOKEN_THEN) t_take(ct->t, TOKEN_THEN);
	if (n) {
		if (t_type(ct->t) == TOKEN_LET) t_take(ct->t, TOKEN_LET);
		stmt(ct);
	} else
		t_next_line(ct->t);
}

static void inchar_stmt(struct cttype *ct)
{
	long int n1ind;

	t_take(ct->t, TOKEN_INCHAR);
	PDEBUG(lg, "inchar:\n");
	if (t_type(ct->t) == TOKEN_VARIABLE) {
		n1ind = t_variable(ct->t);
		tinybc_set(ct, n1ind, inch() & A_CHARTEXT);
	}
	t_take(ct->t, TOKEN_VARIABLE);
	t_take(ct->t, TOKEN_LF);
}

static void inkey_stmt(struct cttype *ct)
{
	long int n1ind;

	t_take(ct->t, TOKEN_INKEY);
	PDEBUG(lg, "inkey:\n");
	if (t_type(ct->t) == TOKEN_VARIABLE) {
		n1ind = t_variable(ct->t);
		tinybc_set(ct, n1ind, wgetch(stdscr));
	}
	t_take(ct->t, TOKEN_VARIABLE);
	t_take(ct->t, TOKEN_LF);
}

static void input_stmt(struct cttype *ct)
{
	char buffer[MAX_STRLEN], *p;
	long int n1ind, i, c, n;

	t_take(ct->t, TOKEN_INPUT);
	PDEBUG(lg, "input:\n");
	strcpy(buffer, "");
	printw("? ");
	interactive(0);
	refresh();
	getnstr(buffer, MAX_STRLEN - 1);
	p = buffer;
	for (; ;)
		if (t_type(ct->t) == TOKEN_VARIABLE) {
			n1ind = t_variable(ct->t);
			while (*p && !isdigit(*p) && *p != '-' &&
				(*p < 'A' || *p > 'Z'))
				p++;
			if (*p && (isdigit(*p) || *p == '-')) {
				tinybc_set(ct, n1ind, atoi(p));
				while (isdigit(*p) || *p == '-') p++;
			} else if (*p && *p >= 'A' && *p <= 'Z') {
				tinybc_set(ct, n1ind,
					tinybc_get(ct, *p - 'A'));
				while (isdigit(*p) || *p == '-') p++;
			}
			t_take(ct->t, TOKEN_VARIABLE);
		} else if (t_type(ct->t) == TOKEN_COMMA) {
			t_take(ct->t, TOKEN_COMMA);
		} else
			break;
	interactive(1);
	refresh();
	t_take(ct->t, TOKEN_LF);
}

static void let_stmt(struct cttype *ct)
{
	long int n1ind;

	n1ind = t_variable(ct->t);
	t_take(ct->t, TOKEN_VARIABLE);
	PDEBUG(lg, "let:\n");
	t_take(ct->t, TOKEN_EQ);
	tinybc_set(ct, n1ind, expr(ct));
	t_take(ct->t, TOKEN_LF);
}

static void locate_stmt(struct cttype *ct)
{
	long int n1, n2;

	t_take(ct->t, TOKEN_LOCATE);
	PDEBUG(lg, "locate:\n");
	if (t_expr_type(ct->t))
		n1 = expr(ct);
	else
		t_take(ct->t, TOKEN_VARIABLE);
	t_take(ct->t, TOKEN_COMMA);
	if (t_expr_type(ct->t)) {
		n2 = expr(ct);
		move(n1, n2);
	} else
		t_take(ct->t, TOKEN_VARIABLE);
	t_take(ct->t, TOKEN_LF);
}

static void nap_stmt(struct cttype *ct)
{
	long int n1;

	t_take(ct->t, TOKEN_NAP);
	PDEBUG(lg, "nap:\n");
	if (t_expr_type(ct->t)) {
		n1 = expr(ct);
		napms(n1);
	} else
		t_take(ct->t, TOKEN_VARIABLE);
	t_take(ct->t, TOKEN_LF);
}

static void print_stmt(struct cttype *ct)
{
	char string[MAX_STRLEN];
	int last;

	t_take(ct->t, TOKEN_PRINT);
	PDEBUG(lg, "print:\n");
	last = 0;
	for (; ;)
		if (t_type(ct->t) == TOKEN_STRING) {
			t_string(ct->t, string, MAX_STRLEN);
			printw("%s", string);
			last = TOKEN_STRING;
			t_take(ct->t, TOKEN_STRING);
		} else if (t_type(ct->t) == TOKEN_COMMA) {
			printw(" ");
			last = TOKEN_COMMA;
			t_take(ct->t, TOKEN_COMMA);
		} else if (t_type(ct->t) == TOKEN_SEMICOLON) {
			last = TOKEN_SEMICOLON;
			t_take(ct->t, TOKEN_SEMICOLON);
		} else if (t_expr_type(ct->t)) {
			last = TOKEN_NUMBER;
			printw("%d", expr(ct));
		} else
			break;
	if (last != TOKEN_COMMA && last != TOKEN_SEMICOLON) {
		scrollok(stdscr, TRUE);
		printw("\n");
		scrollok(stdscr, FALSE);
	}
	refresh();
	t_take(ct->t, TOKEN_LF);
}

static void rem_stmt(struct cttype *ct)
{
	t_take(ct->t, TOKEN_REM);
	PDEBUG(lg, "rem:\n");
	t_take(ct->t, TOKEN_LF);
}

static void return_stmt(struct cttype *ct)
{
	long int linenum;

	t_take(ct->t, TOKEN_RETURN);
	PDEBUG(lg, "return:\n");
	t_take(ct->t, TOKEN_LF);
	if (ct->gosub_stack_ptr > 0)
		linenum = ct->gosub_stack[--(ct->gosub_stack_ptr)];
	else {
		linenum = 0;
		printw("Gosub stack empty, line %d\n",
			t_currline(ct->t));
		t_end(ct->t);
		return;
	}
	t_jump(ct->t, linenum);
}

/* Functions of the new statements must be added here */
static void stmt(struct cttype *ct)
{
	switch (t_type(ct->t)) {
	case TOKEN_AT:
		at_stmt(ct);
		break;
	case TOKEN_CLS:
		cls_stmt(ct);
		break;
	case TOKEN_COLOR:
		color_stmt(ct);
		break;
	case TOKEN_END:
		end_stmt(ct);
		break;
	case TOKEN_GOSUB:
		gosub_stmt(ct);
		break;
	case TOKEN_GOTO:
		goto_stmt(ct);
		break;
	case TOKEN_IF:
		if_stmt(ct);
		break;
	case TOKEN_INCHAR:
		inchar_stmt(ct);
		break;
	case TOKEN_INKEY:
		inkey_stmt(ct);
		break;
	case TOKEN_INPUT:
		input_stmt(ct);
		break;
	case TOKEN_VARIABLE:
		let_stmt(ct);
		break;
	case TOKEN_LOCATE:
		locate_stmt(ct);
		break;
	case TOKEN_NAP:
		nap_stmt(ct);
		break;
	case TOKEN_PRINT:
		print_stmt(ct);
		break;
	case TOKEN_REM:
		rem_stmt(ct);
		break;
	case TOKEN_RETURN:
		return_stmt(ct);
		break;
	case TOKEN_LF:
		t_take(ct->t, TOKEN_LF);
		break;
	default:
		printw("Statement not implemented, line %d\n",
			t_currline(ct->t));
		t_end(ct->t);
	}
}

void tinybc_close(struct cttype *ct)
{
	free(ct->t);

	clear();
	refresh();
	delwin(stdscr);
	endwin();
}

int tinybc_ended(struct cttype *ct)
{
	if (t_ended(ct->t)) {
		PDEBUG(lg, "tinybc ended\n");

		while (wgetch(stdscr) < 0) napms(100);
		attrset(COLOR_PAIR(0));
		bkgd(COLOR_PAIR(0));
		clear();
		refresh();
		interactive(0);
	}
	return t_ended(ct->t);
}

long int tinybc_get(struct cttype *ct, int varind)
{
	long int *data;

	data = t_data(ct->t);
	if (varind >= 0 && (varind + 1) * 4 < t_size(ct->t))
		return data[varind];
	return 0;
}

void tinybc_init(struct cttype *ct, char *program, long int *numbers)
{
	struct ttype *t;
	void *p;

	/* Make sure that your malloc is thread-safe */
	t = (struct ttype *) malloc(sizeof(struct ttype));
	ct->t = t;
	t_init(ct->t, program, numbers);
	srand(time(0));

	initscr();
	start_color();
	intrflush(stdscr, FALSE);
	interactive(0);
}

void tinybc_set(struct cttype *ct, long int varind, long int value)
{
	long int *data;

	data = t_data(ct->t);
	if (varind >= 0 && (varind + 1) * 4 < t_size(ct->t)) {
		data[varind] = value;
		PDEBUG(lg, "set: assign value %d to data element "
			"number %d\n", value, varind);
	}
}

void tinybc_start(struct cttype *ct)
{
	clear();
	refresh();

	interactive(1);
	t_start(ct->t);
	if (t_size(ct->t) < MAX_VARIND * 4) {
		printw("Not enough memory for data\n");
		t_end(ct->t);
	}
}

void tinybc_statement(struct cttype *ct)
{
	if (t_ended(ct->t)) return;
	PDEBUG(lg, "\n---------------- Line %d ----------------\n",
		t_number(ct->t));
	if (t_type(ct->t) != TOKEN_NUMBER) {
		t_end(ct->t);
		PDEBUG(lg, "Ended, line with no number\n");
		return;
	}
	t_currline_set(ct->t, t_number(ct->t));
	if (t_toolong(ct->t)) {
		printw("Ended, too long line, line %d\n",
			t_currline(ct->t));
		t_end(ct->t);
		return;
	}
	/* Line numbers are compulsory */
	t_take(ct->t, TOKEN_NUMBER);
	if (t_type(ct->t) == TOKEN_LET) t_take(ct->t, TOKEN_LET);
	stmt(ct);
	return;
}

