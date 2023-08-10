#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:

    long long N, K;
    long long NMAX = 1e18;
    long long MOD = 1e9 + 7;

    long long ans;
    void InputFormat() {
        LINE(N, K);
    }

    void OutputFormat() {
        LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(1 <= N && N <= NMAX);
        CONS(1 <= K && K <= NMAX);
    }
private:
    
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "3 3"
        });
        Output({
            "39"
        });
    }
    
    void SampleTestCase2() {
        Input({
            "1 10"
        });
        Output({
            "285"
        });
    }

    void BeforeTestCase() {
        
    }

    void TestCases(){
        CASE(N = 3, K = 3);
        CASE(N = 5, K = 5);
        CASE(N = NMAX, K = 1);
        CASE(N = 1, K = NMAX);
        CASE(N = 1, K = 1);
        CASE(N = NMAX, K = NMAX);
        
        /* Menguji 0^0 */
        CASE(N = MOD, K = MOD - 1);
        CASE(N = MOD, K = MOD);
        CASE(N = MOD * 1000LL, K = (MOD - 1) * 31LL);
        for(int i = 0; i < 5; i++) CASE(N = rnd.nextLongLong(2, NMAX-1), K = NMAX);
        for(int i = 0; i < 35; i++) CASE(N = rnd.nextLongLong(1, NMAX), K = rnd.nextLongLong(1, NMAX));
    }

private:
    
};
