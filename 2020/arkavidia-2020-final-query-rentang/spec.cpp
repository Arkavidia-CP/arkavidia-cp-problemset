#include <tcframe/spec.hpp>
#include <assert.h>

using namespace std;
using namespace tcframe;

const int MAXN = 1000000;
const int MAXM = 2000;

class ProblemSpec : public BaseProblemSpec{
    protected:
        //list of variables
        int N, Q;
        vector<int> L, R;
        vector<int> ql, qr;
        vector<int> ans;

    void InputFormat(){
        LINE(N);
        LINES(L, R) % SIZE(N);
        LINE(Q);
        LINES(ql, qr) % SIZE(Q);
    }

    void OutputFormat(){
        LINES(ans) % SIZE(Q);
    }

    void GradingConfig(){
        TimeLimit(1);
        MemoryLimit(64);
    }

    void Constraints(){
        CONS(1 <= N && N <= MAXN);
        CONS(1 <= Q && Q <= MAXN);
        CONS(eachElementBetween(L, 0, MAXM));
        CONS(eachElementBetween(R, 0, MAXM));
        CONS(eachElementBetween(ql, 0, MAXM));
        CONS(eachElementBetween(qr, 0, MAXM));
        CONS(equalSize(L, N));
        CONS(equalSize(R, N));
        CONS(equalSize(ql, Q));
        CONS(equalSize(qr, Q));
        CONS(check(L, R));
        CONS(check(ql, qr));
    }

    private:
        bool check(const vector<int>& a, const vector<int>& b){
            for (int i = 0; i < (int)a.size(); ++i){
                if (a[i] > b[i]) return false;
            }
            return true;
        }

        bool equalSize(const vector<int>& a, int sz){
            return ((int)a.size() == sz);
        }

        bool eachElementBetween(const vector<int>& a, int lo, int hi){
            for (int i = 0; i < (int)a.size(); ++i){
                if (a[i] > hi || a[i] < lo) return false;
            }
            return true;
        }
};

class TestSpec : public BaseTestSpec<ProblemSpec>{
    protected:
        void TestCases(){
            for (int i = 0; i < 2; ++i){
                CASE(
                    N = rnd.nextInt(1, 1000),
                    randomArrayNormal(N, L, R),
                    Q = rnd.nextInt(1, 1000),
                    randomArrayNormal(Q, ql, qr)
                );
            }
            for (int i = 0; i < 5; ++i){
                CASE(
                    N = rnd.nextInt(1000, MAXN),
                    randomArrayNormal(N, L, R),
                    Q = rnd.nextInt(1000, MAXN),
                    randomArrayNormal(Q, ql, qr)
                );
            }
            for (int i = 0; i < 3; ++i){
                CASE(
                    N = rnd.nextInt(10000, MAXN),
                    randomArrayNormal(N, L, R),
                    Q = rnd.nextInt(1, MAXN),
                    randomArrayNormal(Q, ql, qr)
                );
            }
            for (int i = 0; i < 5; ++i){
                CASE(
                    N = rnd.nextInt(100000, MAXN),
                    randomArrayNormal(N, L, R),
                    Q = rnd.nextInt(1000, MAXN),
                    randomArrayNormal(Q, ql, qr)
                );
            }
            for (int i = 0; i < 2; ++i){
                CASE(
                    N = rnd.nextInt(100000, MAXN),
                    randomArrayNormal(N, L, R),
                    Q = rnd.nextInt(100000, MAXN),
                    randomArrayNormal(Q, ql, qr)
                );
            }
            for (int i = 0; i < 3; ++i){
                CASE(
                    N = MAXN,
                    randomArrayNormal(N, L, R),
                    Q = MAXN,
                    randomArrayNormal(Q, ql, qr)
                );
            }
        }
    private:
        void randomArrayNormal(int sz, vector<int> & a, vector<int> & b){
            a.clear();
            b.clear();
            for (int i = 0; i < sz; ++i){
                int l = rnd.nextInt(0, MAXM);
                int r = rnd.nextInt(l, MAXM);
                a.push_back(l);
                b.push_back(r);
            }
        }

};