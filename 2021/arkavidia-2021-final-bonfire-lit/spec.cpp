#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;
using ll = long long;

class ProblemSpec : public BaseProblemSpec {
protected:
    const int NMAX = 1e5;
    const ll PMAX = 1e9;

    int N, Q;
    vector<ll> Xpos, Ypos, Xq, Yq;
    vector<ll> ans;

    void InputFormat() {
        LINE(N);
        LINES(Xpos, Ypos) % SIZE(N);
        LINE(Q);
        LINES(Xq, Yq) % SIZE(Q);
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
        CONS(1 <= Q && Q <= NMAX);
        CONS(valid_pos(N, Xpos));
        CONS(valid_pos(N, Ypos));
        CONS(valid_pos(Q, Xq));
        CONS(valid_pos(Q, Yq));
    }

private:
    bool valid_pos(int sz, const vector<ll>& vec){
        if (sz != vec.size()) return 0;
        for (auto x : vec){
            if (x < 0 || x > PMAX) return 0;
        }
        return 1;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "4",
            "1 2",
            "2 2",
            "3 2",
            "2 4",
            "3",
            "3 3",
            "4 4",
            "1 1",
        });
        Output({
            "1",
            "2",
            "-1"
        });
    }
    void BeforeTestCase() {
        Xpos.clear();
        Ypos.clear();
        Xq.clear();
        Yq.clear();
        ans.clear();
    }

    void TestCases() {
        for (int i=0;i<3;i++){
            CASE(N = 1, Q = rnd.nextInt(1, NMAX), make_random_query(N, Q, Xpos, Ypos, Xq, Yq));
        }
        for (int i=0;i<3;i++){
            CASE(N = rnd.nextInt(1, 100), Q = rnd.nextInt(1, 1000), make_random_query(N, Q, Xpos, Ypos, Xq, Yq));
        }
        for (int i=0;i<3;i++){
            CASE(N = rnd.nextInt(1, 100), Q = NMAX, make_random_query(N, Q, Xpos, Ypos, Xq, Yq));
        }
        for (int i=0;i<3;i++){
            CASE(N = rnd.nextInt(NMAX / 2, NMAX), Q = rnd.nextInt(NMAX / 2, NMAX), make_random_query(N, Q, Xpos, Ypos, Xq, Yq));
        }
        for (int i=0;i<7;i++){
            CASE(N = NMAX, Q = NMAX, make_random_query(N, Q, Xpos, Ypos, Xq, Yq));
        }
        for (int i=0;i<3;i++){
            CASE(N = NMAX, Q = NMAX, make_random_query(N, Q, Xpos, Ypos, Xq, Yq, 0LL, 100LL, PMAX / 2, PMAX));
        }
        for (int i=0;i<3;i++){
            CASE(N = NMAX, Q = NMAX, make_random_query(N, Q, Xpos, Ypos, Xq, Yq, PMAX / 2, PMAX, 0LL, 100LL));
        }
    }

private:
    void make_random_query(int n, int q, vector<ll>& xpos, vector<ll>& ypos, vector<ll>& xq, vector<ll>& yq, ll apos = 0, ll bpos = 1e9, ll aq = 0, ll bq = 1e9){
        for (int i=0;i<n;i++){
            xpos.push_back(rnd.nextLongLong(apos, bpos));
            ypos.push_back(rnd.nextLongLong(apos, bpos));
        }
        for (int i=0;i<q;i++){
            xq.push_back(rnd.nextLongLong(aq, bq));
            yq.push_back(rnd.nextLongLong(aq, bq));
        }
    }
};