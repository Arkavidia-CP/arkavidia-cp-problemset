#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int mx = *max_element(a.begin(), a.end());
    vector<vector<int>> primes(mx + 1);
    for (int i = 2; i <= mx; i++) {
        if (!primes[i].empty()) {
            continue;
        }
        for (int j = i; j <= mx; j += i) {
            primes[j].emplace_back(i);
        }
    }
    auto getAtMostX = [&](int x) -> long long {
        if (x < 0) {
            return 0;
        }
        long long ret = 0;
        vector<int> freq(mx + 1);
        for (int l = 0, r = 0; r < n; r++) {
            for (int p : primes[a[r]]) {
                if (freq[p] == 0) {
                    --x;
                }
                freq[p]++;
            }
            while (x < 0) {
                for (int p : primes[a[l]]) {
                    --freq[p];
                    if (freq[p] == 0) {
                        ++x;
                    }
                }
                l++;
            }
            ret += 1LL * (r - l + 1);
        }
        return ret;
    };
    cout << getAtMostX(k) - getAtMostX(k - 1) << '\n'; 
    
    return 0;
}