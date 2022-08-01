/* Author: Jauhar Wibisono
 * ngecek solusi arkavidia-2021-subgraph-divisibility paling banyak berapa node
 * tree 8 node buat input dapet dari sini:
 * https://math.stackexchange.com/questions/407562/gallery-of-unlabelled-trees-with-n-vertices
 */

#include <bits/stdc++.h>
using namespace std;

const int n = 8, mod = 4; // mod bisa diganti-ganti kalo mau ganti soal
int a[n], m;
bool vis[n];
vector<int> adjl[n];
vector<int> dp[n][mod];

const int maxx = 1e6+8;
int num_of_trees;
int max_ans_size = 0;
vector<pair<int,int>> max_input_tree;
vector<int> max_input_a;
vector<int> max_ans;

void dfs(int now){
    vis[now] = 1;
    dp[now][a[now]].push_back(now);
    vector<int> tmp[mod];
    for (int next : adjl[now]){
        if (vis[next]) continue;
        dfs(next);
        tmp[a[next]] = {next}; // buat ngecilin jawaban
        for (int i=0; i<mod; i++){
            if (!tmp[i].empty()) continue;
            tmp[i] = dp[next][i];
        }
    }
    for (int i=0; i<mod; i++){
        if (!tmp[i].empty()){
            dp[now][(i+a[now])%mod] = tmp[i];
            dp[now][(i+a[now])%mod].push_back(now);
        }
    }
    if (dp[now][a[now]].empty()) dp[now][a[now]] = {now};
}

void tree_check_dfs(int now){
    vis[now] = 1;
    for (int next : adjl[now]){
        if (vis[next]) continue;
        dfs(next);
    }
}

void reset_adjl(){
    for (int i=0; i<n; i++){
        adjl[i].clear();
    }
}

void reset_dp(){
    for (int i=0; i<n; i++){
        for (int j=0; j<mod; j++){
            dp[i][j].clear();
        }
    }
}

int main(){
    freopen("tree_8_node.txt","r",stdin); // input file: all possible trees with 7 nodes
    freopen("bruteforce_result.txt","w",stdout);
    // iterate through all trees of size 7
    cin >> num_of_trees;
    while (num_of_trees--){
        reset_adjl();
        for (int i=1; i<n; i++){
            int u, v;
            cin >> u >> v;
            adjl[u].push_back(v);
            adjl[v].push_back(u);
        }
        // iterate through all possible values
        for (long long values_mask=0; values_mask<(1LL<<(2*n)); values_mask++){
            reset_dp();
            // assign value to nodes
            for (long long pos=0; pos<n; pos++){
                a[pos] = (values_mask >> (pos << 1LL)) & 3LL;
            }
            // get solution
            memset(vis,0,sizeof vis);
            for (int i=0; i<n; i++){
                if (!vis[i]) dfs(i);
            }
            int cur_max_ans_size = maxx;
            vector<int> cur_max_ans;
            for (int i=0; i<n; i++){
                if (dp[i][0].size() > 1){
                    if ((int)dp[i][0].size() < cur_max_ans_size){
                        cur_max_ans_size = (int)dp[i][0].size();
                        cur_max_ans = dp[i][0];
                    }
                }
            }
            if (cur_max_ans_size != maxx && cur_max_ans_size > max_ans_size){
                max_ans_size = cur_max_ans_size;
                max_input_tree.clear();
                max_input_a.clear();
                for (int i=0; i<n; i++){
                    for (int j : adjl[i]){
                        if (i < j) max_input_tree.push_back({i+1,j+1}); 
                    }
                }
                for (int i=0; i<n; i++) max_input_a.push_back(a[i]);
                max_ans = cur_max_ans;
            }
        }
    }
    if (max_ans_size == 0) cout << "No sol\n";
    else{
        cout << "max ans size for all trees with " << n << " nodes is " << max_ans_size << "\n";
        cout << "input:\n";
        cout << n << " " << n-1 << "\n";
        for (int i=0; i<n; i++) cout << max_input_a[i] << " ";
        cout << "\n";
        for (auto p : max_input_tree) cout << p.first << " " << p.second << "\n";
        cout << "output:\n";
        cout << max_ans.size() << "\n";
        for (int u : max_ans) cout << u+1 << " ";
        cout << "\n";
    }
}
