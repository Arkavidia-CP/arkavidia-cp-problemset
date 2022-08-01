#include <bits/stdc++.h>
using namespace std;

long long N, K;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    cin >> N >> K;
    if (K >= 3) {
        cout << N % 2 << '\n';
    } else if (K == 1) {
        cout << N << '\n';
    } else {
        cout << ((N ^ (N+1)) >> 1) << '\n';
    }
}