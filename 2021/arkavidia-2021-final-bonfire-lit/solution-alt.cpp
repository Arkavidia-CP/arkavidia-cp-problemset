/** 
*   Author  : Muhammad Kamal Shafi
*   Problem : Bonfire Lit
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

int n, q;
pii ar[N];
pair<pii, int> quer[N];
int ans[N];

set<pii> setdah; // y-coordinate, score

void tambah(int pos, int val){
    auto temp = setdah.upper_bound(mp(pos + 1, -1));
    temp--;
    if (temp->fi >= val){
        return;
    }
    temp++;
    vector<pii> pus;
    while (temp != setdah.end() && temp->se <= val){
        pus.pb(*temp);
        temp++;
    }
    for (auto x : pus) setdah.erase(x);
    setdah.insert(mp(pos, val));
}
int ask(int pos){
    auto temp = setdah.upper_bound(mp(pos + 1, -1));
    temp--;
    return temp->se;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i=1;i<=n;i++){
        cin >> ar[i].fi >> ar[i].se;
    }
    sort(ar + 1, ar + n + 1);
    cin >> q;
    for (int i=1;i<=q;i++){
        cin >> quer[i].fi.fi >> quer[i].fi.se;
        quer[i].se = i;
    }
    sort(quer + 1, quer + q + 1);
    setdah.insert(mp(-1, -1));
    int id = 1;
    for (int i=1;i<=q;i++){
        int x = quer[i].fi.fi, y = quer[i].fi.se;
        while (id <= n && ar[id].fi <= x){
            tambah(ar[id].se, ar[id].fi + ar[id].se);
            id++;
        }
        int temp = ask(y);
        if (temp >= 0) ans[quer[i].se] = x + y - ask(y);
        else ans[quer[i].se] = -1;
    }
    for (int i=1;i<=q;i++){
        cout << ans[i] << el;
    }

    return 0;
}