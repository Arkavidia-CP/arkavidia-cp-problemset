#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
    const int NMIN = 1;
    const int NMAX = 1e5;
    const int KMIN = 1;
    const int KMAX = 1e5;
    const int QMIN = 1;
    const int QMAX = 2e4;

    int N;
    vector<int> K;
    int Q;
    vector<int> op;
    vector<vector<int>> data;
    vector<long long> ans;
    void InputFormat() {
        LINE(N);
        LINE(K % SIZE(N));
        LINE(Q);
        LINES(op, data) % SIZE(Q);
    }

    void OutputFormat() {
        LINES(ans);
    }

    void GradingConfig() {
        TimeLimit(2);
        MemoryLimit(1024);
    }

    void Constraints() {
        CONS(NMIN <= N && N <= NMAX);
        CONS(QMIN <= Q && Q <= QMAX);
        eachElementBetween(K, KMIN, KMAX);
        eachQueryValid(op, data, N);
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

    bool eachQueryValid(const vector<int>& op, const vector<vector<int>>& data, int N) {
        for (int i = 0; i < op.size(); i++) {
            if (op[i] == 1) {
                if (data[i].size() != 4) return false;
                if (!(1 <= data[i][0] && data[i][0] <= data[i][1] && data[i][1] <= N)) return false;
                if (!(KMIN <= data[i][2] && data[i][2] <= data[i][3] && data[i][3] <= KMAX)) return false;
            } else if (op[i] == 2) {
                if (data[i].size() != 2) return false;
                if (!(1 <= data[i][0] && data[i][0] <= N && 1 <= data[i][1] && data[i][1] <= KMAX)) return false;
            }
        }
        return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "10",
            "5 4 9 3 4 9 5 14 13 21",
            "7",
            "1 1 10 10 20",
            "2 10 20",
            "1 1 10 10 20",
            "1 2 5 3 5",
            "2 4 10",
            "1 1 5 5 10",
            "1 2 3 10 15"
        });
        Output({
            "27",
            "47",
            "11",
            "24",
            "0"
        });
    }

    void BeforeTestCase() {
        K.clear();
        op.clear();
        data.clear();
    }

    void TestCases() {
        CASE(N = 10, Q = 10, generateRandomArray(K, KMIN, KMAX), generateParams(op, data, Q, N, KMIN, KMAX));
        CASE(N = 10, Q = 1000, generateRandomArray(K, KMIN, KMAX), generateParams(op, data, Q, N, KMIN, KMAX));
        CASE(N = 10, Q = QMAX, generateRandomArray(K, KMIN, KMAX), generateParams(op, data, Q, N, KMIN, KMAX));
        CASE(N = 1000, Q = 10, generateRandomArray(K, KMIN, KMAX), generateParams(op, data, Q, N, KMIN, KMAX));
        CASE(N = 1000, Q = 1000, generateRandomArray(K, KMIN, KMAX), generateParams(op, data, Q, N, KMIN, KMAX));
        CASE(N = 1000, Q = QMAX, generateRandomArray(K, KMIN, KMAX), generateParams(op, data, Q, N, KMIN, KMAX));
        CASE(N = 100000, Q = 10, generateRandomArray(K, KMIN, KMAX), generateParams(op, data, Q, N, KMIN, KMAX));
        CASE(N = 100000, Q = 1000, generateRandomArray(K, KMIN, KMAX), generateParams(op, data, Q, N, KMIN, KMAX));
        for (int i = 0; i < 3; i++) {
            CASE(N = 100000, Q = QMAX, generateRandomArray(K, KMIN, KMAX), generateParams(op, data, Q, N, KMIN, KMAX));
        }

        CASE(N = 100000, Q = QMAX, generateRandomArray(K, KMIN, KMAX), generateParamsHard(op, data, Q, N, KMIN, KMAX, 10));
        CASE(N = 100000, Q = QMAX, generateRandomArray(K, KMIN, KMAX), generateParamsHard(op, data, Q, N, KMIN, KMAX, 100));
        CASE(N = 100000, Q = QMAX, generateRandomArray(K, KMIN, KMAX), generateParamsHard(op, data, Q, N, KMIN, KMAX, 1000));
        CASE(N = 100000, Q = QMAX, generateRandomArray(K, KMIN, KMAX), generateParamsHard(op, data, Q, N, KMIN, KMAX, 10000));
        CASE(N = 100000, Q = QMAX, generateRandomArray(K, KMIN, KMAX), generateParamsHard(op, data, Q, N, KMIN, KMAX, 100000));

        CASE(N = 100000, Q = QMAX, generateRandomArray(K, KMIN, KMAX), generateParamsRight(op, data, Q, N, KMIN, KMAX, 300));
        CASE(N = 100000, Q = QMAX, generateRandomArray(K, KMIN, KMAX), generateParamsRight(op, data, Q, N, KMIN, KMAX, 350));
        CASE(N = 100000, Q = QMAX, generateRandomArray(K, KMIN, KMAX), generateParamsRight(op, data, Q, N, KMIN, KMAX, 400));
        CASE(N = 100000, Q = QMAX, generateRandomArray(K, KMIN, KMAX), generateParamsRight(op, data, Q, N, KMIN, KMAX, 316));
        CASE(N = 100000, Q = QMAX, generateRandomArray(K, KMIN, KMAX), generateParamsRight(op, data, Q, N, KMIN, KMAX, 317));
    }

private:
    void generateRandomArray(vector<int> &V, int low, int high) {
        for (int i = 0; i < N; i++) {
            int value = rnd.nextInt(low, high);
            V.push_back(value);
        }
    }

    void generateParams(vector<int> &op, vector<vector<int>> &data, int Q, int N, int low, int high) {
        for (int i = 0; i < Q; i++) {
            int operation = rnd.nextInt(1, 2);
            vector<int> tmp;
            if (operation == 1) {
                int l = rnd.nextInt(1, N);
                int h = rnd.nextInt(1, N);
                int p = rnd.nextInt(low, high);
                int q = rnd.nextInt(low, high);
                if (l > h) swap(l, h);
                if (p > q) swap(p, q);
                op.push_back(operation);
                tmp.push_back(l);
                tmp.push_back(h);
                tmp.push_back(p);
                tmp.push_back(q);
                data.push_back(tmp);
            } else if (operation == 2) {
                int X = rnd.nextInt(1, N);
                int V = rnd.nextInt(low, high);
                op.push_back(operation);
                tmp.push_back(X);
                tmp.push_back(V);
                data.push_back(tmp);
            }
        }
    }

    // condition: N > multiplier
    void generateParamsHard(vector<int> &op, vector<vector<int>> &data, int Q, int N, int low, int high, int multiplier) {
        for (int i = 0; i < Q; i++) {
            int operation = i % 2 + 1;  // alternate 1, 2
            vector<int> tmp;
            if (operation == 1) {
                int l = rnd.nextInt(1, N/multiplier);
                int h = rnd.nextInt(N - N/multiplier, N);
                int p = rnd.nextInt(low, high);
                int q = rnd.nextInt(low, high);
                if (l > h) swap(l, h);
                if (p > q) swap(p, q);
                op.push_back(operation);
                tmp.push_back(l);
                tmp.push_back(h);
                tmp.push_back(p);
                tmp.push_back(q);
                data.push_back(tmp);
            } else if (operation == 2) {
                int X = rnd.nextInt(1, N);
                int V = rnd.nextInt(low, high);
                op.push_back(operation);
                tmp.push_back(X);
                tmp.push_back(V);
                data.push_back(tmp);
            }
        }
    }

    void generateParamsRight(vector<int> &op, vector<vector<int>> &data, int Q, int N, int low, int high, int block_size) {
        for (int i = 0; i < Q; i++) {
            int operation = i % 2 + 1;  // alternate 1, 2
            vector<int> tmp;
            if (operation == 1) {
                int block = N / block_size;
                int l = rnd.nextInt(1, rnd.nextInt(1, block_size));
                int h = block_size * rnd.nextInt(1, block) - rnd.nextInt(1, 10);
                int p = rnd.nextInt(low, high);
                int q = rnd.nextInt(low, high);
                if (l > h) swap(l, h);
                if (p > q) swap(p, q);
                op.push_back(operation);
                tmp.push_back(l);
                tmp.push_back(h);
                tmp.push_back(p);
                tmp.push_back(q);
                data.push_back(tmp);
            } else if (operation == 2) {
                int block = N / block_size;
                int X = block_size * rnd.nextInt(1, block) - rnd.nextInt(1, 10);
                int V = rnd.nextInt(low, high);
                op.push_back(operation);
                tmp.push_back(X);
                tmp.push_back(V);
                data.push_back(tmp);
            }
        }
    }
};