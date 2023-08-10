#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

typedef long long ll;

#define MAXN 20
#define MAXM 20
#define MAXA 1e10

class ProblemSpec: public BaseProblemSpec {
protected:
    int n, m;
    ll x, y;
    vector<vector<ll>> v;
    ll ans_1;
    vector<ll> ans;
    

    void InputFormat() {
        LINE(n, m, x, y);
        LINES(v) % SIZE(n);
    }

    void OutputFormat() {
        LINE(ans_1);
        LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(3<=n && n<=MAXN);
        CONS(3<=m && m<=MAXM);
        CONS(1<=x && x<=MAXA);
        CONS(1<=y && y<=MAXA);
        CONS(eachElementBetweens(v,1,MAXA));
    }

private:
    bool eachElementBetween(const vector<ll>& v, ll lo, ll hi) {
        for (ll x : v) {
            if (x < lo || x > hi) {
                return false;
            }
        }
        return true;
    }

    bool eachElementBetweens(const vector<vector<ll>>& v, ll lo, ll hi) {
        for (auto x : v) {
            if (!eachElementBetween(x, lo, hi)) {
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
            "3 3 5 5",
            "1 3 1",
            "2 2 1",
            "1 2 1"     
        });
        Output({
            "10",
            "1 1 2"
        });
    }

    void SampleTestCase2() {
        Input({
            "3 3 4 2",
            "1 3 1",
            "2 2 1",
            "1 2 3",
        });
        Output({
            "8",
            "2 1 3"
        });
    };

    void BeforeTestCase() {
        v.clear();
    }

    void TestCases() {
        for(int i=0;i<10;i++) {
            CASE(n=rnd.nextInt(3, 10), m=rnd.nextInt(3, 10), randomMatrix(n, m, v, 1, MAXA, rnd.nextInt(0, 1), x, y));
        }
        for(int i=0;i<10;i++) {
            CASE(n=rnd.nextInt(3, 10), m=10, randomMatrix(n, m, v, 1, MAXA, rnd.nextInt(0, 1), x, y));
        }
        for(int i=0;i<10;i++) {
            CASE(n=10, m=rnd.nextInt(3, 10), randomMatrix(n, m, v, 1, MAXA, rnd.nextInt(0, 1), x, y));
        }
        for(int i=0;i<40;i++) {
            CASE(n=rnd.nextInt(MAXN/2, MAXN), m=rnd.nextInt(MAXM/2, MAXM), randomMatrix(n, m, v, MAXA/2, MAXA, rnd.nextInt(0, 4), x, y));
        }
    }

private:
    void randomMatrix(int n, int m, vector<vector<ll>>& v, ll lo, ll hi, bool getAns, ll& x, ll& y) {
        for(int i=0;i<n;i++) {
            vector<ll> temp;
            for(int j=0;j<m;j++) {
                temp.push_back(rnd.nextLongLong(lo, hi));
            }
            v.push_back(temp);
        }
        if(getAns){
            int id = rnd.nextInt(0, m-1);
            ll sum = 0;
            for(int i=0;i<n;i++) {
                sum += v[i][id];
                int idx[] = {(id+1)%m, (id-1+m)%m, id%m};
                id = idx[rnd.nextInt(0, 2)];
            }
            x = min(sum, 10000000000LL);
            y = rnd.nextLongLong(1, MAXA);
        } else{
            x = rnd.nextLongLong(lo, hi);
            y = rnd.nextLongLong(lo, hi);
        }
    }
};