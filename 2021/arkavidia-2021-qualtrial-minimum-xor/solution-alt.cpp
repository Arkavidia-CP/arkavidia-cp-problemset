#include <bits/stdc++.h>


#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define MOD 1000000007
#define pii pair<int,int>
#define pli pair<long long,int>
#define pil pair<int,long long>
#define ll long long
#define el '\n'

using namespace std;

ll n, k;

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k;

    if (k==1){
        cout << n << el;
        return 0;
    }

    if (n%2==0){
        cout << 0 << el;
        return 0;
    }  
    if (k>2){
        cout << 1 << el;
        return 0;
    }

    ll tot = 0;
    for (ll i=0;i<61;i++){
        ll tm = ((ll)1 << i);

        if ((tm&n)==0) break;
        tot+=tm;
    }

    cout << tot << el;

    return 0;
}