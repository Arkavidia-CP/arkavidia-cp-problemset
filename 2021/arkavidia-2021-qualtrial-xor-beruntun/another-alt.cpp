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

// https://math.stackexchange.com/questions/11002/cn-p-even-or-odd

bool odd(int n, int r) {
    n = n - r;
    while (n && r) {
        if (n % 2 == 1 && r % 2 == 1) return 0;
        n /= 2;
        r /= 2;
    }
    return 1;
}

int main () {
    //clock_t start = clock();
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    cin >> n;
    int ans = 0;
    for (int i=0;i<n;i++) {
        int x;
        cin >> x;
        if (odd(n-1, i)) ans ^= x;
    }
    cout << ans << endl;
    //cerr << fixed << setprecision(3) << (clock()-start)*1./CLOCKS_PER_SEC << endl;
    return 0;
}