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

int dp[1200005];
int a[20];
int mask[1200005];
int main () {
    //clock_t start = clock();
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n, q;
    cin >> n >> q;
    for (int i=1;i<=n;i++) {
        cin >> a[i];
    }
    memset(mask,-1,sizeof(mask));
    dp[0] = 2;
    for (int i=1;i<=1200000;i++) {
        bool y = 0;
        for (int j=1;j<=n;j++) {
            if (((i-a[j]) >= 0) && dp[i-a[j]] == 2) y = 1;
        }
        if (y) dp[i] = 1; else dp[i] = 2;
    }
    // for (int i=1;i<=200;i++) {
    //     cout << dp[i];
    // }
    // cout << endl;
    int start = -1, end = -1;
    for (int i=0;i<=1200000;i++) {
        int cur = 0;
        for (int j=i;j<i+20;j++) {
            cur += dp[j] - 1;
            cur *= 2;
        }
        cur /= 2;
        if (mask[cur] == -1) {
            mask[cur] = i;
        } else {
            start = mask[cur];
            end = i-1;
            break;
        }
    }
    start++;
    end++;
    // cout << start << " " << end << endl;
    // for (int i=1;i<=200;i++) {
    //     cout << dp[start + (i-start)%(end-start+1)];
    // }
    // cout << endl;
    // cout << "Cycle: " << start << " " << end << endl;
    while (q--) {
        LL m;
        cin >> m;
        if (m <= start) {
            if (dp[m] == 1) cout << "Elon" << endl;
            else cout << "Melvin" << endl;
        } else {
            if (dp[start + (m-start)%(end-start+1)] == 1) cout << "Elon" << endl;
            else cout << "Melvin" << endl;
        }
    }
    //cerr << fixed << setprecision(3) << (clock()-start)*1./CLOCKS_PER_SEC << endl;
    return 0;
}