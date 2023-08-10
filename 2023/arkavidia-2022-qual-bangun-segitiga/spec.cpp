#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

const int MAXN = 1e5;
const int MAXA = 1e9;

typedef long long ll;

class ProblemSpec: public BaseProblemSpec {
protected:
    int n;
    vector<ll> m, c;
    ll ans;

    void InputFormat() {
        LINE(n);
        LINES(m, c) % SIZE(n);
    }

    void OutputFormat() {
        LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(1<=n && n<=MAXN);
        CONS(eachElementBetween(m,-MAXA, MAXA));
        CONS(eachElementBetween(c,-MAXA, MAXA));
        CONS(notOverlapped(m, c));
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

    bool notOverlapped(const vector<long long>& m, const vector<long long>& c) {
        set<pair<long long, long long>> s;
        for(int i=0;i<m.size();i++) {
            if(s.find({m[i], c[i]}) != s.end()) {
                return false;
            }
            s.insert({m[i], c[i]});
        }
        return true;
    }
};

class TestSpec: public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "4",
            "1 3",
            "5 -10",
            "-3 4",
            "3 0"
        });
        Output({
            "6"
        });
    }

    void BeforeTestCase() {
        m.clear();
        c.clear();
    }

    void TestCases() {
        CASE(n=1; m.push_back(1); c.push_back(1));
        CASE(n=1; m.push_back(-1); c.push_back(1));
        for(int i=0;i<10;i++) {
            CASE(n=10; randomLine(m, c, -MAXA, MAXA));
        }
        CASE(n=10; allParallel(m, c, -MAXA, MAXA));
        CASE(n=10; allDiff(m, c, -MAXA, MAXA));

        for(int i=0;i<10;i++) {
            CASE(n=100; randomLine(m, c, -MAXA, MAXA));
        }
        CASE(n=100; allParallel(m, c, -MAXA, MAXA));
        CASE(n=100; allDiff(m, c, -MAXA, MAXA));

        for(int i=0;i<10;i++) {
            CASE(n=1000; randomLine(m, c, -MAXA, MAXA));
        }
        CASE(n=1000; allParallel(m, c, -MAXA, MAXA));
        CASE(n=1000; allDiff(m, c, -MAXA, MAXA));

        for(int i=0;i<10;i++) {
            CASE(n=rnd.nextInt(1000, MAXN); randomLine(m, c, -MAXA, MAXA));
        }
        CASE(n=rnd.nextInt(1000, MAXN); allDiff( m, c, -MAXA, MAXA));

        for(int i=0;i<3;i++) {
            CASE(n=MAXN; allParallel(m, c, MAXA/2, MAXA));
            CASE(n=MAXN; allParallel(m, c, -MAXA, -MAXA/2));
        }
        CASE(n=MAXN; allParallel(m, c, -MAXA, MAXA));
        CASE(n=MAXN; allDiff(m, c, -MAXA, MAXA));
    }

private:
    void randomLine(vector<ll>&m, vector<ll>&c, ll lo, ll hi) {
        int sz = rnd.nextInt(3, n);
        set<ll> s;
        while(s.size()!=sz){
            s.insert(rnd.nextLongLong(lo, hi));
        }
        vector<ll> v;
        map<ll, set<int>> mp;
        for(auto x : s) {
            v.push_back(x);
        }
        map<ll, int> msz;
        for(int i=0; i<n; i++){
            m.push_back(v[rnd.nextInt(0, sz-1)]);
            msz[m[i]]++;
        }

        for(auto x : msz) {
            while(mp[x.first].size()!=x.second){
                mp[x.first].insert(rnd.nextLongLong(lo, hi));
            }
        }

        for(int i=0;i<n;i++) {
            c.push_back(*mp[m[i]].begin());
            mp[m[i]].erase(mp[m[i]].begin());
        }
    }

    
    void allParallel(vector<ll>&m, vector<ll>&c, ll lo, ll hi) {
        ll a = rnd.nextLongLong(lo, hi);
        set<ll> s;
        while(s.size()!=n){
            s.insert(rnd.nextLongLong(lo, hi));
        }
        for(auto x : s) {
            c.push_back(x);
        }

        rnd.shuffle(c.begin(), c.end());

        for(int i=0;i<n;i++) {
            m.push_back(a);
        }
    }


    void allDiff(vector<ll>&m, vector<ll>&c, ll lo, ll hi) {
        set<ll> s;
        while(s.size()!=n){
            s.insert(rnd.nextLongLong(lo, hi));
        }
        for(auto x : s) {
            m.push_back(x);
        }
        rnd.shuffle(m.begin(), m.end());
        for(int i=0;i<n;i++) {
            c.push_back(rnd.nextLongLong(lo, hi));
        }
    }
};