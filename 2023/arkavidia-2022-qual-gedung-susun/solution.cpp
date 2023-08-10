#include <bits/stdc++.h>

using namespace std;

#define FOR(a, b) for (int i = (int) a; i < (int) b; i++)
#define pb push_back
#define mp make_pair
#define fi first
#define se second
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<long long, long long> pll;

const int mxn = 1e5 + 1;  // limit for array size
const int mxm = 1e2 + 1;
int n, m;  // array size
ll t1[2 * mxm], t2[2 * mxm];
ll b[mxn], d[mxn], gf[mxn];

void build(int type) {  // build the tree
  for (int i = m - 1; i > 0; --i) {
    if(type){
        t1[i] = min(t1[i<<1], t1[i<<1|1]);
    } else{
        t2[i] = min(t2[i<<1], t2[i<<1|1]);
    }
  }
}

void modify(int type, int p, ll value) {  // set value at position p
    if(type){
        for (t1[p += m] = value; p > 1; p >>= 1) t1[p>>1] = min(t1[p], t1[p^1]);
    } else{
        for (t2[p += m] = value; p > 1; p >>= 1) t2[p>>1] = min(t2[p], t2[p^1]);
    }
}

ll query(int type, int l, int r) {  // sum on interval [l, r)
    ll res = 1e18;
    if(type){
        for (l += m, r += m; l < r; l >>= 1, r >>= 1) {
            if (l&1) res = min(res, t1[l++]);
            if (r&1) res = min(res, t1[--r]);
        }
    } else{
        for (l += m, r += m; l < r; l >>= 1, r >>= 1) {
            if (l&1) res = min(res, t2[l++]);
            if (r&1) res = min(res, t2[--r]);
        }
    }
    return res;
}

int main() { 
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    for(int i=0; i<n; i++){
        cin >> gf[i];  
    }
    for(int i=0; i<n; i++){
        cin >> b[i];
    }
    for(int i=0; i<n; i++){
        cin >> d[i];
    }

    for (int i = 0; i < m; ++i) {
        t1[i + m] = b[0] + abs(gf[0]-i-1) + i;
        t2[i + m] = b[0] + abs(gf[0]-i-1) + (m-1-i);
    }
    build(0);
    build(1);

    // for(int i=0; i<n; i++){
    //     cout << query(1, i, i) << " ";
    // }
    // cout << "\n";
    // for(int i=0; i<n; i++){
    //     cout << query(0, i, i) << " ";
    // }
    // cout << "\n";


    for(int i=1; i<n; i++){
        ll dp[m];
        for(int j=0; j<m; j++){
            dp[j] = b[i]+abs(gf[i]-j-1) + 
                    min(query(1, j, min(1LL*m, j+d[i-1]+1))-j, 
                    query(0, max(0LL, j-d[i-1]), j+1)-m+1+j);
        }
        for(int j=0; j<m; j++){
            t1[j + m] = dp[j] + j;
            t2[j + m] = dp[j] + (m-1-j);
        }
        build(0);
        build(1);

        // for(int i=0; i<n; i++){
        //     cout << query(1, i, i) << " ";
        // }
        // cout << "\n";
        // for(int i=0; i<n; i++){
        //     cout << query(0, i, i) << " ";
        // }
        // cout << "\n";

        if(i==n-1){
            ll ans = 1e18;
            for(int j=0; j<m; j++){
                ans = min(ans, dp[j]);
            }
            cout << ans << "\n";
        }
    }


    return 0;
}
