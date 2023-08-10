#include <bits/stdc++.h>
using namespace std;

int main(){
    int n,k;
    cin>>n>>k;
    k = min(k, n-k);
    int arr[n];
    for(int &num:arr)cin>>num;

    int totalsum = accumulate(arr, arr+n, 0);
    int dp[totalsum+1][k] = {};
    vector<pair<int,int>> state; // all state that {sum, student} is possible 
    dp[0][0] = 1;
    state.push_back({0,0});

    vector<int> sumk; // state that can be reached by using k student
    for(int num:arr){
        int len = state.size();
        for(int i=0;i<len;i++){
            int sum = state[i].first;
            int student = state[i].second;
            if(sum + num <= totalsum && dp[sum+num][student+1] == 0){
                dp[sum+num][student+1] = 1;
                if(student < k-1)state.push_back({sum+num, student+1});
                else sumk.push_back(sum+num);
            }
        }
    }
    
    int ans = totalsum;
    for(int sum:sumk)
        ans = min(ans, abs((totalsum-sum) - sum));
    
    cout<<ans<<endl;
    

    return 0;
}
/*
Sample Input/Output

6 3
4 2 9 8 8 6 
1

5 4
7 8 8 7 9 
21

9 6
9 3 3 5 10 3 4 6 3 
0

5 2
7 9 3 10 4 
1
*/