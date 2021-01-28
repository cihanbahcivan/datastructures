#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>

using namespace std;

class Node
{
public:
	int value;
	Node* next;
	Node* prev;

	Node();
	Node(int, Node*, Node*);
};

#endif