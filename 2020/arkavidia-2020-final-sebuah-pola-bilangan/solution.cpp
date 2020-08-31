#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define MOD 1000000007
#define pii pair<int,int>
#define LL long long
using namespace std;

LL n, k;
LL awal(int x) {
    if (x == 0) return 1;
    else return (4*n - 4*x) * x + 1;
}

int main () {
    //clock_t start = clock();
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n >> k;
        LL l = 0, h = (n+1)/2-1, lapis = 0;
        while (l <= h) {
            LL m = (l+h)/2;
            if (awal(m) <= k) {
                lapis = m;
                l = m + 1;
            } else {
                h = m - 1;
            }
        }
        k -= awal(lapis)-1;
        if (k % 4 == 1) cout << k / 4 + lapis + 1 << " " << lapis + 1 << endl;
        else if (k % 4 == 2) cout << n - lapis << " " << k / 4 + lapis + 1 << endl; 
        else if (k % 4 == 3) cout << n - lapis - k / 4 << " " << n - lapis << endl;
        else cout << lapis + 1 << " " << n - lapis - k / 4 + 1 << endl;
    }
    //cerr << fixed << setprecision(3) << (clock()-start)*1./CLOCKS_PER_SEC << endl;
    return 0;
}