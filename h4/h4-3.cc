#include <stdio.h>
#include <iostream>

struct List {
	int data;
	struct List *next;
};
struct List *newList()
{
	struct List *l = (struct List*) malloc(sizeof *l);
	l->data = 0;
	l->next = NULL;
	return l;
}
void destroy_list(struct List *root)
{
	while (root) {
		struct List *next = root->next;
		free(root);
		root = next;
	}
}
struct List *list_add(struct List *root, int x)
{
	while (root->next)
		root = root->next;
	root->next = newList();
	root->next->data = x;
	return root->next;
}
struct List *list_remove(struct List **self)
{
	if (!*self)
		return NULL;
	if (!(*self)->next) {
		free(*self);
		*self = NULL;
		return NULL;
	}
	struct List *next = (*self)->next;
	(*self)->data = next->data;
	(*self)->next = next->next;
	free(next);
	return *self;
}
void show(struct List *root)
{
	while (root) {
		printf("%d\n", root->data);
		root = root->next;
	}
}
int main()
{
	struct List *list;
	int x;

	list = newList();
	std::cout << "Give me some numbers\n-9 to quit: ";
	std::cin >> x;
	list->data = x;
	struct List *end = list;
	while (std::cin >> x) {
		if (x == -9)
			break;
		end = list_add(end, x);
	}
	std::cout << "I lied, I still need one more number: ";
	std::cin >> x;
	struct List *last = NULL;
	end = list;
	while (end) {
		if (end->data == x)
			last = end;
		end = end->next;
	}
	if (!last)
		show(list);
	else
		show(list_remove(&last));
	destroy_list(list);
	return 0;
}
