#include<bits/stdc++.h>
using namespace std;

/* 
Problem: Hadiah Untuk Kembaran
Author: Hasan
Sol: Chintya W
*/

int lcm(int a, int b){
	int maks;
	if (a>b) maks = a;
	else maks = b;
	
	do {
		if (maks % a == 0 && maks % b == 0){
			return maks;
		}
		else ++maks;
	} while (true);
}

int main(){
	int q, n, x, y;
	cin>>q;
	for (int i=0;i<q;i++){
		cin>>n>>x>>y;
		int j,k;
		j = n/x - n/lcm(x,y);
		k = n/y - n/lcm(x,y);
		cout<<j<<" "<<k<<endl;
	}
}
