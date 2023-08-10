#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

#define MAXN 100000
#define MAXA 1000000

class ProblemSpec : public BaseProblemSpec {
protected:
	int n, m, q;
	vector<int> a, u, v, qt, qa, qb;
	vector<int> ans;

	void InputFormat() {
		LINE(n, m, q);
		LINE(a % SIZE(n));
		LINES(u, v) % SIZE(m);
		LINES(qt, qa, qb) % SIZE(q);
	}

	void OutputFormat() {
		LINES(ans) % SIZE(cntq2(qt));
	}

	void GradingConfig() {
		TimeLimit(1);
		MemoryLimit(256);
	}

	void Constraints() {
		CONS(1 <= n && n <= MAXN);
		CONS(1 <= m && m <= MAXN);
		CONS(1 <= q && q <= MAXN);
		CONS(eachElementBetween(a, 1, MAXA));
		CONS(eachElementBetween(u, 1, n));
		CONS(eachElementBetween(v, 1, n));
		CONS(queryCONS(q, n, qt, qa, qb));
	}

private:
	bool eachElementBetween(vector<int> a, int mn, int mx){
		for (int x : a){
			if (x < mn || x > mx) return false;
		}
		return true;
	}
    bool queryCONS(int q, int n, vector<int> qt, vector<int> qa, vector<int> qb){
        if(qt.size() != q || qa.size() != q || qb.size() != q)return false;
        for(int i=0;i<q;i++){
            if(qt[i] == 1){
                if(qa[i] < 1 || qa[i] > n)return false;
                if(qb[i] < 1 || qb[i] > MAXA)return false;
            }else if(qt[i] == 2){
                if(qa[i] < 1 || qa[i] > n)return false;
                if(qb[i] < 1 || qb[i] > n)return false;
            }else return false;
        }
        return true;
    }
    int cntq2(vector<int> qt){
        int cnt = 0;
        for(int x : qt)
            if(x == 2)
                cnt++;
        return cnt;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
	void SampleTestCase1() {
		Input({
			"5 2 4",
			"1 2 3 4 5",
            "3 4",
            "4 5",
            "2 1 3",
            "1 5 2",
            "2 5 1",
			"2 3 5"
		});
		Output({
			"4",
			"3",
			"0"
		});
	}

	void BeforeTestCase(){
		a.clear();
		u.clear();
		v.clear();
		qt.clear();
		qa.clear();
		qb.clear();
	}

	void TestCases() {
        for(int i=0;i<10;i++)CASE(n = 10, m = 10, q = 10, randomVal(n,a,1,1000), randomUnconnectedGraph(n,m,u,v), randomQuery(n,q,qt,qa,qb,5));
        for(int i=0;i<10;i++)CASE(n = 1000, m = 1000, q = 1000, randomVal(n,a,1,1000000), randomUnconnectedGraph(n,m,u,v), randomQuery(n,q,qt,qa,qb,500));
        for(int i=0;i<10;i++)CASE(n = MAXN, m = MAXN, q = MAXN, randomVal(n,a,1,MAXA), randomUnconnectedGraph(n,m,u,v), randomQuery(n,q,qt,qa,qb,MAXN/2));
        for(int i=0;i<10;i++)CASE(n = MAXN, m = MAXN, q = MAXN, randomVal(n,a,1,MAXA), randomUnconnectedGraph(n,m,u,v), randomQuery(n,q,qt,qa,qb,MAXN)); // all change
        for(int i=0;i<10;i++)CASE(n = MAXN, m = MAXN, q = MAXN, randomVal(n,a,1,MAXA), randomUnconnectedGraph(n,m,u,v), randomQuery(n,q,qt,qa,qb,0)); // all ask
        for(int i=0;i<10;i++)CASE(n = rnd.nextInt(1,MAXN), m = rnd.nextInt(1,MAXN), q = rnd.nextInt(1,MAXN), randomVal(n,a,1,MAXA), randomUnconnectedGraph(n,m,u,v), randomQuery(n,q,qt,qa,qb,rnd.nextInt(sqrt(q),q/2))); // random
	}

private:

	void randomVal(int n, vector<int> &a, int mn, int mx){
		for (int i=0; i<n; i++) a.push_back(rnd.nextInt(mn, mx));
	}

    void randomQuery(int n, int q, vector<int>& qt, vector<int>& qa, vector<int>& qb, int q1){
        int q2 = q - q1;
        for(int i=0;i<q;i++){
            int tipe = rnd.nextInt(1,2);
            if(tipe == 1){
                qt.push_back(1);
                int node = rnd.nextInt(1,n);
                int val = rnd.nextInt(1,MAXA);
                qa.push_back(node);
                qb.push_back(val);
            }else{
                qt.push_back(2);
                int a = rnd.nextInt(1,n);
                int b = rnd.nextInt(1,n);
                qa.push_back(a);
                qb.push_back(b);
            }
        }
    }

	void randomUnconnectedGraph(int n, int m, vector<int>& u, vector<int>& v) {
	    for (int i=0; i<m; i++){
	    	int uu = rnd.nextInt(1, n);
	    	int vv = rnd.nextInt(1, n);
	    	u.push_back(uu);
	    	v.push_back(vv);
	    }
	}

	void randomQueries(int n, int q, vector<int>& u, vector<int>& v) {
	    for (int i=0; i<q; i++){
	    	int uu = rnd.nextInt(1, n);
	    	int vv = rnd.nextInt(1, n);
	    	u.push_back(uu);
	    	v.push_back(vv);
	    }
	}
};