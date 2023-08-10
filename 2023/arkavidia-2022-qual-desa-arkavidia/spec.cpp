#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

#define MAXN 2e5

class ProblemSpec: public BaseProblemSpec {
protected:
    int n;
    vector<int> u,v;
    int ans;

    void InputFormat() {
        LINE(n);
        LINES(u,v) % SIZE(n-1);
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
        CONS(eachElementBetween(u,1,n));
        CONS(eachElementBetween(v,1,n));
        CONS(noDoubleEdge(u,v));
        CONS(noSelfLoop(u,v));
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
};

class TestSpec: public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "7",
            "1 2",
            "3 4",
            "2 3",
            "3 5",
            "5 6",
            "4 7"        
        });
        Output({
            "3"
        });
    }

    void SampleTestCase2() {
        Input({
            "8",
            "1 2",
            "1 3",
            "1 4",
            "1 5",
            "1 6",
            "6 7",
            "7 8"
        });
        Output({
            "2"
        });
    };

    void BeforeTestCase() {
        u.clear();
        v.clear();
    }

    void TestCases() {
        for(int i=0;i<10;i++) {
            CASE(n=10,randomTree(n,u,v));
        }
        for(int i=0;i<10;i++) {
            CASE(n=10,linearTree(n,u,v));
        }
        for(int i=0;i<10;i++) {
            CASE(n=rnd.nextInt(100,10000),randomTree(n,u,v));
        }
        for(int i=0;i<10;i++) {
            CASE(n=rnd.nextInt(100,10000),linearTree(n,u,v));
        }        
        for(int i=0;i<10;i++) {
            CASE(n=MAXN,randomTree(n,u,v));
        }
        for(int i=0;i<10;i++) {
            CASE(n=MAXN,linearTree(n,u,v));
        }        
    }

private:
    void renumber(int n, vector<int>& u, vector<int>& v) {
        vector<int> permutation;
        for (int i = 1; i <= n; i++) {
            permutation.push_back(i);
        }
        rnd.shuffle(permutation.begin(), permutation.end());
        for (int i = 0; i < (int) u.size(); i++) {
            u[i] = permutation[u[i] - 1];
            v[i] = permutation[v[i] - 1];
        }
    }

    void randomTree(int n, vector<int>& u, vector<int>& v) {
		for (int i = 1; i < n; i++) {
		    u.push_back(i + 1);
		    v.push_back(rnd.nextInt(1, i));
		}
		renumber(n, u, v);
	}
    void linearTree(int n, vector<int>& u, vector<int>& v) {
		for (int i = 2; i <= n; i++) {
		    u.push_back(i);
		    v.push_back(i - 1);
		}
		renumber(n, u, v);
	}    
};