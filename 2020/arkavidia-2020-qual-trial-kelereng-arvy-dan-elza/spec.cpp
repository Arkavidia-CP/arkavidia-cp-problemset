#include <tcframe/spec.hpp>
using namespace std;
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
    int a, b;
    int ans;

    void InputFormat() {
        LINE(a, b);
    }

    void OutputFormat() {
        LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(64);
    }

    void Constraints() {
        CONS(1 <= a && a <= 100);
        CONS(1 <= b && b <= 100);
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void TestCases() {
        for (int i = 0; i < 5; ++i){
            CASE(
                a = rnd.nextInt(1, 100),
                b = rnd.nextInt(1, 100)
            );
        }
    }
};