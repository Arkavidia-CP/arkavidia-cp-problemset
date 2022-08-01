// Author: Muhammad Hasan
#include <bits/stdc++.h>

using namespace std;

const long long INF = 1e18;

struct Edge {
    int from, to;
    long long capacity, cost;
    Edge(int from, int to, long long cap, long long cost) : 
    from(from), to(to), capacity(cap), cost(cost) { }
};

vector<vector<int>> adj;
vector<vector<long long>> cost, capacity;

void shortest_paths(int n, int v0, vector<long long>& d, vector<int>& p) {
    d.assign(n, INF);
    d[v0] = 0;
    vector<bool> inq(n, false);
    queue<int> q;
    q.emplace(v0);
    p.assign(n, -1);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;
        for (int v : adj[u]) {
            if (capacity[u][v] > 0 && d[v] > d[u] + cost[u][v]) {
                d[v] = d[u] + cost[u][v];
                p[v] = u;
                if (!inq[v]) {
                    inq[v] = true;
                    q.emplace(v);
                }
            }
        }
    }
}

long long min_cost_flow(int N, const vector<Edge>& edges, long long K, int s, int t) {
    adj.assign(N, vector<int>());
    cost.assign(N, vector<long long>(N, 0));
    capacity.assign(N, vector<long long>(N, 0));
    for (Edge e : edges) {
        adj[e.from].emplace_back(e.to);
        adj[e.to].emplace_back(e.from);
        cost[e.from][e.to] = e.cost;
        cost[e.to][e.from] = -e.cost;
        capacity[e.from][e.to] = e.capacity;
    }

    long long flow = 0;
    long long cost = 0;
    vector<long long> d;
    vector<int> p;
    while (flow < K) {
        shortest_paths(N, s, d, p);
        if (d[t] == INF)
            break;

        // find max flow on that path
        long long f = K - flow;
        int cur = t;
        while (cur != s) {
            f = min(f, capacity[p[cur]][cur]);
            cur = p[cur];
        }

        // apply flow
        flow += f;
        cost += f * d[t];
        cur = t;
        while (cur != s) {
            capacity[p[cur]][cur] -= f;
            capacity[cur][p[cur]] += f;
            cur = p[cur];
        }
    }

    // if (flow < K) return -1;
    return cost;
}

long long binpow(long long x, int y) {
    long long ret = 1;
    while (y > 0) {
        if (y % 2 == 1) ret = (ret * x);
        y /= 2;
        x = (x * x);
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> v(m + 1);
    for (int i = 1; i <= m; i++) {
        cin >> v[i].first >> v[i].second;
    }
    vector<Edge> edges;
    int nodes = m + n + m * n + 5;
    int source = 0, sink = nodes - 1;
    for (int i = 1; i <= m; i++) {
        edges.emplace_back(source, i, 1, 0);
        for (int val = v[i].first; val <= v[i].second; val++) {
            edges.emplace_back(i, m + val, 1, 0);
        }
    }
    vector<long long> pre(m + 1);
    for (int it = 0; it <= m; it++) {
        pre[it] = binpow(it, 7);
    }
    int curNode = 1 + m + n; // intermediate node from val to sink
    for (int val = 1; val <= n; val++) {
        for (int it = 1; it <= m; it++) {
            edges.emplace_back(m + val, ++curNode, 1, 0);
            edges.emplace_back(curNode, sink, 1, pre[it] - pre[it - 1]);
        }
    }
    long long d = min_cost_flow(nodes, edges, INF, source, sink);
    vector<int> ans(m + 1, -1);
    for (int i = 1; i <= m; i++) {
        for (int val = v[i].first; val <= v[i].second; val++) {
            if (capacity[i][m + val] == 0)
                ans[i] = val;
        }
        assert(ans[i] != -1);
    }
    cout << d << '\n';
    for (int i = 1; i <= m; i++) {
        cout << ans[i] << " \n"[i == m];
    }

    return 0;
}