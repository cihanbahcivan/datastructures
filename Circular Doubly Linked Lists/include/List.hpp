#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include "Node.hpp"

using namespace std;

class List
{
public:
	Node* mid;
	int nodeCount;

	List();
	void AddNext(int, int);
	void AddPrev(int, int);
};

#endif