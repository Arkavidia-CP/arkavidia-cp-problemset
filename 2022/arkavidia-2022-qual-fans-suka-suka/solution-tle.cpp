/* Author: Jauhar Wibisono
 * O(4^N * N)
 */

#include <bits/stdc++.h>
using namespace std;

const int maxn = 20;
int n;
long long k[1<<maxn], a[1<<maxn], b[1<<maxn];
long long dp[1<<maxn][2]; // dp[pemenangnya siapa][babak keberapa]
long long ans;

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i=0; i<(1<<n); i++) cin >> k[i] >> a[i] >> b[i];

	memset(dp, 0, sizeof dp);
	
	// iterate babak
	for (int i=1; i<=n; i++) {
		// proses pertandingan per blok 
		for (int l=0; l<(1<<n); l+=(1<<i)) {
			int m = l+(1<<(i-1)), r = l+(1<<i); // pertandingan blok ini antara tim bernomor [l, m) dan [m, r)
			
			// hitung penonton max tiap pemenang blok ini
			for (int p=l; p<m; p++) {
				dp[p][i&1] = 0;
				for (int q=m; q<r; q++) {
					if (k[p] < k[q]) dp[p][i&1] = max(dp[p][i&1], dp[p][!(i&1)] + a[p] + dp[q][!(i&1)] + b[q]);
					else dp[p][i&1] = max(dp[p][i&1], dp[p][!(i&1)] + b[p] + dp[q][!(i&1)] + a[q]);
				}
			}
			for (int p=m; p<r; p++) {
				dp[p][i&1] = 0;
				for (int q=l; q<m; q++) {
					if (k[p] < k[q]) dp[p][i&1] = max(dp[p][i&1], dp[p][!(i&1)] + a[p] + dp[q][!(i&1)] + b[q]);
					else dp[p][i&1] = max(dp[p][i&1], dp[p][!(i&1)] + b[p] + dp[q][!(i&1)] + a[q]);
				}
			}
		}

		for (int j=0; j<(1<<n); j++) cout << dp[j][i&1] << ' ';
		cout << '\n';
	}

	ans = 0;
	for (int i=0; i<(1<<n); i++) ans = max(ans, dp[i][n&1]);

	cout << ans << '\n';
	return 0;
}