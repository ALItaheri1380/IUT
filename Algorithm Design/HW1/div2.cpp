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

int divide_and_conquer(int D, int I, int node)
{
    if(D == 0) return node;
    return divide_and_conquer(--D, (I + 1) /2, (I%2==0)? node*2 + 1:node*2);
}
int main() {
    migmig
    
    int L , D , I , node;
    cin >> L;
    for (int o = 0; o < L; o++)
    {
        node = 1;
        cin >> D >> I;D--;
        cout<<divide_and_conquer(D, I, node)<<endl;
    }
}