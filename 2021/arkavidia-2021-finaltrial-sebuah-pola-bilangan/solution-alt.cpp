#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define pb push_back

typedef long long LL;

int tc;
LL n, k;

pair<LL, LL> f(LL n, LL k){
    LL bil = (4 * n + 11) / 8;
    LL tot;
    if (n%2 == 0) {
        tot = bil-1;
    }else {
        tot = bil;
    }
    LL lo = 1;
    LL hi = tot;
    LL pertama = 4 * n * tot - 4 * tot * (tot + 1) + 4 * tot;
    LL indeks = tot;
    while (lo <= hi){
        LL mid = (lo + hi) >> 1;
        if (4 * n * mid - 4 * mid *(mid+1) + 4*mid >= k){
            pertama = 4 * n * mid - 4 * mid * (mid+1) + 4*mid;
            indeks = mid;
            hi = mid - 1;
        }else {
            lo = mid + 1;
        }
    }
    LL selisih = k - (4 * n *(indeks-1) - 4 *(indeks-1)*indeks + 4*(indeks-1));
    LL size = n + 2 - 2 * indeks;
    LL x, y;
    // cout << selisih << " " << indeks << " " << size << '\n';
    if (selisih % 4 == 1) {
        x = indeks; y = indeks;
        x += selisih / 4;
    }else if (selisih % 4 == 2){
        x = indeks+size-1; y = indeks;
        y += selisih / 4;
    }else if (selisih%4 == 3){
        x = indeks+size-1; y = indeks+size-1;
        x -= selisih / 4;
    }else {
        x = indeks; y = indeks+size-1;
        y -= (selisih/4 - 1);
    }
    return {x, y};
}

int main(){
    // ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> tc;
    while(tc--){
        cin >> n >> k;
        pair<LL, LL> ans = f(n, k);
        cout << ans.fi << " " << ans.se << '\n';
    }
    return 0;
}