#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int NMax = 100000;

class ProblemSpec : public BaseProblemSpec {
protected:
    int N, Q;
    vector<int> OP;
    vector<vector<int>> DATA;
    vector<int> RES;

    void InputFormat() {
        LINE(N, Q);
        LINES(OP, DATA) % SIZE(Q);
    }

    void OutputFormat() {
        LINES(RES);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(64);
    }

    void Constraints() {
        CONS(1 <= N && N <= NMax);
        CONS(1 <= Q && Q <= NMax);
        CONS(eachElementBetween(DATA, 1, N));
        CONS(isValidQuery(N, Q, OP, DATA));
    }

private:
    bool eachElementBetween(const vector<vector<int>>& v, int lo, int hi) {
        for (vector<int> x : v) {
        	for (int y : x) {
        		if (y < lo || y > hi)
        			return false;
        	}
        }
        return true;
    }

    bool isValidQuery(const int& n, const int& q, const vector<int>& op, const vector<vector<int>>& data) {
   		vector<bool> vis(NMax);
   		set<pair<int, int>> st;
   		if ((int) op.size() != q) return false;
   		if ((int) data.size() != q) return false;
    	for (int i = 0; i < q; i++) {
    		if (op[i] == 3) continue;
    		if ((int) data[i].size() != 2) return false;
    		int u = data[i][0];
    		int v = data[i][1];
    		if (op[i] == 1) {
    			if (vis[u]) return false;
    			if (vis[v]) return false;
    			vis[u] = 1;
    			vis[v] = 1;
    			st.insert({u, v});
    		} else if (op[i] == 2) {
    			if (!vis[u]) return false;
    			if (!vis[v]) return false;
    			vis[u] = 0;
    			vis[v] = 0;
    			auto it = st.find({u, v});
    			if (it == st.end()) return false;
    			st.erase(it);
    		}
    	}
    	return true;
    }
    
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
    	Input({
    		"6 3",
    		"1 2 4",
    		"1 5 6",
    		"3"
    	});
    	Output({
    		"2"
    	});
    }

    void BeforeTestCase() {
     	OP.clear();
     	for (int i = 0; i < (int) DATA.size(); i++) {
     		DATA[i].clear();
     	}
     	DATA.clear();
    }

    void TestCases() {
    	CASE(N = 6, Q = 3, OP = {1, 1, 3}, DATA = {{2, 4}, {5, 6}, {}});
    	CASE(N = 10, Q = 4, OP = {1, 1, 1, 3}, DATA = {{2, 5}, {4, 6}, {7, 8}, {}});
    	CASE(N = 10, Q = 5, OP = {1, 1, 1, 2, 3}, DATA = {{2, 5}, {4, 6}, {7, 8}, {7, 8}, {}});
    	CASE(N = 10, Q = 3, OP = {1, 1, 3}, DATA = {{2, 5}, {4, 6}, {}});
    	CASE(N = 1, Q = 1, OP = {3}, DATA = {{}});
    	for (int i = 0; i < 5; i++) {
    		CASE(randomN(N, 1, 100), randomQ(Q, 1, 200), randomQuery(N, Q, OP, DATA, rnd.nextInt(50, 70)));
    	}
    	for (int i = 0; i < 5; i++) {
    		CASE(randomN(N, 101, 1000), randomQ(Q, 1000, 2000), randomQuery(N, Q, OP, DATA, rnd.nextInt(40, 80)));
    	}
    	for (int i = 0; i < 5; i++) {
    		CASE(randomN(N, 1001, 5000), randomQ(Q, 1001, 2000), randomQuery(N, Q, OP, DATA, rnd.nextInt(45, 100)));		
    	}
    	for (int i = 0; i < 5; i++) {
    		CASE(randomN(N, 5001, NMax), randomQ(Q, 5001, NMax), randomQuery(N, Q, OP, DATA, rnd.nextInt(60, 100)));
    	}
    	for (int i = 0; i < 5; i++) {
    		CASE(randomN(N, NMax, NMax), randomQ(Q, NMax, NMax), randomQuery(N, Q, OP, DATA, rnd.nextInt(40, 100)));
    	}
    }

private:
	void randomN(int& n, int lo, int hi) {
		n = rnd.nextInt(lo, hi);
	}
    
    void randomQ(int& q, int lo, int hi) {
    	q = rnd.nextInt(lo, hi);
    }

    void randomQuery(int& n, int& q, vector<int>& op, vector<vector<int>>& data, int chance) {
    	assert(chance <= 100);
    	op.resize(q);
    	data.resize(q);
    	vector<int> permutation(n);
   		iota(permutation.begin(), permutation.end(), 1);
   		rnd.shuffle(permutation.begin(), permutation.end());
   		vector<int> available;
   		for (int i = 0; i < n - 1; i += 2) {
   			available.push_back(i);
   			if (permutation[i] > permutation[i + 1])
   				swap(permutation[i], permutation[i + 1]);
   		}
   		vector<int> vis(NMax);
    	for (int i = 0, j = 1; i < q; i++) {
    		int turn = rnd.nextInt(1, 100);
    		if (turn <= chance) {	
    			int randomIdx = rnd.nextInt(0, (int) available.size() - 1);
    			int u = permutation[available[randomIdx]];
    			int v = permutation[available[randomIdx] + 1];
    			op[i] = 1 + vis[randomIdx];
    			vis[randomIdx] ^= 1;
    			data[i] = {u, v};
    		} else {
    			op[i] = 3;
    		}
    	}
    }
};
