#include "Node.hpp"

Node::Node()
{
	value = 0;
	next = NULL;
	prev = NULL;
}

Node::Node(int _value, Node* _next, Node* _prev)
{
	value = _value;
	next = _next;
	prev = _prev;
}
