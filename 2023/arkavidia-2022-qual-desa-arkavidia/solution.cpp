#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    int ans = 0;
    function<int(int, int)> dfs = [&](int u, int p) {
        int res = 2;
        for (int v : adj[u]) {
            if (v == p) {
                continue;
            }
            res = min(res, dfs(v, u));
        }
        // Having a leaf neighbor
        if (res == 0) {
            ans++;
            return 1;
        }
        // Having at least one that is a guard
        if (res == 1) {
            return 2;
        }
        // Must be a leaf
        return 0;
    };
    if (dfs(1, 1) == 0) {
        ans++;
    }
    cout << ans << '\n';
    
    return 0;
}