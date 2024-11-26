#include <bits/stdc++.h>
using namespace std;

class Person{
protected:
        int age;
        string name;
    public:
        virtual void getdata(){}
        virtual void putdata(){}
};
class Professor:public Person{
private:
    int share;
    static int flag;
    int curid;
public:
    void getdata(){
        flag++;
        string line;
        getline( cin, line );
        getline( cin, line );
        istringstream is( line );
        is>>name;
        is>>age;
        is>>share;
        curid=Professor::flag;
    }
    void putdata(){
        cout<<name<<" "<<age<<" "<<share<<" "<<curid<<'\n';
    }
};
class Student : public Person{
    int marck[6];
    static int flag;
    int curid;
public:
    void getdata(){
        flag++;
        string line;
        getline( cin, line );
        getline( cin, line );
        istringstream is( line );
        is>>name;
        is>>age;
        int i=0;
        while(is>>marck[i]){
            i++;
        }
        curid=Student::flag;
    }
    int sum(int a[]){
        int s=0;
        for (int i = 0; i < 6; ++i) {
            s+=a[i];
        }
        return s;
    }
    void putdata(){
        int SUM= sum(marck);
        cout<<" "<<name<<" "<<age<<" "<<SUM<<" "<<curid<<endl;
    }

};
int Student::flag(0);
int Professor::flag(0);
int main(){

    int n, val;
    cin>>n; //The number of objects that is going to be created.
    Person *per[n];

    for(int i = 0;i < n;i++){

        cin>>val;
        if(val == 1){
            // If val is 1 current object is of type Professor
            per[i] = new Professor;

        }
        else per[i] = new Student; // Else the current object is of type Student

        per[i]->getdata(); // Get the data from the user.

    }

    for(int i=0;i<n;i++)
        per[i]->putdata(); // Print the required output for each object.

    return 0;

}