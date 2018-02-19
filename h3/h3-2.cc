/*
 * Tom Maltese
 * MTH4300 - Prof. Matic. HW 3 problem 2
 */
#include <stdio.h>
#include <math.h>
int combosFrom(int top, int target, int power)
{
	if (top <= 0)
		return 0;
	int need = target - pow(top, power);
	if (need == 0)
		return 1;
	else if (need < 0)
		return 0;
	int combos = 0;
	for (top--; top; top--) {
		combos += combosFrom(top, need, power);
	}
	return combos;
}
int combinations(int target, int power)
{
	int top = trunc(pow(target, 1.0 / (double)power));
	int total = 0;
	while (top) {
		total += combosFrom(top, target, power);
		top--;
	}
	return total;
}
int main()
{
	int target, power;
	printf("Give me two numbers: ");
	if (scanf("%d", &target) != 1 || scanf("%d", &power) != 1) {
		fprintf(stderr, "Invalid input\n");
		return 1;
	}
	printf("%d\n", combinations(target, power));
}
