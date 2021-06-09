#include "PriorityQueue.h"
#include <iostream>
using namespace std;

template <class T>
void PriorityQueue<T>::push(T add, int prior)
{
	if (size == 0)
	{
		head = new Node(add, prior);
		tail = head;
	}
	else
	{
		Node* newNod = new Node(add, prior);
		Node* cur = head;
		while ((newNod->priority < cur->priority) && (cur->next != NULL))
		{
			cur = cur->next;
		}
		if ((newNod->priority <= cur->priority) && (cur->next == NULL)) {
			newNod->before = cur;
			newNod->next = NULL;
			cur->next = newNod;
			tail = newNod;
		}
		else if ((newNod->priority >= cur->priority) && (cur->before == NULL))
		{
			newNod->before = NULL;
			newNod->next = cur;
			cur->before = newNod;
			head = newNod;
		}
		else {
			newNod->next = cur;
			newNod->before = cur->before;
			cur->before->next = newNod;
			cur->before = newNod;

		}
	}
	size++;
}

template <class T>
size_t PriorityQueue<T>::get_size()
{
	return size;
}

template <class T>
T PriorityQueue<T>::pop()
{
	T cont;
	if (size == 1)
	{
		cont = head->content;
		size = 0;
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
int PriorityQueue<T>::tail_priority() {
	return tail->priority;
}

template <class T>
void PriorityQueue<T>::clear()
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
bool PriorityQueue<T>::isEmpty()
{
	if (head == NULL)
		return true;
	return false;
}