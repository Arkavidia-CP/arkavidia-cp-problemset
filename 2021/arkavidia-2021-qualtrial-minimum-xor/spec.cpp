#include <tcframe/spec.hpp>
using namespace tcframe;
#define MAXN 1e18
#define MAXK 1e18

class ProblemSpec : public BaseProblemSpec {
protected:
    long long N, K;
    long long ans;

    void InputFormat() {
        LINE(N, K);
    }

    void OutputFormat() {
        LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(64);
    }

    void Constraints() {
        CONS(0 <= N && N <= MAXN);
        CONS(1 <= K && K <= MAXK);
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "5 3"
        });
        Output({
            "1"
        });
    }

    void TestCases() {
        CASE(N = 1, K = 1);
        CASE(N = 12345678987, K = 161);
        CASE(N = 0, K = 1);
        CASE(N = 0, K = 2);
        CASE(N = 0, K = 3);
        CASE(N = MAXN, K = MAXK);
        CASE(N = rnd.nextLongLong(1, MAXN/2) * 2 - 1, K = 1);
        CASE(N = rnd.nextLongLong(1, MAXN/2) * 2, K = 1);
        for(int i = 0; i < 4; i++){
            CASE(N = rnd.nextLongLong(1, MAXN/2) * 2, K = 2);
            CASE(N = rnd.nextLongLong(1, MAXN/2) * 2 - 1, K = 2);
        }
        CASE(N = rnd.nextLongLong(1, MAXN/2) * 2 - 1, K = 3);
        CASE(N = rnd.nextLongLong(1, MAXN/2) * 2 - 1, K = 5);
        CASE(N = rnd.nextLongLong(1, MAXN/2) * 2 - 1, K = 8);
        for(int i = 0; i < 5; i++){
            CASE(N = rnd.nextLongLong(1, MAXN/2) * 2 - 1, K = rnd.nextLongLong(1, MAXK));
        }
    }
};