/**
* Author    : Muhammad Hasan (mhasan01)
* Problem   : Hadiah untuk Kembaran
**/
#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9 + 100;

void solve() {
    int n, x, y;
    cin >> n >> x >> y;
    int fpb = __gcd(x, y);
    int kpk = (x / fpb >= (INF + y - 1) / y ? INF : (x / fpb) * y);
    int budi_dono = n / kpk; // jumlah permen yang habis dibagi x dan y
    int budi = n / x - budi_dono; // jawaban untuk budi
    int dono = n / y - budi_dono; // jawaban untuk dono
    cout << budi << ' ' << dono << '\n';
}

int main() { 
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tc;
    cin >> tc;
    for (int T = 1; T <= tc; T++) {
        solve();
    }

    return 0;
}