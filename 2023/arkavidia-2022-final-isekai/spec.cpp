#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:

    long long N, K;
    long long NMAX = 1e9;

    long long ansU, ansL;
    void InputFormat() {
        LINE(N, K);
    }

    void OutputFormat() {
        LINE(ansU, ansL);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(1 <= N && N <= NMAX);
        CONS(0 <= K && K <= NMAX);
    }
private:
    
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "3 1"
        });
        Output({
            "2 3"
        });
    }

    void SampleTestCase2() {
        Input({
            "5 2"
        });
        Output({
            "2 5"
        });
    }

    void BeforeTestCase() {
        
    }

    void TestCases(){
        CASE(N = 3, K = 1);
        CASE(N = 3, K = 0);
        CASE(N = 5, K = 3);
        CASE(N = NMAX, K = 1);
        for(int i = 0; i < 30; i++) CASE(N = rnd.nextLongLong(1, NMAX), K = rnd.nextLongLong(0, N-1));
        for(int i = 0; i < 10; i++) CASE(N = rnd.nextLongLong(1, NMAX), K = N-1);
        CASE(N = 101, K = 50);
        CASE(N = 1000000, K = 9);
    }

private:
    
};
