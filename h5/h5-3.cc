/*
 * Tom Maltese
 * Homework 5, Problem 3
 * Merge Sort, without recursion
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define ARRAY_SIZE(x) (sizeof x / sizeof x[0])
#define MIN(x,y) ((x) < (y)) ? (x) : (y)

void show(int *a, int size, char const *msg, ...);

void merge_sort(int *a, int size)
{
	int *buf = (int *) malloc(size * sizeof *buf);
	int maxchunk = (size % 2 == 0) ? size / 2 : (size + 1) / 2;
	for (int chunksize = 1; chunksize <= maxchunk; chunksize = chunksize * 2) {
		memset(buf, 0, size * sizeof *buf);
		printf("[chunksize = %d]\n", chunksize);
		for (int chunk = 0; chunk < size; chunk += chunksize * 2) {
			int i, j, k;
			int L_END, R_END;
			i = k = chunk;
			j = i + chunksize;
			//L_END = MIN(i + chunksize, size);
			//R_END = MIN(j + chunksize, size);
			L_END = i + chunksize;
			R_END = j + chunksize;
			while (i < L_END && i < size) {
				while (j < R_END && j < size && a[j] <= a[i]) {
					printf("writing %d to buf[%d]\n", a[j], k);
					buf[k++] = a[j++];
				}
				printf("writing %d to buf[%d]\n", a[i], k);
				buf[k++] = a[i++];
			}
			while (j < R_END && j < size) {
				printf("writing %d to buf[%d]\n", a[j], k);
				buf[k++] = a[j++];
			}
		}
		for (int c = 0; c < size; c++) {
			a[c] = buf[c];
		}
		printf("[/chunksize = %d]\n", chunksize);
		//show(a, size, "after chunksize = %d: ", chunksize);
		//printf("OK.\n");
	}
	free(buf);
}

void show(int *a, int size, char const *msg, ...)
{
	if (msg) {
		va_list args;
		va_start(args, msg);
		vprintf(msg, args);
		va_end(args);
	}
	for (int i = 0; i < size; i++)
		printf(" %d", a[i]);
	putchar('\n');
}
int main()
{
	int A[] = {6, 5, 3, 10, 1, 8, 7, 2, 4, 9};
	//int A[] = {6, 5, 3};
	int size = ARRAY_SIZE(A);
	show(A, size, "Before: ");
	merge_sort(A, size);
	show(A, size, "After : ");
}
