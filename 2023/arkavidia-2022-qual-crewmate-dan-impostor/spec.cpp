#include <tcframe/spec.hpp>
#include<bits/stdc++.h>
using namespace tcframe;
using namespace std;

#define MAXN 1e5
#define sz(x) (int)(x).size()

class ProblemSpec: public BaseProblemSpec {
protected:
    int n;
    vector<int> t;
    int ans;
    void InputFormat() {
        LINE(n);
        LINE(t);
    }

    void OutputFormat() {
        LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(3);
        MemoryLimit(256);   
    }

    void Constraints() {
        CONS(2<=n && n<=MAXN);
        CONS(valid(t));
    }

private:
    bool valid(vector<int> a) {
        for(int i=0;i<sz(a);i++) {
            int x = a[i];
            if(x<1 || x>n || x==i+1) {
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
            "3",
            "2 3 2"
        });
        Output({
            "1"
        });
    }

    void SampleTestCase2() {
        Input({
            "6",
            "3 1 2 6 4 5"
        });
        Output({
            "2"
        });
    }
    
    void BeforeTestCase() {
        t.clear();
    }

    void TestCases() {
        for(int i=0;i<10;i++) {
            CASE(n=11,rand_T(n,t,5.0));
        }
        for(int i=0;i<10;i++) {
            CASE(n=11,rand_T(n,t));
        }
        // ans < (n-1)/2
        for(int i=0;i<10;i++) {
            CASE(n=rnd.nextInt(100,10000),rand_T(n,t, 0.5));
        }
        // ans = (n-1)/2 hampir selalu
        for(int i=0;i<10;i++) {
            CASE(n=rnd.nextInt(100,10000),rand_T(n,t,0.0));
        }
        // ans hampir mendekati (n-1)/2
        for(int i=0;i<5;i++) {
            CASE(n=MAXN,rand_T(n,t,0.5));
        }
        // ans mendekati n/3
        for(int i=0;i<5;i++) {
            CASE(n=MAXN,rand_T(n,t,7.0));
        }
        // ans = (n-1)/2
        for(int i=0;i<10;i++) {
            CASE(n=MAXN,rand_T(n,t));
        }                
    }

private:
    void rand_T(int n, vector<int>& t, double c3Percentage = 0.2) {
        int m = round(n/(1.0+c3Percentage));
        for(int i=0;i<m;i++) {
            int temp = rnd.nextInt(1,m);
            while(temp==i+1) {
                temp = rnd.nextInt(1,m);
            }
            t.push_back(temp);
        }
        // spam cycle size 3
        for(int i=m;i<n;i++) {
            if(((i-m)%3)==2) {
                t.push_back(i-1);
            } else {
                if(i+1<n) {
                    t.push_back(i+2);
                } else {
                    t.push_back(i);
                }
            }
        }
    }
};