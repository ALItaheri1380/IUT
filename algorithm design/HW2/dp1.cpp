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
int Max = 0 , temp;
int arr[1000][1000];
int dp[1000][1000];

void zero(int satr , int sotoon)
{
    for (int i = 0; i <= satr; i++)
        for (int j = 0; j <= sotoon; j++) dp[i][j] = 0; 
}
int Dp(int satr , int sotton)
{
    for (int i = 0; i < sotton; i++) dp[0][i] = 1;
    for (int i = 0; i <= satr; i++) dp[i][0] = 1;
    for (int i = 1; i <=satr; i++)
        for (int j = 1; j < sotton; j++)
            dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % 1000000; 
    return dp[satr][sotton - 1];
}

int main()
{
    while (true)
    {
        int satr, sotoon;cin>>satr>>sotoon;
        if(satr == 0 && sotoon ==0 ) return 0;
        cout<<Dp(satr , sotoon)<<endl;
        zero(satr , sotoon);
    }
}