#include "Stack.h"
using namespace std;

template <class T>
void Stack<T>::push(T add)
{
	if (size == 0)
	{
		head = new Node(add);
		tail = head;
	}
	else
	{
		Node* curr = new Node(add);
		curr->before = tail;
		tail->next = curr;
		tail = curr;
	}
	size++;
}

template <class T>
size_t Stack<T>::get_size()
{
	return size;
}

template <class T>
T Stack<T>::pop()
{
	T cont;
	if (size == 1)
	{
		size = 0;
		cont = tail->content;
		head = NULL;
		tail = NULL;

	}
	else if (size > 1)
	{
		cont = tail->content;
		tail = tail->before;
		delete tail->next;
		tail->next = NULL;
		size--;
	}
	else
		throw out_of_range("Segmentation fault");
	return cont;
}

template <class T>
T Stack<T>::get_last() {
	return tail->content;
}

template <class T>
void Stack<T>::clear()
{
	if (head != NULL)
	{
		while (head->next != NULL)
		{
			head = head->next;
			delete head->before;
		}
		size = 0;
		head = NULL;
		tail = NULL;
	}
}

template <class T>
bool Stack<T>::isEmpty()
{
	if (head == NULL)
		return true;
	return false;
}
