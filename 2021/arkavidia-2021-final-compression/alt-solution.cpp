/**
*   Author  : Muhammad Kamal Shafi
*   Problem : String Compression
**/
#pragma gcc optimize ("O2")
#pragma gcc optimize ("unroll-loops")

#include <bits/stdc++.h>


#define fi first
#define se second
#define pb(a) push_back(a)
#define mp(a, b) make_pair(a, b)
#define el '\n'

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int N = 7e2 + 10;
const int INF = 1e9 + 10;

int n;
string s;
int cost[27];
int z[N][N];
int dp[N][N];
int h[N][N];

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    cin >> s;
    cin >> cost[26];
    for (int i=0;i<26;i++){
        cin >> cost[i];
    }
    s = "*" + s;
    for (int i=1;i<=n;i++){
        for (int j=i + 1, l = i, r = i;j<=n;j++){
            if (j <= r) z[i][j] = min(r - j + 1, z[i][j - l + i]);
            while (j + z[i][j] <= n && s[i + z[i][j]] == s[j + z[i][j]]) ++z[i][j];
            if (j + z[i][j] - 1 > r){
                l = j;
                r = j + z[i][j] - 1;
            }
        }
    }
    for (int i=1;i<=n;i++){
        fill(dp[i], dp[i] + N, INF);
    }
    for (int len=1;len<=n;len++){
        if (len == 1){
            for (int i=1;i<=n;i++){
                dp[i][i] = cost[s[i] - 'a'];
                h[i][i] = i;
            }
        } else{
            for (int i=1;i + len - 1<=n;i++){
                int j = i + len - 1;
                for (int mid=h[i][j - 1];mid<=h[i + 1][j];mid++){
                    dp[i][j] = min(dp[i][j], dp[i][mid] + dp[mid + 1][j]);
                    if (!h[i][j]) h[i][j] = mid;
                    else if (dp[i][h[i][j]] + dp[h[i][j] + 1][j] > dp[i][mid] + dp[mid + 1][j]) h[i][j] = mid;
                }
            }
        }
        for (int i=1;i + len + len - 1 <= n;i++){
            for (int j=i + len;j + len - 1<=n;j+=len){
                if (z[i][j] >= len){
                    dp[i][j + len - 1] = min(dp[i][j + len - 1], dp[i][i + len - 1] + cost[26]);
                } else break;
            }
        }
    }
    cout << dp[1][n] << el;

    return 0;
}