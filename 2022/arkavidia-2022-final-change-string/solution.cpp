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
    
    string s;
    int n;
    cin >> n;
    cin >> s;
    bool odds[20];
    memset(odds, false, sizeof(odds));
    for(int i=1; i<=s.size(); ++i){
        if(s[s.size() - i] == 'A'){
            int k = __builtin_ctz(i);
            odds[k] = !(odds[k]);
        }
    }
    bool win = false;
    for(bool u : odds){
        win |= u;
    }
    if(win) cout << "Arka\n";
    else cout << "Vidia\n";
}