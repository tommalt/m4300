#ifndef TREE_H
#define TREE_H

#include <assert.h>

template <typename T>
struct Tree {
	T value;
	Tree *left, *right;
	Tree() :  left(nullptr) , right(nullptr) {}
};
template <typename T>
Tree<T> *tree_insert(Tree<T> **root, T value)
{
	if (!*root) {
		*root = new Tree<T>;
		(*root)->value = value;
		return *root;
	}
	if (value < (*root)->value) {
		return tree_insert(&(*root)->left, value);
	} else if (value > (*root)->value) {
		return tree_insert(&(*root)->right, value);
	} else {
		return nullptr;
	}
}
template <typename T>
Tree<T> *tree_delete(Tree<T> **root)
{
	Tree<T> *r =  *root;
	if (r) {
		if (r->left) {
			Tree<T> *upper, *lower;
			upper = r->left;
			if (upper->right) {
				lower = upper->right;
				while (lower->right) {
					upper = upper->right;
					lower = lower->right;
				}
				r->value = lower->value;
				if (!lower->left) {
					delete lower;
					upper->right = nullptr;
				} else {
					tree_delete(&upper->right);
				}
			} else {
				r->value = upper->value;
				if (upper->left == nullptr) {
					delete upper;
					r->left = nullptr;
				} else {
					tree_delete(&r->left);
				}
			}
		} else {
			if (r->right != nullptr) {
				Tree<T> *upper, *lower;
				upper = r->right;
				if (upper->left) {
					lower = upper->left;
					while (lower->left) {
						upper = upper->left;
						lower = lower->left;
					}
					root->value = lower->value;
					if (lower->right == nullptr) {
						delete lower;
						upper->left = nullptr;
					} else {
						tree_delete(&upper->left);
					}
				} else {
					r->value = upper->value;
					if (upper->right == nullptr) {
						delete upper;
						r->right = nullptr;
					} else {
						tree_delete(&r->right);
					}
				}
			} else {
				delete *root;
				*root = nullptr;
			}
		}
	}
}
template <template <typename> class Tree, class T>
Tree<T> *tree_find(Tree<T> *root, T value)
{
	if (!root)
		return nullptr;
	if (value < root->value)
		return tree_find(root->left, value);
	else if (value > root->value)
		return tree_find(root->right, value);
	return root;
}

template <typename T>
void destroy_tree(Tree<T> **root)
{
	if (!*root)
		return;
	destroy_tree(&(*root)->left);
	destroy_tree(&(*root)->right);
	delete *root;
	*root = nullptr;
}
template <typename T>
Tree<T> *tree_copy(Tree<T> const *src, Tree<T> **dest)
{
	assert(*dest == nullptr);
	if (!src)
		return nullptr;
	tree_insert(dest, src->value);
	tree_copy(src->left, &(*dest)->left);
	tree_copy(src->right, &(*dest)->right);
}


#endif
