#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

#define MAXN 3e5
#define MAXNUM 1e9

class ProblemSpec: public BaseProblemSpec {
protected:
    int n,m;
    vector<int> u,v;
    vector<int>a;
    vector<int>b;
    int tot;
    vector<int> ans;

    void InputFormat() {
        LINE(n,m);
        LINE(a);
        LINE(b);
        LINES(u,v) % SIZE(m-1);
    }

    void OutputFormat() {
        LINE(tot);
        LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(2);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(1<=n && n<=MAXN);
        CONS(1<=m && m<=MAXN);
        CONS(eachElementBetween(a,1,MAXNUM));
        CONS(eachElementBetween(b,1,m));
        CONS(eachElementBetween(u,1,m));
        CONS(eachElementBetween(v,1,m));
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
            "5 5",
            "4 2 1 5 3",
            "1 1 5 3 4",
            "1 5",
            "3 5",
            "2 4",
            "4 3"        
        });
        Output({
            "1",
            "5"
        });
    }

    void BeforeTestCase() {
        a.clear();
        b.clear();
        u.clear();
        v.clear();
    }

    void TestCases() {
        for(int i=0;i<10;i++) {
            CASE(n=5,m=5,fillSame(n,a,MAXNUM),rand_permute(n,b),randomTree(m,u,v));
        }
        for(int i=0;i<5;i++){
            CASE(n=20,m=1,rand_T(n,a,1000),rand_T(n,b,m),randomTree(m,u,v));
        }
        for(int i=0;i<10;i++) {
            CASE(n=20,m=10,rand_T(n,a,1000),rand_T(n,b,m),randomTree(m,u,v));
        }
        for(int i=0;i<10;i++) {
            CASE(n=200,m=100,rand_T(n,a,10000),rand_T(n,b,m),randomTree(m,u,v));
        }
        for(int i=0;i<10;i++) {
            CASE(n=rnd.nextInt(1,2000),m=rnd.nextInt(1,1000),rand_T(n,a,MAXN),rand_T(n,b,m),randomTree(m,u,v));
        }
        for(int i=0;i<10;i++) {
            CASE(n=2047,m=2047,fillSame(n,a,MAXNUM),fillSameCity(n,b,m),balanceBinTree(m,u,v));
        }
        for(int i=0;i<5;i++){
            CASE(n=MAXN,m=MAXN,rand_T(n,a,MAXNUM),rand_permute(n,b),linearTree(m,u,v));
        }
        for(int i=0;i<5;i++) {
            CASE(n=MAXN,m=MAXN,fillSame(n,a,MAXNUM),rand_permute(n,b),randomTree(m,u,v));
        }
        for(int i=0;i<5;i++) {
            CASE(n=MAXN,m=MAXN,rand_T(n,a,MAXNUM),rand_T(n,b,m),modifiedBinTree(m,u,v));
        }    
        for(int i=0;i<8;i++) {
            CASE(n=MAXN,m=MAXN,rand_T(n,a,MAXNUM),rand_T(n,b,m),randomTree(m,u,v));
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
    void rand_T(int n, vector<int>& t, int maks) {
        for(int i=0;i<n;i++) {
            int temp = rnd.nextInt(1,maks);
            t.push_back(temp);
        }
    }
    void fillSame(int n, vector<int>& t, int num){
        for(int i=0;i<n;i++) {
            t.push_back(num);
        }
    }
    void rand_permute(int n, vector<int>& t){
        deque<int>dq;
        for(int i=0;i<n;i++){
            dq.push_back(i+1);
        }
        for(int i=0;i<n;i++){
            int idx=rnd.nextInt(0,n-i-1);
            t.push_back(dq[idx]);
            swap(dq[idx],dq[n-i-1]);
            dq.pop_back();
        }
    }
    void modifiedBinTree(int n, vector<int>& u, vector<int>& v) {
		for (int i = 1; i+1 <= n ; i+=2) {
		    u.push_back(i);
            v.push_back(i+1);
		}
        for(int i=3;i<=n;i+=2){
            u.push_back(i-2);
            v.push_back(i);
        }
		renumber(n, u, v);
	}

    void balanceBinTree(int n, vector<int>& u, vector<int>& v){
        for(int i=1;i<=n;i++){
            u.push_back(i);
            v.push_back(2*i);
            u.push_back(i);
            v.push_back(2*i+1);
            if(2*i+1 == n)break;
        }
        renumber(n, u, v);
    }

    void fillSameCity(int n,vector<int>&t,int m){
        for(int i=1;i<=n;i++){
            t.push_back(i);
        }
        rnd.shuffle(t.begin(), t.end());
    }
};