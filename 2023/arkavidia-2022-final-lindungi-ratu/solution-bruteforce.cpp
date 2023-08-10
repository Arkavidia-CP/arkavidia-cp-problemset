#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e3 + 5;
int mat[maxn][maxn];
int n, m;

int isPerimeter(int x, int y){
    return x == 0 || y == 0 || x == n-1  || y == m-1;
}

int dist(pair<int,int> a, pair<int,int> b){
    int dx = abs(a.first - b.first);
    int dy = abs(a.second - b.second);
    return max(dx,dy);
}

int main(){
    cin>>n>>m;
    char x;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++){
            cin>>x;
            mat[i][j] = (x == '*');
            // cin>>mat[i][j];
        }
    vector<pair<int,int>> coordinate0; // coordinate for 0 cell in perimeter
    vector<pair<int,int>> coordinate1; // coordinate for 1 cell inside matrix (excluding perimeter)
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++){
            if(isPerimeter(i,j)){
                if(mat[i][j] == 0)coordinate0.push_back({i,j});
            }else{
                if(mat[i][j] == 1)coordinate1.push_back({i,j});
            }
        }

    n = coordinate1.size();
    m = coordinate0.size();
    if(m > n){ // if cell that need to fill is more than available point, no solution   
        cout << -1 << endl;
        return 0;
    }

    // job assignment problem bruteforce solution O(n!)
    int jobassign[n][n] = {};
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            jobassign[i][j] = dist(coordinate1[i], coordinate0[j]);
        }       
    }

    int ans = 1e9;
    vector<int> pickjob; // how people pick the job
    for(int i=0;i<n;i++)pickjob.push_back(i);

    do{ // iterate all possible picking permutation O(n!)
        int count = 0;
        for(int i=0;i<n;i++){ // person i pick the job in pickjob[i] so jobasssign[i][pickjob[i]]
            count += jobassign[i][pickjob[i]];
        }
        ans = min(ans, count);
    }while(next_permutation(pickjob.begin(), pickjob.end()));

    cout << ans << endl;

    return 0;
}