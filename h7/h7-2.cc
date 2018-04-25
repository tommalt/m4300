/*
 * Tom Maltese
 * MTH 4300
 * Homework #7
 * Problem 2
 */
#include <stdio.h>
#include <set>
#include <iostream>

int insert_if_prime(std::set<int> *primes, int n)
{
	std::set<int>::iterator it;
	int biggest;

	biggest = (*primes->rbegin()) + 2;
	for ( ; biggest <= n; biggest += 2) {
		int _is_prime = 1;
		for (it = primes->begin(); it != primes->end() &&
				(*it) * (*it) <= biggest && _is_prime; it++)
			if (biggest % *it == 0)
				_is_prime = 0;
		if (_is_prime)
			primes->insert(biggest);
	}
	return (primes->find(n) != primes->end()) ? 1 : 0;
}
int isprime(int n)
{
	static std::set<int> primes = {2, 3, 5, 7, 11};
	if (primes.find(n) != primes.end())
		return 1;
	if (n % 2 == 0)
		return 0;
	int biggest = *primes.rbegin();
	if (n > biggest)
		return insert_if_prime(&primes, n);
	return 0;
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
		if (!isprime(p) || !isprime(q))
			continue;
		p2 = p * p;
		q2 = q * q;
		int c = p2 + q2 + a;
		if (isprime(c)) {
			printf("(%d,%d) is an alpha couple\n", p, q);
		}
	} while (1);
}

