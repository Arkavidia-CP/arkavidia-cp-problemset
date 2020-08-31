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

vector<vector<int>> vis;
vector<vector<int>> cnt;

int count(int r1, int c1, int r2, int c2) {
    return cnt[r2][c2] - cnt[r1-1][c2] - cnt[r2][c1-1] + cnt[r1-1][c1-1];
}

bool bisa(int r1, int c1, int r2, int c2) {
    /*
    K-
    -O
    */
    if ((r1 > r2 && c1 > c2) || (r1 < r2 && c1 < c2)) {
        if (r1 > r2) {
            swap(r1, r2);
            swap(c1, c2);
        }
        if (count(r1,c1,r1,c2) + count(r1,c2,r2,c2) == 0 || count(r1,c1,r2,c1) + count(r2,c1,r2,c2) == 0) return 1; else return 0;
    } else {
        if (r1 > r2) {
            swap(r1, r2);
            swap(c1, c2);
        }
        if (count(r1,c2,r2,c2) + count(r1,c2,r1,c1) == 0 || count(r2,c2,r2,c1) + count(r1,c1,r2,c1) == 0) return 1; else return 0;
    }
}

int main () {
    //clock_t start = clock();
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int r,c;
    cin >> r >> c;
    vis.resize(r+5);
    for (int i=0;i<=r;i++) {
        vis[i].resize(c+5);
    }
    cnt.resize(r+5);
    for (int i=0;i<=r;i++) {
        cnt[i].resize(c+5);
    }
    for (int i=0;i<=r;i++) {
        for (int j=0;j<=c;j++) {
            vis[i][j] = 0;
            cnt[i][j] = 0;
        }
    }
    char m[r+5][c+5];
    for (int i=1;i<=r;i++) {
        string s;
        cin >> s;
        for (int j=1;j<=c;j++) {
            m[i][j] = s[j-1];
        }
    }
    int a,b;
    cin >> a >> b;
    int dx[] = {a,a,-a,-a,b,b,-b,-b};
    int dy[] = {b,-b,b,-b,a,-a,a,-a};
    pii start;
    // memset (cnt,0,sizeof(cnt));
    for (int i=1;i<=r;i++) {
        for (int j=1;j<=c;j++) {
            if (m[i][j] == 'X') cnt[i][j] = 1;
            if (m[i][j] == 'K') {
                start = {i,j};
            }
        }
    }
    for (int i=1;i<=r;i++) {
        for (int j=1;j<=c;j++) {
            cnt[i][j] += cnt[i][j-1];
        }
    }
    for (int i=1;i<=r;i++) {
        for (int j=1;j<=c;j++) {
            cnt[i][j] += cnt[i-1][j];
        }
    }
    // memset (vis,0,sizeof(vis));
    vis[start.fi][start.se] = 1;
    queue<pii> q;
    q.push(start);
    while (!q.empty()) {
        pii cur = q.front();
        q.pop();
        for (int i=0;i<8;i++) {
            pii next = mp(cur.fi + dx[i], cur.se + dy[i]);
            if (next.fi >= 1 && next.fi <= r && next.se >= 1 && next.se <= c && m[next.fi][next.se] != 'X' && bisa(cur.fi, cur.se, next.fi, next.se) && vis[next.fi][next.se] == 0) {
                vis[next.fi][next.se] = vis[cur.fi][cur.se] + 1;
                q.push(next);
            }
        }
    }
    // for (int i=1;i<=r;i++) {
    //     for (int j=1;j<=c;j++) {
    //         cout << vis[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    pii fin;
    for (int i=1;i<=r;i++) {
        for (int j=1;j<=c;j++) {
            if (m[i][j] == 'O') {
                fin = mp(i, j);
            }
        }
    }
    cout << vis[fin.fi][fin.se] - 1 << endl;

    //cerr << fixed << setprecision(3) << (clock()-start)*1./CLOCKS_PER_SEC << endl;
    return 0;
}