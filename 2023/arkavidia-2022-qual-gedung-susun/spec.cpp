#include <tcframe/spec.hpp>

using namespace tcframe;
using namespace std;

typedef long long ll;

#define MAXN 1e5
#define MAXM 1e2
#define MAXA 1e9

class ProblemSpec: public BaseProblemSpec {
protected:
    int n, m;
    vector<int> d, GF;
    vector<ll> b;
    ll ans;
    

    void InputFormat() {
        LINE(n, m);
        LINE(GF);
        LINE(b);
        LINE(d);
    }

    void OutputFormat() {
        LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(2);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(2<=n && n<=MAXN);
        CONS(2<=m && m<=MAXM);
        CONS(eachElementBetween(GF,1,m));
        CONS(eachElementBetween(b,0LL,MAXA));
        CONS(eachElementBetween(d,1,m-1));
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

    bool eachElementBetween(const vector<ll>& v, ll lo, ll hi) {
        for (ll x : v) {
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
            "2 2",
            "1 2",
            "10 8",
            "1 1"       
        });
        Output({
            "19"
        });
    }

    void SampleTestCase2() {
        Input({
            "4 5",
            "4 2 1 4",
            "11 12 7 6",
            "1 4 2 1",
        });
        Output({
            "41"
        });
    };

    void BeforeTestCase() {
        GF.clear();
        b.clear();
        d.clear();
    }

    void TestCases() {
        for(int i=0;i<10;i++) {
            CASE(n=rnd.nextInt(2, 10), m=10, randomArray(n,GF,1,m), randomArray(n,b,0,MAXA), randomArray(n,d,1,m-1));
        }
        for(int i=0;i<10;i++) {
            CASE(n=10, m=rnd.nextInt(2, 10), randomArray(n,GF,1,m), randomArray(n,b,0,MAXA), randomArray(n,d,1,max(m-1, 1)));
        }
        for(int i=0;i<10;i++) {
            CASE(n=rnd.nextInt(100, 10000), m=MAXM, randomArray(n,GF,1,m), randomArray(n,b,0,MAXA), randomArray(n,d,1,m-1));
        }
        for(int i=0;i<10;i++) {
            CASE(n=10000, m=rnd.nextInt(MAXM/2, MAXM), randomArray(n,GF,1,m), randomArray(n,b,0,MAXA), randomArray(n,d,1,m-1));
        }        
        for(int i=0;i<10;i++) {
            CASE(n=rnd.nextInt(10000, MAXN), m=rnd.nextInt(10, MAXM), randomArray(n,GF,1,m), randomArray(n,b,MAXA/2,MAXA), randomArray(n,d,1,m-1));
        }
        for(int i=0;i<10;i++) {
            CASE(n=rnd.nextInt(MAXN/2, MAXN), m=rnd.nextInt(MAXM/2, MAXM), randomArray(n,GF,1,m), randomArray(n,b,0,MAXA), randomArray(n,d,1,m-1));
        }        
        CASE(n=MAXN, m=MAXM, randomArray(n,GF,1,m), randomArray(n,b,0,MAXA), randomArray(n,d,1,m-1));
        CASE(n=MAXN, m=MAXM, randomArray(n,GF,1,m), randomArray(n,b,0,MAXA), randomArray(n,d,1,m-1));
        CASE(n=MAXN, m=MAXM, randomArray(n,GF,1,m), randomArray(n,b,0,MAXA), randomArray(n,d,1,m-1));
    }

private:
    void randomArray(int n, vector<int>& a, int lo, int hi) {
        a.resize(n);
        for (int i = 0; i < n; i++) {
            a[i] = rnd.nextInt(lo, hi);
        }
    }

    void randomArray(int n, vector<ll>& a, ll lo, ll hi) {
        a.resize(n);
        for (int i = 0; i < n; i++) {
            a[i] = rnd.nextLongLong(lo, hi);
        }
    }
};