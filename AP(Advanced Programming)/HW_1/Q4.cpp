#include<iostream>
using namespace std;
struct Rational
{
    int a;
    int b;
};
int bmm(int a, int b)
{
    if (b == 0)
        return a;
    return bmm(b, a % b);
}
void getRational(Rational *i)
{
    int a, b;
    cin>>a;
    cin>>b;
    i->a = a;
    i->b = b;
    if(i->b == 0)
    	i->b=1;
}
void print(Rational i)
{
   cout<< i.a<< "/"<<i.b<<endl;
}
void simplify(Rational *i)
{
    int bm=bmm(i->a, i->b);
    i->a =i->a/ bm;
    i->b =i->b/bm;
}

 Rational add(Rational q1,Rational q2)
{
    struct Rational aa;
    aa.a = (q1.a * q2.b) + (q1.b * q2.a);
    aa.b = q1.b * q2.b;
    return aa;
}

Rational subtract(Rational q1,Rational q2)
{
    struct Rational aa;
    aa.a = (q1.a * q2.b) - (q1.b * q2.a);
    aa.b = q1.b * q2.b;
    return aa;
}

Rational multiply(Rational q1,Rational q2)
{
    struct Rational aa;
    aa.a = q1.a * q2.a;
    aa.b = q1.b * q2.b;
    return aa;
}

void reverse(Rational *i)
{
    int temp = i->a;
    i->a = i->b;
    i->b = temp;
}

Rational divide(Rational q1,Rational q2)
{
    struct Rational aa;
    aa.a=q1.a*q2.b;
    aa.b=q1.b*q2.a;
    if(aa.b==0)
    {
    	aa.b=1;
    	aa.a=0;
	}
    return aa;
}
int main()
{
    Rational a, b;
    getRational(&a);
    getRational(&b);
    print(add(a , b));
    simplify(&a);
    print(a);
    print(subtract(a,b));
    print(multiply(a,b));
    print(divide(a,b));
    reverse(&a);
    print(a);
    return 0;
}