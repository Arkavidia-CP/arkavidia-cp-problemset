/* Author: Jauhar Wibisono
 * O(2^N * N^2)
 * bisa dibikin TLE kalau mau
 */

#include <bits/stdc++.h>
using namespace std;

const int maxn = 20;
int n;
pair<long long, int> k[1<<maxn];
long long a[1<<maxn], b[1<<maxn];
long long pref[1<<maxn], suff[1<<maxn]; // prefix & suffix max
long long dp[1<<maxn][2]; // dp[pemenangnya siapa][babak keberapa]
long long ans;

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i=0; i<(1<<n); i++) cin >> k[i].first >> a[i] >> b[i];

	for (int i=0; i<(1<<n); i++) k[i].second = i;
	memset(dp, 0, sizeof dp);
	
	// iterate babak
	for (int i=1; i<=n; i++) {
		// proses pertandingan per blok 
		for (int l=0; l<(1<<n); l+=(1<<i)) {
			int m = l+(1<<(i-1)), r = l+(1<<i); // pertandingan blok ini antara tim bernomor [l, m) dan [m, r)
			
			// bikin prefix & suffix max untuk blok ini
			pref[l] = dp[k[l].second][!(i&1)] + a[k[l].second];
			for (int j=l+1; j<m; j++) pref[j] = max(pref[j-1], dp[k[j].second][!(i&1)] + a[k[j].second]);
			pref[m] = dp[k[m].second][!(i&1)] + a[k[m].second];
			for (int j=m+1; j<r; j++) pref[j] = max(pref[j-1], dp[k[j].second][!(i&1)] + a[k[j].second]);
			suff[m-1] = dp[k[m-1].second][!(i&1)] + b[k[m-1].second];
			for (int j=m-2; j>=l; j--) suff[j] = max(suff[j+1], dp[k[j].second][!(i&1)] + b[k[j].second]);
			suff[r-1] = dp[k[r-1].second][!(i&1)] + b[k[r-1].second];
			for (int j=r-2; j>=m; j--) suff[j] = max(suff[j+1], dp[k[j].second][!(i&1)] + b[k[j].second]);

			// hitung penonton max tiap pemenang blok ini pakai binary search
			for (int j=l; j<m; j++) {
				int who = k[j].second;
				int ll = m, rr = r-1, pr = r;
				while (ll <= rr) {
					int mid = (ll+rr)/2;
					if (k[j].first < k[mid].first) {
						pr = mid;
						rr = mid-1;
					}
					else ll = mid+1;
				}
				if (pr == m) dp[who][i&1] = suff[pr] + a[who] + dp[who][!(i&1)];
				else if (pr == r) dp[who][i&1] = pref[pr-1] + b[who] + dp[who][!(i&1)];
				else dp[who][i&1] = max(pref[pr-1] + b[who] + dp[who][!(i&1)], suff[pr] + a[who] + dp[who][!(i&1)]);
			}
			for (int j=m; j<r; j++) {
				int who = k[j].second;
				int ll = l, rr = m-1, pl = m;
				while (ll <= rr) {
					int mid = (ll+rr)/2;
					if (k[j].first < k[mid].first) {
						pl = mid;
						rr = mid-1;
					}
					else ll = mid+1;
				}
				if (pl == l) dp[who][i&1] = suff[pl] + a[who] + dp[who][!(i&1)];
				else if (pl == m) dp[who][i&1] = pref[pl-1] + b[who] + dp[who][!(i&1)];
				else dp[who][i&1] = max(pref[pl-1] + b[who] + dp[who][!(i&1)], suff[pl] + a[who] + dp[who][!(i&1)]);	
			}

			// sort tim blok ini by kekuatan
			sort(k+l, k+r);
		}
	}

	ans = 0;
	for (int i=0; i<(1<<n); i++) ans = max(ans, dp[i][n&1]);

	cout << ans << '\n';
	return 0;
}