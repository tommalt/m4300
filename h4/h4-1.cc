#include <stdio.h>
#include <stdlib.h>

void show(int *x, int n, char const *msg);
void __memmove_reverse(void *dest, void const *src, int n);
void __memmove_forward(void *dest, void const *src, int n);
void __memmove(void *dest, void const *src, int n);
void f(int **x, int *n);

void show(int *x, int n, char const *msg)
{
	if (msg)
		printf("%s", msg);
	for (int i = 0; i < n; i++)
		printf("%d ", x[i]);
	putchar('\n');
}
void __memmove_reverse(void *dest, void const *src, int n)
{
	char const *s = (char const*) src;
	char       *d = (char *) dest;
	s += (n - 1);
	d += (n - 1);
	for (int i = 0; i < n; i++)
		*d-- = *s--;
}
void __memmove_forward(void *dest, void const *src, int n)
{
	char const *s = (char const*) src;
	char       *d = (char*) dest;
	for (int i = 0; i < n; i++)
		*d++ = *s++;
}
void __memmove(void *dest, void const *src, int n)
{
	if (dest > src)
		__memmove_reverse(dest, src, n);
	else
		__memmove_forward(dest, src, n);
}
void f(int **x, int *n)
{
	int i, size, newsize;
	size = newsize = *n;
	for (i = 0; i < size; i++) {
		if ((*x)[i] == 5)
			newsize--;
		else if ((*x)[i] == 0)
			newsize += 2;
	}
	int *d, *s;
	for (d = s = *x; s < *x + size; d += (*d != 5) ? 1 : 0)
		*d = *s++;
	size = d - *x;
	*x   = (int*) realloc(*x , newsize * sizeof **x);
	*n   = newsize;
	int *end = *x + size;
	d = end - 1;
	for ( ; d >= *x; d--) {
		if (*d == 0) {
			__memmove(d + 3, d + 1, (end - (d + 1)) * sizeof **x);
			for (int i = 0; i < 3; i++)
				d[i] = 1;
			end += 2;
		}
	}
}
int main()
{
	int *x = (int *) malloc(0x10000 * sizeof *x);
	int n = 0;
	int tmp;
	printf("Enter some numbers.\nEnter -1 to stop: ");
	while (scanf("%d", &tmp) == 1) {
		if (tmp == -1)
			break;
		x[n++] = tmp;
	}
	if (!n)
		return 1;
	show(x, n, "input: ");
	f(&x, &n);
	show(x, n, "output: ");
	free(x);
}
