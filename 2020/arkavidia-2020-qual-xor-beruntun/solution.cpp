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

const int N = 2e5 + 7;

int n;
int ar[N];

int fac[N];

bool comb(int a, int b){
    int atas = fac[a];
    int bawah = fac[b] + fac[a-b];

    return (bawah>=atas);
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i=1;i<=n;i++){
        cin >> ar[i];
    }

    for (int i=1;i<N;i++){
        int tm = 0;
        int cur = i;
        while (cur % 2 == 0){
            tm++;
            cur/=2;
        }

        fac[i] = fac[i-1] + tm;
    }

    int res = 0;
    for (int i=1;i<=n;i++){
        if (comb(n-1, i-1)){
            res = (res ^ ar[i]);
        }
    }

    cout << res << el;

    return 0;
}