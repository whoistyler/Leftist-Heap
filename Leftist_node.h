#ifndef LEFTIST_NODE_H
#define LEFTIST_NODE_H

#include <algorithm>

#ifndef nullptr
#define nullptr 0
#endif

template <typename Type>
class Leftist_node {
private:
	Type element;
	Leftist_node *left_tree;
	Leftist_node *right_tree;
	int heap_null_path_length;
	int tempCount;

public:
	Leftist_node(Type const &);

	Type retrieve() const;
	bool empty() const;
	Leftist_node *left() const;
	Leftist_node *right() const;
	int count(Type const &) const;
	int null_path_length() const;

	void push(Leftist_node *, Leftist_node *&);
	void clear();
};

//Constructor
template <typename Type>
Leftist_node<Type>::Leftist_node(Type const &obj) :
	element(obj),
	left_tree(nullptr),
	right_tree(nullptr),
	heap_null_path_length(0) {
}


//If heap EMPTY
template <typename Type>
bool Leftist_node<Type>::empty() const {
	return (this == nullptr);
}

//Returns the element stored in the node
template <typename Type>
Type Leftist_node<Type>::retrieve() const{
	return element;
}

//Returns the address of left subtree
template <typename Type>
Leftist_node <Type>* Leftist_node<Type>::left() const {
	return this->left_tree;
}

//Returns the address of right subtree
template <typename Type>
Leftist_node <Type>* Leftist_node<Type>::right() const {
	return this->right_tree;
}

//Returns the number of instances of the argument in this sub-tree
template <typename Type>
int Leftist_node<Type>::null_path_length() const {
	if (this != nullptr) {
		return heap_null_path_length;
	}
	else {
		return -1;
	}
}

//Returns the number of instances of the argument in this sub-tree
template <typename Type>
int Leftist_node<Type>::count(const Type & obj) const{
	int count = 0;
	if(this == NULL) {
		return count;
	}
	else {
		if (left_tree != nullptr) {
			count+= left_tree->count(obj);
		}
		if (right_tree != nullptr) {
			count += right_tree->count(obj);
		}
		if (element == obj) {
			count++;
		}
	}
	return count;
}

template <typename Type>
void Leftist_node<Type>::push(Leftist_node *new_heap, Leftist_node *&ptr_to_this) {
	if (new_heap == nullptr) {
		return;
	}
	else {//If node is not null insert
		if (this == nullptr) {
			ptr_to_this = new_heap;
			return;
		}
		if (ptr_to_this->element <= new_heap->element) {
			right_tree->push(new_heap, right_tree);
			
			if ((left_tree == nullptr) && (right_tree != nullptr)) {
				std::swap(ptr_to_this->right_tree, ptr_to_this->left_tree);
			}
			else if ((left_tree != nullptr) && (right_tree != nullptr)) {
				heap_null_path_length = std::min(1 + left_tree->null_path_length(), right_tree->null_path_length() + 1);
				if ((ptr_to_this->left_tree->null_path_length()) < (ptr_to_this->right_tree->null_path_length())) {
					std::swap(ptr_to_this->right_tree, ptr_to_this->left_tree);
				}
			}
		}
		else {
			ptr_to_this = new_heap;
			new_heap->push(this, ptr_to_this);

		}
	}
}

template <typename Type>
void Leftist_node<Type>::clear() {
	if (this == nullptr) {
		return;
	}
	else {
		left_tree->clear();

		right_tree->clear();
		delete this;
	}
}
#endif