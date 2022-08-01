/* Author: Jauhar Wibisono
 * sol 2 arkavidia-2021-subgraph-divisibility
 * pake random
 */

#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e5+7;
int n, m, a[maxn];
vector<int> adjl[maxn];
bool vis[maxn];
int cnt_tree = 0;
vector<int> tree_nodes[maxn];

void init_dfs(int u){
	vis[u] = 1;
	tree_nodes[cnt_tree].push_back(u);
	for (int v : adjl[u]){
		if (vis[v]) continue;
		init_dfs(v);
	}
}

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);
	mt19937 rng((unsigned long long)(new char));
	cin >> n >> m;
	for (int i=1; i<=n; i++){
		cin >> a[i];
		a[i] %= 4;
	}
	for (int i=0; i<m; i++){
		int u, v;
		cin >> u >> v;
		adjl[u].push_back(v);
		adjl[v].push_back(u);
	}
	memset(vis,0,sizeof vis);
	for (int i=1; i<=n; i++){
		if (vis[i]) continue;
		init_dfs(i);
		cnt_tree++;
	}
	for (int i=0; i<cnt_tree; i++){
		// coba random 8 kali di tree ini
		for (int coba=0; coba<8; coba++){
			// prepare bfs
			vector<int> ans;
			int sum = 0;
			queue<pair<int,int>> q;
			// random shuffle adjl
			for (int u : tree_nodes[i]) shuffle(adjl[u].begin(),adjl[u].end(),rng);
			// pilih starting node random
			q.push({tree_nodes[i][rng()%tree_nodes[i].size()],0});
			// bfs
			while (!q.empty()){
				int u = q.front().first, p = q.front().second;
				q.pop();
				ans.push_back(u);
				sum += a[u];
				sum %= 4;
				if (sum == 0 && ans.size() > 1){
					cout << ans.size() << "\n";
					for (int v : ans) cout << v << " ";
					cout << "\n";
					return 0;
				}
				for (int v : adjl[u]){
					if (v == p) continue;
					q.push({v,u});
				}
			}
		}
	}
	cout << -1 << "\n";
}