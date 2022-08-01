#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define MOD 1e17
#define INF 1234567890
#define pii pair<LL,LL>
#define LL long long
using namespace std;

// ans = 2 * length - diameter
const LL MAXN = 200000;

vector<pii> adj[MAXN + 5];
LL vis[MAXN + 5];
bool diam[MAXN + 5];
vector<LL> ans;
LL start, fin;
vector<LL> finish;

void dfs(LL cur) {
    vis[cur] = 1;
    ans.pb(cur);
    sort (adj[cur].begin(), adj[cur].end());
    LL biggestdiam = 0; // biggest flagged node
    for (LL i=0;i<adj[cur].size();i++) {
        pii next = adj[cur][i];
        if (diam[next.fi] == 1 && !vis[next.fi]) biggestdiam = max(biggestdiam, next.fi);
    }
    // cout << cur << " " << biggestdiam << endl;
    for (LL i=0;i<adj[cur].size();i++) {
        pii next = adj[cur][i];
        if (vis[next.fi] == 0 && next.fi != biggestdiam) {
            dfs(next.fi);
            ans.pb(cur);
        }
    }
    // dfs ke biggest diam kalo ada
    if (vis[biggestdiam] == 0 && biggestdiam != 0) {
        dfs(biggestdiam);
        ans.pb(cur);
    }
}

int main () {
    //clock_t start = clock();
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    LL n;
    cin >> n;
    LL len = 0;
    map<pii, LL> m;    // nyimpen weight buat edge tertentu
    for (LL i=1;i<n;i++) {
        LL x,y,w;
        cin >> x >> y >> w;
        m[{x, y}] = w;
        m[{y, x}] = w;
        adj[x].pb({y, w});
        adj[y].pb({x, w});
        len += 2*w;
    }

    // dijkstra dari node 1, ambil ujungnya
    priority_queue<pii, vector<pii>, greater<pii>> s;
    s.push({0, 1});
    for (LL i=1;i<=n;i++) vis[i] = MOD;
    vis[1] = 0;
    while (!s.empty()) {
        LL cur = s.top().se;
        s.pop();
        for (LL i=0;i<adj[cur].size();i++) {
            pii next = adj[cur][i];
            if (vis[cur] + next.se < vis[next.fi]) {
                vis[next.fi] = vis[cur] + next.se;
                s.push({vis[cur] + next.se, next.fi});
            }
        }
    }
    LL maxvis = 0, nod = INT_MAX;
    for (LL i=1;i<=n;i++) {
        if (vis[i] > maxvis) {
            maxvis = vis[i];
            nod = i;
        }
    }

    // dijkstra dari salah satu ujung, ambil ujung satunya lagi
    s.push({0, nod});
    for (LL i=1;i<=n;i++) vis[i] = MOD;
    vis[nod] = 0;
    while (!s.empty()) {
        LL cur = s.top().se;
        s.pop();
        for (LL i=0;i<adj[cur].size();i++) {
            pii next = adj[cur][i];
            if (vis[cur] + next.se < vis[next.fi]) {
                vis[next.fi] = vis[cur] + next.se;
                s.push({vis[cur] + next.se, next.fi});
            }
        }
    }
    maxvis = 0;
    LL nod2 = INT_MAX;
    for (LL i=1;i<=n;i++) {
        if (vis[i] > maxvis) {
            maxvis = vis[i];
            nod2 = i;
        }
    }

    // diameternya diawali oleh salah satu ujung (yang paling kecil indexnya), flag semua node dalem semua possible diameter (backtrack dari semua possible ujung)
    start = min(nod, nod2);
    LL par[n+5];
    memset (par,0,sizeof(par));
    s.push({0, start});
    for (LL i=1;i<=n;i++) vis[i] = MOD;
    vis[start] = 0;
    while (!s.empty()) {
        LL cur = s.top().se;
        s.pop();
        for (LL i=0;i<adj[cur].size();i++) {
            pii next = adj[cur][i];
            if (vis[cur] + next.se < vis[next.fi]) {
                par[next.fi] = cur;
                vis[next.fi] = vis[cur] + next.se;
                s.push({vis[cur] + next.se, next.fi});
            }
        }
    }
    maxvis = 0;
    for (LL i=1;i<=n;i++) {
        maxvis = max(maxvis, vis[i]);
    }
    for (LL i=1;i<=n;i++) {
        if (vis[i] == maxvis) finish.pb(i);
    }
    memset (diam, 0, sizeof(diam));
    for (LL i=0;i<finish.size();i++) {
        // cout << i << endl;
        fin = finish[i];
        while (fin != start && fin >= 1) {
            diam[fin] = 1;
            if (i == 0) len -= m[{fin,par[fin]}];
            fin = par[fin];
            // cout << fin << " " << diam[fin] << endl;
            if (i > 0 && diam[fin]) break;
        }
        diam[start] = 1;
    }
    // for (LL i=1;i<=n;i++) cout << diam[i] << " ";
    // cout << endl;

    memset(vis,0,sizeof(vis));
    dfs(start);
    
    cout << len << endl;
    vector<LL> temp;
    // cout << ans[0] << " ";
    temp.pb(ans[0]);
    for (LL i=1;i<ans.size();i++) {
        // cout << ans[i] << " ";
        temp.pb(ans[i]);
        len -= m[{ans[i], ans[i-1]}];
        if (len == 0) break;
    }
    cout << temp.size() << endl;
    for (LL i=0;i<temp.size();i++){
        cout << temp[i];
        if (i != (LL) temp.size() - 1) cout << " ";
    }
    cout << endl;

    //cerr << fixed << setprecision(3) << (clock()-start)*1./CLOCKS_PER_SEC << endl;
    return 0;
}