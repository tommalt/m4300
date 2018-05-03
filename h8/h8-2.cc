/*
 * Tom Maltese
 * MTH 4300
 * Homework 8
 * Problem 2
 */

#include <math.h>
#include <stdlib.h>
#include <string.h>   /* strlen */

#include <iostream>
#include <sstream>
#include <fstream>

#include <omp.h>

#include "timer4300.cpp"

int isnumeric(char c)
{
	return ('0' <= c) && (c <= '9');
}
std::string slurp(std::string fname)
{
	std::ifstream file(fname);
	if (!file.is_open())
		return {};
	std::stringstream ss;
	ss << file.rdbuf();
	return ss.str();
}
int getNextInteger(char const *text, std::streampos size, std::streampos *pos)
{
	char const *endptr;
	std::streampos i;
	std::streampos j;
	text = text + *pos; 
	// strtol
	for (i = *pos; i < size && !isnumeric(*text); i += 1, text++)
		;
	endptr = text;
	for (j = i; j < size && isnumeric(*endptr); j += 1, endptr++)
		;
	--endptr;
	int sum = 0;
	for (int power = 0; endptr >= text; power++, endptr--)
		sum += ((int)(*endptr - 48)) * ((int)pow(10, power));
	if (i > *pos && *(text - 1) == '-')
		sum = -sum;
	*pos += (i - *pos) + (j - i);
	return sum;
}
void readSequenceFromFile(std::string filename, int **sequencePointer, int *length)
{
	std::string content = slurp(filename);
	char const *text = content.c_str();
	int size = (int) content.size();

	std::streampos p = 0;
	int  len = *length = getNextInteger(text, size, &p);
	int *seq = *sequencePointer = (int*) realloc(*sequencePointer, len * sizeof **sequencePointer);

	int i;
	for (i = 0; i < len; i++) {
		int tmp = getNextInteger(text, size, &p);
		if (tmp == -9)
			break;
		seq[i] = tmp; 
	}
	for ( ; i < len; i++)
		seq[i] = 0;
}
void printSep(std::ofstream *f, int *seq, int len, char sep)
{
	int i;
	for (i = 0; i < len - 1; i++)
		*f << seq[i] << sep;
	*f << seq[i] << '\n';
}
void printToFile(std::string filename, int *seq, int len)
{
	std::ofstream file(filename);
	if (!file.is_open())
		return;
	printSep(&file, seq, len, ' ');
}
void serial(int *seq, int size, int K, int m)
{
	int *next;
	int *freq;
	next = (int *) malloc(size * sizeof *next);
	freq = (int *) calloc(10, sizeof *freq);
	do {
		for (int i = 0; i < size; i++) {
			for (int c = 1; c <= K; c++) {
				int k;
				k = i - c;
				k = (k < 0) ? size + k : k;
				freq[seq[k]]++;
				k = i + c;
				k = (k >= size) ? (k - size) : k;
				freq[seq[k]]++;
			}
			int maxix;
			int max;
			maxix = 0;
			max = freq[0];
			for (int k = 1; k < 10; k++) {
				maxix = (freq[k] > max) ? k : maxix;
				max = freq[maxix];
			}
			/* check if there are any tie breakers */
			for (int i = 0; i < 10; i++) {
				if (freq[i] == max) {
					maxix = i;
					break;
				}
			}
			next[i] = maxix;
			memset(freq, 0, 10 * sizeof *freq);
		}
		memcpy(seq, next, size * sizeof *seq);
		/* avoid doing extra work: if all the values are the same, they won't change */
		int cmp = seq[0];
		int i;
		for (i = 1; i < size; i++) {
			if (cmp != seq[i])
				break;
		}
		if (i == size)
			break;
	} while (--m);
	free(freq);
	free(next);
}
int main(int argc, char **argv)
{
	if (argc < 2) {
		printf("Usage: %s [FILE]\n", argv[0]);
		return 1;
	}
	int k, m;
	std::cout << "Enter K and M: ";
	std::cin >> k >> m;
	if (k <= 0) {
		printf("K must be a positive integer\n");
		return 1;
	}
	if (m <= 0) {
		printf("M must be a positive integer\n");
		return 1;
	}

	int *seq;
	int size;
	seq = NULL;
	size = 0;
	readSequenceFromFile(argv[1], &seq, &size);

	serial(seq, size, k, m);

	printf("Voter, Politician");
	for (int i = 0; i < size; i++) {
		printf("%d %d\n", i, seq[i]);
	}
}
