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

#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h> /* Added */

#define MAX_NUMLEN 10
#define MAX_STRLEN FILENAME_MAX
#define ARRSIZE 100000
#ifdef DEBUG
#define PDEBUG(log, ...) fprintf(log, __VA_ARGS__)
#else
#define PDEBUG(log, ...)
#endif

/* Token types of the new statements must be added here */
enum {
	TOKEN_NONE,
	TOKEN_ASTR,
	TOKEN_CLS, /* Added */
	TOKEN_COLOR, /* Added */
	TOKEN_COMMA,
	TOKEN_CR,
	TOKEN_END,
	TOKEN_EQ,
	TOKEN_GE,
	TOKEN_GOSUB,
	TOKEN_GOTO,
	TOKEN_GT,
	TOKEN_IF,
	TOKEN_INCHAR, /* Added */
	TOKEN_INKEY, /* Added */
	TOKEN_INPUT,
	TOKEN_LE,
	TOKEN_LET,
	TOKEN_LOCATE, /* Added */
	TOKEN_LPAREN,
	TOKEN_LT,
	TOKEN_MINUS,
	TOKEN_NAP, /* Added */
	TOKEN_NOTEQ,
	TOKEN_NUMBER,
	TOKEN_PLUS,
	TOKEN_PRINT,
	TOKEN_REM,
	TOKEN_RETURN,
	TOKEN_RND,
	TOKEN_RPAREN,
	TOKEN_SEMICOLON,
	TOKEN_SLASH,
	TOKEN_STRING,
	TOKEN_THEN,
	TOKEN_VARIABLE
};

struct ttype {
	const char *program;
	const char *ptr, *next;
	int currentline;
	int currtype;
	int ended;
	int firstline;
	int *numbers;
};

int t_currline(struct ttype *t);
int t_ended(struct ttype *t);
int t_expr_type(struct ttype *t);
int t_number(struct ttype *t);
int t_toolong(struct ttype *t);
int t_type(struct ttype *t);
int t_variable(struct ttype *t);
void t_currline_set(struct ttype *t, int currline);
void t_end(struct ttype *t);
void t_init(struct ttype *t,  const char *program, int *numbers);
void t_jump(struct ttype *t, int line);
void t_next_line(struct ttype *t);
void t_next(struct ttype *t);
void t_start(struct ttype *t);
void t_string(struct ttype *t, char *dest, int len);
void t_take(struct ttype *t, int expected);

FILE *lg;

#endif /* __TOKENIZER_H__ */

