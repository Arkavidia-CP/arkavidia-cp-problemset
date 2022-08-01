/** 
*   Author  : Muhammad Kamal Shafi
*   Problem : Panen Buah
**/
#include <bits/stdc++.h>


#define fi first
#define se second
#define pb(a) push_back(a)
#define mp(a, b) make_pair(a, b)
#define el '\n'

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pil = pair<int, ll>;
using pli = pair<ll, int>;

const int N = 2e5 + 10;

int n;
vector<pil> adj[N];
bool bisa[N];

pli dfs_diameter(int node, int p, ll dist){
    pli ret = mp(dist, node);
    for (auto x : adj[node]){
        if (x.fi == p) continue;
        auto cur = dfs_diameter(x.fi, node, dist + x.se);
        if (cur.fi > ret.fi){
            ret = cur;
        } else if (cur.fi == ret.fi){
            ret.se = min(ret.se, cur.se);
        }
    }
    return ret;
}
ll ddist;
bool dfs_mark(int node, int p, ll dist){
    bool ret = 0;
    for (auto x : adj[node]){
        if (x.fi == p) continue;
        ret |= dfs_mark(x.fi, node, dist + x.se);
    }
    if (dist == ddist) ret = 1;
    if (ret){
        bisa[node] = 1;
    }
    return ret;
}

vector<int> ans;
void solve(int node, int p, bool dobel){
    ans.pb(node);
    int nbisa = -1;
    vector<pil> nx;
    for (auto x : adj[node]){
        if (x.fi == p) continue;
        if (!dobel && bisa[x.fi]) nbisa = max(nbisa, x.fi);
        nx.pb(x);
    }
    sort(nx.begin(), nx.end());
    for (auto x : nx){
        if (x.fi == p || x.fi == nbisa) continue;
        solve(x.fi, node, 1);
        ans.pb(node);
    }
    if (nbisa != -1) solve(nbisa, node, 0);
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    ll tot = 0;
    for (int i=1;i<n;i++){
        int a, b;
        ll w;
        cin >> a >> b >> w;
        adj[a].pb(mp(b, w));
        adj[b].pb(mp(a, w));
        tot += w;
    }
    tot *= 2LL;
    auto snode = dfs_diameter(1, 1, 0);
    {
        auto temp = dfs_diameter(snode.se, snode.se, 0);
        snode.fi = temp.fi;
        if (snode.se > temp.se){
            snode = temp;
        }
    }
    tot -= snode.fi;
    ddist = snode.fi;
    dfs_mark(snode.se, snode.se, 0);
    solve(snode.se, snode.se, 0);
    cout << tot << el;
    cout << ans.size() << el;
    for (int i=0;i<ans.size();i++){
        cout << ans[i];
        if (i != (int) ans.size() - 1) cout << " ";
    }
    cout << el;

    return 0;
}