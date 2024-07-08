#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define migmig ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define REP(i, a, b) for(int i=a;i<=b; i++)
#define F first
#define S second
typedef vector<int> vi;
typedef pair<int,int> pi;
typedef long long ll;
typedef long double ld;
const int inf = (int)1e9 + 7;
const long long INF = (long long)1e18 + 7; 
const int maxn=2*1e5+50;
vector<string> State, bk;
queue<string> Queue;

bool check(string ph)
{
    int fba = 0;
    for(int i = 0 ; i < ph.size() ; i++){
        if(ph[i] == '(') fba++;
        else if(ph[i] == ')') --fba;
        if(fba < 0 ) return false;
    }
    return (fba == 0);
}

void Bk(string ph)
{
    Queue.push(ph);
    State.pb(ph);
    bool b;
    int flag;

    while(!Queue.empty())
    {
        string cur = Queue.front();
        Queue.pop();

        if (check(cur)) {
            bk.pb(cur);
            b = true;
        }
        if(!b){
            for (int k = 0; k < cur.length(); k++) {
                string temp = cur.substr(0, k) + cur.substr(k + 1);
                if (find(State.begin(), State.end(), temp) == State.end()) {
                    Queue.push(temp);
                    State.pb(temp);
                }
            }
        }
    }
}
int main()
{
    migmig
    string str;
    cin>>str;
    Bk(str);
    for (auto x : bk)  cout << x << endl;
}