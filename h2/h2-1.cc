/*
 * Tom Maltese
 * MTH 4300 - Prof. Matic. HW 2 problem 1
 * 
 * we can model the system of equations with matrices
 * let the matrix A be a 2x2 matrix corresponding to the
 * coefficients 'a11 a12 a21 a22'.
 * let the vector x be of length 2, corresponding to the
 * variables 'x and y'
 * we have:
 *       Ax = b
   solving for x:
 *       A^-1 Ax = A^-1 b
 *       x = A^-1 b
 */
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 256
#define TOKENSIZE 32
#define IFS ' '

/*
 * Inverse of a (row major) 2 by 2 matrix
 * [0] = [0,0]
 * [1] = [0,1]
 * [2] = [1,0]
 * [3] = [1,1]
 */
int mat22inv(double *m, double *out)
{
	double buf[4];
	double dterm;		/* matrix determinant */
	int i;

	dterm = m[0] * m[3] - m[1] * m[2];
	if (dterm == 0.0)
		return 1;
	buf[0] = m[3];
	buf[1] = -m[1];
	buf[2] = -m[2];
	buf[3] = m[0];
	for (i = 0; i < 4; i++)
		buf[i] /= dterm;
	memcpy(out, buf, sizeof buf);
	return 0;
}
/*
 * dot product
 */
double dotv(double *a, double *b, int size)
{
	int i;
	double t = 0.0;
	for (i = 0; i < size; i++)
		t += a[i] * b[i];
	return t;
}
/* slicing by row/col */
void matrix_col(double *m, int c, int nrow, int ncol, double *out)
{
	int i;
	for (i = 0; i < nrow; i++) 
		out[i] = m[i * ncol + c];
}
void matrix_row(double *m, int r, int ncol, double *out)
{
	double *ptr = m + (r * ncol);
	memcpy(out, ptr, ncol * sizeof *out); 
}
/* matrix multiplication */
void mmul(double *a, double *b,
         int ra, int ca,	/* rows and columns of a, b */
         int rb, int cb,
         double *out)
{
	assert(ca == rb && "mmul: ncol(A) != nrow(B)");
	double buf[ra * cb];
	double arow[ca];	/* temporaries for parts of a, b */
	double bcol[rb];	/* tmpa is a row vector, tmpb a column vector */
	int r, c;

	for (r = 0; r < ra; r++) {
		matrix_row(a, r, ca, arow);
		for (c = 0; c < cb; c++) {
			matrix_col(b, c, rb, cb, bcol);
			buf[(r * cb) + c] = dotv(arow,bcol, rb/*could use ca here, same thing*/);
		}
	}
	memcpy(out, buf, sizeof buf);
}

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
		begin = next;
		tokptr++;
	}
	return c;
}
void strremove(char *str, int (*pred)(int))
{
	/* pred(d) shall return true if d is to be removed, false otherwise */
	char *d, *s;
	for (d = s = str; (*d = *s++); d += (!pred(*d) ? 1 : 0))
		;
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
	double A[4];
	double Ainv[4];
	double x[2];
	double b[2];
	double inputs[6];
	char **tokens = NULL;
	int ntok = 0, nread = 0;
	int i = 0, j = 0;
	do {
		nread += readline(stdin, &tokens, &ntok);
		for ( ; j < ntok && i < 6; j++) {
			inputs[i++] = strtod(tokens[j], NULL);
		}
		if (nread >= 6)
			goto __break;
	} while (1);
__break:
	for (i = 0; i < ntok; i++)
		free(tokens[i]);
	free(tokens);

	memcpy(A, inputs, 4 * sizeof (double));
	memcpy(b, inputs + 4, 2 * sizeof (double));

	mat22inv(A, Ainv);
	mmul(Ainv, b, 2, 2, 2, 1, x);
	printf("x=%.4f\ny=%.4f\n", x[0],x[1]);
}
