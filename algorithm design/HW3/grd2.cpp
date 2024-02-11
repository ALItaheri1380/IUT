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
vector<int> Graph[maxn];
short int check = 0;
int n, u, v, Max;

int main() {
    while (true) {
        cin >> n;
        if (n == 0) return 0;
        Max = -1;
        check = 0;
        for (int i = 0; i < maxn; i++) Graph[i].clear();
        for (int i = 0; i < n; i++) {
            cin >> u >> v;
            Graph[u].push_back(v);
            Graph[v].push_back(u);
            Max = max(u, max(v, Max));
        }
        for (int i = 0; i <= Max + 2; i++) {if (Graph[i].size() % 2 == 1) {check = 1;break;}}
        cout << (check ? "NO\n" : "YES\n");
    }
}