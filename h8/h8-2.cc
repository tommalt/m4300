/*
 * Tom Maltese
 * MTH 4300
 * Homework 8
 * Problem 2
 */

/*
 Description
Use the function readSequenceFromFile that you created in homework 2 to read the sequence xx of non-negative integers from the file hw6_input.txt. (You should have downloaded the file while solving the previous problem.) The sequence xx is written to the file according to the convention we created in homework 2.

Read the numbers kk and mm from the standard input. Each of the elements of the sequence x[0]x[0], x[1]x[1], ……, x[n−1]x[n−1] corresponds to one of the citizens in a country. The number nn is read from the file as explained in the homework 22. The citizens live in a circle. Hence, the first left neighbor of the citizen 00 is n−1n−1; the second from the left neighbor is n−2n−2. The first from the right neighbor of the citizen 00 is the citizen 11, and the second from the right is the citizen 22.

The number x[i]x[i] is a politician for whom the citizen ii is planning to vote in the upcoming election. As you can see from the file, the politicians are represented by the numbers from the set {0,1,2,3,…,9}{0,1,2,3,…,9}.

The citizens are talking about the politicians and they often change their opinions on how to vote. During each of the next mm days, each citizen looks at kk of his(/her) nearest neighbors that are located to the left and kk of the nearest neighbors that are located to the right. Then during the night, each citizen decides to change the favorite politician to the one that the majority of his/her neighbors preferred the day before (if there is a tie, a politician with the smaller id is chosen). This crazy behavior continues for mm days and nights.

Find out who is going to vote for whom after mm days and mm nights. Create two functions: a non-parallel version, and a parallel one using openmp and compare their performance.

Remark: Be careful when designing the algorithms: When changing the opinion of the candidate 88, you will look at the neighbor 77. However you have to keep in mind that you need to consider the value x[7]x[7] that was during the day, which could be tricky if you already changed x[7]x[7].
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
int main()
{
	int k, m;
	std::cout << "Enter K and M: ";
	std::cin >> k >> m;

	int *seq;
	int size;
	seq = NULL;
	size = 0;
	readSequenceFromFile("hw6_input.txt", &seq, &size);
}
