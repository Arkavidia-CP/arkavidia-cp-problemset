#include <bits/stdc++.h>
using namespace std;

#define ull unsigned long long
#define ll long long
#define fi first
#define se second
#define pb(a) push_back(a)
#define mp(a, b) make_pair(a, b)
#define el '\n'

const int mxn=1e3;
const int mxk=5;
const int mxu=1e3;
ll p[mxn+1], c[mxn+1], dp[mxn+1][(1<<mxk)][mxu+1];

int main() {
    ll n, u, day; cin >> n >> u >> day;

    ll dayconfig = 1;
    for(ll i=0;i<day;i++) dayconfig *= 2;

    for(ll i=1;i<=n;i++) cin >> p[i] >> c[i];

    p[0] = 0;
    c[0] = 0;

    for(ll i=0;i<=n;i++) {
        for(ll j=0;j<dayconfig;j++) {
            for(ll k=0;k<=u;k++) {
                dp[i][j][k] = 0;
            }
        }
    }

    for(ll i=1; i<=n; i++) {
        ll daybef = min(i-1, day);

        for(ll j=0; j<dayconfig; j++) {
            ll buybefore = __builtin_popcount(j);
            if (buybefore > daybef) continue;

            ll todayskip = (j << 1) & (dayconfig-1);
            ll todaybuy = todayskip | 1;

            ll curc = c[i];

            for(ll k=0;k<=u;k++) {
                dp[i][todayskip][k] = max(dp[i][todayskip][k], dp[i-1][j][k]);

                ll buycost = curc * ((buybefore == 0 ? 1 : buybefore));
                if (k + buycost <= u) {
                    dp[i][todaybuy][k+buycost] = max(dp[i][todaybuy][k+buycost], dp[i-1][j][k] + p[i]);
                }
            }
        }
    }

    ll ans = -1;
    for(ll i=0;i<dayconfig;i++) {
        for(ll j=0;j<=u;j++) {
            ans = max(ans, dp[n][i][j]);
        }
    }

    cout << ans << el;
}
