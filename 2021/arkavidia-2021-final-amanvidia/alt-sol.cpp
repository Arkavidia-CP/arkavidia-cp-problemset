#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

const int N = 2e7;
const int M = 25;

int n;
int ada[N + 5];
int pw[M + 5];
int pre[M + 5];

void init () {
    pw[0] = 1;
    pre[0] = 1;
    for (int i = 1; i < M; i++) {
        pw[i] = (1LL * pw[i - 1] * 10) % n;
        pre[i] = (pre[i - 1] + pw[i]) % n;
    }
}

string bin (int k) {
    string ret;
    while (k) {
        if (k & 1) ret.push_back('1');
        else ret.push_back('0');
        k >>= 1;
    }
    while ((int)ret.length() < M) {
        ret.push_back('0');
    }
    reverse(ret.begin(), ret.end());
    return ret;
}

string sub (string a, string b) {
    string ret;
    assert (M == (int)a.length());
    bool carry = false;
    for (int i = M - 1; i >= 0; i--) {
        int da = a[i] - '0';
        int db = b[i] - '0';
        if (!carry) {
            if (da == 1 && db == 0) { ret.push_back('1'); }
            if (da == 1 && db == 1) { ret.push_back('0'); }
            if (da == 0 && db == 0) { ret.push_back('0'); }
            if (da == 0 && db == 1) { ret.push_back('9'); carry = true; }
        } else {
            if (da == 1 && db == 0) { ret.push_back('0'); carry = false; }
            if (da == 1 && db == 1) { ret.push_back('9'); }
            if (da == 0 && db == 0) { ret.push_back('9'); }
            if (da == 0 && db == 1) { ret.push_back('8'); }
        }
    }
    reverse (ret.begin(), ret.end());
    int lz = 0;
    while (ret[lz] == '0') lz++;
    return ret.substr(lz, M - lz);
}

void solve() {
    cin >> n;
    init();
    memset (ada, -1, sizeof(ada));
    int cur = 0;
    ada[0] = 0;
    for (int i = 1; i <= n; i++) {
        if (i & 1) {
            cur = (cur + 1) % n;
        } else {
            int tr = (i ? __builtin_ctz(i) : M);
            cur = (cur + pw[tr] - pre[tr - 1]) % n;
            if (cur < 0) cur += n;
        }
        if (ada[cur] != -1) {
            // cerr << ada[cur] << ' ' << i << '\n';
            string x = bin(ada[cur]);
            string y = bin(i);
            // cerr << x << ' ' << y << '\n';
            cout << (sub(y, x)) << '\n';
            return;
        } else {
            ada[cur] = i;
        }
    }
    assert (false);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int TC = 1;
    for(int i = 1; i <= TC; i++) {
        solve();
    }
  
    return 0;
}