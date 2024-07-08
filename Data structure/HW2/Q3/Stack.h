

// Description:  The usual fare.  Descriptions, invariants, precondition and postcondition are
//        omitted because they are duplicated elsewhere, namely Question 1.
template <class T>
class Stack {
    class Node {
        public: 
            T data;
            Node *next;
    };
    private:
        Node* head;
    public:
        Stack();
        ~Stack();
        void push(T x);
        T pop();
        T peek();
        bool isEmpty();
};



////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////


template <class T> 
Stack<T>::Stack() {
    head = NULL;
}


template <class T> 
void Stack<T>::push(T x) {
    Node *newhead = new Node;
    newhead->data = x;
    newhead->next = head;
    head = newhead;
}


template <class T> 
T Stack<T>::pop() {
    T ret = head->data;
    Node *old_head = head;
    head = head->next;
    delete old_head;
    return ret;
}

template <class T> 
T Stack<T>::peek() {
    return head->data;
}


template <class T> 
bool Stack<T>::isEmpty() {
    return (head == NULL);
}


template <class T> 
Stack<T>::~Stack() {
    Node *p = head;
    while (p != NULL) {
        head = head->next;
        delete p;
        p = head;
    }
}


