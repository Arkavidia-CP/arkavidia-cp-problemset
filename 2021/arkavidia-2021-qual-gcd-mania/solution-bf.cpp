/** 
*   Author  : Muhammad Kamal Shafi
*   Problem : Farras and gcd
**/
#pragma gcc optimize ("O2")
#pragma gcc optimize ("unroll-loops")

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
const int INF = 1e9;

int n;
int ar[N];
int q;
int l, r;

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    int base = INF;
    for (int i=1;i<=n;i++){
        cin >> ar[i];
        base = min(base, ar[i]);
    }
    int gcc = 0;
    for (int i=1;i<=n;i++){
        gcc = __gcd(gcc, ar[i] - base);
    }
    cin >> q;
    while (q--){
        int l, r;
        cin >> l >> r;
        int ans = 0;
        for (int i=l;i<=r;i++){
            ans = max(ans, __gcd(base + i, gcc));
        }
        cout << ans << el;
    }

    return 0;
}