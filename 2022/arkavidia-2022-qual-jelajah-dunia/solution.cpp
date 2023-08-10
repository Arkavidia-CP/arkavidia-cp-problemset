#include <bits/stdc++.h>

using namespace std;

#define FOR(a, b) for (int i = (int) a; i < (int) b; i++)
#define pb push_back
#define mp make_pair
#define fi first
#define se second
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<long long, long long> pll;
const ll mod = 1e9+7;
ll fact[2000001];

void prec(){
    fact[0] = 1;
    for(int i = 1; i <= 2000000; i++){
        fact[i] = (fact[i-1]*i)%mod;
    }
}

ll binpow(ll a, ll b){
    a %= mod;
    ll res = 1;
    while(b > 0){
        if(b&1){
            res = (res*a)%mod;
        }
        a = (a*a)%mod;
        b >>= 1;
    }
    return res;
}

ll C(ll n, ll k){
    if(k > n){
        return 0;
    }
    return (fact[n]*binpow(fact[k], mod-2)%mod*binpow(fact[n-k], mod-2)%mod)%mod;
}

int main() { 
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    prec();
    while(t--){
        ll k;
        cin >> k;
        ll xa, ya, xb, yb;
        cin >> xa >> ya >> xb >> yb;
        if((xa + k > ya && xb + k > yb) || (xa + k < ya && xb + k < yb)){
            ll xa_ = ya - k;
            ll ya_ = xa + k;
            if(xb - xa >= 0 && yb - ya >= 0){
                if((xa + k > ya && xa + k > yb) || (xa + k < ya && xb + k < ya)){
                    ll n = (xb - xa) + (yb - ya);
                    ll r = (xb - xa);
                    cout << C(n, r) << "\n";
                } else{
                    ll n1 = (xb - xa) + (yb - ya);
                    ll r1 = (xb - xa);
                    ll n2 = (xb - xa_) + (yb - ya_);
                    ll r2 = (xb - xa_);
                    // cout << n1 << " " << r1 << " " << n2 << " " << r2 << endl;
                    cout << (C(n1, r1) - C(n2, r2) + mod)%mod << "\n";
                }
            } else{
                cout << "0\n";
            }
        } else{
            cout << "0\n";
        }
    }


    return 0;
}