/*
 * Tom Maltese
 * Homework 5, Problem 2
 */
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

#define MIN(x,y) ((x) < (y)) ? (x) : (y)

int nextPowerOf2(int x)
{
	x--;
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	x++;
	return x;
}
class Array {
	int *m_data;
	int m_size;
	int m_cap;
public:
	Array() : m_data(NULL), m_size(0), m_cap(0)
	{}
	~Array()
	{
		if (this->m_data)
			free(this->m_data);
	}
	int *data()
	{
		return this->m_data;
	}
	int size()
	{
		return this->m_size;
	}
	int capacity()
	{
		return this->m_cap;
	}
	void push_back(int x)
	{
		if (!this->m_data)
			this->realloc(2);
		if (this->m_size >= this->m_cap) {
			this->realloc(nextPowerOf2(this->m_cap + 2));
		}
		m_data[m_size++] = x;
	}
	void realloc(int newcap)
	{
		this->m_data = (int *) ::realloc(this->m_data, newcap * sizeof *m_data);
		this->m_cap = newcap;
	}
	void trunc(int newsize)
	{
		newsize = MIN(newsize, this->m_size);
		this->m_size = newsize;
	}
};
void show(Array *a, char const *msg)
{
	int *d =a->data();
	if (msg)
		printf("%s:", msg);
	for (int i = 0; i < a->size(); i++)
		printf(" %d", d[i]);
	putchar('\n');
}
int main()
{
	Array x;
	Array y;
	int tmp;
	std::cout << "Give me some numbers. -9 to stop: ";
	while (std::cin >> tmp && tmp != -9) {
		x.push_back(tmp);
	}
	int *data = x.data();
	for (int i = 0; i < x.size(); i++) {
		if (data[i] >= 0) {
			y.push_back(data[i]);
		} else {
			int newsize = y.size() - (-data[i]);
			newsize = (newsize < 0) ? 0 : newsize;
			y.trunc(newsize);
		}
	}
	show(&x, "Input");
	show(&y, "Output");
}
