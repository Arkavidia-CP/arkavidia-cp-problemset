#include<bits/stdc++.h>
using namespace std;

pair <long long, long long> bezout(long long a, long long b){
    if(a==0){
        return {0, 1};
    }else{
        pair <long long, long long> rek = bezout(b%a, a);
        return {rek.second - (b/a)*rek.first, rek.first};
    }
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    pair <long long, long long> bez, mul;
    long long q, n, m, x, y, ans, rn, rm, gcd, bounce, dif;
    cin >> q;
    while(q>0){
        cin >> n >> m >> x >> y;
        bez = bezout(n, m);
        gcd = 2*n*bez.first + 2*m*bez.second;
        rn = 2*n/gcd;
        rm = 2*m/gcd;
        ans = 1e18;
        if((y-x)%gcd == 0){
            dif = (y-x)/gcd;
            mul.first = (bez.first * dif % rm +rm)%rm;
            mul.second = (-bez.second * dif % rn + rn)%rn;
            ans = min(ans, x + 2*n*mul.first);
        }
        if(((2*m+1-y)-x)%gcd == 0){
            dif = (2*m+1-y-x)/gcd;
            mul.first = (bez.first * dif % rm +rm)%rm;
            mul.second = (-bez.second * dif % rn + rn)%rn;
            ans = min(ans, x + 2*n*mul.first);
        }
        if((y-(2*n+1-x))%gcd == 0){
            dif = (y-(2*n+1-x))/gcd;
            mul.first = (bez.first * dif % rm +rm)%rm;
            mul.second = (-bez.second * dif % rn + rn)%rn;
            ans = min(ans, (2*n+1-x) + 2*n*mul.first);
        }
        if(((2*m+1-y)-(2*n+1-x))%gcd == 0){
            dif = ((2*m+1-y)-(2*n+1-x))/gcd;
            mul.first = (bez.first * dif % rm +rm)%rm;
            mul.second = (-bez.second * dif % rn + rn)%rn;
            ans = min(ans, (2*n+1-x) + 2*n*mul.first);
        }
        if(2*n*m/gcd<ans){
            cout << 0 << endl;
        }else{
            bounce = (ans-1)/n + (ans-1)/m;
            cout << bounce%9 +1 << endl;
        }
        q--;
    }
}
