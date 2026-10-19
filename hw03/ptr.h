#ifndef PTR_H
#define PTR_H

/*
 * swap_float
 * Takes pointors to two floats, a and b.
 * Swaps the values stored at those addresses.
 * Assumes a and b point to valid float objects.
 */
void swap_float(float *a, float *b);

/*
 * minmax
 * Takes an array pointer a, its length n, and output pointers min and max.
 * Stores the smallest and largest values in *min and *max.
 * Returns 0 on success, -1 if n < 1 or any pointer is NULL.
 * Assumes a points to at least n readable floats when n >= 1.
 * On failure, leaves *min and *max unchanged.
 */
int minmax(const float *a, int n, float *min, float *max);

/*
 * find_above 
 * Takes an array pointer a, its length n, and a threshold
 * Returns a pointer to the first element greather than threshold, or NULL if no such element exists.
 * Assumes a points to at least n readable floats when n > 0.
 * Returns NULL if a is NULL or n < 1.
 */
const float *find_above(const float *a, int n, float threshold);

/*
 * reverse
 * Takes an array pointer a and its length n.
 * Reverse the array in place.
 * Does nothing if a is NULL or n < 2.
 * Assumes a points to at least n  writable floats when n >= 2.
 */
void reverse(float *a, int n);

#endif 