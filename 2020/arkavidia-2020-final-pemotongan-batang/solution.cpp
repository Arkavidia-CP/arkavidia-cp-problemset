#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define pb push_back
#define sz(a) (int)(a).size()
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vvi = vector<vi>;
using vll = vector<ll>;
using vvll = vector<vll>;

const ll MOD = 1e9 + 7;
const ll INF = 1e18;
const ll IINF = INT_MAX;

ll n;
int q;
set<pll> poslen;
set<pll> lenpos;

void show(set<pll> s) { // for debug
    cout << "SHOWING SET" << '\n';
    set<pll>::iterator it;
    for (it = s.begin(); it != s.end(); it++) {
        pll cur = *it;
        cout << cur.fi << ' ' << cur.se << '\n';
    }
    cout << "END OF SHOWING SET" << '\n';
}

void potong(ll pos) {
    set<pll>::iterator it = poslen.lower_bound({pos, 0});
    pll cur = *it;
    if (cur.fi == pos) return;

    poslen.erase(cur);
    lenpos.erase({cur.se, cur.fi});

    poslen.insert({cur.fi, cur.fi - pos}); 
    poslen.insert({pos, cur.se - (cur.fi - pos)});

    lenpos.insert({cur.fi - pos, cur.fi});
    lenpos.insert({cur.se - (cur.fi - pos), pos});
    // show(poslen);
    // show(lenpos);
}

void sambung(ll pos) {
    set<pll>::iterator it = poslen.lower_bound({pos, 0});
    pll one = *it;
    poslen.erase(one);
    lenpos.erase({one.se, one.fi});
    
    it = poslen.lower_bound({pos, 0});
    pll two = *it;
    poslen.erase(two);
    lenpos.erase({two.se, two.fi});
    
    poslen.insert({two.fi, one.se + two.se});
    lenpos.insert({one.se + two.se, two.fi});
    // show(poslen);
    // show(lenpos);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> q;
    poslen.insert({n, n});
    lenpos.insert({n, n});
    while (q--) {
        // asumsi tc:
        // query "sambung" kalo udah di potong di posisi itu

        int type;
        ll val;
        cin >> type;
        if (type == 1) {
            cin >> val;
            potong(val);
        } else if (type == 2) { 
            cin >> val;
            if (val == n) continue;
            sambung(val);
        } else {
            set<pll>::iterator biggest = lenpos.end();
            biggest--;
            pll ans = *(biggest);
            cout << ans.fi << '\n';
        }
    }    
    return 0;
}