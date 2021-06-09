#pragma once
#include <iostream>
template <class T>
class PriorityQueue
{
private:
    class Node
    {
    public:
        Node(T content, int prior = 0, Node* before = NULL, Node* next = NULL)
        {
            this->content = content;
            this->priority = prior;
            this->before = before;
            this->next = next;
        };
        ~Node()
        {  }
        T content;
        int priority;
        Node* next;
        Node* before;
    private:

    };

    Node* head;
    Node* tail;
    size_t size;

public:
    PriorityQueue(Node* head = NULL, Node* tail = NULL) {
        this->head = head;
        this->tail = tail;
        size = 0;
    };
    void push(T, int);
    size_t get_size();
    T pop();
    int tail_priority();
    void clear();
    bool isEmpty();
    ~PriorityQueue()
    {
        while ((head != NULL) && (head->next != NULL))
        {
            head = head->next;
            delete head->before;
        }
        size = 0;
        delete head;
    };
};

