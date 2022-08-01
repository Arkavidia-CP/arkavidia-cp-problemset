#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
    const int NMAX = 1e6;
    const int QMAX = 1e3;

    int Q;
    vector<int> N, M, X, Y, ans;

    void InputFormat() {
        LINE(Q);
        LINES(N, M, X, Y) % SIZE(Q);
    }

    void OutputFormat() {
        LINES(ans) % SIZE(Q);
    }

    void GradingConfig() {
        TimeLimit(2);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(0 < Q && Q < QMAX);
        CONS(valid_query(Q, N, M, X, Y));
    }

private:
    bool valid_query(int sz, const vector<int>& N, const vector<int>& M, const vector<int>& X, const vector<int>& Y){
        if (sz != N.size()) return 0;
        for(int i=0; i<sz; i++){
            if (N[i] < 1 || N[i] > NMAX) return 0;
            if (M[i] < 1 || M[i] > NMAX) return 0;
            if (X[i] < 1 || X[i] > N[i]) return 0;
            if (Y[i] < 1 || Y[i] > M[i]) return 0;
        }
        return 1;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
           "12",
           "3 4 1 1",
           "3 4 1 2",
           "3 4 1 3",
           "3 4 1 4",
           "3 4 2 1",
           "3 4 2 2",
           "3 4 2 3",
           "3 4 2 4",
           "3 4 3 1",
           "3 4 3 2",
           "3 4 3 3",
           "3 4 3 4",
        });
        Output({
            "1",
            "4",
            "3",
            "6",
            "4",
            "1",
            "6",
            "3",
            "5",
            "6",
            "1",
            "2"
        });
    }
    void BeforeTestCase() {
        N.clear();
        M.clear();
        X.clear();
        Y.clear();
    }

    void TestCases() {
        for (int i=0;i<5;i++){
            CASE(Q = 3, N = vector<int>(3, rnd.nextInt(5, 10)), M = vector<int>(3, rnd.nextInt(5, 10)), X = {rnd.nextInt(1, N[0]), rnd.nextInt(1, N[1]), rnd.nextInt(1, N[2])}, Y = {rnd.nextInt(1, M[0]), rnd.nextInt(1, M[1]), rnd.nextInt(1, M[2])});
        }
        for (int i=0;i<3;i++){
            CASE(Q = 1, make_random_query(Q, N, M, X, Y, 1, 1000));
        }
        for (int i=0;i<3;i++){
            CASE(Q = 1, make_random_query(Q, N, M, X, Y, 1000, NMAX));
        }

        for (int i=0;i<3;i++){
            CASE(Q = rnd.nextInt(1, 100), make_random_query(Q, N, M, X, Y, 1, 1000));
        }
        for (int i=0;i<3;i++){
            CASE(Q = rnd.nextInt(1, 100), make_random_query(Q, N, M, X, Y, 1000, NMAX));
        }

        for (int i=0;i<3;i++){
            CASE(Q = rnd.nextInt(100, QMAX), make_random_query(Q, N, M, X, Y, 1, 1000));
        }
        for (int i=0;i<3;i++){
            CASE(Q = rnd.nextInt(100, QMAX), make_random_query(Q, N, M, X, Y, 1000, NMAX));
        }
    }

private:
    void make_random_query(int q, vector<int>& n, vector<int>& m, vector<int>& x, vector<int>& y, int l, int r){
        int curn, curm;
        for(int i=0; i<q; i++){
            curn = rnd.nextInt(l, r);
            curm = rnd.nextInt(l, r);
            n.push_back(curn);
            m.push_back(curm);
            x.push_back(rnd.nextInt(1, curn));
            y.push_back(rnd.nextInt(1, curm));
        }
    }
};