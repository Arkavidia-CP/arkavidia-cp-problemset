/** 
*   Author  : Muhammad Hasan (mhasan01)
*   Problem : Subgraph Divisibilty
**/
#include <bits/stdc++.h>

using namespace std;

const int N = 3e5 + 5;
const int MOD = 4;

int n, m;
int a[N];
vector<int> adj[N];
vector<int> dp[N][MOD];
bool vis[N];

// checks whether this node has a solution already
// if it has than terminate the program
void check(int u) {
    if ((int) dp[u][0].size() <= 1) return;
    vector<int>& answer = dp[u][0];
    int len = answer.size();
    cout << len << '\n';
    for (int i = 0; i < len; i++) {
        cout << answer[i] << (i == len - 1 ? '\n' : ' ');
    }
    exit(0);
}

void dfs(int u, int p) {
    vis[u] = 1;
    // take the value of it node itself
    dp[u][a[u]] = {u};
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
        // temp is the current/unchanged state for dp[u]
        // i.e. temp[x] = dp[u][x]
        vector<vector<int>> temp(MOD);
        for (int it = 0; it < MOD; it++) {
            temp[it] = dp[u][it];
        }
        // do dynamic programming with it's child
        for (int i = 0; i < MOD; i++) {
            // rename current/unchanged dp state dp[u][i] = temp[i] to parent
            vector<int>& parent = temp[i];
            // if we don't have any node in parent to merge with the child then skip
            if (parent.empty()) continue;
            for (int j = 0; j < MOD; j++) {
                // rename dp[v][j] as child
                vector<int>& child = dp[v][j];
                // if we don't have any node in child to merge with the parent then skip
                if (child.empty()) continue;
                int k = (i + j) % MOD;
                vector<int>& new_dp = dp[u][k];
                // if the solution for (x mod MOD) = k has length > 1
                // don't make it longer and just skip it
                if ((int) new_dp.size() > 1) continue;
                // check if empty to handle duplicates
                if (new_dp.empty()) new_dp.insert(new_dp.end(), parent.begin(), parent.end());
                new_dp.insert(new_dp.end(), child.begin(), child.end());
            }
        }
        check(u);
    }
    check(u);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] %= MOD;
    }
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        dfs(i, i);
    }
    cout << -1 << '\n';

    return 0;
}