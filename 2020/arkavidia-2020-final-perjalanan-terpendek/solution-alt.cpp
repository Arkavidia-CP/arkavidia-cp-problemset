#include <bits/stdc++.h>
#define pb push_back
#define fi first
#define se second

using namespace std;

typedef long long LL;

const int MAXN = 1e6;

int n, m;
vector<int> edges[MAXN+2];
bool visit[MAXN+2];
LL res[MAXN+2], cnt[MAXN+2], dist;
int city;

void dfs(int node){
	visit[node] = true;
	for (auto neks : edges[node]){
		if (!visit[neks]){
			dfs(neks);
			cnt[node] += cnt[neks];
			res[node] += res[neks] + cnt[neks];
		}
	}
	cnt[node]++;
}

void dfs1(int node){
	visit[node] = true;
	for (auto neks:edges[node]){
		if (!visit[neks]){
			res[neks] = res[node] - cnt[neks] + n - cnt[neks];
			dfs1(neks); 
		}
	}
}



int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 0; i < m; ++i){
		int x, y;
		cin >> x >> y;
		edges[x].pb(y);
		edges[y].pb(x);
	}
	dfs(1);
	memset(visit, false, sizeof visit);
	dfs1(1);
	for (int i = 1; i <= n; ++i){
		if (i == 1){
			city = 1;
			dist = res[i];
		}else if (res[i] < dist){
			city = i;
			dist = res[i];
		}
	}
	cout << city << " " << dist << '\n';
	return 0;
}
