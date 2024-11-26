#include <iostream>
using namespace std;
class S
{
private:
    static S *instances[2];
    static int kol;
    float data = 0;
    S() {}
public:
    S(S const &) = delete;
    void operator=(S const &) = delete;

    static S &makeInstance()
    {
        if (kol >= 2)
            return *(instances[0]);
        instances[kol] = new S;
        kol++;
        return *(instances[kol - 1]);
    }

    static S &getInstance(int index)
    {
        return *(instances[index]);
    }

    float getData()
    {
        return data;
    }

    void setData(float _data)
    {
        data = _data;
    }
};
int S::kol = 0;
S *S::instances[2];

int main()
{
    S &a = S::makeInstance();
    a.setData(10);
    S &b = S::makeInstance();
    b.setData(20);
    S &c = S::makeInstance();
    S &d = S::getInstance(1);
    cout << "a = " << a.getData() << endl;
    cout << "b = " << b.getData() << endl;
    cout << "c = " << c.getData() << endl;
    cout << "d = " << d.getData() << endl;
}