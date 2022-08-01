/* Author: Jauhar Wibisono
 * sol arkavidia-2021-subgraph-divisibility
 */

/* dp tree */

#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e5+7, mod = 4; // mod bisa diganti-ganti kalo mau ganti soal
int n, a[maxn], m;
bool vis[maxn];
vector<int> adjl[maxn];
vector<int> dp[maxn][mod];
vector<int> ans;

void dfs(int now){
	vis[now] = 1;
	dp[now][a[now]].push_back(now);
	vector<int> tmp[mod];
	for (int next : adjl[now]){
		if (vis[next]) continue;
		dfs(next);
		vector<int> tmp2[mod];
		tmp2[a[next]] = {next}; // buat ngecilin jawaban
		for (int i=0; i<mod; i++){
			for (int j=0; j<mod; j++){
				if (tmp2[(i+j)%mod].empty() && (i == 0 || !tmp[i].empty()) && !dp[next][j].empty() && tmp[i].size()+dp[next][j].size() <= 20){ // 20 magic number
					tmp2[(i+j)%mod] = tmp[i];
					for (int u : dp[next][j]) tmp2[(i+j)%mod].push_back(u);
				}
			}
		}
		for (int i=0; i<mod; i++) tmp[i] = tmp2[i];
	}
	for (int i=0; i<mod; i++){
		if (!tmp[i].empty()){
			dp[now][(i+a[now])%mod] = tmp[i];
			dp[now][(i+a[now])%mod].push_back(now);
		}
	}
	if (dp[now][a[now]].empty()) dp[now][a[now]] = {now};
}

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);
	cin >> n >> m;
	for (int i=1; i<=n; i++){
		cin >> a[i];
		a[i] %= mod;
	}
	for (int i=1; i<=m; i++){
		int u, v;
		cin >> u >> v;
		adjl[u].push_back(v);
		adjl[v].push_back(u);
	}
	memset(vis,0,sizeof vis);
	for (int i=1; i<=n; i++){
		if (!vis[i]) dfs(i);
	}
	for (int i=1; i<=n; i++){
		if (dp[i][0].size()>1){
			ans = dp[i][0];
			break;		
		}
	}
	if (ans.empty()) cout << -1 << "\n";
	else{
		cout << ans.size() << "\n";
		for (int u : ans) {
			cout << u;
			if (u != ans[ans.size()-1]) cout << ' ';
		}
		cout << "\n";
	}
}
