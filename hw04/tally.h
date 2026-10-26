#ifndef TALLY_H
#define TALLY_H

#include <stdio.h>

#define TALLY_MAX 4 /* talies that can exist at the same time */
#define TALLY_NAMES 16 /* different names one tally can hold */
#define TALLY_LEN 15 /* longest name, wihtout the '\0' */

/* Opaque type: the structure is defined privately in tally.c */
typedef struct tally tally_t;

/*
 * Takes: no arguments.
 * Returns: a pointer to a new, empty tally, or NULL if all
 *          TALLY_MAX tallies are already in use.
 * Assumes: none.
 */
tally_t *tally_create(void);

/*
 * Takes : no arguments.
 * Returns: a pointer to a new, empty tally, or NULL if all TALLY_MAX tallies are already in use.
 * Assumes: none.
 */
void tally_destroy(tally_t *t);

/*
 * Takes : a tally pointer t and a name string.
 * Returns: the new count for name, or -1 if the input is invalid or a new cannot fit in the tally.
 * Assumes: name is a valid, null-terminated string if non-NULL.
 */
int tally_add(tally_t *t, const char *name);

/*
 * Takes: a tally pointer t and a name string.
 * Returns: the number of times name was added, 0 if never added, or 0 if t or name is NULL.
 * Assumes: name is a valid, null-terminated string if non-NULL.
 */
int tally_count(const tally_t *t, const char *name);

/*
 * Takes: a tally pointer t 
 * Returns: the number of distinct names in t, or 0 if t is NULL.
 * Assumes: t is either NULL or a valid tally pointer.
 */
int tally_size(const tally_t *t);

/*
 * Takes: a tally pointer t and an output stream out.
 * Returns: nothing.
 * Assumes: t and out are valid pointers. Prints each name and its count on one line, in alphebetical order.
 */
void tally_print(const tally_t *t, FILE *out);

#endif /* TALLY_H */