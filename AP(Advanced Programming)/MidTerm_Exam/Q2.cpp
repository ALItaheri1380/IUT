#include<iostream>
#include<string>
using namespace std;

class Rational {
private:
    int a;
    int b;
public:
    Rational() :a{ 0 }, b{ 1 }
    {

    }
    friend istream& operator >> (istream& in, Rational& x);
    friend Rational subtract(Rational q1, Rational q2);

    void print()
    {
    	if(b<0)
    	{
    		b*=-1;
    		a*=-1;
		}
        cout << a << "/" << b << endl;
    }
};
int main() {
    Rational p1;
    Rational p2;
    cin >> p1;
    cin >> p2;
    Rational temp = subtract(p1, p2);
    temp.print();

}
int bmm(int a, int b)
{
    if (b == 0)
        return a;
    return bmm(b, a % b);
}
istream& operator >> (istream& in, Rational& x) {
    string y;
    in >> y;
    string m = "";
    int i = 0;
    while (y[i] != '/')
    {
        m += y[i];
        i++;
    }
    i++;
    x.a = stoi(m);
    m = "";
    for (; i < y.size(); i++)
    {
        m += y[i];
    }
    x.b = stoi(m);
    if (x.b == 0)
        x.b = 1;
    return in;
}
Rational subtract(Rational q1, Rational q2) {
    Rational aa;
    aa.a = (q1.a * q2.b) - (q1.b * q2.a);
    aa.b = q1.b * q2.b;
    int g = bmm(aa.a, aa.b);
    aa.a /= g;
    aa.b /= g;
    return aa;
}