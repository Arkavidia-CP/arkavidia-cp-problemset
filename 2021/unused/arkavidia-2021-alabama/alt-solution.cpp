#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define MOD 1000000007
#define INF 1234567890
#define pii pair<int,int>
#define LL long long
using namespace std;

const int N = 5000;
vector<int> adj[N+5];
int in[N+5];
int par[N+5];

int main () {
    //clock_t start = clock();
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    memset(in,0,sizeof(in));
    memset(par,0,sizeof(par));
    int n;
    cin >> n;
    for (int i=1;i<=n;i++) {
        int k;
        cin >> k;
        while (k--) {
            int x;
            cin >> x;
            adj[i].pb(x);
            in[x]++;
        }
    }
    // for (int i=1;i<=n;i++) {
    //     cout << i << " => ";
    //     for (auto x : adj[i]) {
    //         cout << x << " ";
    //     }
    //     cout << endl;
    // }
    queue<int> q;
    for (int i=1;i<=n;i++) {
        if (in[i] == 0) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (auto des : adj[cur]) { // descendants
            in[des]--;
            if (in[des] == 0) q.push(des);
            par[des] = cur;
        }
    }
    // cout << "ANSWER:" << endl;
    for (int i=1;i<=n;i++) cout << par[i] << " ";
    cout << endl;
    //cerr << fixed << setprecision(3) << (clock()-start)*1./CLOCKS_PER_SEC << endl;
    return 0;
}
/*
3
2 2 3
1 3
0

4
1 3
1 4
0
0

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