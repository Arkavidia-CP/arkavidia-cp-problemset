#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:

    string s;
    long long LENMAX = 1e5;

    long long ans;
    void InputFormat() {
        LINE(s);
    }

    void OutputFormat() {
        LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(1 <= s.length() && s.length() <= LENMAX);
    }
private:
    
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "aarraan"
        });
        Output({
            "9"
        });
    }
    
    void SampleTestCase2() {
        Input({
            "arkavidiaviii"
        });
        Output({
            "34"
        });
    }

    void BeforeTestCase() {
        s = "";
    }

    void TestCases(){
        CASE(s = randomString(10));
        CASE(s = randomString(100));
        CASE(s = randomString(1000));
        CASE(s = randomString(10000));
        for (int i = 0; i < 10; i++) CASE(s = randomString(rnd.nextInt(1, 10));
        for (int i = 0; i < 10; i++) CASE(s = randomString(rnd.nextInt(10, 100));
        for (int i = 0; i < 10; i++) CASE(s = randomString(rnd.nextInt(100, 1000));
        for (int i = 0; i < 10; i++) CASE(s = randomString(rnd.nextInt(1000, 10000));
    }

private:
    string randomString(int n) {
        string str = "";
        for (int i = 0; i < n; i++) {
            str += (char)(rnd.nextInt(0, 25) + 'a');
        }
        return str;
    }
};