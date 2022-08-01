#include <bits/stdc++.h>

using namespace std;

const int mod = 998244353;

vector<int> multiply(vector<int> & a, vector<int> & b) {
  int n = a.size();
  vector<int> ret(n, 0);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      int z = (i + j);
      if (z >= n) z -= n;
      ret[z] = (ret[z] + 1LL * a[i] * b[j]) % mod;
    }
  }
  return ret;
}

vector<int> pow(vector<int> b, long long e) {
  vector<int> r(b.size(), 0);
  r[0] = 1;
  for (; e; e >>= 1, b = multiply(b, b)) {
    if (e & 1)
      r = multiply(r, b);
  }
  return r;
}

int main() {
  int n, m;
  long long r;
  scanf("%d %d %lld", &n, &m, &r);
  vector<int> cnt(n, 0);
  for (int i = 0; i < m; ++i) {
    int x;
    scanf("%d", &x);
    ++cnt[x % n];
  }
  vector<int> ans = pow(cnt, r);
  for (int i = 0; i < n; ++i)
    printf("%d%c", ans[i], i+1 == n ? '\n' : ' ');
  return 0;
}