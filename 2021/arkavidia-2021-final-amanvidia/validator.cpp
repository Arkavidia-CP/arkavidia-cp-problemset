#include <bits/stdc++.h>
#define LL long long
using namespace std;

const int EXIT_AC = 42;
const int EXIT_WA = 43;

int wa() {
    exit(EXIT_WA);
}

int ac() {
    exit(EXIT_AC);
}

int main(int argc, char* argv[]) {
    ifstream tc_in(argv[1]);
    ifstream tc_out(argv[2]);
    string feedback_path = argv[3];
    feedback_path += "/judgeerror.txt";
    ofstream feedback(feedback_path);

    string tc_ans;
    tc_out >> tc_ans;

    string con_ans;
    if (!(cin >> con_ans)) {
        feedback << "no input" << endl;
        return wa();
    }

    LL n;
    tc_in >> n;
    LL cur = 0, mul10 = 1;
    if (con_ans.size() > 25) {
        feedback << "digits > 25" << endl;
        return wa();
    }
    set<char> digits;
    for (int i=con_ans.size()-1;i>=0;i--) {
        if (con_ans[i] < '0' || con_ans[i] > '9') {
            feedback << "not a digit" << endl;
            return wa();
        }
        cur += mul10 * (con_ans[i] - '0');
        cur %= n;
        mul10 *= 10;
        mul10 %= n;
        digits.insert(con_ans[i]);
    }
    if (cur != 0) {
        feedback << "not a multiple" << endl;
        return wa();
    }

    for (char i = '2'; i <= '7'; i++) {
        if (digits.find(i) != digits.end()) {
            feedback << "Found digit: " << i << endl;
            return wa();
        }
    }

    return ac();
}