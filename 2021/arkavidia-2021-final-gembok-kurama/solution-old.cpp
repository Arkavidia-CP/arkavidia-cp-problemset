//W A S
//GembokHokki
#include <bits/stdc++.h>
using namespace std;
int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t, cs = 1;  cin >> t;
	while(t--){
        int n; cin >> n;
        string s, ans = ""; cin >> s;
        for(int i = 0; i < n; i ++) ans += '9';
        for(int i = 0; i < n; i ++) {
            int t = (10 - (s[i] - '0')) % 10;
            string temp;
            for(int j = i; j < n; j++)	temp += ('0' + (char)(((int)s[j] + t - '0') % 10));
            for(int j = 0; j < i; j++)	temp += ('0' + (char)(((int)s[j] + t - '0') % 10));
            ans = min(ans, temp);
        }
        cout << "Kasus ke- " << cs++ << ":" << endl;
        cout << ans << endl;
	}
	return 0;
}
