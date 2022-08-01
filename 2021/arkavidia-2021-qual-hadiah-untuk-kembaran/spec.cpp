#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

const int MAXQ = 1e5;
const int MAXN = 1e9;

class ProblemSpec : public BaseProblemSpec {
protected:
	int Q;
    vector<int> N, X, Y;
    vector<int> ANS_X, ANS_Y;

	void InputFormat() {
	  LINE(Q);
      LINES(N, X, Y) % SIZE(Q);
	}

    void OutputFormat() {
    	LINES(ANS_X, ANS_Y) % SIZE(Q);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(64);
    }

    void Constraints() {
        CONS(1 <= Q && Q <= MAXQ);
        CONS(eachElementBetween(N, 1, MAXN));
        CONS(eachElementBetween(X, 1, MAXN));
        CONS(eachElementBetween(Y, 1, MAXN));
        CONS(eachElementBetween(ANS_X, 0, MAXN));
        CONS(eachElementBetween(ANS_Y, 0, MAXN));
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
        	"3",
            "10 2 3",
            "100 2 4",
            "100 3 3"
            
        });
        Output({
        	"4 2",
            "25 0",
            "0 0"
        });
    }

    void BeforeTestCase(){
    	N.clear(); X.clear(); Y.clear();
        ANS_X.clear(); ANS_Y.clear();
    }

    void TestCases() {
        CASE(Q = 5, generateRandom(Q, N, X, Y, 1, 10));
        CASE(Q = 10, generateRandom(Q, N, X, Y, 1, 100));
        CASE(Q = 20, generateRandom(Q, N, X, Y, 1, 1000));
        for (int i = 0; i < 4; i++) {
            CASE(Q = rnd.nextInt(1, MAXQ / 2), generateRandom(Q, N, X, Y, 1, rnd.nextInt(MAXN / 2, MAXN)));
            CASE(Q = rnd.nextInt(MAXQ / 2 + 1, MAXQ), generateRandom(Q, N, X, Y, 1, MAXN));
            CASE(Q = rnd.nextInt(1, MAXQ / 2), generateRandomMaximumN(Q, N, X, Y, 1, rnd.nextInt(MAXN / 2, MAXN)));
            CASE(Q = rnd.nextInt(MAXQ / 2 + 1, MAXQ), generateRandomMaximumN(Q, N, X, Y, 1, MAXN));
            CASE(Q = 100, generateRandomMinimumN(Q, N, X, Y, 1, rnd.nextInt(MAXN / 2, MAXN)));
            CASE(Q = 100, generateRandomMinimumN(Q, N, X, Y, 1, MAXN));
            CASE(Q = MAXQ, generateRandom(Q, N, X, Y, 1, MAXN));
        }
    }

private:

    void generateRandom(int q, vector<int>& N, vector<int>& X, vector<int>& Y, int lowest, int highest) {
        assert(lowest <= highest);
        for (int i = 0; i < q; i++) {
            int n = rnd.nextInt(lowest, highest);
            int x = rnd.nextInt(lowest, highest);
            int y = rnd.nextInt(lowest, highest);
            N.emplace_back(n); X.emplace_back(x); Y.emplace_back(y);
        }
    }

    void generateRandomMaximumN(int q, vector<int>& N, vector<int>& X, vector<int>& Y, int lowest, int highest) {
        assert(lowest <= highest);
        for (int i = 0; i < q; i++) {
            int n = rnd.nextInt(lowest, highest);
            int x = rnd.nextInt(lowest, n);
            int y = rnd.nextInt(lowest, n);
            N.emplace_back(n); X.emplace_back(x); Y.emplace_back(y);
        }
    }

    void generateRandomMinimumN(int q, vector<int>& N, vector<int>& X, vector<int>& Y, int lowest, int highest) {
        assert(lowest <= highest);
        for (int i = 0; i < q; i++) {
            int n = rnd.nextInt(lowest, highest);
            int x = rnd.nextInt(n, highest);
            int y = rnd.nextInt(n, highest);
            N.emplace_back(n); X.emplace_back(x); Y.emplace_back(y);
        }
    }

};