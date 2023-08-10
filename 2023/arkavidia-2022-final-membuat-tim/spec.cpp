#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
    const int NMAX = 30;
    const int AMAX = 1000;
    int N, K;
    vector<int> murid;

    int ans;
    void InputFormat() {
        LINE(N, K);
        LINE(murid % SIZE(N));
    }

    void OutputFormat1() {
        LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(512);
    }

    void Constraints() {
        CONS(2 <= N <= NMAX);
        CONS(1 <= K < N);
        CONS(array_cons(murid));
    }

private:
    bool array_cons(vector<int> murid){
        if(murid.size() != N)return false;
        int pos = 1;
        for(int val : murid){
            if(val > AMAX || val <= 0)pos = 0;
        }
        return pos;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:

    void SampleTestCase() {
        Input({
            "6 3",
            "4 2 9 8 8 6"
        });
        Output({
            "1"
        });
    }

    void BeforeTestCase(){
        murid.clear();
    }

    void TestCases() {
        for(int i=0;i<10;i++)CASE(N = 5, K = rnd.nextInt(1,4), random_murid(N, murid, 10));
        for(int i=0;i<10;i++)CASE(N = 10, K = rnd.nextInt(1,9), random_murid(N, murid, 100));
        for(int i=0;i<10;i++)CASE(N = 20, K = rnd.nextInt(1,19), random_murid(N, murid, 500));
        for(int i=0;i<10;i++)CASE(N = 30, K = rnd.nextInt(1,29), random_murid(N, murid, 1000));
        for(int i=0;i<10;i++)CASE(N = rnd.nextInt(2,30), K = rnd.nextInt(1,N), random_murid(N, murid, 1000));
        for(int i=0;i<10;i++)CASE(N = 30, K = 15, random_murid(N, murid, 1000));
    }

private:
    void random_murid(int n, vector<int>& murid, int nmax){
        for(int i=0;i<n;i++){
            murid.push_back(rnd.nextInt(1,nmax));
        }
    }
};
