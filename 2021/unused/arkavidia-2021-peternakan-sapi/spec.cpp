#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
    const int NMIN = 2;
    const int NMAX = 1e5;
    const int HMIN = 1;
    const int HMAX = 1e9;
    const int QMIN = 1;
    const int QMAX = 1e5;

    int N;
    vector<int> H;
    int Q;
    vector<int> op;
    vector<int> leftOp;
    vector<int> rightOp;
    vector<int> ansmin, ansmax;
    void InputFormat() {
        LINE(N);
        LINE(H % SIZE(N));
        LINE(Q);
        LINES(op, leftOp, rightOp) % SIZE(Q);
    }

    void OutputFormat() {
        LINES(ansmin, ansmax);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(128);
    }

    void Constraints() {
        CONS(NMIN <= N && N <= NMAX);
        CONS(QMIN <= Q && Q <= QMAX);
        eachElementBetween(H, HMIN, HMAX);
    }

private:
    bool eachElementBetween(const vector<int>& v, int lo, int hi) {
        for (int x : v) {
            if (x < lo || x > hi) {
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
            "5",
            "1 5 2 3 9",
            "10",
            "1 3 5",
            "3 3 10",
            "1 3 5",
            "1 1 5",
            "1 1 3",
            "2 1 5",
            "4 1 3",
            "1 2 5",
            "3 3 6",
            "1 2 4"
        });
        Output({
            "2 9",
            "3 10",
            "1 10",
            "1 10",
            "1 9",
            "3 6"
        });
    }

    void BeforeTestCase() {
        H.clear();
        op.clear();
        leftOp.clear();
        rightOp.clear();
    }

    void TestCases() {
        CASE(N = 10, Q = 10, generateRandomArray(H, HMIN, HMAX), generateParams(op, leftOp, rightOp, Q, N, HMIN, HMAX));
        CASE(N = 10, Q = 1000, generateRandomArray(H, HMIN, HMAX), generateParams(op, leftOp, rightOp, Q, N, HMIN, HMAX));
        CASE(N = 10, Q = 100000, generateRandomArray(H, HMIN, HMAX), generateParams(op, leftOp, rightOp, Q, N, HMIN, HMAX));
        CASE(N = 1000, Q = 10, generateRandomArray(H, HMIN, HMAX), generateParams(op, leftOp, rightOp, Q, N, HMIN, HMAX));
        CASE(N = 1000, Q = 1000, generateRandomArray(H, HMIN, HMAX), generateParams(op, leftOp, rightOp, Q, N, HMIN, HMAX));
        CASE(N = 1000, Q = 100000, generateRandomArray(H, HMIN, HMAX), generateParams(op, leftOp, rightOp, Q, N, HMIN, HMAX));
        CASE(N = 100000, Q = 10, generateRandomArray(H, HMIN, HMAX), generateParams(op, leftOp, rightOp, Q, N, HMIN, HMAX));
        CASE(N = 100000, Q = 1000, generateRandomArray(H, HMIN, HMAX), generateParams(op, leftOp, rightOp, Q, N, HMIN, HMAX));
        for (int i = 0; i < 5; i++) {
            CASE(N = 100000, Q = 100000, generateRandomArray(H, HMIN, HMAX), generateParams(op, leftOp, rightOp, Q, N, HMIN, HMAX));
        }
        for (int i = 0; i < 5; i++) {
            CASE(N = 100000, Q = 100000, generateRandomArray(H, HMIN, HMAX), generateParamsHard(op, leftOp, rightOp, Q, N, HMIN, HMAX));
        }
    }

private:
    void generateRandomArray(vector<int> &V, int low, int high) {
        for (int i = 0; i < N; i++) {
            int value = rnd.nextInt(low, high);
            V.push_back(value);
        }
    }

    void generateParams(vector<int> &op, vector<int> &leftOp, vector<int> &rightOp, int Q, int N, int low, int high) {
        for (int i = 0; i < Q; i++) {
            int operation = rnd.nextInt(1, 4);
            if (operation == 1) {
                int l = rnd.nextInt(1, N);
                int h = rnd.nextInt(1, N);
                if (l > h) swap(l, h);
                op.push_back(operation);
                leftOp.push_back(l);
                rightOp.push_back(h);
            } else if (operation == 2) {
                int l = rnd.nextInt(1, N);
                int h = rnd.nextInt(1, N);
                while (l == h) h = rnd.nextInt(1, N);   // l != h
                op.push_back(operation);
                leftOp.push_back(l);
                rightOp.push_back(h);
            } else if (operation == 3) {
                int l = rnd.nextInt(1, N);
                int h = rnd.nextInt(low, high);
                op.push_back(operation);
                leftOp.push_back(l);
                rightOp.push_back(h);
            } else {
                int l = rnd.nextInt(1, N);
                int h = rnd.nextInt(1, N);
                if (l > h) swap(l, h);
                op.push_back(operation);
                leftOp.push_back(l);
                rightOp.push_back(h);
            }
        }
    }

    void generateParamsHard(vector<int> &op, vector<int> &leftOp, vector<int> &rightOp, int Q, int N, int low, int high) {
        for (int i = 0; i < Q; i++) {
            int operation = rnd.nextInt(1, 4);
            if (operation == 1) {
                int l = rnd.nextInt(1, N/20);
                int h = rnd.nextInt(N - N/20, N);
                if (l > h) swap(l, h);
                op.push_back(operation);
                leftOp.push_back(l);
                rightOp.push_back(h);
            } else if (operation == 2) {
                int l = rnd.nextInt(1, N);
                int h = rnd.nextInt(1, N);
                while (l == h) h = rnd.nextInt(1, N);   // l != h
                op.push_back(operation);
                leftOp.push_back(l);
                rightOp.push_back(h);
            } else if (operation == 3) {
                int l = rnd.nextInt(1, N);
                int h = rnd.nextInt(low, high);
                op.push_back(operation);
                leftOp.push_back(l);
                rightOp.push_back(h);
            } else {
                int l = rnd.nextInt(1, N/20);
                int h = rnd.nextInt(N - N/20, N);
                if (l > h) swap(l, h);
                op.push_back(operation);
                leftOp.push_back(l);
                rightOp.push_back(h);
            }
        }
    }
};