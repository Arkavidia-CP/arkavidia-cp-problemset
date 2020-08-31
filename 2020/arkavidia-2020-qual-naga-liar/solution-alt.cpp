#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const LL MOD = 1e9 + 7;

LL N, ans;

LL mulmod(LL a, LL b, LL mod){
    LL res = 0;
    while (b > 0){
        if (b&1){
            res = (res + a) % mod;
        }
        b >>= 1;
        a = (a + a) % mod;
    }
    return res;
}

LL powmod(LL a, LL b, LL mod){
    LL res = 1;
    while (b > 0){
        if (b&1){
            res = mulmod(res%mod, a%mod, mod);
        }
        b >>= 1;
        a = mulmod(a%mod, a%mod, mod);
    }
    return res;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    --N;
    int pw = 0;
    LL bit;
    for (bit = 1; bit <= N; bit *= 2){
        if (!(N&bit)){
            ans = ((ans%MOD) + mulmod(bit%MOD, pw, MOD))%MOD;
        }
        ++pw;
    }
    ans = (mulmod(bit%MOD, pw, MOD) - ans + MOD) % MOD;
    cout << mulmod(ans, powmod(N+1, MOD-2, MOD), MOD) << '\n';
    return 0;
}