#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;

const int NMAX = 1e9;
const int QMAX = 1e5;

using ll = long long;

class ProblemSpec: public BaseProblemSpec {
protected:
    int N, Q;
    vector<int> que;
    vector<ll> ans;

    void InputFormat() {
        LINE(N);
        LINE(Q);
        LINES(que) % SIZE(Q);
    }

    void OutputFormat() {
        LINES(ans) % SIZE(Q);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(1 <= N && N <= NMAX);
        CONS(1 <= Q && Q <= QMAX);
        CONS(eachElementBetween(que, 1, NMAX));
    }

private:
    bool eachElementBetween(const vector<int>& v, int low, int high) {
        for (const int& x: v) {
            if (x < low || x > high) {
                return false;
            }
        }
        return true;
    }
    
};

class TestSpec: public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "3",
            "2",
            "1",
            "3"
        });
        Output({
            "1",
            "3"
        });
    }

    void BeforeTestCase() {
        que.clear();
        ans.clear();
    }

    void TestCases() {
        CASE(N = 5, Q = 5, generateRandomArray(que, Q, 1, 10));
        CASE(N = 10, Q = 10, generateRandomArray(que, Q, 1, 100));
        CASE(N = 100, Q = 100, generateRandomArray(que, Q, 1, 100));
        for (int i = 0; i < 5; i++) {
            CASE(N = rnd.nextInt(1000, NMAX),
                Q = rnd.nextInt(1000, QMAX),
                generateRandomArray(que, Q, 1, NMAX)
            );
        }
        for (int i = 0; i < 10; i++) {
            CASE(N = NMAX,
                Q = QMAX,
                generateRandomArray(que, Q, 1, NMAX)
            );
        }
        for (int i = 0; i < 10; i++) {
            CASE(N = NMAX,
                Q = QMAX,
                generateRandomArray(que, Q, NMAX / 2, NMAX)
            );
        }
    }
private:
    void generateRandomArray(vector<int>& v, int n, int low, int high) {
        for (int i = 0; i < n; i++) {
            v.emplace_back(rnd.nextInt(low, high));
        }
    }
};