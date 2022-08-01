/** 
*   Author  : Muhammad Kamal Shafi
*   Problem : GCD Mania
**/
#include <bits/stdc++.h>

#define pb(a) push_back(a)
#define el '\n'

using namespace std;

const int N = 1e5 + 10;
const int INF = 1e9;

int n;
int ar[N];
int q;

vector<int> fac;

bool possible(int l, int r, int x){
    if (l <= 0 && 0 <= r) return 1;
    return (r / x) - ((l - 1) / x) > 0;
}

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
    int gc = 0;
    for (int i=1;i<=n;i++){
        gc = __gcd(gc, ar[i] - base);
    }
    for (int i=1;i * i<=gc;i++){
        if (gc % i == 0){
            int j = gc / i;
            fac.pb(i);
            if (i != j) fac.pb(j);
        }
    }

    cin >> q;
    while (q--){
        int l, r;
        cin >> l >> r;

        int ans = 0;
        if (gc){
            for (auto x : fac){
                if (possible(l + base, r + base, x)){
                    ans = max(ans, x);
                }
            }
        } else{
            ans = base + r;
        }
        cout << ans << el;
    }

    return 0;
}