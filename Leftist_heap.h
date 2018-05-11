#ifndef LEFTIST_HEAP_H
#define LEFTIST_HEAP_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Leftist_node.h"

template <typename Type>
class Leftist_heap {
private:
	Leftist_node<Type> *root_node;
	int heap_size;

public:
	Leftist_heap();
	~Leftist_heap();

	void swap(Leftist_heap &heap);


	bool empty() const;
	int size() const;
	int null_path_length() const;
	Type top() const;
	int count(Type const &) const;

	void push(Type const &);
	Type pop();
	void clear();
	
	template <typename T>
	friend std::ostream &operator<<(std::ostream &, Leftist_heap<T> const &);
};

//Constructor
template <typename Type>
Leftist_heap<Type>::Leftist_heap() :
	root_node(nullptr),
	heap_size(0) {
	// does nothing
}


//Deconstructor
template <typename Type>
Leftist_heap<Type>::~Leftist_heap() {
	clear();
}

//Swapfunction??
template <typename Type>
void Leftist_heap<Type>::swap(Leftist_heap<Type> &heap) {
	std::swap(root_node, heap.root_node);
	std::swap(heap_size, heap.heap_size);
}

//Output function
template <typename T>
std::ostream &operator<<(std::ostream &out, Leftist_heap<T> const &heap) {
	return out;
}

template <typename Type>
bool Leftist_heap<Type>::empty() const{
	if (heap_size==0) {
		return 1;
	}
	else {
		return 0;
	}
}

template <typename Type>
int Leftist_heap<Type>::size() const{
	return heap_size;
}

template <typename Type>
int Leftist_heap<Type>::null_path_length() const{
	if ((root_node != nullptr)&&(heap_size!=0)) {
		return root_node->null_path_length();
	}
	else {
		return -1;
	}
}

template <typename Type>
int Leftist_heap<Type>::count(const Type &obj) const{
	//Branch through the tree to find the number of instances within the entire tree
	int instances=root_node->count(obj);
	return instances;

}

template <typename Type>
Type Leftist_heap<Type>::top() const{
	if (root_node != nullptr) {
		return root_node->retrieve();
	}
	else {
		throw underflow();
	}
}

//Create new leftist node
//insert element by calling node.push(
//use root_node as second argument
//use Root? as first argument
template <typename Type>
void Leftist_heap<Type>::push(const Type & obj) {
	Leftist_node<Type> * myNode= new Leftist_node<Type> (obj);
	root_node->push(myNode, root_node);
	heap_size++;
}

//Delete last element in heap and node
//If tree empty throw underflow excpetion
//if not empty
	//Left subtree of root is made the root
	//right subtree of origional root node if pushed into the new node
template <typename Type>
Type Leftist_heap<Type>::pop() {
	if ((root_node != nullptr)&&(empty()==0)) {
		Type leastElement = root_node->retrieve();
		Leftist_node<Type> * temp_node = root_node;
		root_node = root_node->left();
		root_node->push(temp_node->right(), root_node);
		delete temp_node;
		heap_size--;
		return leastElement;
	}
	else {
		throw underflow();
	}
}

//Call clear on the root node and reset the root node and heap size
template <typename Type>
void Leftist_heap<Type>::clear() {
	if (heap_size != 0) {
		root_node->clear();
		heap_size = 0;
	}
}
#endif