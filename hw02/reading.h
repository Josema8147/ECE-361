#ifndef READING_H
#define READING_H

/*
 *Read sensor readings from stdin into caller-provided arrays.
 *
 * Parameters:
 *   ticks        - destination array for tick values
 *   temps        - destination array for temperatures
 *   hums         - destination array for humidity values
 *   capacity     - maximum number of readings the arrays can hold
 *   skipped      - output pointer for the number of invalied lines
 * 
 *  Returns:
 *    Number of valid readings storesd, from 0 to capacity.
 *
 *  Assumes:
 *    All arrays have space for at least capacity elements,
 *    capacity >= 1, and skipped is not NULL. 
 *
 */
int reading_read(int ticks[], float temps[], float hums[],
                 int capacity, int *skipped);

#endif