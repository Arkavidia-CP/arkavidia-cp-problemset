#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e3 + 5;
vector<int> adj[N];
bool is_anc[N][N];// true if i ancestornya j
int n;
int ans[N];

// forests itu old forests
vector<int> addTree(int q, vector<int> forests) {
    vector<int> desc, ndesc, ret;
    // cout << "ADDING " << q << '\n';
    for (auto t: forests) {
        if (is_anc[q][t]) {
            desc.push_back(t);
        } else {
            ndesc.push_back(t);
        }
    }
    if (desc.empty()) {
        bool parentless = true;
        for (auto t: forests) {
            if (is_anc[t][q]) {
                ret = forests;
                adj[t] = addTree(q, adj[t]);
                parentless = false;
                break;
            }
        }
        if (parentless) {
            ret = forests;
            ret.push_back(q);
        }
    } else { // jadi root tree himpunan forest baru
        ret = ndesc;
        ret.push_back(q);
        for (auto t: desc) {
            adj[q] = addTree(t, adj[q]);
        }
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    // tcnya asumsi complete, bukan yg harus di process:
    // cth yg di process: x anc y, y anc z. tapi di tc nya ga ada x anc z.
    // cth complete: x anc y z, y anc z
    // dijamin ga ada i ancestor i
    // pasti ada jawaban (1 tree)
    cin >> n;
    for (int u = 1; u <= n; u++) {
        int sz;
        cin >> sz;
        for (int j = 0; j < sz; j++) {
            int v;
            cin >> v;
            is_anc[u][v] = true;
        }
    }

    vector<int> forests;
    for (int i = 1; i <= n; i++) {
        forests = addTree(i, forests);
    }
    for (int u = 1; u <= n; u++) {
        for (int v: adj[u]) {
            ans[v] = u;
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i];
        if (i == n) cout << '\n';
        else cout << ' ';
    }
    return 0;
}

/*
9
8 2 3 4 5 6 7 8 9
5 5 6 7 8 9
1 4
0
0
3 7 8 9
1 8
0
0
*/ 