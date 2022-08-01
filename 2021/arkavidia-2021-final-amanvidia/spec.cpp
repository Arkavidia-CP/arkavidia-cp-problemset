#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace std;
using namespace tcframe;

#define MAXN 20000000

class ProblemSpec : public BaseProblemSpec {
protected:
    long long N;
    string ans;

    void InputFormat() {
        LINE(N);
    }

    void OutputFormat() {
        LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(2);
        MemoryLimit(512);
    }

    void Constraints() {
        CONS(1 <= N <= MAXN);
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "13"
        });
        Output({
            "91"
        });
    }

    void SampleTestCase2() {
        Input({
            "5"
        });
        Output({
            "10000"
        });
    }

    void TestCases() {
        CASE(N = 1);
        for(int i = 0; i < 10; i++){
            CASE(N = rnd.nextInt(1, 5000));
        }
        for(int i = 0; i < 10; i++){
            CASE(N = rnd.nextInt(MAXN/2, MAXN));
        }

        // Crypto.Util.number.getPrime(25)
        CASE(N = 16777216);
        CASE(N = 17252867);
        CASE(N = 17673343);
        CASE(N = 18245281);
        CASE(N = 18985909);
        CASE(N = 19751629);
        CASE(N = 20000000);
    }
};