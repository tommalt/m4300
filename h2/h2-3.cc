/*
 * Tom Maltese
 * MTH 4300 - Prof. Matic. HW 2 problem 3
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
int done(int *values, int n)
{
	int fst, i;
	fst = values[0];
	for (i = 0; i < n; i++)
		if (values[i] != fst)
			return 0;
	return 1;
}
/*
 * array_remove does exactly what you would think.
 * return: new array length
 */
int array_remove(int *a, int i, int len)
{
	memmove(a + i, a + i + 1, (len-i) * sizeof *a);
	return len - 1;
}
int array_remove_range(int *a, int begin, int end, int len)
{
	memmove(a + begin, a + end, (len-end) * sizeof *a);
	return len - (end - begin);
}
int *find_next(int *cur, int len)
{
	int i, c;
	c = *cur;
	for (i = 0; i < len; i++, cur++)
		if (*cur != c)
			return cur;
	return cur;
}
int main()
{
	char **tokens = NULL;
	int ntok = 0;
	int i;

	readline(stdin, &tokens, &ntok);
	int values[ntok];
	for (i = 0; i < ntok; i++)
		values[i] = atoi(tokens[i]);

	int *cur, *next, len, sub;
	len = ntok;
	do {
		cur = values + 0;
		next = find_next(cur, len);
		if (*next == -1)
			goto __break;
		sub = *cur ^ *next; /* 1^2 == 3, 1^3 == 2, 2^3 == 1 */
		len = array_remove(values, next - cur, len);
		cur = next -1;
		*cur = sub;

	} while (1);
__break:

	for (i = 0; i < (len-1); i++)
		printf("%d ", values[i]);
	putchar('\n');
	return 0;

}

