/*
 * Tom Maltese
 * MTH 4300
 * Homework #7
 * Problem 1
 */
#include <stdio.h>
#include <iostream>
#include "Tree.h"
#include "Frac.h"

template <typename T>
void show(Tree<T> *root, char sep='\n')
{
	if (root) {
		show(root->left);
		std::cout << root->value << sep;
		show(root->right);
	}
}
class SetOfFractions {
	Tree<Frac> *root;

	static void swap(SetOfFractions & left, SetOfFractions & right)
	{
		Tree<Frac> *tmp;
		tmp = right.root;
		right.root = left.root;
		left.root = tmp;
	}
public:
	SetOfFractions() : root() {}
	~SetOfFractions() { destroy_tree(&root); }
	SetOfFractions(SetOfFractions const & other)
	{
		if (!other.root) {
			destroy_tree(&this->root);
			return;
		}
		if (this->root)
			destroy_tree(&this->root);
		tree_copy(other.root, &this->root);
	}
	SetOfFractions(SetOfFractions && other)
	{
		if (!other.root) {
			destroy_tree(&this->root);
			return;
		}
		if (this->root)
			destroy_tree(&this->root);
		this->root = other.root;
		other.root = nullptr;
	}
	SetOfFractions &operator=(SetOfFractions const & other)
	{
		if (this == &other)
			return *this;
		SetOfFractions copy(other);
		swap(*this, copy);
		return *this;
	}
	SetOfFractions &operator=(SetOfFractions && other)
	{
		if (this == &other)
			return *this;
		swap(*this, other);
		other.root = nullptr;
	}
	int isElement(Frac const & f) const
	{
		void *found = tree_find(root, f);
		if (found != nullptr)
			return 1;
		return 0;
	}
	int insertInS(Frac const & f)
	{
		void *inserted = tree_insert(&root, f);
		if (inserted)
			return 1;
		return 0;
	}
	void printAllFractions() const
	{
		show(root);
	}
};

using namespace std;

int main()
{
	int a, b, c;	
	Frac f;
	SetOfFractions set;
	a = 1;
	while (a != 0) {
		cout<< "0 = exit\n1 = insert\n2 = find\n3 = show all\n[0-3]: ";
		cin >> a;
		if (a == 1) {
			cout << "Numerator, denominator: ";
			cin >> b >> c;
			f.setNum(b);
			f.setDen(c);
			set.insertInS(f);
		} else if (a == 2) {
			cout << "Numerator, denominator: ";
			cin >> b >> c;
			f.setNum(b);
			f.setDen(c);
			if (set.isElement(f)) {
				cout << "Yes\n";
			} else {
				cout << "No\n";
			}
		} else if (a == 3) {
			cout << "All fractions:\n";
			set.printAllFractions();
		}
	}
}
