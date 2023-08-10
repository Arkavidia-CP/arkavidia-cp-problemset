#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
int n, m;
vector<int> link(maxn);
vector<int> cost(maxn);
vector<int> sz(maxn);

int find(int x){
    int temp=x; 
    while(x!=link[x])x=link[x]; 
    link[temp]=x; 
    return x;
}

void unite(int a,int b){
    a=find(a); 
    b=find(b);
    if(a==b)return; 
    if(sz[a]<sz[b])swap(a,b); 
    sz[a]+=sz[b]; 
    link[b]=a; 
}

int main(){
    cin>>n>>m;
    int q;cin>>q;
    for (int i = 1; i <= n; i++) link[i] = i;
    for (int i = 1; i <= n; i++) sz[i] = 1;
    for (int i = 1; i <= n; i++) cin>>cost[i];

    multiset<int> repmin[n+1]; // representative minimum{cost, idx}
    for(int i=0;i<m;i++){
        int a,b;
        cin>>a>>b;
        unite(a,b);
    }

    for(int i=1;i<=n;i++){
        int rep = find(i);
        repmin[rep].insert(cost[i]);
    }
    
    while(q--){
        int t,a,b;
        cin>>t>>a>>b;
        if(t==1){
            int rep = find(a);
            repmin[rep].erase(repmin[rep].find(cost[a]));
            cost[a] = b;
            repmin[rep].insert(cost[a]);
        }else{
            a = find(a);
            b = find(b);
            if(a == b){
                cout<<0<<endl;
            }else{
                int ans = *repmin[a].begin() + *repmin[b].begin();
                cout<<ans<<endl;
            }
        }

    }
    

    return 0;
}