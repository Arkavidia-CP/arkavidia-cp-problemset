//by irfansofyana 
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int MAXX = 1e6;
const LL MOD = 1e9+7;
const LL MAXB = 1e18;

LL N;
vector<LL> primes;
bitset<MAXX+5> bil;

LL mulmod(LL a, LL b, LL mod){
    LL x = 0;
    LL y = a%mod;
    while (b > 0){
        if (b%2 == 1){
            x = (x + y) % mod;
        }
        y = (y * 2)%mod;
        b >>= 1;
    }
    return x%mod;
}

LL powmod(LL a, LL b, LL mod){
    LL x = 1;
    LL y = a;
    while (b > 0){
        if (b%2 == 1){
            x = mulmod((x%mod), (y%mod), mod);
        }
        y = mulmod((y%mod), (y%mod), mod);
        b >>= 1;
    }
    return x%mod;
}

void sieve(){
    bil.set();
    bil[0] = bil[1] = false;
    for (int i = 2; i <= MAXX; ++i){
        if (bil[i]){
            primes.push_back(i);
            for (LL j = 1LL*i*i; j <= MAXX; j += i){
                bil[j] = false;
            }
        }
    }
}

int millerRabin(LL p, int it){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<LL> dis(1, MAXB);
    if (p == 1) return 0;
    if (p == 2) return 1;
    if (p != 2 && p % 2 == 0) return 0;
    LL d = p-1;
    while (d%2 == 0) d /= 2;
    LL s = (p-1) / d;
    for (int i = 0; i < it; ++i){
        LL random = dis(gen);
        LL a = random % (p-1) + 1;
        LL mod = powmod(a, d, p);
        if (mod == 1) continue;
        for (int i = 0; i <= s-1; ++i){
            if (mod == p-1) break;
            mod = mulmod((mod%p), (mod%p), p);
        }
        if (mod != p-1) return 0;
    } 
    return 1;
}

LL findSqrt(LL n){
    LL low = 1, high = 2e9, mid, ans = -1;
    while(low<=high){
        mid = (low+high)/2;
        if(mid*mid <= n){
            low = mid+1;
            ans = mid;
        }
        else high = mid-1;
    }
    return ans;
}

LL findPrimeFactor(LL N){
    LL res = 0;
    for (auto prime: primes){
        if (1LL * prime * prime * prime > N){
            break;
        }
        int pow = 0;
        while(N % prime == 0){
            pow++;
            N /= prime;
        }
        if (pow > 0){
            ++res;
        }
    }
    if (N == 1){
        return res;
    }
    else if (millerRabin(N, 1000)){
        ++res;
    }else{
        LL sqrtN = findSqrt(N);
        if (sqrtN * sqrtN == N && millerRabin(sqrtN, 1000)){
            ++res;
        }else if (N != 1){
            res += 2;
        }
    }
    return res;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    sieve();
    cin >> N;
    if (N == 1) cout << 0 << '\n';
    else cout << powmod(2, findPrimeFactor(N)-1, MOD) << '\n';
    return 0;
}