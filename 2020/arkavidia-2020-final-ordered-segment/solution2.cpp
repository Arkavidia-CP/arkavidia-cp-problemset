#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
int n, q, arr[N], ne[N], pre0[N], pre1[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    cin >> n >> arr[1];
    pre1[1] = 1;
    ne[1] = 1;

    for(int i = 2; i <= n; i++){
        cin >> arr[i];

        if(arr[i] > arr[i - 1]){
            pre1[i] = pre1[i - 1] + 1;
            pre0[i] = pre0[i - 1];
            ne[i] = 1;
        } else {
            pre1[i] = pre1[i - 1];
            pre0[i] = pre0[i - 1] + 1;
            ne[i] = 0;
        }
    }



    cin >> q;
    while(q--){
        int a, b;
        cin >> a >> b;

        int cnt0 = pre0[b] - pre0[a - 1];
        int cnt1 = pre1[b] - pre1[a - 1];

        if(cnt0 > 1){
            cout << "TIDAK" << '\n';
        } else {
            if(cnt0 == 0){
                cout << "YA" << '\n';
            } else {
                if(ne[a] == 0){
                    cout << "YA" << '\n';
                } else {
                    cout << "TIDAK" << '\n';
                }
            }
        }
    }
    return 0;
}