#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
    const int NMAX = 1000000;
    int N;
    string S, ans;

    void InputFormat() {
        LINE(N);
        LINE(S);
    }

    void OutputFormat1() {
        LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(1 <= S.length() && S.length() <= NMAX);
        CONS(1 <= N <= NMAX);
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:

    vector<char> chars;

    void SampleTestCase1() {
        Input({
            "5",
            "AAAAA"
        });
        Output({
            "Arka"
        });
    }
    void SampleTestCase2() {
        Input({
            "3",
            "ABA"
        });
        Output({
            "Vidia"
        });
    }

    void TestCases() {
        chars.clear();
        chars.push_back('A');
        chars.push_back('B');
        for (int i=0;i<60;i++){
            int len;
            if(i<10){
                len = rnd.nextInt(1, 10);
            }
            else if(i<20){
                len = rnd.nextInt(11, 100);
            }
            else if(i<30){
                len = rnd.nextInt(101, 1000);
            }
            else if(i<40){
                len = rnd.nextInt(1001, 10000);
            }
            else if(i<50){
                len = rnd.nextInt(10001, 100000);
            }else{
                len = rnd.nextInt(100001, 1000000);
            }

            if(i%2 == 0){
                make_random_query(len, chars);
            }else{
                make_vidia_query(len, chars);
            }
        }
    }

private:
    void make_random_query(int len, vector<char>& chars){
        string s;
        s = "";
        for(int j=0; j<len; j++){
            s += chars[rnd.nextInt(0, 1)];
        }
        CASE(N = len, S = s);
    }

    void make_vidia_query(int len, vector<char>& chars){
        string s;
        s = "";
        bool odds[20];
        memset(odds, false, sizeof(odds));
        for(int j=0; j<len; j++){
            char c = chars[rnd.nextInt(0, 1)];
            s += c;
            int pow = __builtin_ctz(len-j);
            if(c == 'A') {
                odds[pow] = !(odds[pow]);
            }
            if(len - j - (1<<pow) == 0){
                if(odds[pow]){
                    s[j] = (s[j] == 'A') ? 'B' : 'A';
                    odds[pow] = false;
                }
            }
        }
        CASE(N = len, S = s);
    }
};
