#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
    const long long NMAX = 20, QMAX = 1e5;

    long long N, Q;
    vector<long long> A, M;
    vector<string> ans;

    void InputFormat() {
        LINE(N, Q);
        LINE(A % SIZE(N));
        LINES(M) % SIZE(Q);
    }

    void OutputFormat() {
        LINES(ans) % SIZE(Q);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(128);
    }

    void Constraints() {
        CONS(1 <= N && N <= NMAX);
        CONS(1 <= Q && Q <= QMAX);
        CONS(validA(A, N));
        CONS(validM(M, Q));
    }
private:
    bool validA(vector<long long> A, long long N){
        if (N != A.size()) return 0;
        for(int i=0; i<A.size(); i++){
            if(A[i]<1 || A[i]>20) return 0;
        }
        return 1;
    }
    bool validM(vector<long long> M, long long Q){
        if (Q != M.size()) return 0;
        for(int i=0; i<M.size(); i++){
            if(M[i]<1 || M[i]>1e18) return 0;
        }
        return 1;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "4 5",
            "1 2 3 4",
            "13",
            "26",
            "39",
            "52",
            "65",
        });
        Output({
            "Elon",
            "Elon",
            "Elon",
            "Elon",
            "Melvin",
        });
    }
    void BeforeTestCase() {
        A.clear();
        M.clear();
        ans.clear();
    }

    void TestCases() {
        for (int i=1;i<=10;i++){
            CASE(N = i, Q = rnd.nextInt(1, 1000), make_random_query(i, Q, A, M, 1, 1e6));
            CASE(N = i, Q = rnd.nextInt(1, 100000), make_random_query(i, Q, A, M, 1e6, 1e12));
            CASE(N = i, Q = rnd.nextInt(10000, 100000), make_random_query(i, Q, A, M, 1e12, 1e18));
        }
    }

private:
    void make_random_query(long long N, long long Q, vector<long long>& A, vector<long long>& M, long long l, long long r){
        bool used[21];
        for(int i=1; i<=20; i++){
            used[i] = false;
        }
        long long use, current;
        for(int i=0; i<N; i++){
            use = rnd.nextInt(0, 19-i);
            current = 1;
            while(used[current] || use>0){
                if(!used[current]){
                    use--;
                }
                current++;
            }
            used[current] = true;
            A.push_back(current);
        }
        for(int i=0; i<Q; i++){
            M.push_back(rnd.nextLongLong(l, r));
        }
    }
};