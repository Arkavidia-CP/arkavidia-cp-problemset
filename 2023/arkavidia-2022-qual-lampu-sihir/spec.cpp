#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
    const int NMAX = 1e6;
    const long long WMAX = 1e18;
    int N;
    long long K;
    vector<long long> w;
    long long ans;

    void InputFormat() {
        LINE(N, K);
        LINE(w);
    }

    void OutputFormat1() {
        LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(256);
    }

    void Constraints() {
        for(auto wi : w){
            CONS(1LL <= wi && wi <= WMAX);
        }
        CONS(1 <= N <= NMAX);
        CONS(1LL <= K <= WMAX);
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:

    vector<char> chars;

    void SampleTestCase1() {
        Input({
            "4 10",
            "9 6 16 3"
        });
        Output({
            "2"
        });
    }
    void SampleTestCase2() {
        Input({
            "3 1000000000",
            "2000000000 3000000000 4000000000"
        });
        Output({
            "1000000000"
        });
    }

    void TestCases() {
        for (int i=0;i<60;i++){
            int n;
            long long wmax;
            if(i<10){
                n = rnd.nextInt(1, 10);
                wmax = rnd.nextLongLong(1LL,100LL);
            }
            else if(i<20){
                n = rnd.nextInt(11, 100);
                wmax = rnd.nextLongLong(1LL,500LL);
            }
            else if(i<30){
                n = rnd.nextInt(101, 1000);
                wmax = rnd.nextLongLong(1LL,1000LL);
            }
            else if(i<40){
                n = rnd.nextInt(1001, 10000);
                wmax = rnd.nextLongLong(1LL, 100000LL);
            }
            else if(i<50){
                n = rnd.nextInt(10001, 100000);
                wmax = rnd.nextLongLong(1LL, 10000000LL);
            }else{
                n = rnd.nextInt(100001, 1000000);
                wmax = rnd.nextLongLong(1LL, WMAX);
            }
            make_random_query(n, wmax);
        }
    }

private:
    void make_random_query(int len, long long wmax){
        vector<long long> wq;
        long long k = rnd.nextLongLong(1,wmax);
        for(int j=0; j<len; j++){
            wq.push_back(rnd.nextLongLong(1LL,wmax));
        }
        CASE(N = len, K = k, w = wq);
    }
};
