/* Author: Jauhar Wibisono
 * O(2^N * N)
 */

#include <bits/stdc++.h>
using namespace std;

const int maxn = 20;
int n;
long long k[1<<maxn], a[1<<maxn], b[1<<maxn];
long long s[1<<maxn][2]; // index tim sorted by kekuatan
long long pref[1<<maxn], suff[1<<maxn]; // prefix & suffix max
long long dp[1<<maxn][2]; // dp[pemenangnya siapa][babak keberapa]
long long ans;

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i=0; i<(1<<n); i++) cin >> k[i] >> a[i] >> b[i];

	for (int i=0; i<(1<<n); i++) s[i][1] = i;
	memset(dp, 0, sizeof dp);
	
	// iterate babak
	for (int i=1; i<=n; i++) {
		// proses pertandingan per blok 
		for (int l=0; l<(1<<n); l+=(1<<i)) {
			int m = l+(1<<(i-1)), r = l+(1<<i); // pertandingan blok ini antara tim bernomor [l, m) dan [m, r)
			
			// bikin prefix & suffix max untuk blok ini
			pref[l] = dp[s[l][i&1]][!(i&1)] + a[s[l][i&1]];
			for (int j=l+1; j<m; j++) pref[j] = max(pref[j-1], dp[s[j][i&1]][!(i&1)] + a[s[j][i&1]]);
			pref[m] = dp[s[m][i&1]][!(i&1)] + a[s[m][i&1]];
			for (int j=m+1; j<r; j++) pref[j] = max(pref[j-1], dp[s[j][i&1]][!(i&1)] + a[s[j][i&1]]);
			suff[m-1] = dp[s[m-1][i&1]][!(i&1)] + b[s[m-1][i&1]];
			for (int j=m-2; j>=l; j--) suff[j] = max(suff[j+1], dp[s[j][i&1]][!(i&1)] + b[s[j][i&1]]);
			suff[r-1] = dp[s[r-1][i&1]][!(i&1)] + b[s[r-1][i&1]];
			for (int j=r-2; j>=m; j--) suff[j] = max(suff[j+1], dp[s[j][i&1]][!(i&1)] + b[s[j][i&1]]);

			// hitung penonton max tiap pemenang blok ini pakai two pointers
			for (int j=l, pr=m; j<m; j++) {
				int who = s[j][i&1];
				while (pr < r && k[who] > k[s[pr][i&1]]) pr++;
				if (pr == m) dp[who][i&1] = suff[pr] + a[who] + dp[who][!(i&1)];
				else if (pr == r) dp[who][i&1] = pref[pr-1] + b[who] + dp[who][!(i&1)];
				else dp[who][i&1] = max(pref[pr-1] + b[who] + dp[who][!(i&1)], suff[pr] + a[who] + dp[who][!(i&1)]);
			}
			for (int j=m, pl=l; j<r; j++) {
				int who = s[j][i&1];
				while (pl < m && k[who] > k[s[pl][i&1]]) pl++;
				if (pl == l) dp[who][i&1] = suff[pl] + a[who] + dp[who][!(i&1)];
				else if (pl == m) dp[who][i&1] = pref[pl-1] + b[who] + dp[who][!(i&1)];
				else dp[who][i&1] = max(pref[pl-1] + b[who] + dp[who][!(i&1)], suff[pl] + a[who] + dp[who][!(i&1)]);	
			}

			// sort tim blok ini by kekuatan 
			// pakai merge-nya merge sort
			for (int pl=l, pr=m, j=l; j<r; j++) {
				if (pl == m || (pr < r && k[s[pr][i&1]] < k[s[pl][i&1]])) s[j][!(i&1)] = s[pr][i&1], pr++;
				else s[j][!(i&1)] = s[pl][i&1], pl++;
			}
		}
	}


	ans = 0;
	for (int i=0; i<(1<<n); i++) ans = max(ans, dp[i][n&1]);

	cout << ans << '\n';
	return 0;
}