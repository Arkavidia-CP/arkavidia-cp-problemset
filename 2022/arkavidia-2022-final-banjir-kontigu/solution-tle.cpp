/* Author: Jauhar Wibisono
 * O(NQ)
 */

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5+3;
int n, m, q;
long long a[maxn];
vector<int> adjl[maxn];
long long ca[maxn];
bool vis[maxn];

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m >> q;
	for (int i=1; i<=n; i++) cin >> a[i];
	for (int i=0; i<m; i++) {
		int u, v;
		cin >> u >> v;
		adjl[u].push_back(v);
		adjl[v].push_back(u);
	}

	while (q--) {
		char type;
		cin >> type;
		if (type == '1') {
			int i, x;
			cin >> i >> x;
			a[i] = x;
		} else {
			int l, r;
			cin >> l >> r;
			
			memset(ca, 0, sizeof ca);
			for (int i=l; i<=r; i++) ca[i] = a[i];
			memset(vis, false, sizeof vis);
			long long ans = 0;
			for (int i=1; i<=n; i++) {
				if (!vis[i]) {
					long long mn = 1e9+3;
					auto dfs = [&mn](auto self, int u) -> void {
						if (vis[u]) return;
						vis[u] = true;
						mn = min(mn, ca[u]);
						for (int v : adjl[u]) self(self, v);
					};
					dfs(dfs, i);
					ans += mn;
				}
			}

			cout << ans << '\n';
		}
	}
	return 0;
}