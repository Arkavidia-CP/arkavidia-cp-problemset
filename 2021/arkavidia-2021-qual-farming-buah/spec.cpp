#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;
using ll = long long;

const int NMax = 2e5;
const ll WMax = 1e9;

class ProblemSpec : public BaseProblemSpec {
protected:
    int N;
    vector<int> U, V;
    vector<ll> W;
    ll TOT;
    ll LEN;
    vector<ll> ans;

    void InputFormat() {
        LINE(N);
        LINES(U, V, W) % SIZE(N - 1);
    }

    void OutputFormat() {
        LINE(TOT);
        LINE(LEN);
        LINE(ans % SIZE(LEN));
    }

    void GradingConfig() {
        TimeLimit(2);
        MemoryLimit(128);
    }

    void Constraints() {
        CONS(1 <= N && N <= NMax);
        CONS(eachElementBetween(U, 1, N));
        CONS(eachElementBetween(V, 1, N));
        CONS(eachElementBetween(W, 1LL, WMax));
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
    bool eachElementBetween(const vector<ll>& v, ll lo, ll hi) {
        for (int x : v) {
            if (x < lo || x > hi) {
                return false;
            }
        }
        return true;
    }

    bool noDoubleEdge(const vector<int> &u, const vector<int>& v) {
  		int len = u.size();
  		vector<set<int>> st(NMax + 5);
  		for (int i = 0; i < len; i++) {
  			if (st[u[i]].find(v[i]) != st[u[i]].end()) return false;
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

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
    	Input({
            "6",
            "1 2 1",
            "2 3 1",
            "3 4 1",
            "2 5 1",
            "2 6 1"
    	});
    	Output({
            "7",
            "8",
            "1 2 5 2 6 2 3 4",
    	});
    }

    void BeforeTestCase() {
        U.clear();
        V.clear();
        W.clear();
        ans.clear();
    }

    void TestCases() {
        for (int i=0;i<5;i++){
            CASE(N = NMax, genWeight(N, W), randomTree(N, U, V));
        }
        for (int i=0;i<3;i++){
            CASE(N = NMax, genWeight(N, W, WMax / 2, WMax), randomTree(N, U, V));
        }
        for (int i=0;i<3;i++){
            CASE(N = NMax, genWeight(N, W, WMax, WMax), randomTree(N, U, V));
        }
        for (int i=0;i<5;i++){
            CASE(N = rnd.nextInt(1, 100), genWeight(N, W), randomTree(N, U, V));
        }
        for (int i=0;i<10;i++){
            CASE(N = NMax, genWeight(N, W, 1, WMax), linearTree(N, U, V));
        }
    }

private:
    void genWeight(int n, vector<ll>& w, ll a = 1LL, ll b = WMax){
        for (int i=0;i<n - 1;i++){
            w.push_back(rnd.nextLongLong(a, b));
        }
    }

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
