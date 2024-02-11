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
vector<string> bk;

void BK(int n, int h, string s) {
    if (n == 0 && h == 0) {bk.pb(s);return;}
    if (n > 0 && h > 0) BK(n - 1, h - 1, s + "1");
    if (n > 0 && n > h) BK(n - 1, h, s + "0");
}

int main() {
    int t;cin >> t;
    for (int i = 0; i < t; i++) {
        int n, h;cin >> n >> h;
        bk.clear();
        BK(n, h, "");
        sort(bk.begin(), bk.end());
        for(int i = 0 ; i < bk.size() ; i++) cout<<bk[i]<<endl;
        if (i < t - 1) cout << endl;
    }
}