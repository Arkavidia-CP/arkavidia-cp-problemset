#include <bits/stdc++.h>
using namespace std;

constexpr long long PMOD = 1e9 + 7;
long long N;

long long powmod(long long x) {
    if (x == 0) return 1;
    if (x == 1) return 3;
    long long p = powmod(x / 2);
    return (((p * p) % PMOD) * powmod(x % 2)) % PMOD;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    cin >> N;
    if (N == 4) {
        cout << 1 << '\n';
    } else {
        cout << (2 * powmod(N-5)) % PMOD << '\n';
    }
}