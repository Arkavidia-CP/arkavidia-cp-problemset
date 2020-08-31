//by wiwit rifai
#include <bits/stdc++.h>

using namespace std;

int main() {
  int n, q;
  cin >> n >> q;
  vector<int> go(n+2, -1);
  set<int> nodes;
  nodes.insert(n+1);
  while (q--) {
    int t, x, y;
    cin >> t;
    if (t != 3)
      cin >> x >> y;
    if (t == 3) {
      int ans = 0;
      int now = *nodes.begin();
      while (now != n+1) {
        ++ans;
        now = go[now];
        now = *nodes.upper_bound(now);
      }
      printf("%d\n", ans);
    }
    else if (t == 1) {
      assert(!nodes.count(x) && !nodes.count(y));
      nodes.insert(x);
      nodes.insert(y);
      go[x] = y;
      go[y] = x;
    }
    else if (t == 2) {
      assert(nodes.count(x) && nodes.count(y));
      assert(go[x] == y && go[y] == x); 
      nodes.erase(x);
      nodes.erase(y);
      go[x] = go[y] = -1;
    }
    else
      assert(false);
  }
  return 0;
}
