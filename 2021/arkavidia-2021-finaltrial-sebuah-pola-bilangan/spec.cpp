//by irfansofyana
#include <tcframe/spec.hpp>
#include <assert.h>

using namespace std;
using namespace tcframe;

typedef long long LL;

const LL MAXN = 1e9;
const LL MAXK = 1e18;
const int MAXTC = 1e5;


class ProblemSpec: public BaseProblemSpec{
    protected:
        int tc;
        vector<LL> n, k;
        vector<LL> ansx, ansy;

    void InputFormat(){
        LINE(tc);
        LINES(n, k) % SIZE(tc);
    }

    void OutputFormat(){
        LINES(ansx, ansy) % SIZE(tc);
    }

    void GradingConfig(){
        TimeLimit(1);
        MemoryLimit(256);
    }

    void Constraints(){
        CONS(eachElementBetween(n, 1, MAXN));
        CONS(validK(n, k));
        CONS(1 <= tc <= MAXTC);
    }

    private:
        bool eachElementBetween(const vector<LL> &a, LL lo, LL hi){
            for (int i = 0; i < (int)a.size(); ++i){
                if (a[i] < lo || a[i] > hi) return false;
            }
            return true;
        }

        bool validK(const vector<LL> &n, const vector<LL> &k){
            assert(n.size() == k.size());
            for (int i = 0; i < (int)n.size(); ++i){
                if (k[i] < 1 || k[i] > n[i] * n[i]) return false;
            }
            return true;
        }
};

class TestSpec : public BaseTestSpec<ProblemSpec>{
    protected:
        void TestCases(){
            CASE(tc = 1, n = {1}, k = {1});
            CASE(tc = 2, n = {5, 6}, k = {25, 20});
            for (int i = 0; i < 3; ++i){
                CASE(randomSmall(tc, n, k));
            }
            for (int i = 0; i < 3; ++i){
                CASE(randomMedium(tc, n, k));
            }
            for (int i = 0; i < 9; ++i){
                CASE(randomLarge(tc, n, k));
            }
            for (int i = 0; i < 3; ++i){
                CASE(randomWorstCase(tc, n, k));
            }
        }
    
    private:
        void randomSmall(int &tc, vector<LL> &n, vector<LL> &k){
            tc = rnd.nextInt(1, 1000);
            n.clear();
            k.clear();
            for (int i = 0; i < tc; ++i){
                LL tempN = rnd.nextLongLong(1, MAXTC);
                LL tempK = rnd.nextLongLong(1, tempN*tempN);
                n.push_back(tempN);
                k.push_back(tempK);
            }
        }
        void randomMedium(int &tc, vector<LL> &n, vector<LL> &k){
            tc = rnd.nextInt(1001, MAXTC);
            n.clear();
            k.clear();
            for (int i = 0; i < tc; ++i){
                LL tempN = rnd.nextLongLong(MAXTC+1, 100*MAXTC);
                LL tempK = rnd.nextLongLong(1, tempN*tempN);
                n.push_back(tempN);
                k.push_back(tempK);
            }
        }
        void randomLarge(int &tc, vector<LL> &n, vector<LL> &k){
            tc = rnd.nextInt(1001, MAXTC);
            n.clear();
            k.clear();
            for (int i = 0; i < tc; ++i){
                LL tempN = rnd.nextLongLong(100*MAXTC+1, MAXN);
                LL tempK;
                if (rnd.nextInt(0, 1) == 0)
                    tempK = rnd.nextLongLong(MAXN, tempN*tempN);
                else
                    tempK = rnd.nextLongLong(1, tempN*tempN);
                n.push_back(tempN);
                k.push_back(tempK);
            }
        }
        void randomWorstCase(int &tc, vector<LL> &n, vector<LL> &k){
            tc = MAXTC;
            n.clear();
            k.clear();
            for (int i = 0; i < tc; ++i){
                LL tempN = MAXN;
                LL tempK = rnd.nextLongLong(MAXN, tempN*tempN);
                n.push_back(tempN);
                k.push_back(tempK);
            }
        }
};