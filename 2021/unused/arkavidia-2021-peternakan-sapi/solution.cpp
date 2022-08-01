/**
*   Author  : Muhammad Hasan
*   Problem : Peternakan Sapi
**/
#include <bits/stdc++.h>

using namespace std;

const int INF = 2e9;

mt19937 rng32(chrono::steady_clock::now().time_since_epoch().count());

typedef struct item * pitem;
struct item {
    int prior, value, cnt;
    int mini, maxi;
    bool rev;
    pitem l, r;
    item(int value) : prior(rng32()), value(value), cnt(0), mini(value), maxi(value), rev(false),
                  l(NULL), r(NULL) { }
};

int cnt(pitem it) {
    return it ? it->cnt : 0;
}

int maxi(pitem it) {
    return it ? it->maxi : 0;
}

int mini(pitem it) {
    return it ? it->mini : INF;
}

void upd(pitem it) {
    if (!it) return;
    it->cnt = cnt(it->l) + cnt(it->r) + 1;
    it->maxi = max(it->value, max(maxi(it->l), maxi(it->r)));
    it->mini = min(it->value, min(mini(it->l), mini(it->r)));
}

void push(pitem it) {
    if (it && it->rev) {
        it->rev = false;
        swap(it->l, it->r);
        if (it->l)  it->l->rev ^= true;
        if (it->r)  it->r->rev ^= true;
    }
}

void merge(pitem& t, pitem l, pitem r) {
    push(l);
    push(r);
    if (!l || !r)
        t = l ? l : r;
    else if (l->prior > r->prior)
        merge(l->r, l->r, r),  t = l;
    else
        merge(r->l, l, r->l),  t = r;
    upd(t);
}

// l = [0..pos-1], r = [pos..sz]
void split(pitem t, pitem& l, pitem& r, int key, int add = 0) {
    if (!t)
        return void( l = r = 0 );
    push(t);
    int cur_key = add + cnt(t->l); // implicit key
    if(key <= cur_key)
        split(t->l, l, t->l, key, add),  r = t;
    else
        split(t->r, t->r, r, key, add + 1 + cnt(t->l)),  l = t;
    upd(t);
}

void reverse(pitem t, int l, int r) {
    pitem t1, t2, t3;
    split(t, t1, t2, l);
    split(t2, t2, t3, r - l + 1);
    t2->rev ^= true;
    merge(t, t1, t2);
    merge(t, t, t3);
}

void output(pitem t) {
    if (!t)  return;
    push(t);
    output(t->l);
    cerr << t->value << ' ';
    output(t->r);
}

void insert(pitem& t, int pos, pitem new_item) {
    if (!t) {
        t = new_item;
        return;
    }
    pitem t1, t2;
    split(t, t1, t2, pos);
    merge(t1, t1, new_item);
    merge(t, t1, t2);
    upd(t);
}

// Zero Index
int get_at(pitem t, int pos) {
    pitem t1, t2, t3;
    split(t, t1, t2, pos);
    split(t2, t2, t3, 1);
    int ret = t2->value;
    merge(t1, t1, t2);
    merge(t, t1, t3);
    return ret;
}

// Zero Index
void erase_at(pitem& t, int pos) {
    pitem t1, t2, t3;
    split(t, t1, t2, pos);
    split(t2, t2, t3, 1);
    merge(t, t1, t3);
    upd(t);
}

pair<int, int> func(pitem t, int l, int r) {
    pitem t1, t2, t3;
    split(t, t1, t2, l);
    split(t2, t2, t3, r - l + 1);
    int ret_mini = mini(t2), ret_maxi = maxi(t2); // don't forget to change upd() and call it at the end of methods
    merge(t, t1, t2);
    merge(t, t, t3);
    return make_pair(ret_mini, ret_maxi);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    pitem myTreap = NULL;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        pitem new_item = new item(x);
        insert(myTreap, i, new_item);
    }

    auto answer = [&](int L, int R) -> void {
        auto ans = func(myTreap, L, R);
        cout << ans.first << ' ' << ans.second << '\n';
    };

    auto change = [&](int X, int V) -> void {
        erase_at(myTreap, X);
        pitem new_item = new item(V);
        insert(myTreap, X, new_item);
    };

    auto reverse_slots = [&](int L, int R) -> void {
        reverse(myTreap, L, R);
    };

    int q;
    cin >> q;
    while (q--) {
        int tp;
        cin >> tp;
        if (tp == 1) {
            int L, R;
            cin >> L >> R;
            L--, R--;
            assert(L <= R);
            answer(L, R);
        } else if (tp == 2) {
            int X, Y;
            cin >> X >> Y;
            X--, Y--;
            assert(X != Y);
            int val_X = get_at(myTreap, X);
            int val_Y = get_at(myTreap, Y);
            change(X, val_Y);
            change(Y, val_X);
        } else if (tp == 3) {
            int X, V;
            cin >> X >> V;
            X--;
            change(X, V);
        } else if (tp == 4) {
            int L, R;
            cin >> L >> R;
            L--, R--;
            reverse_slots(L, R);
        } else {
            assert(false);
        }
    }

    return 0;
}