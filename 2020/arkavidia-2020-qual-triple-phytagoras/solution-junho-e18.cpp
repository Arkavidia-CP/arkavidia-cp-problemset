#include <bits/stdc++.h>

using namespace std;
using u64 = uint64_t;
using u128 = __uint128_t;

const long long N = 1e6 + 5;
bool prime[N];
u64 we;

void sieve(){
    for(int i = 2; i < N; i++){
        prime[i] = true;
    }
    for(int i = 2; i < N; i++){
        if(prime[i]){
            for(int j = 2 * i; j < N; j += i){
                prime[j] = false;
            }
        }
    }
}

u64 binpower(u64 base, u64 e, u64 mod) {
    u64 result = 1;
    base %= mod;
    while (e) {
        if (e & 1)
            result = (u128)result * base % mod;
        base = (u128)base * base % mod;
        e >>= 1;
    }
    return result;
}

bool check_composite(u64 n, u64 a, u64 d, int s) {
    u64 x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (u128)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
}

bool MillerRabin(u64 n) { // returns true if n is prime, else returns false.
    if (n < 2)
        return false;

    int r = 0;
    u64 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }

    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a)
            return true;
        if (check_composite(n, a, d, r))
            return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    sieve();

    cin >> we;
    
    int ans = 0;

    for(u64 i = 2; i < N; i++){
        int cnt = 0;
        while(we % i == 0){
            we /= i;
            if(cnt == 0){
                cnt = 1;
            }
        }

        ans += cnt;
    }

    if(MillerRabin(we)){
        ans++;
    } else {
        u64 x = floor(sqrt(we));
        if(MillerRabin(x) && x * x == we){
            ans++;
        } else if(we != 1){
            ans += 2;
        }
    }
    //cout << ans << '\n';
    int res = 1;
    while(ans){
        res *= 2;
        ans--;
    }

    res /= 2;
    cout << res << '\n';
    return 0;
}