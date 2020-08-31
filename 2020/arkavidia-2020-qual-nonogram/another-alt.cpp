#include <bits/stdc++.h>
using namespace std;
#define MAXN 5000
#define INF 1000000007

int dp[MAXN+5][MAXN+5];
int arr[MAXN+5], block[MAXN+5];
int n,k;

bool jumpCheck(int now, int pos){
	return now + block[pos] <= n && !arr[now+block[pos]];
}

int rekur(int now, int pos){
	if(now >= n){
		return (pos == k);
	}

	int &ret = dp[now][pos];
	if(ret != -1)return ret;

	if(pos == k){
		if(arr[now]) ret = 0;
		else ret = rekur(now+1, pos);
	} else {
		if(arr[now]){
			if(jumpCheck(now, pos)){
				ret = rekur(now+block[pos]+1, pos+1);
			} else {
				ret = 0;
			}
		} else {
			ret = rekur(now+1, pos);
			if(jumpCheck(now, pos)){
				ret += rekur(now+block[pos]+1, pos+1);
			}
		}
	}
	ret %= INF;
	return ret;
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%d", &arr[i]);
	}
	scanf("%d", &k);
	for(int i = 0; i < k; i++){
		scanf("%d", &block[i]);
	}
	memset(dp, -1, sizeof(dp));
	printf("%d\n", rekur(0,0));
}