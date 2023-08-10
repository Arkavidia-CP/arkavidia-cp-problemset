#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5+5;
const int inf = 1e9;
int n,m;
vector<int> adj[maxn];
bool visited[maxn];
vector<int> value(maxn);
vector<int> ans(maxn, inf);

void dfs(int node){
    visited[node] = true;
    ans[node] = min(ans[node], value[node]);
    for(auto next:adj[node]){
        if(visited[next])continue;
        ans[next] = min(ans[next], ans[node]);
        dfs(next); 
    }
}

int main(){
    int n, root;
    scanf("%d %d", &n, &root);
    for(int i=1;i<=n;i++)scanf("%d", &value[i]);

    int a,b;
    for(int i=1;i<n;i++){
        scanf("%d %d", &a, &b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(root);
    for(int i=1;i<=n;i++){
        printf("%d", ans[i]);
        if(i == n)printf("\n");
        else printf(" ");
    }

    return 0;
}

/*
Sample Input/Output
6 1
9 6 7 4 8 5
5 2
2 3
5 4
1 2
3 6

4 1
3 1 5 5
2 3
1 3
4 2

9 1
8 1 7 6 9 7 5 10 8
5 9
3 7
5 1
8 1
4 1
9 3
5 6
9 2


*/