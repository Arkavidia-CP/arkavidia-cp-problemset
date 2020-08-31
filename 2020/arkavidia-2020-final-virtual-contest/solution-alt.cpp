#include <bits/stdc++.h>
using namespace std;

const int N = 2e4 + 5;
// const int Q = 3e4 + 5;
// 225 * 224 = N + Q
multiset<int, greater<int>> score[250];
int n, q;
int ar[N];
int sz;

void show() { // debug
    for (int i = 0; i < 225; i++) {
        if (score[i].empty()) return;
        cout << "    ";
        cout << "[" << i << "]" << " -> ";
        for (auto it: score[i]) {
            cout << it << " ";
        }
        cout << '\n';
    }
}

void add(int x) {
    bool done = false;
    for (int i = 0; i < sz + 1 && !done; i++) {
        if (score[i + 1].empty() || x >= *score[i].begin() ||  x >= *score[i + 1].begin()) {
            score[i].insert(x);
            int cur_sz = score[i].size();
            if (cur_sz == sz + 1) {
                multiset<int, greater<int>>::iterator last = score[i].end();
                last--;
                x = *last;
                score[i].erase(last);
            } else {
                done = true;
            }
        }
    }
    return;
}

void ask(int rank) {
    int i;
    for (i = 0; i < 225; i++) {
        int cur_sz = score[i].size();
        if (rank > cur_sz) {
            rank -= cur_sz;
        } else {
            break;
        }
    }
    for (auto it: score[i]) {
        rank--;
        if (rank == 0) {
            cout << it << '\n';
            return;
        }
    }
    return;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> ar[i];
    }
    cin >> q;
    sz = sqrt(n + q) + 1;
    for (int i = 0; i < n; i++) {
        add(ar[i]);
    }
    // show();
    while (q--) {
        int x, val;
        cin >> x >> val;
        if (x == 1) {
            add(val);
            // show(); cout << '\n';
        } else {
            ask(val);
        }
    }
    return 0;
}