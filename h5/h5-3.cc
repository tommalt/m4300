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
void mergelast3(int *a, int size);
void merge_sort(int *a, int size);

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
		for (int c = 0; c < size; c++) {
			a[c] = buf[c];
		}
		for (int c = 0; c < last_chunk; c++)
			buf[c] = 0;
	}
	free(buf);
}
int main()
{
	int A[] = {6, 5, 3, 10, 1, 8, 7, 2, 4, 9};
	int B[] = {6, 5, 3};
	int C[] = {3, 5, 6, 1, 10};
	int D[] = {88, 99, 6, 5, 3, 10, 1, 8, 7, 2, 4, 9, 11};
	int F[] = {101, 100};
	int E[] = {1};
	int sizes[] = {
		ARRAY_SIZE(A),
		ARRAY_SIZE(B),
		ARRAY_SIZE(C),
		ARRAY_SIZE(D),
		ARRAY_SIZE(E),
		ARRAY_SIZE(F),
	};
	int *arrays[] = {
		A, B, C, D, E, F
	};
	int n = ARRAY_SIZE(arrays);
	for (int i = 0; i < n; i++) {
		int *a = arrays[i];
		int size = sizes[i];
		show(a, size, "Input  : ");
		merge_sort(a, size);
		show(a, size, "Output : ");
	}
}
