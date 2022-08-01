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
    int n;
    cin >> n;
    int a[n+5];
    for (int i=1;i<=n;i++) cin >> a[i];
    int q;
    cin >> q;
    while (q--) {
        int op;
        cin >> op;
        int l,r;
        cin >> l >> r;
        if (op == 1) {
            int mini = a[l], maxi = a[l];
            for (int i=l+1;i<=r;i++) {
                mini = min(mini, a[i]);
                maxi = max(maxi, a[i]);
            }
            cout << mini << " " << maxi << endl;
        } else if (op == 2) {
            swap(a[l], a[r]);
        } else if (op == 3) {
            a[l] = r;
        } else {
            reverse(a+l, a+r+1);
        }
    }
    //cerr << fixed << setprecision(3) << (clock()-start)*1./CLOCKS_PER_SEC << endl;
    return 0;
}