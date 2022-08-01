#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;

const int NMAX = 1e5;
const int QMAX = 1e5;
const int EMAX = 1e9;

class ProblemSpec : public BaseProblemSpec {
protected:
    int N, Q;
    vector<int> V, Query;
    vector<long long> Answer;

    void InputFormat() {
        LINE(N);
        LINE(V % SIZE(N));
        LINE(Q);
        LINES(Query) % SIZE(Q);
    }

    void OutputFormat() {
        LINES(Answer) % SIZE(Q);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(64);
    }

    void Constraints() {
        CONS(1 <= N && N <= NMAX);
        CONS(1 <= Q && Q <= QMAX);
        CONS(eachElementBetween(V, 1, EMAX));
    }

private:
    bool eachElementBetween(vector<int>& V, int low, int high) {
        for (int x : V) {
            if (x < low || x > high)
                return false;
        }
        return true;
    }

};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "4",
            "3 1 4 2",
            "2",
            "1",
            "3"
        });
        Output({
            "2",
            "3"
        });
    }

    void BeforeTestCase() {
    	V.clear();
        Query.clear();
        Answer.clear();
    }

    void TestCases() {
        CASE(N = 5, Q = 5, generateRandomArray(V, N, 1, 100), generateRandomArray(Query, Q, 1, 100));
        CASE(N = 10, Q = 10, generateRandomArray(V, N, 1, 100), generateRandomArray(Query, Q, 1, 100));
        CASE(N = 100, Q = 100, generateRandomArray(V, N, 1, 100), generateRandomArray(Query, Q, 1, 100));
        for (int i = 0; i < 5; i++) {
            CASE(N = rnd.nextInt(1000, NMAX),
                 Q = rnd.nextInt(1000, QMAX),
                 generateRandomArray(V, N, 1, EMAX),
                 generateRandomArray(Query, Q, 1, EMAX)
                );
        }
        for (int i = 0; i < 20; i++) {
            CASE(N = NMAX,
                 Q = QMAX,
                 generateRandomArray(V, N, 1, EMAX),
                 generateRandomArray(Query, Q, 1, EMAX)
                );
        }
        for (int i = 0; i < 10; i++) {
            CASE(N = NMAX,
                 Q = QMAX,
                 generateRandomArray(V, N, EMAX / 2, EMAX),
                 generateRandomArray(Query, Q, EMAX / 2, EMAX)
                );
        }
    }

private:
    void generateRandomArray(vector<int>& V, int n, int low, int high) {
        for (int i = 0; i < n; i++) {
            int value = rnd.nextInt(low, high);
            V.emplace_back(value);
        }
    }

};