#include<tcframe/spec.hpp>
#include<bits/stdc++.h>
using namespace tcframe;
using namespace std;

#define MAXN 1e3
#define MINN 1
#define MAXK 5
#define MINK 1
#define MAXU 1e3
#define MINU 1
#define MAXP 1e9
#define MAXC 1e2
#define ll long long

class ProblemSpec: public BaseProblemSpec {
protected:
    int n,u,k;
    vector<int> p,c;
    ll ans;

    void InputFormat() {
        LINE(n,u,k);
        LINES(p,c) % SIZE(n);
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
        CONS(1<=u && u<=MAXU);
        CONS(1<=k && k<=MAXK);
        eachElementBetween(p,1,MAXP);
        eachElementBetween(c,1,MAXC);
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
            "5 50 2",
            "1 100",
            "2 30",
            "1 20",
            "3 30",
            "7 20"
        });
        Output({
            "10"
        });
    }

    void SampleTestCase2() {
        Input({
            "10 50 5",
            "1 1",
            "2 2",
            "3 3",
            "4 4",
            "5 5",
            "6 6",
            "7 7",
            "8 8",
            "9 9",
            "10 10"
        });
        Output({
            "33"
        });
    }

    void BeforeTestCase() {
        p.clear();
        c.clear();
    }

    void TestCases() {
        CASE(n=rnd.nextInt(10,100),k=rnd.nextInt(1,MAXK),ansIsZero(n));
        CASE(n=rnd.nextInt(100,MAXN),k=rnd.nextInt(1,MAXK),ansIsZero(n));
        for(int i=1;i<=MAXK;i++) {
            for(int j=0;j<3;j++) {
                CASE(n=10,k=i,randomUPC(n));
                CASE(n=10,k=i,allCisOne(n));
            }
            for(int j=0;j<3;j++) {
                CASE(n=rnd.nextInt(10,500),k=i,randomUPC(n));
                CASE(n=rnd.nextInt(10,500),k=i,allCisOne(n));
            }
            for(int j=0;j<3;j++) {
                CASE(n=MAXN,k=i,randomUPC(n));
                CASE(n=MAXN,k=i,allCisOne(n));
            }
        }
        for(int i=0;i<3;i++) {
            CASE(n=rnd.nextInt(100,MAXN),k=rnd.nextInt(1,MAXK),allCisOneMax(n));
        }
    }
private:
    void ansIsZero(int n) {
        u = rnd.nextInt(1,MAXC-1);
        for(int i=0;i<n;i++) {
            p.push_back(rnd.nextInt(1,MAXP));
            c.push_back(rnd.nextInt(u+1,MAXC));
        }
    }

    void randomUPC(int n) {
        // cout << n << "\n";
        int sum = 0;
        for(int i=0;i<n;i++) {
            p.push_back(rnd.nextInt(1,MAXP));
            c.push_back(rnd.nextInt(1,MAXC));
            sum += c[i];
        }
        u = rnd.nextInt(MINU,MAXU);
    }

    void allCisOne(int n) {
        // cout << n << "\n";
        int sum = 0;
        for(int i=0;i<n;i++) {
            p.push_back(rnd.nextInt(1,MAXP));
            c.push_back(1);
            sum += c[i];
        }
        int temp = MAXU;
        u = rnd.nextInt(MINU,min(temp,sum+1));
    }

    void allCisOneMax(int n) {
        // cout << n << "\n";
        int sum = 0;
        for(int i=0;i<n;i++) {
            p.push_back(rnd.nextInt(1,MAXP));
            c.push_back(1);
        }
        u = rnd.nextInt(MINU,MAXU);
    }    
};