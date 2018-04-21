/*
 * Tom Maltese
 * MTH 4300
 * Homework #7
 * Problem 2
 */
#include <stdio.h>

#include <iostream>
#include <vector>

int isprime(int n)
{
	if (n <= 1)
		return 0;
	else if (n <= 3)
		return 1;
	else if ((n % 2) == 0 || (n % 3) == 0)
		return 0;
	int i;
	i = 5;
	while (i * i <= n) {
		if ((n % i) == 0 || (n % (i + 2)) == 0)
			return 0;
		i += 6;
	}
	return 1;
}
int main()
{
	int a, p, q;
	int p2, q2;

	std::cout << "Enter alpha: ";
	std::cin >> a;
	std::cout << "Enter pairs if (p, q), type 0 to quit\n";
	p = q = -1;
	do {
		std::cin >> p;
		if (p <= 0)
			break;
		std::cin >> q;
		if (q <= 0)
			break;
		p2 = p * p;
		q2 = q * q;
		int c = p2 + q2 + a;
		if (isprime(c)) {
			printf("(%d,%d) is an alpha couple\n", p, q);
		}
	} while (1);
}
