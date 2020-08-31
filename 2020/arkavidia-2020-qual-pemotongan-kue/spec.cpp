#include <tcframe/spec.hpp>
#include <assert.h>

using namespace tcframe;
using namespace std;

typedef long long LL;

const LL MAXN = 1e18;

class ProblemSpec : public BaseProblemSpec{
    protected:
        LL N;
        int ans;
    
    void InputFormat(){
        LINE(N);
    }

    void OutputFormat(){
        LINE(ans);
    }

    void GradingConfig(){
        TimeLimit(1);
        MemoryLimit(64);
    }

    void Constraints(){
        CONS(4 <= N && N <= MAXN);
    }

};

class TestSpec : public BaseTestSpec<ProblemSpec>{
    protected:
        void TestCases(){
        	CASE(N = 4);
            CASE(N = 5);
            CASE(N = 6);
            for (int i = 0; i < 10; ++i){
                CASE(N = rnd.nextLongLong(100001, 2*1e9));
            }
            for (int i = 0; i < 10; ++i){
                CASE(N = rnd.nextLongLong(100, 100000));
            }
            CASE(N = MAXN);
            for (int i = 0; i < 20; ++i){
                CASE(N = rnd.nextLongLong(2*1e9, MAXN));
            }
        }
};