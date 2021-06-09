#pragma once
#include <iostream>

template <class T>
class Stack
{
private:
    class Node
    {
    public:
        Node(T content = 0, Node* before = NULL, Node* next = NULL)
        {
            this->content = content;
            this->before = before;
            this->next = next;
        };
        ~Node()
        {  }
        T content;
        Node* next;
        Node* before;
    private:

    };

    Node* head;
    Node* tail;
    size_t size;

public:
    Stack(Node* head = NULL, Node* tail = NULL) {
        this->head = head;
        this->tail = tail;
        size = 0;
    };
    void push(T);
    size_t get_size();
    T pop();
    T get_last();
    void clear();
    bool isEmpty();
    ~Stack()
    {
        if (head != NULL)
        {
            while (head->next != NULL)
            {
                head = head->next;
                delete head->before;
            }
            size = 0;
            delete head;
        }
    };
};

