#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:

    int n,m,k;
    int pot, x, y;
    const int maxn = 1e5;
    const int maxpot = 1e6;
    const int maxy = 200;
    const int inf = 1e9;
    long long ans;
    vector<int> a,b,c;

    void InputFormat() {
        LINE(n,m,k,pot,x,y);
        LINE(a % SIZE(n));
        LINE(b % SIZE(m));
        LINE(c % SIZE(k));
    }

    void OutputFormat() {
        LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(1 <= n && n <= maxn);
        CONS(1 <= m && m <= maxn);
        CONS(1 <= m && m <= maxn);
        CONS(0 <= pot && pot <= maxpot);
        CONS(0 <= x && x <= inf);
        CONS(1 <= y && y <= maxy);
        CONS(arrCons(a));
        CONS(arrCons(b));
        CONS(arrCons(c));
    }
private:
    bool arrCons(vector<int> arr){
        if(arr.size() > maxn)return false;
        for(int i=0;i<arr.size();i++){
            if(arr[i] > inf || arr[i] < 1)return false;
        }
        return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "3 4 3 0 2 3",
            "3 4 1",
            "3 1 2 2",
            "6 1 4"
        });
        Output({
            "11"
        });
    }
    
    void SampleTestCase2() {
        Input({
            "3 3 3 2 5 3",
            "3 4 1",
            "5 2 3",
            "7 1 3"
        });
        Output({
            "21"
        });
    }

    void BeforeTestCase() {
        a.clear();
        b.clear();
        c.clear();
    }

    void TestCases(){
        for(int i = 0; i < 5; i++) CASE(random_size(n,m,k,1000), pot = rnd.nextInt(0, m+k), x = rnd.nextInt(0,1e4), y = rnd.nextInt(1,10), random_all_array(n,m,k,a,b,c,1e3));    
        for(int i = 0; i < 5; i++) CASE(random_size(n,m,k,10000), pot = rnd.nextInt(0, (m+k)/2), x = rnd.nextInt(1e3,1e7), y = rnd.nextInt(1,20), random_all_array(n,m,k,a,b,c,1e6));
        for(int i = 0; i < 5; i++) CASE(random_size(n,m,k,maxn), pot = 1e4, x = rnd.nextInt(0,maxn), y = rnd.nextInt(1,50), random_all_array(n,m,k,a,b,c,inf));
        for(int i = 0; i < 5; i++) CASE(random_size(n,m,k,maxn), pot = 0, x = rnd.nextInt(0,maxn), y = rnd.nextInt(1,100), random_all_array(n,m,k,a,b,c,inf));
        for(int i = 0; i < 5; i++) CASE(n=maxn, m=maxn, k=maxn, pot = 0, x = rnd.nextInt(maxn, inf), y = 200, random_all_array(n,m,k,a,b,c,inf));
        for(int i = 0; i < 5; i++) CASE(n=maxn, m=maxn, k=maxn, pot = 2*maxn, x = rnd.nextInt(maxn, inf), y = 100, random_all_array(n,m,k,a,b,c,inf));    
        for(int i = 0; i < 5; i++) CASE(n=maxn, m=maxn, k=maxn, pot = 1e6, x = rnd.nextInt(maxn, inf), y = 20, random_all_array(n,m,k,a,b,c,inf));    
    }

private:
    void random_dec(int &x, int &y, int lim){
        x = rnd.nextInt(1, lim);
        y = rnd.nextInt(1, lim);
    }

    void random_array(int size, vector<int> &arr, int maxx){
        arr.resize(size);
        for(int i=0;i<size;i++){
            arr[i] = rnd.nextInt(1, maxx);
        }
    }

    void random_all_array(int n, int m, int k, vector<int> &a, vector<int> &b, vector<int> &c, int lim){
        random_array(n, a, lim);
        random_array(m, b, lim);
        random_array(k, c, lim);
    }

    void random_size(int &n, int &m, int &k, int lim){
        n = rnd.nextInt(1, lim);
        m = rnd.nextInt(1, lim);
        k = rnd.nextInt(1, lim);
    }

};