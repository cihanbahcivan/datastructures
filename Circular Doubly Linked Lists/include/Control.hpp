#ifndef CONTROL_HPP
#define CONTROL_HPP

#include <iostream>
#include "List.hpp"
#include "Node.hpp"
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

class Control
{
public:

	Control();
	List** text;
	int lineCount;
	void ListCount();
	void ReadLines();
	void FindMinMax();
	void SwapWings(int, int);
	void SwapNodes(Node*, Node*);
	void RelinkPrev(Node*, Node*);
	void RelinkNext(Node*, Node*);
	void Print(int,int);
	~Control();
};

#endif