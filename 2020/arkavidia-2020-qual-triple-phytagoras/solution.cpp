#include <bits/stdc++.h>

using namespace std;

long long n;
set<long long> st;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    cin >> n;

    for(long long i = 3; i * i <= n; i += 2){
        while(n % i == 0){
            st.insert(i);
            n /= i;
        }
    }

    if(n > 2){
        st.insert(n);
    }

    long long res = 1;
    for(int i = 0; i < st.size(); i++){
        res *= 2;
    }
    res /= 2;
    cout << res << '\n';
    return 0;
}