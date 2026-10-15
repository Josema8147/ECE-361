#ifndef STATS_H
#define STATS_H

/*
 * Return the minimum element of array a.
 * Assumes a points to an array contatining at least n elements, and n >= 1. 
 */
float stats_min(const float a[], int n);

/*
 * Return the maximum element of array a using recursion.
 * Assumes a points to an array containing at least n elements, and n >= 1. 
 */
float stats_max(const float a[], int n);

/*
 * Return the maximum element using tail recursion.
 * Assumes a points to an array containing at least n elements,
 * and n >= 1.
 */
float stats_max_tail(const float a[], int n);

/*
 * Return the arithmetic mean of array a
 * Assumes a points to an array containing at least n elements, and n >= 1.
 */
float stats_mean(const float a[], int n);

/*
 * Find the longest consecutive run where a[i] > threshold.
 * Stores the starting array index in start_index, or -1 if no run exists.
 * Returns the length of the longest run, or 0 if no run exists.
 * Assumes a contains at least n elements, and n >= 0, and start_index points to a valid int.
 */
int stats_longest_run(const float a[], int n, float threshold, int *start_index);

#endif