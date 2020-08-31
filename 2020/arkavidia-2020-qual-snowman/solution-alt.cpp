#include <bits/stdc++.h>
using namespace std;
#define MAXN 100000
#define INF 1000000007
int arr[MAXN+5], val[MAXN+5];
int n,q,a,b;

pair<int, int> t[4*MAXN];

pair<int, int> combine(pair<int, int> a, pair<int, int> b) {
    if (a.first > b.first)
        return a;
    if (b.first > a.first)
        return b;
    return min(a,b);
}

void build(int a[], int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = make_pair(a[tl], tl);
    } else {
        int tm = (tl + tr) / 2;
        build(a, v*2, tl, tm);
        build(a, v*2+1, tm+1, tr);
        t[v] = combine(t[v*2], t[v*2+1]);
    }
}

pair<int, int> get_max(int v, int tl, int tr, int l, int r) {
    if (l > r)
        return make_pair(-INF, INF);
    if (l == tl && r == tr)
        return t[v];
    int tm = (tl + tr) / 2;
    return combine(get_max(v*2, tl, tm, l, min(r, tm)),
                   get_max(v*2+1, tm+1, tr, max(l, tm+1), r));
}

void update(int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
        t[v] = make_pair(new_val, tl);
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update(v*2, tl, tm, pos, new_val);
        else
            update(v*2+1, tm+1, tr, pos, new_val);
        t[v] = combine(t[v*2], t[v*2+1]);
    }
}

void precompute(){
	int a,b,dist;
	a = b = dist = 0;
	while(b < n){
		b++;
		if(b-a > 1){
			if(dist != arr[b] - arr[b-1]){
				val[a] = b-a;
				int cur = val[a];
				while(dist != arr[b] - arr[b-1]){
					a++;
					cur--;
					val[a] = cur;
					dist = arr[a+1] - arr[a];
				}
			}
		} else {
			dist = arr[a+1]-arr[a];
		}
	}
	val[a] = b-a;
	int cur = val[a];
	while(a < n){
		a++;
		cur--;
		val[a] = cur;
	}
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%d", &arr[i]);
	}
	precompute();
	build(val, 1, 0, n-1);
	scanf("%d", &q);
	for(int i = 0; i < q; i++){
		scanf("%d %d", &a, &b);
		a--;
		b--;
		pair<int,int> ans1 = get_max(1, 0, n-1, a, b);
		if(a < ans1.second){
			pair<int,int> ans2 = get_max(1, 0, n-1, a, ans1.second-1);
			printf("%d\n", max(ans2.first, min(ans1.first, b-ans1.second+1)));
		} else {
			printf("%d\n", min(b-a+1, ans1.first));
		}
	}
	return 0;
}