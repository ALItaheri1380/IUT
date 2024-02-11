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

int Dp(int satr , int sotoon)
{
    for (int i = 1; i < satr + 1; i++)
        for (int j = 1; j < sotoon + 1; j++)
            if(arr[i][j] == 0)
            {
                temp = 1 + min(min(dp[i-1][j] , dp[i][j-1]) , dp[i-1][j-1]);
                dp[i][j] = temp;
                Max = max(temp , Max);
            }
    return Max;
}
int main()
{
    int satr ,sotoon;cin>>satr>>sotoon;
    for (int i = 1; i < satr + 1; i++)
        for (int j = 1; j < sotoon + 1; j++) cin>>arr[i][j];
    cout<<Dp(satr , sotoon);
}