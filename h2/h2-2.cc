/*
 * Tom Maltese
 * MTH 4300 - Prof. Matic. HW 2 problem 2
 */
#include <stdio.h>
#include <iostream>

int main()
{
	int m, a, b, c;
	std::cin >> m >> a >> b >> c;

	int i, tmp;
	for (i = 1; i < m && (tmp = ((a * i + b) % m)) != c; i++)
		;
	if (tmp == c)
		printf("%d\n", i);
	else
		printf("There is no such x\n");
}
