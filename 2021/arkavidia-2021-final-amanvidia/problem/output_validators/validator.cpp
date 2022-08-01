#include <bits/stdc++.h>
#define LL long long
using namespace std;

const int EXIT_AC = 42;
const int EXIT_WA = 43;

int wa() {
    // cout << "WA" << endl;
    // return 0;
    exit(EXIT_WA);
}

int ac() {
    // cout << "AC" << endl;
    // return 0;
    exit(EXIT_AC);
}

int main(int argc, char* argv[]) {
    ifstream tc_in(argv[1]);
    ifstream tc_out(argv[2]);
    ifstream con_out(argv[3]);

    string tc_ans;
    tc_out >> tc_ans;

    string con_ans;
    if (!(cin >> con_ans)) {
        return wa();
    }

    LL n;
    tc_in >> n;
    LL cur = 0, mul10 = 1;
    set<char> digits;
    for (int i=con_ans.size()-1;i>=0;i--) {
        if (con_ans[i] < '0' || con_ans[i] > '9') return wa();
        cur += mul10 * (con_ans[i] - '0');
        cur %= n;
        mul10 *= 10;
        mul10 %= n;
        digits.insert(con_ans[i]);
    }
    if (cur == 0 && digits.size() <= 4) {
        return ac();
    } else {
        return wa();
    }
}