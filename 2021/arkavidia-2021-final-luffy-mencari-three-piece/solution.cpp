#include<bits/stdc++.h>
using namespace std;

long long gcd(long long a, long long b){
    if(a>b){
        long long c = a;
        a = b;
        b = c;
    }
    if(a==0){
        return b;
    }else{
        return gcd(b%a, a);
    }
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    long long in[3], q, t, ans;
    char s;
    cin >> in[0] >> in[1] >> in[2] >> q;
    while(q>0){
        cin >> s >> t;
        in[s-'a'] += t;
        ans = in[0]+in[1]+in[2] -gcd(in[0],in[1])-gcd(in[0],in[2])-gcd(in[1],in[2]) +gcd(gcd(in[0],in[1]),in[2]);
        cout << ans << endl;
        q--;
    }
}
