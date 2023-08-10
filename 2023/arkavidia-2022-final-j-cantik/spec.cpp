#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

#define MAXN 1e5
#define MAXA 1e5
#define sz(x) (int)(x).size()
#define ll long long

class ProblemSpec: public BaseProblemSpec {
protected:
    int n,k;
    vector<int> a;
    ll ans;

    void InputFormat() {
        LINE(n,k);
        LINE(a);
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
        CONS(0<=k && k<=MAXN);
        CONS(valid(a));
    }

private:
    bool valid(vector<int> a) {
        for(int i=0;i<sz(a);i++) {
            int x = a[i];
            if(x<1 || x>MAXA) {
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
            "4 2",
            "6 2 3 5"
        });
        Output({
            "5"
        });
    }

    void SampleTestCase2() {
        Input({
            "5 0",
            "1 2 1 1 3"
        });
        Output({
            "4"
        });
    }

    void SampleTestCase3() {
        Input({
            "6 1",
            "2 3 5 4 7 6"
        });
        Output({
            "5"
        });
    }

    void BeforeTestCase() {
        a.clear();
    }

    void TestCases() {
        for(int i=0;i<20;i++) {
            CASE(n=10,distPrime(a,n,k,3,500));
        }
        for(int i=0;i<20;i++) {
            CASE(n=rnd.nextInt(100,10000),distPrime(a,n,k,10000,MAXA));
        }
        for(int i=0;i<20;i++) {
            CASE(n=MAXN,distPrime(a,n,k,10000,MAXA));
        }
    }

private:
    void distPrime(vector<int> &ai, int &ni, int &ki, int ctPrime, int mxa) {
        vector<int> primes;
        vector<bool> isPrime(mxa+1, true);
        for(int i=2;i<=mxa;i++) {
            if(isPrime[i]) {
                primes.push_back(i);
                for(int j=i+i;j<=mxa;j+=i) {
                    isPrime[j] = false;
                }
                if(sz(primes)==ctPrime) {
                    break;
                }
            }
        }
        ctPrime = min(ctPrime, sz(primes));
        vector<int> cnt(ctPrime);
        for(int i=0;i<ctPrime;i++) {
            cnt[i] = rnd.nextInt(2,max(2,mxa/(primes[i]*5)));
        }
        ai.resize(ni);
        for(int i=0;i<ni;i++) {
            ai[i] = 1;
        }
        int ctPrimeFinal=0;
        for(int i=0;i<ctPrime;i++) {
            bool ok = false;
            for(int j=0;j<cnt[i];j++) {
                int ctLoop=0;
                while(true) {
                    ctLoop++;
                    int idx = rnd.nextInt(0,ni-1);
                    if(1ll*ai[idx]*primes[i]<=mxa) {
                        ai[idx] *= primes[i];
                        if(!ok) {
                            ok = 1;
                            ctPrimeFinal++;
                        }
                        break;
                    }
                    if(ctLoop>=200) {
                        break;
                    }
                }
            }
        }
        ki = rnd.nextInt(0,ctPrimeFinal);
    }
};