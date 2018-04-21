#ifndef FRAC_H
#define FRAC_H

class Frac {
      private:
	long num;
	long den;

      public:
	Frac(const long & = 0, const long & = 1);
	Frac(const Frac &);
	void operator=(const Frac &);
	long getNum() const;
	long getDen() const;
	void setNum(const long &);
	void setDen(const long &);
	long operator<(const Frac &) const;
	long operator>(const Frac &) const;
	friend std::ostream &operator<<(std::ostream & s, Frac const & self);
};
Frac::Frac(const long &_num, const long &_den)
{
	num = _num;
	den = _den;
	if (den == 0) {
		num = 0;
		den = 1;
	}
	if (den < 0) {
		num *= -1;
		den *= -1;
	}
}
Frac::Frac(const Frac &_copyFrom)
{
	num = _copyFrom.getNum();
	den = _copyFrom.getDen();
}
long Frac::getNum() const
{
	return num;
}
long Frac::getDen() const
{
	return den;
}
void Frac::setNum(const long &_n)
{
	num = _n;
}
void Frac::setDen(const long &_d)
{
	den = _d;
	if (den == 0) {
		num = 0;
		den = 1;
	}
	if (den < 0) {
		num *= -1;
		den *= -1;
	}
}
void Frac::operator=(const Frac &_copyFrom)
{
	den = _copyFrom.getDen();
	num = _copyFrom.getNum();
}
long Frac::operator<(const Frac &_cW) const
{
	if (num * _cW.getDen() < den * _cW.getNum()) {
		return 1;
	}
	return 0;
}
long Frac::operator>(const Frac &_cW) const
{
	if (num * _cW.getDen() > den * _cW.getNum()) {
		return 1;
	}
	return 0;
}

std::ostream & operator<<(std::ostream & s, Frac const & self)
{
	s << self.num << '/' << self.den;
	return s;
}
#endif
