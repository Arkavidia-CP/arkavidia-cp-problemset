/** 
*   Author  : Morgen Sudyanto
*   Problem : Gembok Hokki
**/
#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define MOD 1000000007
#define INF 1234567890
#define pii pair<int,int>
#define LL long long
using namespace std;

void csort(vector<int> &p, vector<int> &c) {
    int n = p.size();
    int cnt[n+5];
    memset (cnt,0,sizeof(cnt));
    for (int i=0;i<c.size();i++) cnt[c[i]]++;
    vector<int> p_new(n);
    vector<int> pos(n);
    pos[0] = 0;
    for (int i=1;i<n;i++) {
        pos[i] = pos[i-1] + cnt[i-1];
    }
    for (int i=0;i<p.size();i++) {
        p_new[pos[c[p[i]]]] = p[i];
        pos[c[p[i]]]++;
    }
    p = p_new;
}

int main () {
    //clock_t start = clock();
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int tc;
    cin >> tc;
    while (tc--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        string ans = "";
        for (int i=0;i<s.size();i++) ans += s[i];
        for (int d = 0; d < 10; d++) {
            for (int i=0;i<s.size();i++) {
                s[i]++;
                if (s[i] > '9') s[i] -= 10;
            }
            int k = 0;
            vector<int> p(n);
            vector<pii> v;
            for (int i=0;i<s.size();i++) {
                v.pb({s[i], i});
            }
            sort (v.begin(), v.end());
            for (int i=0;i<s.size();i++) {
                p[i] = v[i].se;
            }

            vector<int> c(n);
            for (int i=1;i<v.size();i++) {
                if (v[i].fi == v[i-1].fi) c[p[i]] = c[p[i-1]];
                else c[p[i]] = c[p[i-1]] + 1;
            }

            while ((1 << k) < s.size()) {
                for (int i=0;i<n;i++) {
                    p[i] = (p[i] - (1 << k) + n) % n;
                }

                csort(p, c);

                vector<int> c_new(n);
                c_new[p[0]] = 0;
                for (int i=1;i<v.size();i++) {
                    pii prev = {c[p[i-1]], c[(p[i-1] + (1 << k)) % n]};
                    pii now = {c[p[i]], c[(p[i] + (1 << k)) % n]};
                    if (now == prev) c_new[p[i]] = c_new[p[i-1]];
                    else c_new[p[i]] = c_new[p[i-1]] + 1;
                }
                c = c_new;
                k++;
            }
            string minans = "";
            for (int i=p[0];i<s.size();i++) minans += s[i];
            for (int i=0;i<p[0];i++) minans += s[i];
            ans = min(ans, minans);
            // for (int i=0;i<s.size();i++) cout << p[i] << " ";
            // cout << endl;
        }
        cout << ans << endl;
    }

    //cerr << fixed << setprecision(3) << (clock()-start)*1./CLOCKS_PER_SEC << endl;
    return 0;
}

/*
3
4
1234
5
11114
3
100
*/