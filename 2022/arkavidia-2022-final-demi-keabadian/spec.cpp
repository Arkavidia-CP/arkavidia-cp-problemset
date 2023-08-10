#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

typedef long long ll;

#define MAXN 3e4
#define MAXM 1e2
#define MAXA 1e9

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

class ProblemSpec: public BaseProblemSpec {
protected:
    int n, m;
    vector<ll> w;
    vector<int> x, u,v;
    ll ans;

    void InputFormat() {
        LINE(n, m);
        LINE(x);
        LINE(w);
        LINES(u,v) % SIZE(m-1);
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
        CONS(1<=m && m<=MAXM);
        CONS(eachElementBetween(x,0, MAXN));
        CONS(eachElementBetween(w,1, MAXA));
        CONS(eachElementBetween(u,1,m));
        CONS(eachElementBetween(v,1,m));
        CONS(noDoubleEdge(u,v));
        CONS(noSelfLoop(u,v));
        CONS(uniqueWeight(w));
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

    
    bool eachElementBetween(const vector<ll>& v, int lo, int hi) {
        for (int x : v) {
            if (x < lo || x > hi) {
                return false;
            }
        }
        return true;
    }    

    bool noDoubleEdge(const vector<int> &u, const vector<int>& v) {
  		int len = u.size();
  		vector<set<int>> st(MAXN + 5);
  		for (int i = 0; i < len; i++) {
  			if (st[u[i]].find(v[i]) != st[u[i]].end() || st[v[i]].find(u[i])!=st[v[i]].end()) return false;
  			st[u[i]].insert(v[i]);
  		}
  		return true;
    }

    bool noSelfLoop(const vector<int>& u, const vector<int>& v) {
    	int len = u.size();
    	for (int i = 0; i < len; i++) {
    		if (u[i] == v[i]) return false;
    	}
    	return true;
    }    

    bool uniqueWeight(const vector<ll>& w) {
    	int len = w.size();
    	set<ll> st;
    	for (int i = 0; i < len; i++) {
    		if (st.find(w[i]) != st.end()) return false;
    		st.insert(w[i]);
    	}
    	return true;
    }
};

class TestSpec: public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "4 6",
            "4 0 3 4 2 4",
            "2 4 8 16 32 64",
            "1 2",
            "2 3",
            "3 4",
            "2 5",
            "5 6", 
        });
        Output({
            "16"
        });
    }

    void SampleTestCase2() {
        Input({
            "8 8",
            "8 5 7 7 3 8 2 1",
            "2 10 11 3 6 19 22 42",
            "1 2",
            "1 3",
            "2 4",
            "2 5",
            "5 6",
            "5 7",
            "5 8",
        });
        Output({
            "588486564"
        });
    };

    void BeforeTestCase() {
        w.clear();
        x.clear();
        u.clear();
        v.clear();
    }

    void TestCases() {
        for(int i=0; i<5; i++) {
            CASE(n = rnd.nextInt(1, 10), m = rnd.nextInt(1, 10), randomTree(u, v),  randomX(x, 0, rnd.nextInt(n, n+1)), randomWeight(w));
            CASE(n = rnd.nextInt(1, 10), m = rnd.nextInt(1, 10), linearTree(u, v),  randomX(x, 0, rnd.nextInt(n, n+1)), randomWeight(w));
        }

        for(int i=0; i<5; i++) {
            CASE(n = rnd.nextInt(1, 100), m = rnd.nextInt(1, 100), randomTree(u, v),  randomX(x, 0, rnd.nextInt(n, n+3)), randomWeight(w));
            CASE(n = rnd.nextInt(1, 100), m = rnd.nextInt(1, 100), linearTree(u, v),  randomX(x, 0, rnd.nextInt(n, n+3)), randomWeight(w));
        }

        for(int i=0; i<5; i++) {
            CASE(n = rnd.nextInt(1, 1000), m = rnd.nextInt(50, 100), randomTree(u, v),  randomX(x, 0, rnd.nextInt(n, n+5)), randomWeight(w));
            CASE(n = rnd.nextInt(1, 1000), m = rnd.nextInt(50, 100), linearTree(u, v),  randomX(x, 0, rnd.nextInt(n, n+5)), randomWeight(w));
        }

        for(int i=0; i<5; i++) {
            CASE(n = rnd.nextInt(1000, MAXN), m = rnd.nextInt(50, 100), randomTree(u, v),  randomX(x, n/2, rnd.nextInt(n, MAXN)), randomWeight(w));
        }

        for(int i=0; i<5; i++) {
            CASE(n = rnd.nextInt(MAXN/2, MAXN), m = rnd.nextInt(50, 100), randomTree(u, v),  randomX(x, n/2, rnd.nextInt(n, MAXN)), randomWeight(w));
            CASE(n = rnd.nextInt(MAXN/2, MAXN), m = rnd.nextInt(50, 100), randomTree(u, v),  randomX(x, n/2, rnd.nextInt(n, MAXN)), randomWeight(w, MAXA/2, MAXA));
            CASE(n = rnd.nextInt(MAXN/2, MAXN), m = rnd.nextInt(50, 100), randomTree(u, v),  randomX(x, 0, rnd.nextInt(n, MAXN)), randomWeight(w, MAXA/2, MAXA));
        }

        
    }

private:

    void randomWeight(vector<ll>& w, ll lo=1, ll hi=MAXA) {
        ll h = hi-(m-1);
        ll l = lo;
        for(int i=0; i<m; i++){
            w.push_back(rnd.nextLongLong(l, h));
            l = w[i]+1;
            h++;
        }
        shuffle(w.begin(), w.end(), rng);
    }

    void dfs(int now, int par, vector<vector<int>>& adj, vector<int>& x, int lo, int hi) {
        int sum = x[now-1];
        int pref = 0;
        for(int i=0; i<(int)adj[now].size(); i++) {
            int next = adj[now][i];
            if(next == par) continue;
            if(i == (int) adj[now].size()-1) {
                int tp = rnd.nextInt(1, 20);
                if(tp <= 2) {
                    x[next-1] = max(sum - pref - 1, 0);
                } else {
                    x[next-1] = rnd.nextInt(max(0, sum - pref), hi);
                }
            } else {
                x[next-1] = rnd.nextInt(lo, hi);
            }
            pref += x[next-1];
            dfs(next, now, adj, x, lo, hi);
        }
    }

    void randomX(vector<int>& x, int lo, int hi) {
        vector<vector<int>> adj(m+1);
        for(int i=0; i<m-1; i++){
            adj[u[i]].push_back(v[i]);
            adj[v[i]].push_back(u[i]);
        }
        x.assign(m, 0);
        x[0] = rnd.nextInt(n, hi);
        dfs(1, -1, adj, x, lo, hi);
    }

    void renumber(vector<int>& u, vector<int>& v) {
        vector<int> permutation;
        for (int i = 1; i <= m; i++) {
            permutation.push_back(i);
        }
        shuffle(permutation.begin(), permutation.end(), rng);
        for (int i = 0; i < (int) u.size(); i++) {
            u[i] = permutation[u[i] - 1];
            v[i] = permutation[v[i] - 1];
        }
    }

    void randomTree(vector<int>& u, vector<int>& v) {
		for (int i = 1; i < m; i++) {
		    u.push_back(i + 1);
		    v.push_back(rnd.nextInt(1, i));
		}
		renumber(u, v);
	}

    void linearTree(vector<int>& u, vector<int>& v) {
		for (int i = 2; i <= m; i++) {
		    u.push_back(i);
		    v.push_back(i - 1);
		}
		renumber(u, v);
	}    
};