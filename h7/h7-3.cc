#include <math.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

static std::set<int> powers;

int impl(int target, std::set<int>::reverse_iterator top, int k)
{
	if (top == powers.rend())
		return -1;
	k++;
	target = target - *top;
	if (target == 0)
		return k;
	if (target < 0)
		return -1;
	std::vector<int> ks;
	for (top++; top != powers.rend(); top++) {
		ks.push_back(impl(target, top, k));
	}
	std::sort(ks.begin(),ks.end());
	auto it = std::upper_bound(ks.begin(),ks.end(), -1);
	return (it == ks.end()) ? -1 : *it;
}
int minK(int n, int a)
{
	int max = floor(pow(n, 1.0 / (double) a));
	printf("Max is %d\n", max);
	while (max)
		powers.insert(pow(max--, a));
	auto top = powers.rbegin();
	std::set<int> ks;
	while (top != powers.rend()) {
		ks.insert(impl(n, top++, 0));
	}
	auto it = ks.upper_bound(-1);
	return (it == ks.end()) ? 0 : *it;
}
int main()
{
	int n, a, k;
	std::cout << "Enter [n, alpha]: ";
	std::cin >> n >> a;
	k = minK(n, a);
	printf("Min K: %d\n", k);
}
