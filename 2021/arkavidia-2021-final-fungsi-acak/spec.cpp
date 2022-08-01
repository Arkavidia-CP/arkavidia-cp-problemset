#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int NMAX = 1e5;

class ProblemSpec : public BaseProblemSpec {

protected:
    int N;
    vector<int> L, R;
    int RES;

    void InputFormat() {
        LINE(N);
        LINES(L, R) % SIZE(N);
    }

    void OutputFormat() {
        LINE(RES);
    }

    void GradingConfig() {
        TimeLimit(2);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(1 <= N && N <= NMAX);
        CONS(constraintOnIntervals(L, R, N));
    }

private:
    bool constraintOnIntervals(const vector<int>& l, const vector<int>& r, int n) {
        for (int i = 0; i < n; i++) {
            if (l[i] > r[i]) return false;
            if (l[i] < 1 || l[i] > NMAX) return false;
            if (r[i] < 1 || r[i] > NMAX) return false;
        }
        return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "2",
            "1 2",
            "3 4"
        });
        Output({
            "2"
        });
    }

    void SampleTestCase2() {
        Input({
            "3",
            "1 3",
            "1 2",
            "5 6"
        });
        Output({
            "666666674"
        });
    }

    void BeforeTestCase() {
        L.clear(), R.clear();
    }

    void TestCases() {
        CASE(N = 1, L = {1}, R = {1});
        CASE(N = 1, L = {1}, R = {NMAX});
        CASE(N = 2, L = {1, 69}, R = {100, 150});
        CASE(N = 2, L = {NMAX, 69}, R = {NMAX, 169});
        CASE(N = 2, L = {NMAX - 69, 1}, R = {NMAX - 50, NMAX});
        CASE(N = 2, L = {1, 1}, R = {NMAX, NMAX});
        CASE(N = 2, L = {1, NMAX}, R = {1, NMAX});
        CASE(N = 3, L = {1, 1, 1}, R = {NMAX, NMAX, 69});
        CASE(N = 4, L = {100, 200, 300, 400}, R = {200, 300, 400, 500});
        CASE(N = 5, L = {1, 2, 3, 4, 5}, R = {NMAX, NMAX - 1, NMAX - 2, NMAX - 3, NMAX - 4});

        for (int i = 0; i < 20; i++) {
            CASE(N = rnd.nextInt(5, 10), randomInterval());
        }
        for (int i = 0; i < 20; i++) {
            CASE(N = rnd.nextInt(10, 50), randomInterval());
        }
        for (int i = 0; i < 20; i++) {
            CASE(N = rnd.nextInt(50, 200), randomInterval());
        }
        for (int i = 0; i < 20; i++) {
            CASE(N = rnd.nextInt(200, NMAX / 2), randomInterval());
        }
        CASE(N = NMAX, L = vector<int>(N, 1), R = vector<int>(N, NMAX));
        for (int i = 0; i < 20; i++) {
            CASE(N = NMAX, randomInterval());
        }
        
    }

private:
    void randomInterval() {
        for (int i = 0; i < N; i++) {
            int x = rnd.nextInt(1, NMAX);
            int y = rnd.nextInt(1, NMAX);
            if (x > y) swap(x, y);
            L.push_back(x);
            R.push_back(y);
        }
    }
};