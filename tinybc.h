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

#ifndef __TINYBC_H__
#define __TINYBC_H__

#define MAX_COLOR 8 /* Added */
#define MAX_FOR_DEPTH 100
#define MAX_GOSUB_DEPTH 100
#define MAX_VARIND 26

struct cttype {
	int colorpairs[MAX_COLOR][MAX_COLOR]; /* Added */
	int currentcolor[3]; /* Added */
	int gosub_stack[MAX_GOSUB_DEPTH];
	int gosub_stack_ptr;
	int lastpair; /* Added */
	long int variables[MAX_VARIND];
	struct ttype *t;
};

void tinybc_init(struct cttype *ct, char *program, int *numbers);
int tinybc_ended(struct cttype *ct);
int tinybc_get(struct cttype *ct, int varind);
void tinibc_close(struct cttype *ct);
void interactive(int mode);
void tinybc_set(struct cttype *ct, int varind, int value);
void tinybc_start(struct cttype *ct);
void tinybc_statement(struct cttype *ct);

#endif /* __TINYBC_H__ */

