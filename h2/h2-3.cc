/*
 * Tom Maltese
 * MTH 4300 - HW 2, problem 3
 */
#include <stdio.h>
#include <iostream>

int main()
{
	int prev, cur, anchor;
	std::cin >> cur;
	anchor = prev = cur;
	int c = 0;
	while (cur != -1) {
		std::cin >> cur;
		if (cur != -1) {
			c++;
			if (cur != prev) {
				if (c % 2 == 0) {
					anchor = prev = cur;
					c = 1;
				} else {
					anchor = prev ^ cur;
					prev = anchor;
					c = 1;
				}
			}
		}
	}
	while (c--) {
		printf("%d ", anchor);
	}
	putchar('\n');
	return 0;
}
