#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

#define MAXN 2e5
#define MAXA 1e9
#define MAXDIFF 1e6

class ProblemSpec: public BaseProblemSpec {
protected:
    int n;
    vector<long long> k, xa, ya, xb, yb;
    vector<long long> ans;

    void InputFormat() {
        LINE(n);
        LINES(k, xa, ya, xb, yb) % SIZE(n);
    }

    void OutputFormat() {
        LINES(ans) % SIZE(n);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(1<=n && n<=MAXN);
        CONS(eachElementBetween(k,-MAXA, MAXA));
        CONS(eachElementBetween(xa,-MAXA, MAXA));
        CONS(eachElementBetween(ya,-MAXA, MAXA));
        CONS(eachElementBetween(xb,-MAXA, MAXA));
        CONS(eachElementBetween(yb,-MAXA, MAXA));
        CONS(eachDistanceBetween(xa, ya, xb, yb, 0, MAXDIFF));
    }

private:
    bool eachElementBetween(const vector<long long>& v, long long lo, long long hi) {
        for (long long x : v) {
            if (x < lo || x > hi) {
                return false;
            }
        }
        return true;
    }    

    bool eachDistanceBetween(const vector<long long>& xa, const vector<long long>& ya, const vector<long long>& xb, const vector<long long>& yb, long long lo, long long hi) {
        for (int i = 0; i < xa.size(); i++) {
            if (abs(xa[i] - xb[i]) + abs(ya[i] - yb[i]) < lo || abs(xa[i] - xb[i]) + abs(ya[i] - yb[i]) > hi) {
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
            "2",
            "-1 0 2 1 4",
            "-1 1 4 0 2"
        });
        Output({
            "3",
            "0"
        });
    }

    void SampleTestCase2() {
        Input({
            "2",
            "2 -1 3 4 1",
            "1 3 1 6 3"
        });
        Output({
            "0",
            "10"
        });
    };

    void BeforeTestCase() {
        k.clear();
        xa.clear();
        ya.clear();
        xb.clear();
        yb.clear();
    }

    void TestCases() {
        for(int i=0;i<10;i++) {
            CASE(n=1, randomLineOffset(k, -MAXA, MAXA), randomCoordinate(xa, ya, xb, yb, -MAXA, MAXA, 0, MAXDIFF));
        }
        CASE(n=1, k={0}, xa={0}, ya={1}, xb={2}, yb={2});
        CASE(n=1, k={0}, xa={1}, ya={1}, xb={2}, yb={3});
        CASE(n=1, k={1}, xa={0}, ya={0}, xb={0}, yb={0});
        for(int i=0;i<5;i++) {
            CASE(n=10, randomLineOffset(k, -MAXA, MAXA), randomCoordinate(xa, ya, xb, yb, -MAXA, MAXA, 0, MAXDIFF));
            CASE(n=10, randomLineOffset(k, -MAXA, MAXA), randomCoordinate(xa, ya, xb, yb, -MAXA, MAXA, MAXDIFF/2, MAXDIFF));
        }
        for(int i=0;i<5;i++) {
            CASE(n=100, randomLineOffset(k, -MAXA, MAXA), randomCoordinate(xa, ya, xb, yb, -MAXA, MAXA, 0, MAXDIFF));
        }       
        for(int i=0;i<5;i++) {
            CASE(n=100, randomLineOffset(k, -MAXA, MAXA), randomCoodinteWithSolution(xa, ya, xb, yb, -MAXA, MAXA, 0, MAXDIFF));
        }       
        for(int i=0;i<2;i++) {
            CASE(n=rnd.nextInt(1000, MAXN), randomLineOffset(k, -MAXA, MAXA), randomCoordinate(xa, ya, xb, yb, MAXA/2, MAXA, MAXDIFF/2, MAXDIFF));
        }       
        for(int i=0;i<2;i++) {
            CASE(n=rnd.nextInt(1000, MAXN), randomLineOffset(k, -MAXA, MAXA), randomCoodinteWithSolution(xa, ya, xb, yb, MAXA/2, MAXA, MAXDIFF/2, MAXDIFF));
        }       
        for(int i=0;i<2;i++) {
            CASE(n=MAXN, randomLineOffset(k, -MAXA, MAXA), randomCoordinate(xa, ya, xb, yb, -MAXA, MAXA, MAXDIFF/2, MAXDIFF));
        }       
        for(int i=0;i<2;i++) {
            CASE(n=MAXN, randomLineOffset(k, -MAXA, MAXA), randomCoodinteWithSolution(xa, ya, xb, yb, -MAXA, MAXA, MAXDIFF/2, MAXDIFF));
        }       
    }

private:

    void randomLineOffset(vector<long long>& k, long long lo, long long hi) {
        for(int i=0;i<n;i++) {
            k.push_back(rnd.nextLongLong(lo,hi));
        }
    }

    void randomCoordinate(vector<long long>& xa, vector<long long>& ya, vector<long long>& xb, vector<long long>& yb, long long lo, long long hi, long long lo1, long long hi1) {
        for(int i=0;i<n;i++) {
            xa.push_back(rnd.nextLongLong(lo,hi));
            long long distX = rnd.nextLongLong(lo1,hi1);
            xb.push_back(rnd.nextLongLong(0,1) ? min(xa[i] + distX, hi) : max(lo, xa[i] - distX));

            ya.push_back(rnd.nextLongLong(lo,hi));
            long long distY = rnd.nextLongLong(max(lo1-distX, 0LL),hi1-distX);
            yb.push_back(rnd.nextLongLong(0,1) ? min(ya[i] + distY, hi) : max(ya[i] - distY, lo));
        }
    }

    void randomCoodinteWithSolution(vector<long long>& xa, vector<long long>& ya, vector<long long>& xb, vector<long long>& yb, long long lo, long long hi, long long lo1, long long hi1) {
        for(int i=0;i<n;i++) {
            xa.push_back(rnd.nextLongLong(lo,hi));
            ya.push_back(rnd.nextLongLong(lo,hi));

            long long distX = rnd.nextLongLong(lo1,hi1);

            xb.push_back(min(hi, xa[i] + distX));
            if(ya[i]-xa[i]<k[i]){
                long long distY = rnd.nextLongLong(max(lo1-distX, 0LL),hi1-distX);
                yb.push_back(min(hi, min(ya[i] + distY, k[i] + xb[i])));
            } else {
                long long distY = rnd.nextLongLong(max(lo1-distX, 0LL),min(hi1-distX, max(k[i]-xb[i]-ya[i], max(lo1-distX, 0LL))));
                yb.push_back(min(hi, ya[i] + distY));
            }
        }
    }
};