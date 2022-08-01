#include<bits/stdc++.h>
using namespace std;

long long vis[20000069], mod[20000069];

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    long long n, x, y;
    cin >> n;
    for(int i=0; i<n; i++){
        vis[i] = -1;
    }
    mod[0] = 0;
    vis[0] = 0;
    bool notfound = true;
    for(int i=1; notfound; i++){
        mod[i] = (mod[i/2]*10 + i%2)%n;
        if(vis[mod[i]]>=0){
            x = vis[mod[i]];
            y = i;
            notfound = false;
        }else{
            vis[mod[i]] = i;
        }
    }
    string xs = "";
    string ys = "";
    for(int i=0; (x>0 || y>0); i++){
        if(x%2 == 0){
            xs = "0" + xs;
        }else{
            xs = "1" + xs;
        }
        if(y%2 == 0){
            ys = "0" + ys;
        }else{
            ys = "1" + ys;
        }
        x = x/2;
        y = y/2;
    }
    string ans = xs;
    long long m = xs.length();
    long long ngutang = 0;
    for(int i=m-1; i>=0; i--){
        if(xs[i]+ngutang > ys[i]){
            ans[i] = ys[i]+10-xs[i]-ngutang+'0';
            ngutang = 1;
        }else{
            ans[i] = ys[i]-xs[i]-ngutang+'0';
            ngutang = 0;
        }
    }
    bool leadingzero = true;
    for(int i=0; i<m; i++){
        if(ans[i] != '0'){
            leadingzero = false;
        }
        if(!leadingzero){
            cout << ans[i];
        }
    }
    cout << endl;
}