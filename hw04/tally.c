#include "tally.h"

#include <string.h>

/*One entry stores a name and its occurrence count. */
struct entry {
    char name[TALLY_LEN + 1]; /* +1 for the null terminator */
    int count;
};

/* Private definition of the opaque tally type. */
struct tally {
    struct entry entries[TALLY_NAMES];
    int size; /* number of distinct names in the tally */
    int in_use; /* flag to indicate if this tally is currently in use */
};

/* All tallies are stored here; no dynamic allocation is needed.*/
static tally_t tallies[TALLY_MAX];

/*
 *Creates an empty tally using an available slot in the static array.
 */
tally_t *tally_create(void) 
{
    int i;

    for (i = 0; i < TALLY_MAX; i++) 
    {
        if (!tallies[i].in_use) 
        {
            tallies[i].in_use = 1;
            tallies[i].size = 0;
            return &tallies[i];
        }
    }
    return NULL; /* No available tally slots */
}

/*
 *Releases a tally slot so it can be used again.
 */
void tally_destroy(tally_t *t)
{
    if (t == NULL) 
    {
        return; /* Do nothing if t is NULL */
    }
    t->size = 0;
    t->in_use = 0;
}

/*
 * Adds one occurence of name.
 * Keeps entries sorted alphabetically.
 */
int tally_add(tally_t *t, const char *name) 
{
   int len = 0;
   int pos;
   int i;

   /* Validate the tally and name pointer. */
   if (t == NULL || name == NULL) 
   {
       return -1; /* Invalid input */
   }

   /* Check the length before copying anything. */
    while (name[len] != '\0' && len <= TALLY_LEN) 
    {
         len++;
    }

    if (len == 0 || len > TALLY_LEN) 
         {
              return -1; /* Name too long */
         }
    
    /* Find the alphabetical insertion position */
    pos = 0;
    while (pos < t->size && strcmp(t->entries[pos].name, name) < 0) 
    {
        pos++;
    }

    /* If the name already exists, increment its count */
    if (pos < t->size && strcmp(t->entries[pos].name, name) == 0) 
    {
        t->entries[pos].count++;
        return t->entries[pos].count;
    }

    /* A new name cannot be added if all slots are occupied. */
    if (t->size == TALLY_NAMES) 
    {
        return -1; /* No space to add a new name */
    }

    /* Shift later entries right to make room. */
    for (i = t->size; i > pos; i--) 
        {
            t->entries[i] = t->entries[i - 1];
        }

    /* Copy the validated name, including its terminating '\0'. */
    for (i = 0; i <= len; i++) 
    {
        t->entries[pos].name[i] = name[i];
    }

    t->entries[pos].count = 1; /* Initialize count for the new name */
    t->size++; /* Increase the size of the tally */

    return 1; /* Return the count for the newly added name */
}

/*
 * Returns how often a name has been added.
 */
int tally_count(const tally_t *t, const char *name) 
{
    int i;

    /* Validate the tally and name pointer. */
    if (t == NULL || name == NULL) 
    {
        return 0; /* Invalid input */
    }

    /* Search for the name in the tally. */
    for (i = 0; i < t->size; i++) 
    {
        if (strcmp(t->entries[i].name, name) == 0) 
        {
            return t->entries[i].count;
        }
    }

    return 0; /* Name not found */
}

/*
 * Returns the number of distinct names in the tally.
 */
int tally_size(const tally_t *t) 
{
    if (t == NULL) 
    {
        return 0; /* Invalid input */
    }

    return t->size; /* Return the number of entries in the tally */
}

/*
 *Prints each name and count, in alphabetical order.
 */
void tally_print(const tally_t *t, FILE *out) 
{
    int i;

    if (t == NULL || out == NULL) 
    {
        return; /* Invalid input */
    }

    for (i = 0; i < t->size; i++) 
    {
        fprintf(out, "%s %d\n", t->entries[i].name, t->entries[i].count);
    }
}