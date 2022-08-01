#include <bits/stdc++.h>
#define LL long long
using namespace std;

int wa() {
    cout << "WA" << endl;
    return 0;
}

int ac() {
    cout << "AC" << endl;
    return 0;
}

int main(int argc, char* argv[]) {
    ifstream tc_in(argv[1]);
    ifstream tc_out(argv[2]);
    ifstream con_out(argv[3]);

    string tc_ans;
    tc_out >> tc_ans;

    string con_ans;
    if (!(con_out >> con_ans)) {
        return wa();
    }

    LL n;
    tc_in >> n;
    LL cur = 0, mul10 = 1;
    bitset<10> ada;
    ada.reset();
    for (int i=con_ans.size()-1;i>=0;i--) {
        if (con_ans[i] < '0' || con_ans[i] > '9') return wa();
        cur += mul10 * (con_ans[i] - '0');
        cur %= n;
        mul10 *= 10;
        mul10 %= n;
        ada[con_ans[i] - '0'] = 1;
    }
    if (cur == 0 && ada.count() <= 4 && !ada[2] && !ada[3] && !ada[4] && !ada[5] && !ada[6] && !ada[7]) {
        return ac();
    } else {
        return wa();
    }
}