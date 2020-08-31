#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;

const int MAXN = 1000000;

class ProblemSpec : public BaseProblemSpec {
protected:
    int N, M;
    long long distSum, targetCity;
    vector<int> A, B;

    void InputFormat() {
        LINE(N, M);
		LINES(A, B) % SIZE(M);
    }

    void OutputFormat() {
        LINE(distSum, targetCity);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(128);
    }

    void Constraints() {
        CONS(1 <= N && N <= MAXN);
        CONS(M < N);
		CONS(eachElementBetween(A, 1, N));
        CONS(eachElementBetween(B, 1, N));
        CONS(isTree(N, M, A, B));
        CONS(A.size() == B.size() && B.size() == M);
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

    bool isTree(const int &N, const int &M, const vector<int> &A, const vector<int> &B){
        vector<bool> visited;
        for(int i = 0; i < N; i++){
            visited.push_back(false);
        }

        vector<vector<int> > adj = convertTo2D(N, A, B);
        bool res = true;
        for(int i = 0; i < N; i++){
            if(!visited[i]){
                res &= dfs(i, i, N, M, adj, visited);
            }
        }
        return res;
    }

    vector<vector<int> > convertTo2D(const int &N, const vector<int> &A, const vector<int> &B){
        vector<vector<int> > v;

        v.resize(N);
        for(int i = 0; i < A.size(); i++){
            v[A[i]-1].push_back(B[i]-1);
            v[B[i]-1].push_back(A[i]-1);
        }
        return v;
    }

    bool dfs(int now, int last, const int &N, const int &M, const vector<vector<int>> &adj, vector<bool> &visited){
        if(visited[now])
            return false;
        visited[now] = true;
        bool res = true;
        for(int i = 0; i < adj[now].size(); i++){
            if(last == adj[now][i]){
                continue;
            }
            res &= dfs(adj[now][i], now, N, M, adj, visited);
        }
        return res;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
	
    void SampleTestCase1() {
        Input({
            "4 3",
			"1 2",
			"2 3",
            "3 4"
        });
        Output({
            "2 4"
        });
    }
	
	void BeforeTestCase() {
		A.clear();
        B.clear();
	}	

    void TestCases() {
        for(int i = 0; i < 3; i++){
            CASE(N = 10, M = N-1, randomTree(N, A, B));
        }
        for(int i = 0; i < 20; i++){
            CASE(N = rnd.nextInt(1, MAXN), M = N-1, randomTree(N, A, B));
        }
    }

private:

    void renumber(int n, vector<int>& u, vector<int>& v) {
        vector<int> permutation;
        for (int i = 0; i < n-1; i++) {
            permutation.push_back(i);
        }
        rnd.shuffle(permutation.begin(), permutation.end());
        vector<int> tempu(u), tempv(v);
        for (int i = 0; i < n-1; i++) {
            tempu[i] = u[permutation[i]];
            tempv[i] = v[permutation[i]];
        }
        u = tempu;
        v = tempv;
    }

    void randomTree(int n, vector<int>& u, vector<int>& v) {
        for (int i = 1; i < n; i++) {
            u.push_back(i);
            v.push_back(rnd.nextInt(0, i - 1));
        }
        renumber(n, u, v);
        for(int i = 0; i < u.size(); i++){
            u[i]++;
            v[i]++;
        }
    }
};

