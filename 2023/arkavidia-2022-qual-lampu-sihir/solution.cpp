//Easier version

#include<bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for(int i = (int) a; i<(int)b; i++)
#define pb push_back
#define mp make_pair
typedef long long ll;
typedef pair<int, int> pii;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    ll n,k;
    cin >> n >> k;
    ll base = 0LL, res = LLONG_MAX;
    ll a[n];
    for(int i=0; i<n; ++i) cin >> a[i];
    
    sort(a,a+n, greater<ll>());

    for(int i=0; i<n; ++i){
        while(k>a[i]){
            k/=2;
            ++base;
        }
        res = min(res, base+a[i]-k);
    }
    cout << res << '\n';
    return 0;
}