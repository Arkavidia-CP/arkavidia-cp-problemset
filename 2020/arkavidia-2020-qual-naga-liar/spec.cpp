#include <tcframe/spec.hpp>
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
    long long A;
    long long res;

    void InputFormat() {
        LINE(A);
    }

    void OutputFormat() {
        LINE(res);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(64);
    }

    void Constraints() {
        CONS(1 <= A && A <= 1000000000000000000);
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "4"
        });
        Output({
            "2"
        });
    }
    void SampleTestCase2() {
        Input({
            "5"
        });
        Output({
            "800000010"
        });
    }

    void TestCases() {
        CASE(A = 4);
        CASE(A = 5);
        CASE(A = 19283928192);
        CASE(A = 500000);
        CASE(A = 1000000000000000000);
        CASE(A = 3);
        CASE(A = 1000000000000);
        CASE(A = 283928192892222222);
        for (int i = 0; i < 3; ++i){
            CASE(A = randomNumber(2, 1000000000000000000));
        }
        for (int i = 0; i < 5; ++i){
            CASE(A = randomNumber(10000000000, 1000000000000000000));
        }
        for (int i = 0; i < 4; ++i){
            CASE(A = randomNumber(100000000000000000, 1000000000000000000));
        }
    }
private:
    long long randomNumber(long long lo, long long hi){
        long long res = rnd.nextLongLong(lo, hi);
        long long num = (long long)1e9 + 7;
        while (res % num == 0){
            res = rnd.nextLongLong(lo, hi);
        }
        return res;
    }
};