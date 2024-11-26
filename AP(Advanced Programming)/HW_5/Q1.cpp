
#include<iostream>

using namespace std;

class A
{
    public:
        A(){
            callA = 0;
        }
    private:
        int callA;
        void inc(){
            callA++;
        }

    protected:
        void func(int & a)
        {
            a = a * 2;
            inc();
        }
    public:
        int getA(){
            return callA;
        }
};

class B
{
    public:
        B(){
            callB = 0;
        }
    private:
        int callB;
        void inc(){
            callB++;
        }
    protected:
        void func(int & a)
        {
            a = a * 3;
            inc();
        }
    public:
        int getB(){
            return callB;
        }
};

class C
{
    public:
        C(){
            callC = 0;
        }
    private:
        int callC;
        void inc(){
            callC++;
        }
    protected:
        void func(int & a)
        {
            a = a * 5;
            inc();
        }
    public:
        int getC(){
            return callC;
        }
};

/*******************************/

class D :protected A, protected B, protected C
{

    int val;
    public:
        //Initially val is 1
         D()
         {
             val = 1;
         }

         //Implement this function
         void update_val(int new_val)
         {
           int w=new_val;
           
           while (w>=2)
           {
               if(w%2==0){
                   A::func(val);
                   w/=2;
               }
               else if (w%3==0)
               {
                   B::func(val);
                   w/=3;
               }
               else if (w%5==0)
               {
                   C::func(val);
                   w/=5;
               }
           }
           
         }
         //For Checking Purpose
         void check(int); //Do not delete this line.
};

/******************************/

void D::check(int new_val)
{
    update_val(new_val);
    cout << "Value = " << val << endl << "A's func called " << getA() << " times " << endl << "B's func called " << getB() << " times" << endl << "C's func called " << getC() << " times" << endl;
}

int main()
{
    D d;
    int new_val;
    cin >> new_val;
    d.check(new_val);

}