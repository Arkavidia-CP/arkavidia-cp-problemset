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

const int mxn = 1e5+1;
const int mxm = 1e2+1;
const ll INF = 1e18;

ll x[4*mxm], y[4*mxm];
int n, m;
ll b[mxn], d[mxn], gf[mxn];

void build(ll t[], ll a[], int v, int tl, int tr, int type) {
    if (tl == tr) {
        if(type){
            t[v] = a[tl]+tl;
        }
        else{
            t[v] = a[tl]+m-1-tl;
        }
    } else {
        int tm = (tl + tr) / 2;
        build(t, a, v*2, tl, tm, type);
        build(t, a, v*2+1, tm+1, tr, type);
        t[v] = min(t[v*2] , t[v*2+1]);
    }
}
ll mn(ll t[], int v, int tl, int tr, int l, int r) {
    if (l > r) 
        return INF;
    if (l == tl && r == tr) {
        return t[v];
    }
    int tm = (tl + tr) / 2;
    return min(mn(t, v*2, tl, tm, l, min(r, tm))
           , mn(t, v*2+1, tm+1, tr, max(l, tm+1), r));
}

void update(ll t[], int v, int tl, int tr, int pos, ll new_val, int type) {
    if (tl == tr) {
        if(type){
            t[v] = new_val+tl;
        } else{
            t[v] = new_val+m-1-tl;
        }
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update(t, v*2, tl, tm, pos, new_val, type);
        else
            update(t, v*2+1, tm+1, tr, pos, new_val, type);
        t[v] = min(t[v*2], t[v*2+1]);
    }
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

    ll init[m];
    for(int i=0; i<m; i++){
        init[i] = b[0]+abs(gf[0]-i-1);
    }

    build(x, init, 1, 0, m-1, 1);
    build(y, init, 1, 0, m-1, 0);

    // for(int i=0; i<n; i++){
    //     cout << mn(x, 1, 0, n-1, i, i) << " ";
    // }
    // cout << "\n";
    // for(int i=0; i<n; i++){
    //     cout << mn(y, 1, 0, n-1, i, i) << " ";
    // }
    // cout << "\n";

    for(int i=1; i<n; i++){
        ll dp[m];
        for(int j=0; j<m; j++){
            dp[j] = b[i]+abs(gf[i]-j-1) + 
                    min(mn(x, 1, 0, m-1, j, min(1LL*m-1, j+d[i-1]))-j, 
                    mn(y, 1, 0, m-1, max(0LL, j-d[i-1]), j)-m+1+j);
        }
        build(x, dp, 1, 0, m-1, 1);
        build(y, dp, 1, 0, m-1, 0);
        // cout << "iterasi " << i << "\n";
        // for(int k=0; k<n; k++){
        //     cout << dp[k] << " ";
        // }
        // cout << "\n";
        // for(int k=0; k<n; k++){
        //     cout << mn(x, 1, 0, n-1, k, k) << " ";
        // }
        // cout << "\n";
        // for(int k=0; k<n; k++){
        //     cout << mn(y, 1, 0, n-1, k, k) << " ";
        // }
        // cout << "\n";
        if(i==n-1){
            ll ans = 1e18;
            for(int i=0; i<m; i++){
                ans = min(ans, dp[i]);
            }
            cout << ans << "\n";
        }
    }


    return 0;
}