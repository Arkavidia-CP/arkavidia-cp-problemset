#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000;
const long long MOD = 1e9 + 7;

int t, n;
long long fibo[MAXN+2];

void gen(){
    fibo[1] = 1;
    fibo[2] = 1;
    for (int i = 3; i <= MAXN; ++i){
        fibo[i] = (fibo[i-1] + fibo[i-2]);
        fibo[i] %= MOD;
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    gen();
    cin >> t;
    while (t--){
        cin >> n;
        cout << fibo[n] << '\n';
    }
    return 0;
}