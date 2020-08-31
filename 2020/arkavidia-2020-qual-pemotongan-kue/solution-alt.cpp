#include <bits/stdc++.h>

typedef long long LL;

using namespace std;

const int MOD = 1e9 + 7;

LL binpow(LL a, LL b){
	LL res = 1;
	while(b>0){
		res *= a;
		res %= MOD;
		if (b&1) {
			a *= a;
			a %= MOD;
		}
		b >>= 1;
	}
	return res;
}

int main(){
	LL n;
	cin >> n;
	if(n==4){
		cout << 1 << endl;
	} else {
		cout << 2 * binpow(3,n-5) << endl;
	}
}

