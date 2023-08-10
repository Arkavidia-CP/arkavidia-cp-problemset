/* Author: Jauhar Wibisono
 * O((N+Q) log^2 N) time, O(N + Q log^2 N) memory
 */


#include <bits/stdc++.h>
using namespace std;

struct node_x {
	node_x *l, *r;
	long long sum;
	node_x(): l(nullptr), r(nullptr), sum(0) {}
	node_x(long long sum): l(nullptr), r(nullptr), sum(sum) {}
	node_x(node_x *l, node_x *r): l(l), r(r), sum(0) {
		if (l) sum += l->sum;
		if (r) sum += r->sum;
	}
};

struct node_y { // bisa juga dibikin array & allocate static
	node_y *l, *r;
	node_x *x;
	node_y(): l(nullptr), r(nullptr), x(nullptr) {}
	node_y(node_y *l, node_y *r, node_x *x): l(l), r(r), x(x) {}
};

typedef node_x * pnode_x;
typedef node_y * pnode_y;

const int maxn = 1e5+3;
int n, m, q;
long long a[maxn];
vector<int> adjl[maxn];
int gid[maxn];
int gl[maxn], gr[maxn];
priority_queue<pair<long long, int>> gpq[maxn];
pnode_y root;

void dfs(int id, int u) {
	if (gid[u] != -1) return;
	gid[u] = id;
	for (int v : adjl[u]) dfs(id, v);
}

void update_x(pnode_x px, int x, int lx, int rx, long long val) {
	// cout << lx << ' ' << rx << '\n';
	if (lx == rx) px->sum = val;
	else {
		if (!px->l) px->l = new node_x();
		if (!px->r) px->r = new node_x();
		int mid = (lx+rx)/2;
		if (x <= mid) update_x(px->l, x, lx, mid, val);
		else update_x(px->r, x, mid+1, rx, val);
		px->sum = px->l->sum + px->r->sum;
	}
}

void update_y(pnode_y py, int x, int y, int ly, int ry, long long val) {
	// cout << ly << ' ' << ry << '\n';
	if (!py->x) py->x = new node_x();
	if (!py->l) py->l = new node_y();
	if (!py->r) py->r = new node_y();
	update_x(py->x, x, 1, n, val);
	if (ly < ry) {
		int mid = (ly+ry)/2;
		if (y <= mid) update_y(py->l, x, y, ly, mid, val);
		else update_y(py->r, x, y, mid+1, ry, val);
	}
}

long long query_x(pnode_x px, int lbx, int rbx, int lx, int rx) {
	if (!px || rx < lbx || lx > rbx) return 0;
	if (lx >= lbx && rx <= rbx) return px->sum;
	int mid = (lx+rx)/2;
	return query_x(px->l, lbx, rbx, lx, mid) + query_x(px->r, lbx, rbx, mid+1, rx);
}

long long query_y(pnode_y py, int lbx, int rbx, int lby, int rby, int ly, int ry) {
	if (!py || ry < lby || ly > rby) return 0;
	if (ly >= lby && ry <= rby) return query_x(py->x, lbx, rbx, 1, n);
	int mid = (ly+ry)/2;
	return query_y(py->l, lbx, rbx, lby, rby, ly, mid) + query_y(py->r, lbx, rbx, lby, rby, mid+1, ry);
}

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

	memset(gid, -1, sizeof gid);
	for (int i=1; i<=n; i++) {
		if (gid[i] == -1) dfs(i, i);
	}
	for (int i=n; i>0; i--) gl[gid[i]] = i;
	for (int i=1; i<=n; i++) gr[gid[i]] = i;
	for (int i=1; i<=n; i++) gpq[gid[i]].emplace(-a[i], i);

	root = new node_y();
	for (int i=1; i<=n; i++) {
		if (gid[i] == i) {
			update_y(root, gl[i], gr[i], 1, n, -gpq[i].top().first);
		}
	}

	while (q--) {
		char type;
		cin >> type;
		if (type == '1') {
			int i, x;
			cin >> i >> x;
			
			a[i] = x;
			int id = gid[i]; 
			while (!gpq[id].empty() && a[gpq[id].top().second] != -gpq[id].top().first) gpq[id].pop();
			gpq[id].emplace(-a[i], i);

			update_y(root, gl[id], gr[id], 1, n, -gpq[id].top().first);
		} else {
			int l, r;
			cin >> l >> r;
			cout << query_y(root, l, n, 1, r, 1, n) << '\n';
		}
	}
	return 0;
}