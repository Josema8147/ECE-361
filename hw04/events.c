#include <stdio.h>
#include <string.h>

#include "tally.h"

int main (void) 
{
    tally_t *t = tally_create();
    char line[TALLY_LEN + 3]; /* +3 for newline, null terminator, and potential extra character */
    int skipped = 0;

    if (t == NULL) 
    {
        fprintf(stderr, "Error: could not create tally.\n");
        return 1;
    }

    while (fgets(line, sizeof(line), stdin) != NULL) 
    {
        size_t len = strlen(line);

        /* Remove the newline, if present */
        if (len > 0 && line[len - 1] == '\n') 
        {
            line[len - 1] = '\0';
        }

        /* Ignore blank lines and comment lines. */
        if (line[0] == '\0' || line[0] == '#') 
        {
            continue;
        }
       
        /* Count lines refused by tally_add(). */
        if (tally_add(t, line) == -1) 
        {
            skipped++;
        }
    }
    
    tally_print(t, stdout);
    printf("names: %d, lines skipped: %d\n", tally_size(t), skipped);

    tally_destroy(t);
    return 0;
}