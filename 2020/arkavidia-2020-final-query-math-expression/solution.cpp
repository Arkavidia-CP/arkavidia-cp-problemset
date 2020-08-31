#include <bits/stdc++.h>
using namespace std;

constexpr long long PMOD = 1e9 + 7;
typedef vector<long long> Opr;

Opr create(char c, long long x) {
    Opr p;
    if (c == '+')
        p.push_back(1);
    p.push_back(x);
    return p;
}

long long eval(const Opr& p, long long x) {
    x = (x * p[0]) % PMOD;
    for (int i = 1; i < (int)p.size(); ++i)
        x = (x + p[i]) % PMOD;
    return x;
}

Opr join(const Opr& p, const Opr& q) {
    Opr r = p;
    r.back() = (r.back() * q[0]) % PMOD;
    for (int i = 1; i < (int)q.size(); ++i)
        r.push_back(q[i]);
    Opr ret;
    ret.push_back(r[0]);
    if (r.size() > 2) {
        ret.push_back(0);
        for (int i = 1; i < (int)r.size() - 1; ++i) {
            ret.back() = (ret.back() + r[i]) % PMOD;
        }
    }
    if (r.size() > 1)
        ret.push_back(r.back());
    return ret;
}

constexpr int MAXN = 1e5;
Opr st[4 * MAXN + 5];
long long num[MAXN + 5];
char op[MAXN + 5];

int N, Q, n, q;
long long x;
char c;

const Opr& build(int v, int lt, int rt) {
    if (lt == rt)
        return st[v] = create(op[lt], num[lt + 1]);
    int mt = (lt + rt) / 2;
    return st[v] = join(build(2 * v, lt, mt), build(2 * v + 1, mt + 1, rt));
}

void update(int v, int lt, int rt, int x, const Opr& p) {
    if (lt == x && rt == x) {
        st[v] = p;
        return;
    }
    int mt = (lt + rt) / 2;
    if (x <= mt)
        update(2 * v, lt, mt, x, p);
    else
        update(2 * v + 1, mt + 1, rt, x, p);
    st[v] = join(st[2 * v], st[2 * v + 1]);
}

Opr query(int v, int lt, int rt, int l, int r) {
    if (lt == l && rt == r)
        return st[v];
    int mt = (lt + rt) / 2;
    return join(
        query(2 * v, lt, mt, l, min(r, mt)), query(2 * v + 1, mt + 1, rt, max(l, mt + 1), r));
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> Q >> num[0];
    for (int i = 0; i < N - 1; ++i)
        cin >> op[i] >> num[i + 1];
    if (N > 1)
        build(1, 0, N - 2);
    while (Q--) {
        cin >> q;
        if (q == 1) {
            cin >> n >> x;
            --n;
            num[n] = x;
            if (N > 1 && n > 0)
                update(1, 0, N - 2, n - 1, create(op[n - 1], num[n]));
        } else if (q == 2) {
            cin >> n >> c;
            --n;
            op[n] = c;
            if (N > 1)
                update(1, 0, N - 2, n, create(op[n], num[n + 1]));
        } else {
            if (N > 1)
                cout << eval(query(1, 0, N - 2, 0, N - 2), num[0]) << '\n';
            else
                cout << num[0] << '\n';
        }
    }
}