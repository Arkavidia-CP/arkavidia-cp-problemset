#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define pb push_back
#define sz(x) (int)(x.size())

const ll INF = 1e18;

const int p=1e5+5;
int a[p];
ll dp[p][305];

void solve(){
    int n,k,l,x,y,z;
    cin>>n>>k>>l>>x>>y>>z;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    a[0]=0;
    a[n+1]=k;
    for(int i=1;i<=n+1;i++){
        for(int j=1;j<=z;j++){
            dp[i][j]=INF;
        }
    }
    dp[0][0]=0;
    for(int i=1;i<=n+1;i++){
        dp[i][0]=dp[i-1][0]+a[i]-a[i-1];
        if(i!=n+1){
            dp[min(i+l,n)][1]=min(dp[min(i+l,n)][1],dp[i][0]+x);
        }
        for(int j=1;j<=z;j++){
            dp[i][j]=min(dp[i][j],dp[i][j-1]);
            dp[i][j]=min(dp[i][j],dp[i-1][j]+a[i]-a[i-1]);
            if(i!=n+1){
                dp[min(i+l,n)][j+1]=min(dp[min(i+l,n)][j+1],dp[i][j]+x);
            }
        }
    }
    for(int i=0;i<=z;i++){
        if(y>=dp[n+1][i]){
            cout<<i<<endl;
            return;
        }
    }
    cout<<-1<<endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t=1;

    while(t--){
        solve();
    }

    return 0;
}