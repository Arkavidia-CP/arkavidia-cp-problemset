#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
vector<int> bit[N];
pair<int, int> ar[N];
int n, q;

void add(int i, int val) {
    while (i <= n) {
        bit[i].push_back(val);
        i += i & -i;
    }
}

int ask(int i, int val) {
    int ret = 0;
    int lo, hi, mid, best;
    while (i > 0) {
        if (bit[i].size()) {
            lo = 0, hi = bit[i].size() - 1, best = -1;
            while (lo <= hi) {
                mid = (lo + hi) / 2;
                if (bit[i][mid] >= val) {
                    best = mid;
                    hi = mid - 1;
                } else lo = mid + 1;
            }
            if (best != -1) {
                ret += bit[i].size() - best;
            }
        }
        i -= i & -i;
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> ar[i].first >> ar[i].second;
    }    
    sort(ar + 1, ar + 1 + n);
    for (int i = 1; i <= n; i++) {
        add(i, ar[i].second);
    }
    for (int i = 1; i <= n; i++) {
        sort(bit[i].begin(), bit[i].end());
    }
    
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        int lo = 1, hi = n, mid, best = -1;
        while (lo <= hi) {
            mid = (lo + hi) / 2;
            if (ar[mid].first <= l) {
                best = mid;
                lo = mid + 1;
            } else hi = mid - 1;
        }
        int ans = 0;
        if (best != -1) {
            ans = ask(best, r);
        }
        cout << ans << '\n';
    }
    return 0;
}