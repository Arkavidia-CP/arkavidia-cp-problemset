#include <bits/stdc++.h>
using namespace std;
#define MAXN 200000
int arr[MAXN+5], temp[MAXN+5];
int n;

//Lucas theorem
int oddCheck(int a, int b){
	while(b){
		if(!(a&1) && (b&1)){
			return false;
		}
		a >>= 1;
		b >>= 1;
	}
	return true;
}

int calc(){
	int res = 0;
	for(int i = 0; i <= n-1; i++){
		if(oddCheck(n-1, i)){
			res ^= arr[i];
		}
	}
	return res;
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%d", &arr[i]);
	}
	printf("%d\n", calc());
}