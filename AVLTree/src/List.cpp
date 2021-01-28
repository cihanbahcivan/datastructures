#include "List.hpp"

List::List()
{
	mid = NULL;
	nodeCount = 0;
}

void List::AddNext(int _value, int length) //Okunan degeri mid pointerinin next tarafina ekleyen metot.
{
	Node* temp = this->mid;

	for (int i = 0; i < length; i++)
	{
		if (temp->next != NULL)
		{
			temp = temp->next;
		}
		else
			break;
	}
	temp->next = new Node(_value,NULL,temp);
}

void List::AddPrev(int _value, int length) //Okunan degeri mid pointerinin prev tarafina ekleyen metot.
{
	Node* temp = this->mid;

	for (int i = 0; i < length; i++)
	{
		if (temp->prev != NULL)
		{
			temp = temp->prev;
		}
		else
			break;
	}
	temp->prev = new Node(_value, temp, NULL);
}
