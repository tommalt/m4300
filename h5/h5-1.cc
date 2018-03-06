/*
 * Tom Maltese
 * HW 5, Problem 1
 */
#include <stdio.h>
#include <iostream>
int *N;
int *P;
int *A;
int f(int n)
{
	if (n == 0)
		return *A;
	int n1 = n - 1;
	int fn = f(n1);
	return ((fn * fn) + fn + 1) % *P;
}
int main()
{
	int n, p, a;
	std::cin >> n >> p >> a;
	N = &n;
	P = &p;
	A = &a;
	printf("Input n : %d\n", n);
	printf("f(n)    : %d\n", f(n));
	printf("f(n + 1): %d\n", f(n + 1));
}
