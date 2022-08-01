#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define MOD 1000000007
#define INF 1234567890
#define pii pair<int,int>
#define LL long long
using namespace std;

int main () {
    //clock_t start = clock();
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    LL n;
    cin >> n;
    for (LL x = n; x <= 1e18;x+=n) {
        LL p = x;
        bitset<10> ada;
        ada.reset();
        while (p) {
            ada[p%10] = 1;
            p /= 10;
        }
        if (ada.count() <= 4 && !ada[2] && !ada[3] && !ada[4] && !ada[5] && !ada[6] && !ada[7] && x % n == 0) {
            cout << -1 << endl;
            return 0;
        }
    }
    //cerr << fixed << setprecision(3) << (clock()-start)*1./CLOCKS_PER_SEC << endl;
    return 0;
}