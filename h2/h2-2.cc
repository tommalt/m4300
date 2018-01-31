/*
 * Tom Maltese
 * MTH 4300 - Prof. Matic. HW 2 problem 2
 */
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 256
#define TOKENSIZE 32
#define IFS ' '
/*  split a string */
int explode(char *buf, char ***tokens, int *ntok, char sep)
{
	int c;
	char *bp;
	bp = buf;
	if (strchr(bp,sep) == NULL)
		return 1;
	c = 1;
	while (*bp)
		if (*bp++ == sep)
			c++;
	if (c > *ntok) {
		char **tmp = (char**) realloc(*tokens, c * sizeof **tokens);
		if (tmp == NULL)
			return 0;
		for (int i = *ntok; i < c; i++)
			tmp[i] = (char*) malloc(TOKENSIZE);
		*tokens = tmp;
		*ntok = c;
	}
	char *begin, *end, *next;
	char **tokptr;
	tokptr = *tokens;
	begin = buf;
	end = buf + strlen(buf);
	while (begin < end) {
		next = strchr(begin+1, (int)sep);
		next = (next==NULL) ? end : next;
		int len = (int)(next - begin);
		strncpy(*tokptr, begin, len);
		(*tokptr)[len] = '\0';
		begin = next + 1;
		tokptr++;
	}
	return c;
}
void strip(char *line)
{
	char *back = line + (strlen(line) - 1);
	while (back != line && !isspace(*back))
		back--;
	*back = '\0';
}
int readline(FILE *f, char ***tokens, int *ntok)
{
	char buf[MAXLINE];
	int buflen;
	fgets(buf, MAXLINE, f);
	if ((buflen = ((int) strlen(buf)))) {
		strip(buf);
		return explode(buf, tokens, ntok, IFS); 
	}
	return 0;
}
int main()
{
	char **tokens = NULL;
	int ntok = 0;
	int i;
	readline(stdin, &tokens, &ntok);

	if (ntok != 4) {
		fprintf(stderr, "Invalid input\n");
		return 1;
	}

	int values[4];  /* 0 = m, 1 = a, 2 = b, 3 = c */
	for (i = 0; i < 4; i++)
		values[i] = atoi(tokens[i]);

	int m = values[0], a = values[1], b = values[2], c = values[3];

	int tmp;
	for (i = 1; i < m && (tmp = ((a * i + b) % m)) != c; i++)
		;
	if (tmp == c)
		printf("%d\n", i);
	else
		printf("There is no such x\n");
}
