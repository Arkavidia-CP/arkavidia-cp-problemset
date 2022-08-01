#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
using ll = long long;
using pii = pair<int, int>;

const int N = 1e5 + 5;
int n, q;
pii ar[N];
pair<pii, int> que[N];
int ans[N];
int bit[2 * N];
int SZBIT;
map<int, int> kompres;

void add(int x, int val) {
    while (x < SZBIT) {
        bit[x] = max(bit[x], val);
        x += x & -x;
    }
}

int ask(int x) {
    int ret = -1;
    while (x > 0) {
        ret = max(ret, bit[x]);
        x -= x & -x;
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    set<int> ys;
    for (int i = 0; i < n; i++) {
        cin >> ar[i].fi >> ar[i].se;
        ys.insert(ar[i].se);
    }
    sort(ar, ar + n);

    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> que[i].fi.fi >> que[i].fi.se;
        ys.insert(que[i].fi.se);
        que[i].se = i;
        ans[i] = -1;
    }
    sort(que, que + q);

    SZBIT = 0;
    for (auto it: ys) {
        kompres[it] = ++SZBIT;
    }
    SZBIT++;
    for (int i = 0; i < SZBIT; i++) bit[i] = -1;

    int id = 0;
    for (int i = 0; i < q; i++) {
        int x, y;
        tie(x, y) = que[i].fi;
        while (id < n && ar[id].fi <= x) {
            add(kompres[ar[id].se], ar[id].fi + ar[id].se);
            id++;
        }
        int val = ask(kompres[y]);
        if (val == -1) continue;
        ans[que[i].se] = x + y - val;
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << '\n';
    }
    return 0;
}