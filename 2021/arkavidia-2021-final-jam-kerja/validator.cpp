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

    LL tc_ans;
    tc_out >> tc_ans;

    // read contestant output
    LL ans;
    if (!(cin >> ans)) {
        feedback << "no input" << endl;
        return wa();
    }
    if (ans != tc_ans) {
        feedback << "wrong D value" << endl;
        return wa();
    }

    int N, M;
    tc_in >> N >> M;

    LL cnt[N + 5];
    memset(cnt,0,sizeof(cnt));
    for (int i = 1; i <= M; i++) {
        int L, R;
        tc_in >> L >> R;
        int X_ans;
        if (!(cin >> X_ans)) {
            feedback << "not enough integers in input" << endl;
            return wa();
        }
        if (X_ans < L || X_ans > R) {
            feedback << "X not in range at: " << i << endl;
            return wa();
        }
        cnt[X_ans]++;
    }

    LL tot = 0;
    for (int i = 1; i <= N; i++) {
        tot += cnt[i] * cnt[i] * cnt[i] * cnt[i] * cnt[i] * cnt[i] * cnt[i];
    }
    if (tot != ans) {
        feedback << "wrong total" << endl;
        return wa();
    }
    return ac();
}