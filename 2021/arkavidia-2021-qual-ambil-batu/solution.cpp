#include<bits/stdc++.h>
using namespace std;

long long seq[1<<20];
bool dp[(1<<20) + 20]; //true kalau elon menang

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    long long n, m, q, seen, mul;
    cin >> n >> q;
    long long A[n];
    for(int i=0; i<n; i++){
        cin >> A[i];
    }
    mul = 1;
    seen = 0;
    for(int i=0; i<20; i++){
        dp[i] = 0;
        for(int j=0; j<n; j++){
            if(A[j]<=i && !dp[i-A[j]]){
                dp[i] = 1;
            }
        }
        seen += mul*dp[i];
        mul*=2;
    }
    for(int i=0; i<mul; i++){
        seq[i] = -1;
    }
    mul/=2;
    int cur = 19;
    while(seq[seen]<0){
        cur++;
        seq[seen] = cur-20;
        dp[cur] = 0;
        for(int j=0; j<n; j++){
            dp[cur] = dp[cur] || (!dp[cur-A[j]]);
        }
        seen /= 2;
        seen += mul*dp[cur];
    }
    long long cyc = cur-19-seq[seen];
    for(int i=0; i<q; i++){
        cin >> m;
        if(m<seq[seen]){
            if(dp[m]){
                cout << "Elon" << endl;
            }else{
                cout << "Melvin" << endl;
            }
        }else{
            if(dp[(m-seq[seen])%cyc +seq[seen]]){
                cout << "Elon" << endl;
            }else{
                cout << "Melvin" << endl;
            }

        }
    }
}
