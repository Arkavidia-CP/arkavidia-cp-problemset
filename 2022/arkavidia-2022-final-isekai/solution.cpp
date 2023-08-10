#include <bits/stdc++.h>

using namespace std;

int main() {
    long long n, k;
    cin >> n >> k;
    if(n == k+1) {
        cout << "1 1\n";
    }
    else {
        long long u = n-1;
        long long l = n * (n-1-k);
        long long gcd = __gcd(u, l);
        u /= gcd;
        l /= gcd;
        cout << u << ' ' << l << '\n';
    }
    return 0;
}