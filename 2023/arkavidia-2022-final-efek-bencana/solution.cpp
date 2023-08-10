#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define pb push_back
#define sz(x) (int)(x.size()) 

const int p=3e5+5;
int val[p];
ll tot[p];
int pos[p];
int edgein[p];

void solve(){
    int n,m;
    cin>>n>>m;
    for(int i=0;i<n;i++){
        cin>>val[i];
    }
    for(int i=0;i<n;i++){
        cin>>pos[i];
        pos[i]--;
        tot[pos[i]]+=val[i];
    }
    for(int i=0;i<m;i++){
        edgein[i]=0;
    }
    vector<vector<int>>adj(m+1);
    for(int i=0;i<m-1;i++){
        int u,v;
        cin>>u>>v;
        u--;v--;
        adj[u].pb(v);
        edgein[v]++;
    }
    deque<int>dq;
    for(int i=0;i<m;i++){
        if(edgein[i]!=0)continue;
        dq.pb(i);
    }
    while(!dq.empty()){
        int u=dq[0];
        dq.pop_front();
        for(int v:adj[u]){
            tot[v]+=tot[u];
            edgein[v]--;
            if(edgein[v]==0){
                dq.pb(v);
            }
        }
    }
    ll mxm=0;
    for(int i=0;i<m;i++){
        mxm=max(mxm,tot[i]);
    }
    vector<int>ans;
    for(int i=0;i<m;i++){
        if(mxm!=tot[i])continue;
        ans.pb(i);
    }
    cout<<sz(ans)<<endl;
    for(int i=0;i<sz(ans);i++){
        if(i==sz(ans)-1){
            cout<<ans[i]+1;
        }else{
            cout<<ans[i]+1<<" ";
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