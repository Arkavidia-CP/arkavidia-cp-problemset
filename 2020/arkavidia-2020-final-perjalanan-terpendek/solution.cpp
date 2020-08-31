#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;
int n, m, dist[N], num[N], root;
long long dp[N];
vector<int> adjList[N];
bool vis[N];

void dfs(int v){
    if(adjList[v].size() == 1 && root != v){
        num[v] = 0;
    } else {
        for(auto x : adjList[v]){
            if(!vis[x]){
                vis[x] = 1;
                dfs(x);
                num[v] += 1 + num[x];
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    cin >> n >> m;
    for(int i = 1; i <= n - 1; i++){
        int a, b;
        cin >> a >> b;
        adjList[a].push_back(b);
        adjList[b].push_back(a);
    }

    vis[1] = 1;
    root = 1;
    dfs(1);
    for(int i = 1; i <= n; i++){
        vis[i] = 0;
    }

    dist[1] = 0;
    vis[1] = 1;
    queue<int> q;
    q.push(1);
    while(!q.empty()){
        int fr = q.front();
        q.pop();

        for(auto x : adjList[fr]){
            if(!vis[x]){
                vis[x] = 1;
                dist[x] = dist[fr] + 1;
                q.push(x);
            }
        }
    }

    for(int i = 1; i <= n; i++){
        dp[1] += (long long) dist[i];
        vis[i] = 0;
    }

    q.push(1);
    vis[1] = 1;
    while(!q.empty()){
        int fr = q.front();
        q.pop();

        for(auto x : adjList[fr]){
            if(!vis[x]){
                vis[x] = 1;
                dp[x] = dp[fr] + (long long) (n - 2 * num[x] - 2);
                q.push(x);
            }
        }
    }
    int idx = -1;
    long long fmin = dp[1];
    for(int i = 2; i <= n; i++){
        fmin = min(fmin, dp[i]);
    }
    for(int i = 1; i <= n; i++){
        if(dp[i] == fmin){
            idx = i;
            break;
        }
    }

    cout << idx << " " << fmin << '\n';
    return 0;
}
