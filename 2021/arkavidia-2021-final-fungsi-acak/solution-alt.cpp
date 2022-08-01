/** 
*   Author  : Muhammad Kamal Shafi
*   Problem : Memilih Bilangan
**/
#include <bits/stdc++.h>


#define fi first
#define se second
#define pb(a) push_back(a)
#define mp(a, b) make_pair(a, b)
#define el '\n'

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int N = 1e5 + 10;
const ll MOD = 1e9 + 7;

int n;
ll t[4 * N], lazy[4 * N];

void build(int v, int tl, int tr){
    lazy[v] = 1;
    if (tl == tr){
        t[v] = 1;
        return;
    }
    int tm = (tl + tr) / 2;
    build(v * 2, tl, tm);
    build(v * 2 + 1, tm + 1, tr);
    t[v] = (t[v * 2] + t[v * 2 + 1]) % MOD;
}
void push(int v){
    t[v * 2] = t[v * 2] * lazy[v] % MOD;
    lazy[v * 2] = lazy[v * 2] * lazy[v] % MOD;
    t[v * 2 + 1] = t[v * 2 + 1] * lazy[v] % MOD;
    lazy[v * 2 + 1] = lazy[v * 2 + 1] * lazy[v] % MOD;
    lazy[v] = 1;
}
void update(int v, int tl, int tr, int l, int r, ll val){
    if (l > r || r < tl || tr < l) return;
    if (l <= tl && tr <= r){
        t[v] = t[v] * val % MOD;
        lazy[v] = lazy[v] * val % MOD;
        return;
    }
    push(v);
    int tm = (tl + tr) / 2;
    update(v * 2, tl, tm, l, r, val);
    update(v * 2 + 1, tm + 1, tr, l, r, val);
    t[v] = (t[v * 2] + t[v * 2 + 1]) % MOD;
}
ll ask(int v, int tl, int tr, int l, int r){
    if (l > r || r < tl || tr < l) return 0;
    if (l <= tl && tr <= r) return t[v];
    push(v);
    int tm = (tl + tr) / 2;
    return (ask(v * 2, tl, tm, l, r) + ask(v * 2 + 1, tm + 1, tr, l, r)) % MOD;
}
ll fpow(ll a, ll b){
    ll ret = 1;
    while (b){
        if (b & 1){
            ret = ret * a % MOD;
        }
        a = a * a % MOD;
        b >>= 1;
    }
    return ret;
}
ll inv(ll a){
    return fpow(a, MOD - 2);
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    build(1, 1, N - 2);
    ll ans = 0, tot = 1;
    for (int i=1;i<=n;i++){
        ll l, r;
        cin >> l >> r;
        tot = tot * (r - l + 1) % MOD;
        ans = (ans + ask(1, 1, N - 2, l, r) * inv(tot)) % MOD;
        update(1, 1, N - 2, l, r, r - l);
        update(1, 1, N - 2, 1, l - 1, r - l + 1);
        update(1, 1, N - 2, r + 1, N - 2, r - l + 1);
    }
    cout << ans << el;

    return 0;
}