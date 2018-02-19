/*
 * Tom Maltese
 * MTH4300 - Prof. Matic. HW 3 problem 2
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int N;        /* user inputs */
int P;
int maxanchor;

/* for rfind_if */
int lesseq(int a, int b)
{
	if (a <= b)
		return 1;
	return 0;
}
int greatereq(int a, int b)
{
	if (a >= b)
		return 1;
	return 0;
}
/*
 * reverse search an array to find something as specified by pred(thing)
 * end is ONE PAST LAST, in typical C++ fashion.
 */
int *rfind_if(int key, int *begin, int *end, int (*pred)(int, int))
{
	for ( ; begin <= end; end--)
		if (pred(*end, key))
			return end;
	return NULL;
}
void descend_impl(int pivot, int *total, int sum, int need, int *complement, int *power)
{
	/* iterate over the viable children of this pivot */
	int *lastchild = rfind_if(need, power + 1, power + pivot, &lesseq);
	if (lastchild == NULL)
		return;
	int nchild = lastchild - power;
	int child[nchild+1];
	memcpy(child+1, power+1, nchild * sizeof *power);
	int c;
	for (c = nchild; c > 0; c--) {
		if (child[c] == need) {
			(*total)++;
		} else if (child[c] < need) {
			int newsum = sum + child[c];
			int newneed = need - child[c];
			descend_impl(c, total, newsum, newneed, complement, power);
		}
		/* continue */
	}
}
void descend(int anchor, int *total,/* # of matches found */
             int *complement, int *power)
{
	int sum, need;
	int ipivot, *ppivot;       /* index, power[index] */

	ppivot = rfind_if(complement[anchor], power + 1, power + anchor, &lesseq);
	/* ^find the first number who's power is <= what we need */
	if (ppivot == NULL)
		return;
	sum = power[anchor] + *ppivot;
	ipivot = (int)(ppivot - power);
	need = N - sum;
	if (need == 0) {
		*total = 1;
		return;
	}
	descend_impl(ipivot, total, sum, need, complement, power);
}

int main()
{
	int i;
	N = 200;		/* user inputs */
	P = 2;
	maxanchor = (int) trunc(pow(N, 1.0 / (double)P));  /* the maximum integer that can be used.
                                                                  we walk down from `maxanchor` to 1 */
	int complement[maxanchor+1];            /* how much to add to power[i] to get n */
	int power[maxanchor+1];               /* power[i] = pow(i,p)  */
	int cpower[maxanchor+1];          /* cumulative sum of powers from [0,i] */
	complement[0] = 0;
	power[0]      = 0;
	cpower[0]     = 0;

	for (i = 1; i <= maxanchor; i++) {
		double tmp; 
		tmp = pow(i,P);
		complement[i] = (double)N - tmp;
		power[i] = tmp;
		cpower[i] = cpower[i-1] + tmp;
	}
	for (i = 1; i <= maxanchor; i++) // debug
		printf("%d,%d,%d,%d\n", i, complement[i], power[i], cpower[i]);

	int anchor;
	int count, total;  /* # of combinations, sum for this combo */
	for (anchor = maxanchor; anchor > 0; anchor--) {
		//memset(seen, 0, sizeof seen);
		total = 0;
		descend(anchor, &total, complement, power);
		count += total;
	}
	printf("count: %d\n", count);
}
