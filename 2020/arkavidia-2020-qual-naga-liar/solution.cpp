#include <bits/stdc++.h>
using namespace std;

constexpr long long PMOD = 1e9 + 7;

struct fracmod {
    fracmod() : fracmod(0) {}
    fracmod(long long x) : val{x} {
        val %= PMOD;
    }

    fracmod operator+(fracmod x) {
        return (val + x.val) % PMOD;
    }

    fracmod operator-(fracmod x) {
        return (val - x.val + PMOD) % PMOD;
    }

    fracmod operator*(fracmod x) {
        return (val * x.val) % PMOD;
    }

    fracmod pow(int k) {
        if (k == 0) return 1;
        if (k == 1) return *this;
        fracmod f = pow(k / 2);
        return f * f * pow(k % 2);
    }

    fracmod operator/(fracmod x) {
        return operator*(x.pow(PMOD - 2));
    }

    long long val;
};

long long n, p;
fracmod N, M;
int k;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    cin >> n;
    N = n;
    --n;
    for (p = 1; p <= n; p *= 2) {
        if (!(p & n)) {
            M = M - fracmod(p) * k;
        }
        ++k;
    }
    M = M + fracmod(p) * k;
    cout << (M / N).val << '\n';
}