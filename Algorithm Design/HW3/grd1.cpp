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

bool compare(pair<pair<int,int>,double> a, pair<pair<int,int>,double> b) 
{return(a.second < b.second);}

int parent_find(int x, vector<int>& parent) 
{
    while(parent[x] != x)
        x = parent[x];
    return x;
}

void dfs(int u, vector<vector<int>>& adj, vector<bool>& visit) 
{
    visit[u] = true;
    for(auto v : adj[u]) if(!visit[v]) dfs(v, adj, visit);
}

int unite(int v1, int v2, vector<int>& parent, vector<int>& grade) 
{
    v2 = parent_find(v2, parent);
    v1 = parent_find(v1, parent); 
    if (v1 == v2) return 0; 
    if(grade[v1] < grade[v2]) swap(v1, v2);
    parent[v2] = v1;
    if(grade[v1] == grade[v2]) grade[v1]++;
    return 1; 
}

int main() 
{
    migmig
    int t;cin >> t;

    for(int i=1; i<=t; i++) 
    {
        int n, r;cin >> n >> r;

        vector<pair<int, int>> Graphland(n);
        vector<pair<pair<int,int>,double>> Graph;
        for(int j=0; j<n; j++) cin >> Graphland[j].first >> Graphland[j].second;
        for(int j=0; j<n; j++) {
            for(int k=j+1; k<n; k++) {
                double d = sqrt(pow(Graphland[j].first - Graphland[k].first, 2) + pow(Graphland[j].second - Graphland[k].second, 2));
                Graph.push_back({{j, k},d});
            }
        }

        sort(Graph.begin(), Graph.end() , compare);

        vector<int> parent(n) ,grade(n, 0);
        for(int j=0; j<n; j++) parent[j] = j;

        double tool_jade = 0 , tool_reil = 0;
        int num_states = 0;

        vector<vector<int>> adj(n);
        for(auto e : Graph) { 
            int u = e.first.first, v = e.first.second;
            double Weight = e.second;
            if(Weight <= r && parent_find(u, parent) != parent_find(v, parent)) {
                unite(u, v, parent, grade);
                tool_jade += Weight;
                adj[u].push_back(v);
                adj[v].push_back(u); 
            }
        }

        vector<bool> visit(n, false);
        for(int u=0; u<n; u++) { 
            if(!visit[u]) {
            dfs(u, adj, visit);
            num_states++;
        }
    }

    for(auto e : Graph) {
        int u = e.first.first, v = e.first.second;
        double Weight = e.second;
        if(Weight > r && parent_find(u, parent) != parent_find(v, parent)) {
            unite(u, v, parent, grade);
            tool_reil += Weight;

            adj[u].push_back(v); 
            adj[v].push_back(u);
        }
    }
    cout <<"Case #"<<i<<": "<<num_states<<' '<<
    round(tool_jade) <<' '<< round(tool_reil)<<'\n';
    }
}