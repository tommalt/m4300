#include <math.h>
#include <stdlib.h>
#include <string.h>   /* strlen */

#include <iostream>
#include <sstream>
#include <fstream>

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
	int *seq = NULL;
	int n = 0;
	readSequenceFromFile("dataForHW2.txt", &seq, &n);
	if (!n)
		return 1;
	std::ofstream out("hw2Output.txt");
	if (!out.is_open())
		return 1;
	// we could create a new sequence, and use printSep, but
	//  that is just so wasteful:
	int y = seq[0];
	out << y;
	for (int i = 1; i < n; i++) {
		y += seq[i];
		out << ',' << y;
	}
	out << '\n';
	free(seq);
}
