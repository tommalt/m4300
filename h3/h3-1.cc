/*
 * Tom Maltese
 * MTH4300 - Prof. Matic. HW 3 problem 1
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	char buf[64];
	fgets(buf, sizeof buf, stdin);
	int len = (int) strlen(buf);
	buf[len-1] = '\0';
	int num = atoi(buf);
	int total = 0;
	int i;
	for (i = 1; i <= num; i++) {
		total += d(i);
	}
	printf("%d\n", total);
}
