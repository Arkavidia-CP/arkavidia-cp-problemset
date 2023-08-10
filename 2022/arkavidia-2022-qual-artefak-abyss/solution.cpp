#include <bits/stdc++.h>
using namespace std;

int main(){
    int n,m,k;
    cin>>n>>m>>k;

    int potion;
    long long x,y;
    cin>>potion>>x>>y;

    long long a[n];
    long long b[m];
    long long c[k];
    for(int i=0;i<n;i++)cin>>a[i];
    for(int i=0;i<m;i++)cin>>b[i];
    for(int i=0;i<k;i++)cin>>c[i];

    long long level1 = 0;
    for(int i=0;i<n;i++)level1 += a[i];

    sort(b,b+m, greater<long long>());
    sort(c,c+k, greater<long long>());

    long long pref2[m+1];
    long long pref3[k+1]; // prefsum for using i potion how many value we can get
    pref2[0] = 0;
    pref3[0] = 0;
    for(int i=1;i<=m;i++){
        pref2[i] = pref2[i-1] + b[i-1];
    }
    for(int i=1;i<=k;i++){
        pref3[i] = pref3[i-1] + c[i-1];
    }

    long long pick2[m+1];
    long long pick3[k+1]; // if we pick only i value without potion how many value we can get
    pick2[0] = 0;
    pick3[0] = 0;
    for(int i=1;i<=m;i++){
        if(b[m-i] > x){ // we pick if the value greater than penalty
            pick2[i] = pick2[i-1] + b[m-i] - x;
        }else pick2[i] = pick2[i-1];
    }
    for(int i=1;i<=k;i++){
        pick3[i] = (pick3[i-1] + c[k-i]) / y ;
    }

    long long best23 = 0; // best potion choice for level 2 and 3
    for(int pot2 = 0; pot2 <= min(m, potion); pot2++){
        int pot3 = potion - pot2;
        pot3 = min(pot3, k);
        long long value = pref2[pot2] + pref3[pot3] + pick2[m-pot2] + pick3[k-pot3];
        best23 = max(best23, value);
    }

    long long ans = best23 + level1;
    cout << ans << endl;
    return 0;
}