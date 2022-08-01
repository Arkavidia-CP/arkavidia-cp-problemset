#include<bits/stdc++.h>
using namespace std;

long long mpow(long long a, long long b, long long mod){
    long long pw[30];
    pw[0] = a;
    for(int i=1; i<30; i++){
        pw[i] = (pw[i-1]*pw[i-1])%mod;
    }
    long long c = b, ret = 1;
    for(int i=0; i<30; i++){
        if(c%2==1){
            ret = (ret*pw[i])%mod;
        }
        c /= 2;
    }
    return ret;
}

long long inverse(long long a, long long mod){
    return mpow(a, mod-2, mod);
}

const long long mod = 998244353;
const long long root = 15311432;
const long long root_1 = 469870224;
const long long root_pw = 1 << 23;

void fft(vector<long long> & a, bool invert) {
    long long n = a.size();

    for (int i = 1, j = 0; i < n; i++) {
        long long bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        long long wlen = invert ? root_1 : root;
        for (int i = len; i < root_pw; i <<= 1)
            wlen = (long long)(1LL * wlen * wlen % mod);

        for (int i = 0; i < n; i += len) {
            long long w = 1;
            for (int j = 0; j < len / 2; j++) {
                long long u = a[i+j], v = (long long)(1LL * a[i+j+len/2] * w % mod);
                a[i+j] = u + v < mod ? u + v : u + v - mod;
                a[i+j+len/2] = u - v >= 0 ? u - v : u - v + mod;
                w = (long long)(1LL * w * wlen % mod);
            }
        }
    }
    if (invert) {
        long long n_1 = inverse(n, mod);
        for(int i=0; i<a.size(); i++){
            a[i] = (long long)(1LL * a[i] * n_1 % mod);
        }

    }
}

vector<long long> multiply(vector<long long> const& a, vector<long long> const& b) {
    vector<long long> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    long long n = 1;
    while (n < a.size() + b.size())
        n <<= 1;
    fa.resize(n);
    fb.resize(n);
    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] = (fa[i]*fb[i])%mod;
    fft(fa, true);
    vector<long long> result(n);
    for (int i = 0; i < n; i++)
        result[i] = fa[i];
    return result;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    long long n, m, r, A;
    cin >> n >> m >> r;
    vector <long long> exp[60], ans;
    for(int i=0; i<n; i++){
        exp[0].push_back(0);
    }
    for(int i=0; i<m; i++){
        cin >> A;
        exp[0][A%n]++;
    }
    for(int i=1; i<60; i++){
        exp[i] = multiply(exp[i-1], exp[i-1]);
        for(int j=0; j<n; j++){
            exp[i][j] %= mod;
        }
        for(int j=n; j<exp[i].size(); j++){
            exp[i][j%n] = (exp[i][j%n] + exp[i][j])%mod;
        }
        exp[i].resize(n);
    }
    ans.push_back(1);
    for(int i=1; i<n; i++){
        ans.push_back(0);
    }
    for(int i=0; i<60; i++){
        if(r%2==1){
            ans = multiply(ans, exp[i]);
            for(int j=0; j<n; j++){
                ans[j] %= mod;
            }
            for(int j=n; j<ans.size(); j++){
                ans[j%n] = (ans[j%n] + ans[j])%mod;
            }
            ans.resize(n);
        }
        r/=2;
    }
    for(int i=0; i<n; i++){
        cout << ans[i];
        if (i != n - 1) cout << " ";
    }
    cout << endl;
}
