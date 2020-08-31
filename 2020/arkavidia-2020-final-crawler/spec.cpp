#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int NMax = 20;
const int MMax = 380;
const int KMax = 1000000;

class ProblemSpec : public BaseProblemSpec {
protected:
    int N, M, K;
    vector<int> U, V;
    vector<int> res;

    void InputFormat() {
        LINE(N, M, K);
        LINES(U, V) % SIZE(M);
    }

    void OutputFormat() {
        LINE(res % SIZE(N));
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(64);
    }

    void Constraints() {
        CONS(1 <= N && N <= NMax);
        CONS(1 <= M && M <= MMax);
        CONS(1 <= K && K <= KMax);
        CONS(eachElementBetween(U, 1, N));
        CONS(eachElementBetween(V, 1, N));
        CONS(noDoubleEdge(U, V));
        CONS(noSelfLoop(U, V));
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
  		set<int> st[NMax + 5];
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
    		"4 6 3",
    		"1 2",
    		"1 3",
    		"2 3",
    		"2 4",
    		"4 1",
    		"4 2"
    	});
    	Output({
    		"1 4 2 2"
    	});
    }

    void BeforeTestCase() {
        U.clear();
        V.clear();
        res.clear();
    }

    void TestCases() {
    	CASE(N = 5, M = 3, K = 2, randomGraph(N, M, U, V));
    	CASE(N = 7, M = 2, K = 1, randomGraph(N, M, U, V));
    	CASE(N = 10, M = 8, K = 10, randomGraph(N, M, U, V));
    	CASE(N = 2, M = 2, K = 2, randomConnectedGraph(N, M, U, V));
    	CASE(N = 5, M = 4, K = 3, randomConnectedGraph(N, M, U, V));
    	CASE(N = 10, M = 9, K = 1000, randomConnectedGraph(N, M, U, V));
    	for (int i = 0; i < 5; i++) {
    		CASE(N = rnd.nextInt(5, NMax / 2), M = rnd.nextInt(1, N - 2), K = rnd.nextInt(1, KMax), randomGraph(N, M, U, V));
    	}
    	for (int i = 0; i < 5; i++) {
    		CASE(N = rnd.nextInt(NMax / 2 + 1, NMax), M = rnd.nextInt(1, N - 2), K = rnd.nextInt(KMax / 2, KMax), randomGraph(N, M, U, V));
    	}
    	for (int i = 0; i < 2; i++) {
    		CASE(N = rnd.nextInt(6, NMax / 2), M = rnd.nextInt(N - 1, min(N*N, MMax)), K = rnd.nextInt(1, KMax), randomConnectedGraph(N, M, U, V));
    	}
    	for (int i = 0; i < 5; i++) {
    		CASE(N = rnd.nextInt(NMax / 2 + 1, NMax), M = rnd.nextInt(N - 1, min(maxx(N), MMax)), K = rnd.nextInt(KMax / 2, KMax), randomConnectedGraph(N, M, U, V));
    	}
    	CASE(N = 10, M = maxx(N), completeGraph(N, M, U, V));
    	CASE(N = 19, M = maxx(N), completeGraph(N, M, U, V));
    	CASE(N = 20, M = maxx(N), completeGraph(N, M, U, V));
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

    void randomGraph(int n, int m, vector<int>& u, vector<int>& v) {
    	vector<int> permutation;
    	for (int i = 0; i < n; i++) {
    		permutation.push_back(i + 1);
    	}
    	rnd.shuffle(permutation.begin(), permutation.end());
    	vector<int> idx;
    	for (int i = 0; i < n - 1; i++) {
    		idx.push_back(i);
    	}
    	rnd.shuffle(idx.begin(), idx.end());
    	for (int i = 0; i < m; i++) {
    		u.push_back(permutation[idx[i]]);
    		v.push_back(permutation[idx[i] + 1]);
    	}
    }

    void randomTree(int n, vector<int>& u, vector<int>& v) {
		for (int i = 1; i < n; i++) {
		    u.push_back(i + 1);
		    v.push_back(rnd.nextInt(1, i));
		}
		renumber(n, u, v);
	}

    void randomConnectedGraph(int n, int m, vector<int> &u, vector<int> &v) {
    	assert(m >= n - 1);
    	randomTree(n, u, v);
		map<pair<int,int>, int> udah;
		for (int i = 0; i < (int)u.size(); ++i){
			udah[{u[i], v[i]}]++;
		}
    	while (u.size() < m) {
    		int newU = rnd.nextInt(1, n);
    		int newV = rnd.nextInt(1, n);
			while (udah.find({newU, newV}) != udah.end() || (newU == newV)){
				newU = rnd.nextInt(1, n);
				newV = rnd.nextInt(1, n);
			}
			udah[{newU, newV}]++;
			u.push_back(newU);
			v.push_back(newV);
    	}
		// cout << "\n";
		// cout << "n = " << n << " m = " << m << '\n'; 
		// for (int i = 0; i < m; ++i){
		// 	cout << i << " " << u[i] << " " << v[i] << '\n';
		// }
    }

    void completeGraph(int n, int m, vector<int> &u, vector<int> &v) {
    	assert(m == maxx(n));
    	for (int i = 0; i < n; i++) {
    		for (int j = i+1; j < n; j++) {
    			u.push_back(i + 1);
    			v.push_back(j + 1);

				u.push_back(j+1);
				v.push_back(i+1);
    		}
    	}
    }

	int maxx(int n){
		return (n*(n-1));
	}
};
