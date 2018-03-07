/*
 * Tom Maltese
 * Homework 5, Problem 3
 * Merge Sort, without recursion
 */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE(x) (sizeof x / sizeof x[0])
#define MIN(x,y) ((x) < (y)) ? (x) : (y)

void die(char const *fmt, ...);
void show(int *a, int size, char const *msg, ...);
void mergelast3(int *a, int size);
void merge_sort(int *a, int size);
int  isSorted(int *a, int size);   /* for debugging/testing only */

void die(char const *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
	exit(1);
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
/*
 * special case for when size is odd, and chunksize = 1 (first iteration)
 */
void mergelast3(int *a, int size)
{
	int begin, end;
	end = size - 1;
	begin = size - 3;
	for (int i = end; i > begin; i--) {
		for (int j = i - 1; j >= begin && a[j] > a[i]; j--) {
			int tmp = a[j];
			a[j] = a[i];
			a[i] = tmp;
		}
	}
}
/*
 * Begin with a `chunksize` = 1, which will be merged with the
 * adjacent chunk into a new chunk of size `chunksize` + 1 = 2.
 * We double the chunk size as we go.
 * We remember the index `last_chunk` pointing to the
 * *BEGINNING OF THE LAST CHUNK*, so that when we iterate over pairs
 * of chunks and the `last_chunk` is the SECOND
 * in the pair, we 'collapse' it in to make a new chunk of
 * unspecified size, storing this as the new 'last_chunk'
 * This handles the case where there is an odd number of chunks.
 */
void merge_sort(int *a, int size)
{
	if (size == 1)
		return;
	int *buf = (int *) malloc(size * sizeof *buf);
	int last_chunk = size;
	for (int chunksize = 1; last_chunk != 0; chunksize *= 2) {
		if (chunksize == 1 && ((size % 2) != 0)) {
			mergelast3(a, size);
			last_chunk = size - 3;
			for (int i = last_chunk; i < size; i++)
				buf[i] = a[i];
		}
		for (int c = 0; c < last_chunk; c += chunksize * 2) {
			int i, j, k, L_END, R_END;
			i = k = c;
			j = i + chunksize;
			L_END = MIN(j, size);
			R_END = MIN(j + chunksize, size);
			if (j == last_chunk) {
				last_chunk = i;
				R_END = size;
			}
			while (i < L_END) {
				while (j < R_END && a[j] <= a[i])
					buf[k++] = a[j++];
				buf[k++] = a[i++];
			}
			while (j < R_END)
				buf[k++] = a[j++];
		}
		for (int c = 0; c < size; c++)
			a[c] = buf[c];
		for (int c = 0; c < last_chunk; c++)
			buf[c] = 0;
	}
	free(buf);
}
int isSorted(int *a, int size)
{
	for (int i = 1; i < size; i++)
		if (a[i - 1] > a[i])
			return 0;
	return 1;
}
int main()
{
	int A[] = {6, 5, 3, 10, 1, 8, 7, 2, 4, 9};
	int B[] = {6, 5, 3};
	int C[] = {3, 5, 6, 1, 10};
	int D[] = {88, 99, 6, 5, 3, 10, 1, 8, 7, 2, 4, 9, 11};
	int F[] = {101, 100};
	int E[] = {1};
	int G[] = {10, 112, 37, 1, 9, 0, -1, -9, 1, 23, 11, 111, 23, 31, 519,
                   75, 590, 10, 100, 10000, -356, 78, 87, 64, 44, 31, 312, 555};
	int sizes[] = {
		ARRAY_SIZE(A),
		ARRAY_SIZE(B),
		ARRAY_SIZE(C),
		ARRAY_SIZE(D),
		ARRAY_SIZE(E),
		ARRAY_SIZE(F),
		ARRAY_SIZE(G),
	};
	int *arrays[] = {
		A, B, C, D, E, F, G
	};
	int n = ARRAY_SIZE(arrays);
	for (int i = 0; i < n; i++) {
		int *a = arrays[i];
		int size = sizes[i];
		show(a, size, "Input  : ");
		merge_sort(a, size);
		show(a, size, "Output : ");
		if (!isSorted(a, size))
			die("Fatal: array is not sorted\n");
	}
}
