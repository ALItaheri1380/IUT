/*
 * Queue.cpp
 *
 * Description: Implementation of an int sequence with enqueue/dequeue ...
 * Class Invariant: ... in FIFO order
 *
 * Author:
 * Date:
 */

#include "Queue.h"
#include <iostream>
using namespace std;

// Description:  Constructor
Queue::Queue() : elementCount(0), capacity(INITIAL_CAPACITY), frontindex(0), backindex(0)
{
    elements = new int[capacity];
}

// Description:  Inserts element x at the back (O(1))
void Queue::enqueue(int x)
{
    if (elementCount == capacity)
    {
        int *temp = new int[capacity * 2];

        backindex += (capacity * (frontindex >= backindex));

        for (int i = frontindex; i < backindex; i++)
            temp[i - frontindex] = elements[i % capacity];

        frontindex = 0;
        backindex = capacity;
        capacity *= 2;
        delete[] elements;
        elements = temp;
        temp = NULL;
    }

    elementCount++;
    elements[backindex] = x;
    backindex = (backindex + 1) % capacity;
}

// Description:  Removes the frontmost element (O(1))
// Precondition:  Queue not empty
void Queue::dequeue()
{
    if (elementCount == 0)
    {
        cout << "empty queue!";
        return;
    }

    if (elementCount < (capacity / 4) && capacity > INITIAL_CAPACITY)
    {
        int *temp = new int[capacity /= 2];

        for (int i = frontindex; i < backindex; i++)
            temp[i - frontindex] = elements[i];

        delete[] elements;
        elements = temp;
        temp = NULL;

        backindex -= frontindex;
        frontindex = 0;
    }

    frontindex = (frontindex + 1) % capacity;
    elementCount--;
}

// Description:  Returns a copy of the frontmost element (O(1))
// Precondition:  Queue not empty
int Queue::peek() const
{
    return elements[frontindex];
}

// Description:  Returns true if and only if queue empty (O(1))
bool Queue::isEmpty() const
{
    return elementCount == 0;
}

Queue::~Queue()
{
    delete[] elements;
}