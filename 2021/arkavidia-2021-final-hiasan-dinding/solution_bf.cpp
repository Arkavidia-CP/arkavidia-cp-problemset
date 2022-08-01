#include <bits/stdc++.h>
using namespace std;

struct pt{
	long long x, y;
};

const int maxn = 2021;
int n, q;
pt poly[maxn];

bool cmp(pt a, pt b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool cw(pt a, pt b, pt c) {
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) < 0;
}

bool ccw(pt a, pt b, pt c) {
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) > 0;
}

void convex_hull(vector<pt>& a) {
    if (a.size() == 1)
        return;

    sort(a.begin(), a.end(), &cmp);
    pt p1 = a[0], p2 = a.back();
    vector<pt> up, down;
    up.push_back(p1);
    down.push_back(p1);
    for (int i = 1; i < (int)a.size(); i++) {
        if (i == a.size() - 1 || cw(p1, a[i], p2)) {
            while (up.size() >= 2 && !cw(up[up.size()-2], up[up.size()-1], a[i]))
                up.pop_back();
            up.push_back(a[i]);
        }
        if (i == a.size() - 1 || ccw(p1, a[i], p2)) {
            while(down.size() >= 2 && !ccw(down[down.size()-2], down[down.size()-1], a[i]))
                down.pop_back();
            down.push_back(a[i]);
        }
    }

    a.clear();
    for (int i = 0; i < (int)up.size(); i++)
        a.push_back(up[i]);
    for (int i = down.size() - 2; i > 0; i--)
        a.push_back(down[i]);
}

long long area(const vector<pt>& fig) {
    long long res = 0;
    for (unsigned i = 0; i < fig.size(); i++) {
        pt p = i ? fig[i - 1] : fig.back();
        pt q = fig[i];
        res += (p.x - q.x) * (p.y + q.y);
    }
    return abs(res);
}

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);
	cin >> n;
	for (int i=0; i<n; i++) cin >> poly[i].x >> poly[i].y;
	cin >> q;
	while (q--){
		long long l, r;
		cin >> l >> r;
		vector<pt> ch;
		for (int i=0; i<n; i++){
			if (poly[i].x >= l && poly[i].x <= r) ch.push_back(poly[i]);
		}
		if (ch.size() < 3){
			cout << "0.0\n";
			continue;
		}
		convex_hull(ch);
		/*
		for (auto p : ch) cout << "(" << p.x << "," << p.y << ")";
		cout << "\n";
		*/
		long long ans = area(ch);
		cout << ans/2 << (ans%2 == 0 ? ".0" : ".5") << "\n";
	}
}