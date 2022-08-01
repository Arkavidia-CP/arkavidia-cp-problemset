#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;
using ll = long long;

const int NMIN = 3;
const int NMAX = 3e5;
const int AMIN = 0;
const int AMAX = 1e9;

class ProblemSpec : public BaseProblemSpec {
protected:
    int N, M, K;
    vector<int> A, U, V;
    vector<int> ans;
    int impossible;

    void InputFormat() {
        LINE(N, M);
        LINE(A % SIZE(N));
        LINES(U, V) % SIZE(M);
    }

    void OutputFormat1() {
        LINE(impossible);
    }

    void OutputFormat2() {
        LINE(K);
        LINE(ans % SIZE(K));
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(128);
    }

    void Constraints() {
        CONS(NMIN <= N && N <= NMAX);
        CONS(eachElementBetween(A, AMIN, AMAX));
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
  		vector<set<int>> st(NMAX + 5);
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
            "8 7",
            "1 2 3 4 5 6 7 8",
            "1 2",
            "1 4",
            "1 8",
            "2 3",
            "2 5",
            "4 6",
            "4 7",
    	});
    	Output({
            "5",
            "3 1 2 6 4",
    	});
    }

    void BeforeTestCase() {
        U.clear();
        V.clear();
        ans.clear();
    }

    void TestCases() {
        // random connected tree
        CASE(N = 10, randomForest(N, A, AMIN, AMAX, U, V, 0));
        CASE(N = 500, randomForest(N, A, AMIN, AMAX, U, V, 0));
        CASE(N = 5000, randomForest(N, A, AMIN, AMAX, U, V, 0));
        CASE(N = 300000, randomForest(N, A, AMIN, AMAX, U, V, 0));

        // random forest
        CASE(N = 10, randomForest(N, A, AMIN, AMAX, U, V, 1));
        CASE(N = 500, randomForest(N, A, AMIN, AMAX, U, V, 1));
        CASE(N = 5000, randomForest(N, A, AMIN, AMAX, U, V, 1));
        CASE(N = 300000, randomForest(N, A, AMIN, AMAX, U, V, 1));

        // not possible, all stars with mid odd and others even
        CASE(N = 10, randomForest(N, A, AMIN, AMAX, U, V, 2));
        CASE(N = 500, randomForest(N, A, AMIN, AMAX, U, V, 2));
        CASE(N = 5000, randomForest(N, A, AMIN, AMAX, U, V, 2));
        CASE(N = 300000, randomForest(N, A, AMIN, AMAX, U, V, 2));

        // possible, all stars with mid odd and others even EXCEPT ONE, with 5 nodes valued 0 1 1 1 1 (mod 4)
        CASE(N = 20, randomForest(N, A, AMIN, AMAX, U, V, 3));
        CASE(N = 300000, randomForest(N, A, AMIN, AMAX, U, V, 3));

        // possible, linear graph 0 0 ... 0 0 1 (one large connected component)
        CASE(N = 10, randomForest(N, A, AMIN, AMAX, U, V, 4));
        CASE(N = 300000, randomForest(N, A, AMIN, AMAX, U, V, 4));

        // possible, all stars impossible except for one tree 1 0 1 0 1 0 1
        CASE(N = 5000, randomForest(N, A, AMIN, AMAX, U, V, 5));
        CASE(N = 300000, randomForest(N, A, AMIN, AMAX, U, V, 5));

        // many trees (1 tree max k+1 nodes)
        CASE(N = 300000, randomForest(N, A, AMIN, AMAX, U, V, 6, 0));   // must be impossible
        CASE(N = 300000, randomForest(N, A, AMIN, AMAX, U, V, 6, 1));
        CASE(N = 300000, randomForest(N, A, AMIN, AMAX, U, V, 6, 2));
        CASE(N = 300000, randomForest(N, A, AMIN, AMAX, U, V, 6, 3));
    }

private:
    void renumberAndShuffleEdges(int n, vector<int>& u, vector<int>& v, vector<int>& a) {
        vector<int> permutation;
        for (int i = 1; i <= n; i++) {
            permutation.push_back(i);
        }
        rnd.shuffle(permutation.begin(), permutation.end());
        for (int i = 0; i < (int) u.size(); i++) {
            u[i] = permutation[u[i] - 1];
            v[i] = permutation[v[i] - 1];
        }
        vector<int> newa;
        for (int i=1;i<=n;i++) newa.push_back(0);
        for (int i=1;i<=n;i++) {
            newa[permutation[i-1] - 1] = a[i - 1];
        }
        for (int i=0;i<n;i++) a[i] = newa[i];

        vector<int> permutationEdge;
        for (int i = 0; i < u.size(); i++) permutationEdge.push_back(i);
        rnd.shuffle(permutationEdge.begin(), permutationEdge.end());
        vector<int> newe((int)u.size(), 0);
        for (int i=0;i<u.size();i++) newe[permutationEdge[i]] = u[i];
        for (int i=0;i<u.size();i++) u[i] = newe[i];
        for (int i=0;i<u.size();i++) newe[permutationEdge[i]] = v[i];
        for (int i=0;i<u.size();i++) v[i] = newe[i];
    }

    void randomForest(int n, vector<int>& a, int lo, int hi, vector<int>& u, vector<int>& v, int type, int treeMaxNodes = 0) {
        a.clear();
        if (type == 0) {    // random connected tree
            for (int i = 1; i <= n; i++){
                a.push_back(rnd.nextInt(lo, hi));
            }
            randomTree(1, n, u, v);
        } else if (type == 1) { // random forest
            for (int i = 1; i <= n; i++){
                a.push_back(rnd.nextInt(lo, hi));
            }
            int cur = 1;
            while (cur <= n) {
                if (cur == n) {
                    randomStar(cur, n, u, v, a, 0);
                    break;
                }
                int next = rnd.nextInt(cur + 1, n);
                randomTree(cur, next, u, v);
                cur = next + 1;
            }
        } else if (type == 2) { // not possible, all stars with mid odd and others even
            for (int i=1;i<=n;i++) {
                a.push_back(0);   
            }
            int cur = 1;
            while (cur <= n) {
                if (cur == n) {
                    randomStar(cur, n, u, v, a, 0);
                    break;
                }
                int next = rnd.nextInt(cur + 1, n);
                randomStar(cur, next, u, v, a, 0);
                cur = next + 1;
            }
        } else if (type == 3) { // possible, all stars with mid odd and others even EXCEPT ONE, with 5 nodes valued 0 1 1 1 1
            for (int i=1;i<=n;i++) {
                a.push_back(0);   
            }
            randomStar(1, 5, u, v, a, 1);
            int cur = 6;
            while (cur <= n) {
                if (cur == n) {
                    randomStar(cur, n, u, v, a, 0);
                    break;
                }
                int next = rnd.nextInt(cur + 1, n);
                randomStar(cur, next, u, v, a, 0);
                cur = next + 1;
            }
        } else if (type == 4) { // possible, linear graph 0 0 ... 0 0 1 (one large connected component)
            for (int i=1;i<=n;i++) {
                a.push_back(0);   
            }
            randomLinear(1, n, u, v, a, 0);
        } else if (type == 5) { // all stars impossible except for one tree 1 0 1 0 1 0 1
            for (int i=1;i<=n;i++) {
                a.push_back(0);   
            }
            randomLinear(1, 7, u, v, a, 1);
            int cur = 8;
            while (cur <= n) {
                if (cur == n) {
                    randomStar(cur, n, u, v, a, 0);
                    break;
                }
                int next = rnd.nextInt(cur + 1, n);
                randomStar(cur, next, u, v, a, 0);
                cur = next + 1;
            }
        } else if (type == 6) { // many trees (1 tree max 3 nodes)
            for (int i=1;i<=n;i++) {
                a.push_back(rnd.nextInt(lo, hi));   
            }
            int cur = 1;
            while (cur <= n) {
                if (cur == n) {
                    randomStar(cur, n, u, v, a, 0);
                    break;
                }
                if (treeMaxNodes == 0) {    // only 1 node in every tree
                    randomTree(cur, cur, u, v);
                    cur++;
                } else {
                    int next = rnd.nextInt(cur + 1, min(cur + treeMaxNodes, n));
                    randomTree(cur, next, u, v);
                    cur = next + 1;
                }
            }
        }
		renumberAndShuffleEdges(n, u, v, a);
        M = u.size();
	}

    void randomLinear(int low, int high, vector<int>& u, vector<int>& v, vector<int>& a, int type) {
        if (type == 0) {    // 0 0 ... 0 0 1
            for (int i=low;i<high;i++) a[i-1] = rnd.nextInt(AMIN, AMAX/4) * 4;
            a[high-1] = rnd.nextInt(AMIN, AMAX/4 - 1) * 4 + 1;
        } else if (type == 1) {    // 1 0 1 0 1 0 1
            for (int i=low;i<=high;i+=2) a[i-1] = rnd.nextInt(AMIN, AMAX/4 - 1) * 4 + 1;
            for (int i=low+1;i<=high;i+=2) a[i-1] = rnd.nextInt(AMIN, AMAX/4) * 4;
        }
        for (int i=low+1;i<=high;i++) {
            u.push_back(i-1);
            v.push_back(i);
        }
    }

    void randomStar(int low, int high, vector<int>& u, vector<int>& v, vector<int>& a, int type) {
        if (type == 0) {    // mid odd, others even
            for (int i=low;i<high;i++) a[i] = rnd.nextInt(AMIN, AMAX/2) * 2;
            a[low - 1] = rnd.nextInt(AMIN, AMAX/2 - 1) * 2 + 1;
        } else if (type == 1) { // mid 0 mod 4, others 1 mod 4
            for (int i=low;i<high;i++) a[i] = rnd.nextInt(AMIN, AMAX/4 - 1) * 4 + 1;
            a[low - 1] = rnd.nextInt(AMIN, AMAX/4) * 4;
        }
        for (int i=low+1;i<=high;i++) {
            u.push_back(low);
            v.push_back(i);
        }
	}

    void randomTree(int low, int high, vector<int>& u, vector<int>& v) {
        for (int i=low;i<high;i++) {
            u.push_back(i + 1);
            v.push_back(rnd.nextInt(low, i));
        }
	}

};
