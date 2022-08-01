/* Author: Jauhar Wibisono
 * alternate solution arkavidia-2021-mengurus-senjata
 */

#include <bits/stdc++.h>
using namespace std;

// sqrt block + BIT

const int maxn = 1e5+4, maxk = 1e5+4, sqrtn = sqrt(maxn);
int n, k[maxn], qq;
long long bit[sqrtn+5][maxk];

void update_bit(int i, int pos, long long val){
	while (pos < maxk){
		bit[i][pos] += val;
		pos += pos&-pos;
	}
}

void build(){
	memset(bit, 0, sizeof bit);
	for (int i=0; i<n; i++) update_bit(i/sqrtn, k[i], k[i]);
}

void update(int i, int v){
	update_bit(i/sqrtn, k[i], -k[i]);
	k[i] = v;
	update_bit(i/sqrtn, k[i], k[i]);
}

long long query_bit(int i, int pos){
	long long ret = 0;
	while (pos > 0){
		ret += bit[i][pos];
		pos -= pos&-pos;
	}
	return ret;
}

long long query(int l, int r, int p, int q){
	long long ret = 0;
	// left
	int i = l;
	for (; i<=r && i%sqrtn>0; i++){
		if (k[i] >= p && k[i] <= q) ret += k[i];
	}
	// mid
	for (; i+sqrtn-1<=r; i+=sqrtn){
		ret += query_bit(i/sqrtn, q) - query_bit(i/sqrtn, p-1);
	}
	// right
	for (; i<=r; i++){
		if (k[i] >= p && k[i] <= q) ret += k[i];
	}
	return ret;
}

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);
	cin >> n;
	for (int i=0; i<n; i++) cin >> k[i];
	build();
	cin >> qq;
	while(qq--){
		int type;
		cin >> type;
		if (type == 1){
			int l, r, p, q;
			cin >> l >> r >> p >> q;
			cout << query(l-1,r-1,p,q) << "\n";
		}
		else{
			int x, v;
			cin >> x >> v;
			update(x-1,v);
		}
	}
}