#include<iostream>
#include<string>
using namespace std;
template<class T>
string myfun(T arr[],int SIZE,string z){/////tabe emtiazi : append kardan arraye ba string , dar soorati ke arraye aval biad
    string y;
    for (int i = 0; i < SIZE; i++)
    {
    y+=to_string(arr[i]);
    }
    return y+z;
}
template<class T>
string myfun(string z,T arr , int SIZE){/////tabe emtiazi : append kardan arraye ba string , dar soorati ke arraye enteha biad
   string y;
    for (int i = 0; i < SIZE; i++)
    {
    y+=to_string(arr[i]);
    }
    return z+y;
}

///////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
string myfun(string a, string b)
{
  return a.append(b);
}
string myfun(int a, string b)
{
  return to_string(a) + b;
}
string myfun(double a, string b)
{
  return to_string(a) + b;
}
string myfun(bool a, string b)//emtiazi
{
  string a2=to_string(a);
  return a2+b;
}
string myfun(string a, int b)
{
  return a+to_string(b);
}
string myfun(string a, double b)
{
  string b2= to_string(b);
  return a +b2;
}
string myfun(string a, bool b)//emtiazi
{
  string b2=to_string(b);
  return a +b2;
}
bool myfun(bool a, bool b)
{
  cout<<boolalpha;
  return a&&b;
}
int myfun(int a, int b)
{
  return a+b;
}
double myfun(double a, double b)
{
  return a+b;
}
double myfun(double x,int y){
    return x+y;
}
double myfun(int x,double y){
    return x+y;
}
template<class T2>
T2* myfun(T2 arr1[], T2 arr2[], int len_arr1, int len_arr2)//jame 2 ta arrey//
{
    T2* res = new T2[len_arr1 + len_arr2];
    for (int i = 0; i < len_arr1; i++)
    {
        res[i] = arr1[i];
    }
    for (int i = 0; i < len_arr2; i++)
    {
        res[len_arr1 + i] = arr2[i];
    }
    return res;

}
template<class T3>
T3* myfun(T3 arr1[], int len_array, T3 newadad) {//ezafe kardan addad  be enteha araye arr1 
    T3* res = new T3[len_array + 1];
    for (int i = 0; i < len_array; i++)
    {
        res[i] = arr1[i];
    }
    res[len_array] = newadad;
    return res;
}
template<class T4>
T4* myfun(T4 newadad, T4 arr1[], int len_array) {//ezafe kardan adad  be ebtedaie arrey arr1

    T4* res = new T4[len_array + 1];
    for (int i = 0; i < len_array; i++) {
        res[i+1] = arr1[i];
    }
    res[0] = newadad;
    return res;
}
int main() {
    double arr1[] = { 1.2,2.4,3.2,4.7,5.1 };
    double arr2[] = { 6,7,8.3 };
    int m, n;
    double x = 2;
    m = sizeof(arr1) / sizeof(arr1[0]);
    n = sizeof(arr2) / sizeof(arr2[0]);
    
    double *d=myfun(arr1, arr2, m, n);
    for (int  i = 0; i < m+n; i++)
    {
        cout<<d[i]<<" | ";
    }
    cout<<'\n';
    double*dd =myfun(x,arr1,m);
    for (int i = 0; i < m+1; i++)
    {
       cout<<dd[i]<<" | ";
    }
    cout<<'\n';
    double* ddd =myfun(arr1,m,x);
    for (int i = 0; i < m+1; i++)
    {
        cout<<ddd[i]<<" | ";
    }
    cout<<'\n';
    cout<<myfun(true,false)<<endl;
    string b="mmmmm";
    string a="ali";
    cout<<myfun(a,b)<<endl;
    cout<<myfun(2.3,5.5)<<endl;
    cout<<myfun(2,1.2)<<endl;
    cout<<myfun(2.5,1)<<endl;
    cout<<myfun(2,1)<<endl;
    cout<<myfun(a,2)<<endl;
    cout<<myfun(a,2.4)<<endl;
    cout<<myfun(2,b)<<endl;
    cout<<myfun(2.3,b)<<endl;
    cout<<myfun(arr1,5,b)<<endl;
    cout<<myfun(b,arr1,5)<<endl;
    cout<<myfun(a,false)<<endl;
    cout<<myfun(true,b)<<endl;
    delete(d);
    delete(dd);
    delete(ddd);
}