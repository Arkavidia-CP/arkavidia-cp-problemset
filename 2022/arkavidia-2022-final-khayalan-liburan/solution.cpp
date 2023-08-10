#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;

#define fs first
#define sc second

const int p=2e5+5;
pll a[p];
ll b[p];
pll c[p];
ll d[p];
int ans[p];

void solve(){
    int n,m,k;
    cin>>n>>m>>k;
    for(int i=0;i<n;i++){
        cin>>a[i].fs;
        a[i].sc=i;
    }
    for(int i=0;i<n;i++){
        cin>>b[i];
    }
    for(int i=0;i<m;i++){
        cin>>c[i].fs;
        c[i].sc=i;
    }
    for(int i=0;i<m;i++){
        cin>>d[i];
    }
    sort(a,a+n);
    sort(c,c+m);
    int idx=0;
    set<pll>sets;
    for(int i=0;i<m;i++){
        while(idx<n && c[i].fs>=a[idx].fs){
            int pos=a[idx].sc;
            sets.insert({2*b[pos]+k,pos});
            idx++;
        }
        auto it=sets.lower_bound(make_pair(d[c[i].sc],0));
        if(it==sets.end()){
            ans[c[i].sc]=-1;
        }else{
            ans[c[i].sc]=it->sc+1;
        }
    }
    for(int i=0;i<m;i++){
        if(i==m-1){
            cout<<ans[i];
        }else{
            cout<<ans[i]<<" ";
        }
    }
    cout<<endl;
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