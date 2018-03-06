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

void show(int *a, int size, char const *msg, ...);

void merge_sort(int *a, int size)
{
	int *buf = (int *) malloc(size * sizeof *buf);
	for (int chunksize = 1; chunksize < 5; chunksize = chunksize * 2) {
		for (int chunk = 0; chunk < size; chunk += chunksize * 2) {
			int i, j, k;
			int L_END, R_END;
			i = k = chunk;
			j = i + chunksize;
			L_END = i + chunksize;
			R_END = j + chunksize;
			while (i < L_END) {
				while (j < R_END && a[j] <= a[i]) {
					buf[k++] = a[j++];
				}
				buf[k++] = a[i++];
			}
			while (j < R_END)
				buf[k++] = a[j++];
			memcpy(a + chunk, buf + chunk, (chunksize * 2) * sizeof *buf);
			//memcpy(a, buf, sizeof a);
			//if (chunksize == 1) {
				//printf("chunk = %d\n", chunk);
				//show(a, size, "A (c = 1): ");
			//}
		}
		show(a, size, "after chunksize = %d: ", chunksize);
	}
	//memcpy(a, buf, sizeof a);
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
	int A[] = {6, 5, 3, 1, 8, 7, 2, 4, 9};
	int size = ARRAY_SIZE(A);
	//show(A, size, "Before: ");
	merge_sort(A, size);
	//show(A, size, "After : ");
}
