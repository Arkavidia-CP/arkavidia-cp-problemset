#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define MOD 1000000007
#define pii pair<int,int>
#define LL long long
using namespace std;

int a[100005], tree[500005];
pii segment[100005];

void build(int node, int start, int end) {
    if (start == end) {
        tree[node] = a[start];
    } else {
        int mid = (start + end) / 2;
        build(2*node, start, mid);
        build(2*node+1, mid+1, end);
        tree[node] = max(tree[2*node], tree[2*node+1]);
    }
}

int query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) {
        return 0;
    } else if (l <= start && end <= r) {
        return tree[node];
    } else {
        int mid = (start + end) / 2;
        int p1 = query(2*node, start, mid, l, r);
        int p2 = query(2*node+1, mid+1, end, l, r);
        return max(p1, p2);
    }
}

int main () {
    //clock_t start = clock();
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    cin >> n;
    for (int i=1;i<=n;i++) cin >> a[i];
    int p = 1, l = 1, r = 2, d = a[l+1] - a[l];
    while (l < n && r <= n) {
        if (a[r] - a[r-1] == d) {
            r++;
        } else {
            segment[p++] = mp(l, r - 1);
            l = r - 1;
            d = a[l+1] - a[l];
        }
    }
    segment[p] = mp(l, r - 1);
    memset(a, 0, sizeof(a));
    memset(tree, 0, sizeof(tree));
    for (int i=1;i<=p;i++) a[i] = segment[i].se - segment[i].fi + 1;
    build(1, 1, p);

    int q;
    cin >> q;
    while (q--) {
        cin >> l >> r;
        int bawah = 0, atas = 0;
        int lo = 1, hi = p;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (segment[mid].fi <= l) {
                bawah = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }

        lo = 1, hi = p;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (segment[mid].se >= r) {
                atas = mid;
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        int ans = query(1, 1, p, bawah + 1, atas - 1);
        ans = max (ans, min(r, segment[bawah].se) - max(l, segment[bawah].fi) + 1);
        ans = max (ans, min(r, segment[atas].se) - max(l, segment[atas].fi) + 1);
        cout << ans << endl;
    }
    //cerr << fixed << setprecision(3) << (clock()-start)*1./CLOCKS_PER_SEC << endl;
    return 0;
}