 class Stack {

    private:
        class StackNode {
            public:
                int data;
                StackNode * next;

            StackNode(){next = nullptr;}    
        };
    
        StackNode * head;
        StackNode * tail;

    public:

        Stack();

        ~Stack();

        void push(int x);

        int pop();
        
        int peek() const;

        void print();

        bool isEmpty() const;
};


