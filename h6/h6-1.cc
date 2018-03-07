#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* memcpy */
#include <stdarg.h>
#include <utility>  /* std::move */
#include <iostream>

void die(char const *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
	exit(1);
}
class BagOfPoints {
	double *sequenceX;
	double *sequenceY;
	int numPoints;
	void realloc(int newsize);
	void swap(BagOfPoints &, BagOfPoints &);
public:
	BagOfPoints(int const & size = 0);
	BagOfPoints(BagOfPoints const &);
	BagOfPoints(BagOfPoints &&);
	~BagOfPoints();
	// assignment BagOfPoints::operators shall return references to *this.
	// Foo x, y, z, bar;
	// bar = ...
	// x = y = z = bar;
	BagOfPoints &operator=(BagOfPoints const &);
	BagOfPoints &operator=(BagOfPoints &&);

	double getX(int const &) const;
	double getY(int const &) const;
	int getLength() const;
	void setTerm(int const &, double const &, double const &);
	void setLength(int const &);
};

void BagOfPoints::realloc(int newsize)
{
	if (newsize > 0) {
		this->sequenceX = (double *) ::realloc(sequenceX, newsize * sizeof *sequenceX);
		this->sequenceY = (double *) ::realloc(sequenceY, newsize * sizeof *sequenceY);
		if (!sequenceX || !sequenceY)
			die("Out of memory\n");
		this->numPoints = newsize;
	}
}
void BagOfPoints::swap(BagOfPoints & fst, BagOfPoints & snd)
{
	double *x = snd.sequenceX;
	double *y = snd.sequenceY;
	int     n = snd.numPoints;
	snd.sequenceX = fst.sequenceX;
	snd.sequenceY = fst.sequenceY;
	snd.numPoints = fst.numPoints;
	fst.sequenceX = x;
	fst.sequenceY = y;
	fst.numPoints = n;
}
BagOfPoints::BagOfPoints(int const & size)
	: sequenceX(NULL), sequenceY(NULL), numPoints(0)
{
	if (size)
		this->realloc(size);
}
BagOfPoints::BagOfPoints(BagOfPoints const & other)
	: sequenceX(NULL), sequenceY(NULL), numPoints(0)
{
	int size = other.numPoints;
	if (size != this->numPoints)
		this->realloc(size);
	memcpy(sequenceX, other.sequenceX, size * sizeof *sequenceX); 
	memcpy(sequenceY, other.sequenceY, size * sizeof *sequenceY); 
}
BagOfPoints::BagOfPoints(BagOfPoints && other)
	: sequenceX(NULL), sequenceY(NULL), numPoints(0)
{
	this->sequenceX = other.sequenceX;
	this->sequenceY = other.sequenceY;
	this->numPoints = other.numPoints;
	other.sequenceX = NULL;
	other.sequenceY = NULL;
}
BagOfPoints::~BagOfPoints()
{
	if (this->sequenceX)
		free(sequenceX);
	if (this->sequenceY)
		free(sequenceY);
	sequenceX = sequenceY = NULL;
	numPoints = 0;
}
BagOfPoints &BagOfPoints::operator=(BagOfPoints const & other)
{
	if (this == &other)
		return *this;
	BagOfPoints copy(other);
	swap(*this, copy);
	return *this;
}
BagOfPoints &BagOfPoints::operator=(BagOfPoints && other)
{
	if (this == &other)
		return *this;
	this->~BagOfPoints();
	swap(*this, other);
	return *this;
}
double BagOfPoints::getX(int const & k) const
{
	assert(k < this->numPoints && "Index out of range");
	return sequenceX[k];
}
double BagOfPoints::getY(int const & k) const
{
	assert(k < this->numPoints && "Index out of range");
	return sequenceY[k];
}
int BagOfPoints::getLength() const
{
	return numPoints;
}
void BagOfPoints::setTerm(int const & i, double const & x, double const & y)
{
	assert(i < this->numPoints && "Index out of range");
	sequenceX[i] = x;
	sequenceY[i] = y;
}
void BagOfPoints::setLength(int const & newsize)
{
	this->realloc(newsize);
}
BagOfPoints reflectPoints(BagOfPoints const & b)
{
	int size = b.getLength();
	BagOfPoints r(size);
	for (int i = 0; i < size; i++) {
		int x, y;
		x = b.getX(i);
		y = b.getY(i);
		r.setTerm(i, -x, -y);
	}
	return r;
}
int main()
{
	int n;
	std::cout << "How many points?: ";
	std::cin >> n;
	std::cout << "Give me the numbers: ";
	BagOfPoints bp(n);
	int x, y, i;
	for (i = 0; i < n; i++) {
		std::cin >> x >> y;
		bp.setTerm(i, x, y);
	}
	BagOfPoints bpReflected = reflectPoints(bp); 

	std::cout << "Reflected points:\n";
	for (i = 0; i < n; i++)
		std::cout << bpReflected.getX(i) << ' ' << bpReflected.getY(i) << '\n';
}
/*
 * Discussion.
 * in main()
 *    BagOfPoints(int const &) is invoked when bp is constructed
 * in reflectPoints(bp), there is no copy into the function argument
 * because it is a reference.
 *    BagOfPoints r(size) invokes the copy constructor 
 * what happens upon the return of reflectPoints(bp) depends on the
 * compiler flags, C++ version, etc.
 * 
 * with just -std=c++11, the compiler performs NRVO (named-return-value optimization)
 * and the value `r` in reflectPoints() is constructed onto the region where
 * bpReflected lives in main().
 * There are only two constructions, and destructions, 1 of each
 *  for bp and bpReflected.
 * 
 * with -fno-elide-constructors, `return r` invokes move ctor, `r` is
 * destroyed and `return r` is moved into bpReflected (move ctor), and
 * `return r` is destroyed. This is in addition to the constructor and destructor
 * calls mentioned above.
 */
