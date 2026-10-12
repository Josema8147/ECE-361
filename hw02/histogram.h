#ifndef HISTOGRAM_H
#define HISTOGRAM_H

/*
 * Print a histogram of temperatures using 5-degree bins from 0 to 100C.
 * Values below 0 go in the the first bin; values at or above 100 go in the last bin.
 * Assumes temps points to an array containing at least n elements, and n >= 0.
 */
void histogram_print(const float temps[], int n);

#endif