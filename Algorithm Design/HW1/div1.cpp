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

int binary_search(int* arr, int low, int high, int key) {
    if (high >= low) {
        int mid = (high + low) / 2;
        if (arr[mid] == key) return mid;
        else if (arr[mid] > key) return binary_search(arr, low, mid - 1, key);
        else return binary_search(arr, mid + 1, high, key);
    }
    return -1; 
}

bool concur(int* arr , int low , int high, int K) {
    int i = low , j = high;
    while (i < j) {
        if (arr[i] + arr[j] == K) return true;
        else if (arr[i] + arr[j] > K) j--;
        else i++;
    }
    return false;  
}

bool Divide(int* arr , int low , int high, int K) {
    if (low > high) return false;
    
    int mid = ((low + high) / 2);
    int res = K - arr[mid];
    
    if (binary_search(arr , low , mid - 1 , res) != -1) return true;
    if (binary_search(arr , mid + 1 , high , res) != -1) return true;
    
    return (Divide(arr , low , mid - 1, K) || Divide(arr , mid + 1 , high, K));
}

int main() {
    migmig
    
    int N, K;
    cin >> N >> K;
    vi arr(N);
    REP(i, 0, N - 1) cin >> arr[i];
    sort(arr.begin(), arr.end());

    if (Divide(arr.data(), 0 , N - 1, K)) cout << "YES";
    else concur(arr.data(), 0 , N - 1, K) ? cout << "YES" : cout << "NO";
}