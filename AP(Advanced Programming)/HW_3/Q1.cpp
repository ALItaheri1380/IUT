#include<iostream>
#include<string>
using namespace std;
class Time {
private:
    int h;
    int m;
public:
    Time(int h1, int m1) {
        if (h1 >= 24 || m1 > 59 || h1<0 || m1<0) {
            cout << "invalid input\n";
            exit(0);
        }
        h = h1;
        m = m1;
    }
    Time(int h1) {
        if (h1 >= 24 || h1<0) {
            cout << "invalid input\n";
            exit(0);
        }
        h = h1;
        m = 0;
    }
    void setter(int h1, int m1) {
        if (h1 >= 24 || m1 > 59 || h1<0 || m1<0) {
            cout << "invalid input\n";
            exit(0);
        }
        h = h1;
        m = m1;
    }
    void set_h(int h1) { 
        if(h1 >= 24 || h1<0){
            cout << "invalid input\n";
            exit(0);
        }
        h = h1;
    }
    void set_m(int m1) {
        if(m1>59 || m1<0){
            cout << "invalid input\n";
            exit(0);
        }
        m = m1;
    }
    string get_h_m() {
        string m2;
        if (m < 10) {
            m2 += '0';
            m2 += to_string(m);
        }
        else {
            m2 = to_string(m);
        }
        return to_string(h) + " : " + m2;
    }
    string get_h() { return to_string(h); }
    string get_m() { return to_string(m); }
    void compear(Time x) {
        if (x.h < h) {
            cout << "sate ersali koochek tare :)\n";
        }
        else if (h == x.h) {
            if (x.m > m) {
                cout << "sate ersali bozorgtare tare :)\n";
            }
            else if(x.m==m){
                cout<<"satha barabarand :)\n";
            }
            else {
                cout << "sate ersali koochek tare:)\n";

            }
        }

        else
            cout << "sate ersali bozorgtare tare:)\n";
    }
    string what_time() {
        if (h >= 0 && h < 12) {
            return "sobh";
        }
        if (h == 12) {
            if (m == 0) {
                return "zohr";
            }
        }
        if (12 <= h && h < 17) {
            return "bade zohr";
        }
        if (17 <= h && h < 20)
        {
            return "asr";
        }
        if (20 <= h && h < 24) {
            return "shab";
        }
    }

};
int main() {
    Time k2{23,60 };
    Time k{ 12,2 };
    k.compear(k2);
    cout << k.get_h_m() << endl;
    cout<<k2.get_h_m() << endl;
    cout << k.what_time()<<endl;
    cout<<k2.what_time()<<endl;
}