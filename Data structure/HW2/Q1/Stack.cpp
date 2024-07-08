#include<iostream>
#include <cstddef> 
#include "Stack.h"

using namespace std;

Stack::Stack()
{
    tail = nullptr;
    head = nullptr;
}

void Stack::push(int X)
{


    StackNode* newNode = new StackNode();
    newNode->data = X;

    if(!head)
    {
        this->head = newNode;
        this->tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }
}

int Stack::pop()
{
    if(!isEmpty())
    {
        if (head == tail)
        {
            StackNode *temp = head;
            int Data = temp->data;

            head = nullptr;
            tail = nullptr;

            delete temp;
            return Data;
        }

        else
        {
            StackNode* temp = head;
            while (temp->next != tail)
            {
                temp = temp->next;
            }
            tail = temp;

            int Data = temp->next->data;

            delete tail->next;
            return Data;

        }
    }
}

int Stack::peek() const
{
    if(!isEmpty())
        return tail->data;
}

bool Stack::isEmpty() const
{
    if(!head)
        return true;
    else
        return false;
}

void Stack::print()
{
    StackNode* temp = head;

    while (temp)
    {
        cout<<temp->data<<"\t\t";
        temp = temp->next;
    }

}

Stack::~Stack()
{
    while (head!=tail)
    {
        StackNode* temp = head;
        head = head->next;
        delete temp;
    }
    delete head;
}