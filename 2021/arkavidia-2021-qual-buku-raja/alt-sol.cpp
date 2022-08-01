/* Author: Jauhar Wibisono
 * alt-sol arkavidia-2021-perintah-raja-mastre
 */

#include <bits/stdc++.h>
using namespace std;

const int maxn=1e5+6, maxm=1e5+6;
int n, m;
int pos[maxn];
long long bit[maxn+maxm];
long long ans=0;

void update(int pos, long long val){
	while (pos<maxn+maxm){
		bit[pos]+=val;
		pos+=pos&-pos;
	}
}

long long query(int pos){
	long long ret=0;
	while (pos>0){
		ret+=bit[pos];
		pos-=pos&-pos;
	}
	return ret;
}

int main(){
	cin >> n >> m;
	for (int i=0;i<n;i++){
		int b;
		cin >> b;
		pos[b]=m+i+1;
	}
	memset(bit,0,sizeof bit);
	for (int i=m+2;i<=n+m+1;i++) update(i,1);
	for (int i=0;i<m;i++){
		int x;
		cin >> x;
		ans+=query(pos[x]);
		update(pos[x],-1);
		pos[x]=m-i;
		update(pos[x]+1,1);
	}
	cout << ans*2 << "\n";
}