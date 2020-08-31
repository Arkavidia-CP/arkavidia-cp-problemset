#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define MOD 1000000007
#define pii pair<int,int>
#define ll long long
#define el '\n'

using namespace std;
using namespace __gnu_pbds;

typedef tree<pii,null_type,greater<pii>,rb_tree_tag,
    tree_order_statistics_node_update> indexed_set;

const int N = 1e4 + 8;

indexed_set scoreboard;
int n, q;
map <int, int> cek; // score, count

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i=0;i<n;i++){
        int tm;
        cin >> tm;
        cek[tm]++;
        scoreboard.insert(mp(tm, cek[tm]));
    }

    cin >> q;
    while (q--){
        int tipe, req;
        cin >> tipe >> req;

        if (tipe == 1){
            cek[req]++;
            scoreboard.insert(mp(req, cek[req]));
        } else{
            cout << (*scoreboard.find_by_order(req-1)).fi << el;
        }
    }

    return 0;
}