#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
#define el '\n'
#define MOD 1000000007
const int N = 101;
int n;
long long num, arr[N], pref[N];
set<long long> st;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> arr[i];
    }
    cin >> num;
    for(int i = 1; i <= n; i++){
        if(arr[i] <= num){
            st.insert(arr[i]);
        }
    }
    

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= 64; j++){
            vector<long long> vc;
            for(auto x : st){
                if(x * arr[i] > num){
                    break;
                } else {
                    vc.push_back(x * arr[i]);
                }
            }
            for(auto x : vc){
                st.insert(x);
            }
        }
    }
    cout << st.size() << '\n';

    return 0;
}