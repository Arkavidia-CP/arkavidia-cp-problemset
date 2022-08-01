#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
#define LL long long

using namespace std;
using namespace tcframe;

const int NMIN = 1;
const int NMAX = 100;
const int MMIN = 1;
const int MMAX = 100;

class ProblemSpec : public BaseProblemSpec {
protected:
    int N, M;
    vector<int> L, R;
    LL ans;
    vector<int> ansX;

    void InputFormat() {
        LINE(N, M);
        LINES(L, R) % SIZE(M);
    }

    void OutputFormat() {
        LINE(ans);
        LINE(ansX % SIZE(M));
    }

    void GradingConfig() {
        TimeLimit(2);
        MemoryLimit(512);
    }

    void Constraints() {
        CONS(NMIN <= N && N <= NMAX);
        CONS(MMIN <= M && M <= MMAX);
        CONS(validRange(L, R, 1, N));
    }

private:
    bool validRange(const vector<int>& l, const vector<int>& r, int lo, int hi) {
        for (int i = 0; i < l.size(); i++) {
            if (l[i] < lo || l[i] > hi || r[i] < lo || r[i] > hi || l[i] > r[i]) {
                return false;
            }
        }
        return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
    	Input({
            "5 6",
            "1 3",
            "2 3",
            "3 3",
            "4 5",
            "4 5",
            "4 5"
    	});
    	Output({
            "132",
            "1 2 3 4 4 5",
    	});
    }

    void BeforeTestCase() {
        L.clear();
        R.clear();
    }

    void TestCases() {
        // special
        CASE(N = 1, M = 1, randomRange(L, R, N, M, N - 1));
        CASE(N = 5, M = 1, randomRange(L, R, N, M, N - 1));
        CASE(N = NMAX, M = 1, randomRange(L, R, N, M, N - 1));
        CASE(N = 1, M = 5, randomRange(L, R, N, M, N - 1));
        CASE(N = 1, M = MMAX, randomRange(L, R, N, M, N - 1));
        CASE(N = 10, M = 10, randomRange(L, R, N, M, N - 1));
        CASE(N = 20, M = 20, randomRange(L, R, N, M, N - 1));

        // abs(r - l) <= d
        for (int i = 0; i < 10; i++) {
            CASE(N = NMAX, M = MMAX, randomRange(L, R, N, M, i));
        }

        // random
        for (int i = 0; i < 10; i++) {
            CASE(N = NMAX, M = MMAX, randomRange(L, R, N, M, N - 1));
        }
    }

private:
    void randomRange(vector<int>& l, vector<int>& r, int n, int m, int d) {
        for (int i = 1; i <= m; i++) {
            int a = rnd.nextInt(1, n);
            int b = rnd.nextInt(a, min(n, a + d));
            l.push_back(a);
            r.push_back(b);
        }
    }
};
