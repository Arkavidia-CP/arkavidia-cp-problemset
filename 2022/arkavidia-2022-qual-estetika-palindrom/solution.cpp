#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MOD = 1e9 + 7;
const int NLOGMAX = 16; // TODO : NLOGMAX = 16
int32_t main() {
    string s; cin >> s;
    vector<int> jml(26, 0);
    for(int i = 0; i < s.length(); i++) {
        jml[s[i]-'a']++;
    }

    vector<vector<int>> dp(27, vector<int>(1 << 16, 0));
    
    dp[0][0] = 1;
    for(int i = 1; i <= 26; i++) {
        for(int j = 0; j < (1 << NLOGMAX); j++) {
            for(int k = j; k >= j-jml[i-1] && k > 0; k = (k-1) & j) {
                dp[i][j] += dp[i-1][k];
                dp[i][j] %= MOD;
            }
            if(j <= jml[i-1]) {
                dp[i][j] += dp[i-1][0];
                dp[i][j] %= MOD;
            }
        }
    }
    int ans = 0;
    for(int i = 1; i <= NLOGMAX; i++) {
        ans = (ans + dp[26][(1 << i) - 1]) % MOD;
    }
    cout << ans << '\n';

    
}