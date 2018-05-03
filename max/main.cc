#include <stdio.h>
int main()
{

	int seq[] = {0, 5, 4, 2, 2, 10, 5, 6, 2, 0, 1};
	int size = sizeof seq / sizeof seq[0];
	int k;
	k = 3;

	int maxix, max, upper;
	maxix = 0;
	max = seq[0];
	upper = k - 1;
	for (int i = 0; i < k; i++) {
		maxix = (seq[i] >= max) ? i : maxix;
		max = seq[maxix];
	}
	printf("%d\n", max);
	for (int i = 1; i <= (size - k); i++) {
		int diff = maxix - i;
		if (diff >= 0) {
			for (int j = upper + 1; j < i + k; j++) {
				if (seq[j] >= max) {
					maxix = j;
					max = seq[maxix];
				}
			}
		} else {
			maxix = i;
			max = seq[i];
			for (int j = i; j < i + k; j++) {
				if (seq[j] >= max) {
					maxix = j;
					max = seq[maxix];
				}
			}
			upper = i + k;
		}
		printf("%d\n", max);
	}
	return 0;
}
