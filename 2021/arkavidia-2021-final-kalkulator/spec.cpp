#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int NMAX = 3e4;
const int MMAX = 1e6;
const int AMAX = 1e9;
const long long RMAX = 1e18;

class ProblemSpec : public BaseProblemSpec {

protected:
    int N, M;
    long long R;
    vector<int> A;
    vector<int> RES;

    void InputFormat() {
        LINE(N, M, R);
        LINE(A % SIZE(M));
    }

    void OutputFormat() {
        LINE(RES % SIZE(N));
    }

    void GradingConfig() {
        TimeLimit(5);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(1 <= N && N <= NMAX);
        CONS(1 <= M && M <= MMAX);
        CONS(1 <= R && R <= RMAX);
        CONS(eachElementBetween(A, 1, AMAX));
    }

private:
    bool eachElementBetween(const vector<int>& ve, int lo, int hi) {
        for (auto& e : ve) {
            if (e < lo || e > hi) return false;
        }
        return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "2 2 3",
            "2 3"
        });
        Output({
            "4 4"
        });
    }

    void SampleTestCase2() {
        Input({
            "3 3 2",
            "10 10 10"
        });
        Output({
            "0 0 9"
        });
    }

    void BeforeTestCase() {
        A.clear();
    }

    void TestCases() {
        CASE(N = 1, M = 1, R = 2, A = {2});
        CASE(N = 2, M = 3, R = 2021, A = {420, 69, 1337});
        CASE(N = 5, M = 5, R = 5, A = {1, 2, 3, 4, 5});
        for (int i = 0; i < 5; i++) {
            CASE(N = rnd.nextInt(5, 20), M = rnd.nextInt(5, 20), R = rnd.nextInt(5, 100), randomArray());
        }
        for (int i = 0; i < 5; i++) {
            CASE(N = rnd.nextInt(20, 100), M = rnd.nextInt(20, 100), R = rnd.nextInt(100, 1000), randomArray());
        }
        for (int i = 0; i < 5; i++) {
            CASE(N = rnd.nextInt(100, 1000), M = rnd.nextInt(100, 1000), R = rnd.nextInt(1000, 1000000), randomArray());
        }
        for (int i = 0; i < 5; i++) {
            CASE(N = rnd.nextInt(1000, 5000), M = rnd.nextInt(1000, 5000), R = rnd.nextLongLong(1000000, 1000000000000), randomArray());
        }
        for (int i = 0; i < 5; i++) {
            CASE(N = rnd.nextInt(5000, 10000), M = rnd.nextInt(5000, 10000), R = rnd.nextInt(2, 5), randomArray());
        }
        for (int i = 0; i < 5; i++) {
            CASE(N = rnd.nextInt(10000, NMAX), M = rnd.nextInt(10000, MMAX), R = RMAX, randomArray());
        }
        CASE(N = NMAX, M = MMAX, R = 1, randomArray());
        CASE(N = NMAX, M = MMAX, R = 2, randomArray());
        CASE(N = NMAX, M = MMAX, R = 2021, randomArray());
        CASE(N = 1, M = MMAX, R = RMAX, randomArray());
        CASE(N = 2, M = MMAX, R = RMAX, randomArray());
        CASE(N = 2021, M = MMAX, R = RMAX, randomArray());
        for (int i = 0; i < 4; i++) {
            CASE(N = NMAX, M = MMAX, R = RMAX, randomArray());
        }   
    }

private:
    void randomArray() {
        for (int i = 0; i < (M / 2); i++) {
            int x = rnd.nextInt(1, N);
            A.push_back(x);
        }
        for (int i = (M / 2); i < M; i++) {
            int x = rnd.nextInt(N, AMAX);
            A.push_back(x);
        }
        rnd.shuffle(A.begin(), A.end());
    }
};