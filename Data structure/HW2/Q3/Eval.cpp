#include "Scanner.h"
#include "Stack.h"  // GENERIC STACK

#include <iostream>

using namespace std;



int isp(Token c)
{
    if(c.tt == lptok)
        return 0;

    else if(c.tt == pltok || c.tt == mitok)
        return 1;

    else if(c.tt == asttok || c.tt == slashtok)
        return 3;
    else
    {
        cout<<"invalid phars!!!!!";
        exit(0);
    }
}

int isp(string c)
{

    if(c == "(")
        return 0;

    else if(c == "+" || c == "-")
        return 1;

    else if(c == "*" || c == "/")
        return 3;

    else
    {
        cout<<"invalid phars!!!!!";
        exit(0);
    }
}

int Find_the_result(string op, int l , int r)
{

    if(op == "+")
        return l + r;

    else if(op == "-")
        return l - r ;

    else if(op == "*")
        return l * r;

    else if(op == "/")
    {
        if(r > 0)
        {
            return l/r;
        }
        else
            return 0;
    }
    else
    {
        cout<<"invalid phars!!!!!";
        exit(0);
    }

}


int main ()
{
    Scanner S(cin);
    Token t;
    Stack<string> Operator;
    Stack<int> operand;
    t = S.getnext();



    // Pretty printer coding demo.  Please remove before coding
    while (t.tt != eof)
    {
        if(t.tt == lptok)
        {
            Operator.push("(");
        }

        else if(t.tt == rptok)
        {
            while(Operator.peek() != "(")
            {
                int op1 = operand.peek();
                operand.pop();

                int op2 = operand.peek();
                operand.pop();

                int result = Find_the_result(Operator.peek(),op2,op1);

                operand.push(result);

                Operator.pop();
            }
            Operator.pop();
        }

        else if
                (
                t.tt == asttok || t.tt == slashtok||
                t.tt == pltok  || t.tt == mitok
                )

        {
            while(!Operator.isEmpty() && isp(Operator.peek()) >= isp(t))
            {
                int op1 = operand.peek();
                operand.pop();

                int op2 = operand.peek();
                operand.pop();

                int result = Find_the_result(Operator.peek(),op2,op1);

                operand.push(result);

                Operator.pop();
            }
            Operator.push(t.text);
        }

        else
        {
            operand.push(t.val);
        }


        t = S.getnext();
    }

    while(!Operator.isEmpty())
    {
        int op1 = operand.peek();
        operand.pop();

        int op2 = operand.peek();
        operand.pop();

        int result = Find_the_result(Operator.peek(),op2,op1);

        operand.push(result);

        Operator.pop();
    }

    cout <<"Result: " << operand.peek() << endl;
    return 0;

}