#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

#define MAXN 1e5
#define MAXNUM 1e9

class ProblemSpec: public BaseProblemSpec {
protected:
    int n,m,k;
    vector<int> a,b,c,d;
    vector<int> ans;

    void InputFormat() {
        LINE(n,m,k);
        LINE(a);
        LINE(b);
        LINE(c);
        LINE(d);
    }

    void OutputFormat() {
        LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(2);
        MemoryLimit(512);
    }

    void Constraints() {
        CONS(1<=n && n<=MAXN);
        CONS(1<=m && m<=MAXNUM);
        CONS(1<=k && k<=MAXNUM);
        CONS(eachElementBetween(a,1,MAXNUM));
        CONS(eachElementBetween(b,1,MAXNUM));
        CONS(eachElementBetween(c,1,MAXNUM));
        CONS(eachElementBetween(d,1,MAXNUM));
    }

private:
    bool eachElementBetween(const vector<int>& v, int lo, int hi) {
        for (int x : v) {
            if (x < lo || x > hi) {
                return false;
            }
        }
        return true;
    }    
};

class TestSpec: public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "3 2 10",
            "10 20 30",
            "4 5 6",
            "100 1",
            "2 10"
        });
        Output({
            "1 -1"
        });
    }

    void BeforeTestCase() {
        a.clear();
        b.clear();
        c.clear();
        d.clear();
    }

    void TestCases() {
        for(int i=0;i<15;i++) {
            CASE(n=20,m=20,k=rnd.nextInt(1,100),rand_T(n,a,70),rand_T(n,b,70),rand_T(n,c,70),rand_T(n,d,100));
        }
        for(int i=0;i<15;i++) {
            CASE(n=100,m=200,k=rnd.nextInt(1,1000),rand_T(n,a,700),rand_T(n,b,700),rand_T(n,c,700),rand_T(n,d,1000));
        }
        for(int i=0;i<15;i++) {
            CASE(n=rnd.nextInt(100,10000),m=rnd.nextInt(100,10000),k=MAXNUM,rand_T(n,a,MAXNUM),rand_T(n,b,MAXNUM),rand_T(n,c,MAXNUM),rand_T(n,d,MAXNUM));
        }
        for(int i=0;i<15;i++) {
            CASE(n=MAXN,m=MAXN,k=MAXNUM,rand_T(n,a,MAXNUM),rand_T(n,b,MAXNUM),rand_T(n,c,MAXNUM),rand_T(n,d,MAXNUM));
        }        
    }

private:
    void rand_T(int n, vector<int>& t, int maks) {
        for(int i=0;i<n;i++) {
            int temp = rnd.nextInt(1,maks);
            t.push_back(temp);
        }    
    }
};