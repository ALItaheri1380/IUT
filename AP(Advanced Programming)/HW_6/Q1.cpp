#include<iostream>
#include<string>
using namespace std;
class Time {
private:
    int h;
    int m;
public:
    Time(int h1=0, int m1=0) {
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
    string get_h() { return to_string(h); }
    string get_m() { return to_string(m); }
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
	operator string() const { 
        string m2;
        string h2;
        if(h<10){
           h2='0';
           h2+=to_string(h);
        }
        else{
            h2=to_string(h);
        }
        if (m < 10) {
            m2 += '0';
            m2 += to_string(m);
        }
        else {
            m2 = to_string(m);
        }
        return h2 + " : " + m2;
	 }
    //--------------------------------------------------------------------//
    friend bool operator> (const Time& c1,const Time& c2);
    friend bool operator>= (const Time& c1,const Time& c2);
    friend bool operator<= (const Time& c1,const Time& c2);
    friend bool operator< (const Time& c1,const Time& c2);
    Time operator+(Time& op1){

            Time temp;
            int chek=0;
            int chek2=0;
            if (op1.h+h>=24)
            {
                temp.h=(op1.h+h)%24;
                if(op1.m+m>=60){
                    temp.m=(op1.m+m)-60;
                    temp.h++;
                }
                else
                    temp.m=(op1.m+m);
                chek++;
            } 
            if(op1.m+m>=60&&chek==0){
                temp.h=op1.h+h;
                temp.m=(op1.m+m)-60;
                temp.h++;
                chek2++;
            }
            if(chek2==0&&chek==0){
                temp.h= op1.h+h;
                temp.m= op1.m+m;
            }
            return temp;

}
    friend ostream & operator << (ostream &out,  Time &c);

    friend istream & operator >> (istream &in,  Time&c);
};
bool operator>=(const Time& op1,const Time& op2){
    if(op1.h>op2.h)
       return true;
    else if(op1.h==op2.h){
        if(op1.m>op2.m)
           return true;
        else if(op1.m==op2.m)
           return true;   
        else
           return false;   
    }    
    else
        return false;   
}
bool operator>(const Time& op1,const Time& op2){
    if(op1.h>op2.h)
       return true;
    else if(op1.h==op2.h){
        if(op1.m>op2.m)
           return true;
        else
           return false;   
    }    
    else
        return false;   
}
bool operator<(const Time& op1,const Time& op2){
    if(op1.h<op2.h)
       return true;
    else if(op1.h==op2.h){
        if(op1.m<op2.m)
           return true;
        else
           return false;   
    }    
    else
        return false; 
}
bool operator<=(const Time& op1,const Time& op2){
    if(op1.h<op2.h)
       return true;
    else if(op1.h==op2.h){
        if(op1.m<op2.m)
           return true;
        if(op1.m==op2.m)
           return true;   
        else
           return false;   
    }    
    else
        return false; 
}
istream & operator >> (istream &in,  Time&time_)
{
    cout << "Enter YOUR HOUR \n";
    in >> time_.h;
    if(time_.h>=24||time_.h<0){
        cout<<"invalid input\n";
        exit(0);
    }
    cout << "Enter YOUR Min \n";
    in >> time_.m;
    if (time_.m>=60||time_.m<0)
    {
        cout<<"invalid input\n";
        exit(0);        
    }
    return in;
}
ostream & operator << (ostream &out,  Time &time_)
{   
        out<< string(time_)+"     the time of day is :  "+time_.what_time();
        return out;
}
int main() {
    Time t;
    cin>>t;
    cout<<t;
    cout<<"\n+--+-+-+-+-+-+--+---+-+-+-+-++--+-+-+-+-+-+-+-+-+\n";
    Time t2;
    cin>>t2;
    cout<<t2;
    cout<<"\n//-+-+---+-++-+-+-+---+++--++-+--+-+-+-+-+-+-+-+-++-+\n";
    Time t3;
    t3=t+t2;
    cout<<"T+T2 IS = "<<t3<<endl;
    cout<<boolalpha<<(t>t2)<<endl;
}