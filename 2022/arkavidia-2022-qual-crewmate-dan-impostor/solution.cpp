#include "bits/stdc++.h"
using namespace std;

#define ll long long
#define ar array
#define sz(x) (int) (x).size()
#define pii pair<int,int>
#define fi first
#define se second
#define ppii pair<pii,pii>

template<typename T>
void min_self(T& A, T B) {
    A = min(A,B);
}
template<typename T>
void max_self(T& A, T B) {
    A = max(A,B);
}

const int mxn=1e5;
int n;
int t[mxn];
int in[mxn], ct[mxn][2];

// tree tunjuk cycle
// tree: (ct0,ct1). parent ct0_parent = sum max(ct0_child,ct1_child) ct1_parent = sum ct0_child
// dp[n][2]. max imposter pas node kiri imporster, max imposter pas node kiri crewmate. [2] lagi buat ujung kanan  

void solve() {
    cin >>n;
    queue<int> q;
    for(int i=0;i<n;i++) {
        cin >>t[i]; t[i]--;
        in[t[i]]++;
    }
    for(int i=0;i<n;i++) {
        ct[i][1] = 1;
    }
    for(int i=0;i<n;i++) {
        if(in[i]==0) {
            q.push(i);
        }
    }
    while(sz(q)) {
        int u = q.front(); q.pop();
        ct[t[u]][0] += max(ct[u][0],ct[u][1]);
        ct[t[u]][1] += ct[u][0];
        in[t[u]]--;
        if(in[t[u]]==0) {
            q.push(t[u]);
        }
    }
    int ans=0;
    for(int i=0;i<n;i++) {
        if(in[i]) {
            // cycle
            int l = i;
            int r = t[i];
            in[r]--;
            ppii dp;
            dp = {{ct[l][0]+ct[r][0],ct[l][0]+ct[r][1]},{ct[l][1]+ct[r][0],0}};
            while(t[r]!=l) {
                ppii new_dp;
                r = t[r];
                in[r]--;
                new_dp.fi.fi = max(dp.fi.fi,dp.fi.se)+ct[r][0];
                new_dp.se.fi = max(dp.se.fi,dp.se.se)+ct[r][0];
                new_dp.fi.se = dp.fi.fi + ct[r][1];
                new_dp.se.se = dp.se.fi + ct[r][1];
                swap(dp,new_dp);
            }
            in[l]--;
            int temp = max(dp.fi.fi,dp.fi.se);
            max_self(temp, dp.se.fi);
            ans += temp;
        }
    }
    // cout <<ans <<"\n";
    cout <<min((n-1)/2,ans) <<"\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
}