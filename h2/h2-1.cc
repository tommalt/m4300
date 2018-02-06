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
#include <string.h>
#include <iostream>
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
int main()
{
	double A[4];
	double Ainv[4];
	double x[2];
	double b[2];
	for (int i = 0; i < 4; i++) 
		std::cin >> A[i];
	for (int i = 0; i < 2; i++)
		std::cin >> b[i];
	mat22inv(A, Ainv);
	mmul(Ainv, b, 2, 2, 2, 1, x);
	printf("x=%.4f\ny=%.4f\n", x[0],x[1]);
}
