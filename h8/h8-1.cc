/*
 * Tom Maltese
 * MTH 4300
 * Homework 8
 * Problem 1
 */
#include <math.h>
#include <stdlib.h>
#include <string.h>   /* strlen */

#include <iostream>
#include <sstream>
#include <fstream>

#include <omp.h>

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
int serial(int *seq, int size)
{
	int count[10];
	memset(count, 0, sizeof count);
	for (int i = 0; i < size; i++) {
		count[seq[i]]++;
	}
	int maxix = 0;
	int max = count[0];
	for (int i = 0; i < 10; i++) {
		maxix = (count[i] > max) ? i : maxix;
		max = count[maxix];
	}
	return maxix;
}
/*
 * Create 'n' arrays of counts where n == number of threads
 * each thread writes to its own buffer
 * after all threads join, sum up the cummulative frequencies
 * to find the max.
 */
int parallel(int *seq, int size)
{
	int n;
#pragma omp parallel
	{
		if (omp_get_thread_num() == 0)
			n = omp_get_num_threads();
	}
#pragma omp barrier

	int count[n][10];
	for (int i = 0; i < n; i++)
		memset(count[i], 0, sizeof count[i]);

#pragma omp parallel num_threads(n)
	{
		int id = omp_get_thread_num();
		for (int i = 0; i < size; i += n) {
			int ix = i + id;
			count[id][seq[ix]]++;
		}
	}
#pragma omp barrier
	int net[10];
	memset(net, 0, sizeof net);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 10; j++) {
			net[j] += count[i][j];
		}
	}
	int max, maxix;
	max = net[0];
	maxix = 0;
	for (int i = 0; i < 10; i++) {
		maxix = (net[i] > max) ? i : maxix;
		max = net[maxix];
	}
	return maxix;
}
int main()
{
	int *seq;
	int size;

	seq  = NULL;
	size = 0;
	readSequenceFromFile("hw6_input.txt", &seq, &size);
	printf("size: %d\n", size);

	int s = serial(seq, size);
	int p = parallel(seq, size);

	printf("serial, parallel: %d %d\n", s, p);
	free(seq);
}
