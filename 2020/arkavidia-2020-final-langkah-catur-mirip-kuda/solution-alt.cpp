#include <bits/stdc++.h>
#define fi first
#define se second

using namespace std;

const int MAXN = 5005;

char arr[MAXN+5][MAXN+5];
int N, M, A, B;
pair<int,int> awal, akhir;
queue<pair<int,int> > antri;

void preprocess(){
    
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < M; ++j){
            cin >> arr[i][j];
        }
    }
    cin >> awal.fi >> awal.se;
    cin >> akhir.fi >> akhir.se;
    
    preprocess();
    
    antri.push(awal);
    while (!antri.empty()){
        pair<int,int> now = antri.front(); antri.pop();

    }

    return 0;
}