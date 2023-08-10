#include <bits/stdc++.h>
using namespace std;
 
const int inf = 1e9 + 7;
const int maxn = 2e5 + 5;
int n, root;
vector<int> adj[maxn];
vector<int> parent(maxn, -1);
vector<int> value(maxn);

void rooting(int node){
    for(int nxt : adj[node]){
        if(parent[nxt] == -1){
            parent[nxt] = node;
            rooting(nxt);
        }
    }
}

int traverse(int node){
    // move from node to root, O(n)
    int minimum = value[node];
    while(node != root){
        node = parent[node];
        minimum = min(minimum, value[node]);
    }
    return minimum;
}

int32_t main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>> n >> root;
    for(int i = 1; i <= n; i++)cin>>value[i];
    for(int i = 1; i < n ; i++){
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    parent[root] = -2;
    rooting(root);

    for(int i = 1; i <= n; i++){
        cout << traverse(i) << " ";
    }
    cout << endl;    
    
    
    
    return 0;
}
