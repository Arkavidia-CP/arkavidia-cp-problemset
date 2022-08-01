#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define MOD 1000000007
#define INF 1234567890
#define pii pair<LL,LL>
#define LL long long
using namespace std;

int main () {
    //clock_t start = clock();
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    LL n;
    cin >> n;
    LL a[n+5];
    for (LL i=1;i<=n;i++) cin >> a[i];
    sort (a+1,a+n+1);
    a[n+1] = -1;
    vector<pair<pii,LL>> v;
    LL cur = 0;
    for (LL i=1;i<=n;i++) {
        if (a[i] == a[i+1]) continue;
        v.pb({{cur, i}, a[i]});
        cur += (a[i+1] - a[i]) * i;
    }
    for (auto x : v) {
        cout << x.fi.fi << " " << x.fi.se << " " << x.se << endl;
    }
    LL q;
    cin >> q;
    while (q--) {
        LL k;
        cin >> k;
        LL l = 0, r = v.size()-1, ans = 0;
        while (l <= r) {
            LL m = (l + r) / 2;
            if (k >= v[m].fi.fi) {
                ans = m;
                l = m+1;
            } else {
                r = m-1;
            }
        }
        cout << v[ans].se + ((k - v[ans].fi.fi) / v[ans].fi.se) << endl;
    }
    //cerr << fixed << setprecision(3) << (clock()-start)*1./CLOCKS_PER_SEC << endl;
    return 0;
}

/*
6
2 2 4 5 6 6
6
0
2
4
11
16
17

out: 2 3 4 6 6 7

1
1
3
0
20
100

out: 1 21 101
*/