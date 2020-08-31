#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int MAXN = 5000;
const LL MOD = 1e9 + 7;


int N, K;
int condition[MAXN+5], arr[MAXN+5];
int prefiks[MAXN+5];
LL dp[MAXN+3][MAXN+3];

int query(int l, int r){
    return (l == 0 ? prefiks[r] : prefiks[r] - prefiks[l-1]);
}

LL cari(int board, int ar){
    if (board >= N){
        if (ar == K) return 1;
        else return 0;
    }
    if (ar == K){
        if (query(board, N-1) == 0) return 1;
        else return 0;
    }
    if (dp[board][ar] != -1) return dp[board][ar];
    LL ways = 0;
    if (condition[board] == 0){
        ways = (ways + cari(board + 1, ar))%MOD;
        int neks = board + arr[ar] - 1;
        if (neks < N && (neks + 1 == N || condition[neks+1] == 0)){
            ways = (ways + cari(neks+2, ar + 1))%MOD;
        }
    }else {
        int neks = board + arr[ar] - 1;
        if (neks < N && (neks + 1 == N || condition[neks+1] == 0)){
            ways = (ways + cari(neks+2, ar + 1))%MOD;
        } 
    }
    return dp[board][ar] = ways;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    for (int i = 0; i < N; ++i){
        cin >> condition[i];
        prefiks[i] = (i == 0 ? condition[i] : condition[i] + prefiks[i-1]);
    }
    cin >> K;
    for (int i = 0; i < K; ++i){
        cin >> arr[i];
    }
    memset(dp, -1, sizeof dp);
    cout << cari(0, 0) << '\n';
    return 0;
}