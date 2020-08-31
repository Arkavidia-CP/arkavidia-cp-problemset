#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

struct point {
  long long x, y;
  point(long long _x = 0, long long _y = 0) : x(_x), y(_y) {}
  point operator+(point p) { return point(x+p.x, y+p.y); }
  point operator-(point p) { return point(x-p.x, y-p.y); }
  long long operator*(point p) { return x * p.x + y * p.y; }
  long long operator%(point p) { return x * p.y - y * p.x; }
};

bool ccw(point a, point b, point c) {
  return (b - a) % (c - a) > 0;
}

ostream& operator<<(ostream& os, point p) {
  return os << "(" << p.x << "," << p.y << ")";
}

int main() {
  int n, l, r;
  scanf("%d %d %d", &n, &l, &r);
  vector<point> points(n);
  point pl(l, 0), pr(r, 0);
  for (int i = 0; i < n; ++i) {
    int x, y;
    scanf("%d %d", &x, &y);
    assert(y != 0);
    points[i] = point(x, y);
  }
  int nmask = 1 << n;
  int ans = 0;
  for (int mask = 0; mask < nmask; ++mask) {
    bool ok = 1;
    for (int i = 0; i < n && ok; ++i) {
      if ((mask & (1 << i)) == 0) continue;
      if (points[i].y < 0) continue;
      for (int j = 0; j < n && ok; ++j) {
        if ((mask & (1 << j)) == 0) continue;
        if (points[j].y > 0) continue;
        if (ccw(points[i], points[j], pl) || ccw(points[j], points[i], pr)) {
          ok = 0;
        }
      }
    }
    ans += ok;
  }
  ans %= mod;
  printf("%d\n", ans);
  return 0;
}
