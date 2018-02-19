/*
 * Tom Maltese
 * MTH4300 - Prof. Matic. HW 3 problem 1
 */
#include <stdio.h>
int d(int n)
{
	int i;
	int total = 0;
	if (n < 2)
		return 1;
	for (i = 2; i < n; i++)
		if (n % i == 0)
			total++;
	return total + 2;    /* +2 for 1 and n */
}
int main()
{
	int n;
	printf("Give me a number: ");
	if (scanf("%d", &n) != 1) {
		fprintf(stderr,"Invalid input\n");
		return 1;
	}
	int total = 0;
	int i;
	for (i = 1; i <= n; i++) {
		total += d(i);
	}
	printf("%d\n", total);
}
