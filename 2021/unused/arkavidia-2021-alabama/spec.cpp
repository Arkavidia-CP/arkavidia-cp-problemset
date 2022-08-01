#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
    const int NMAX = 2e3;

    int N;
    vector<int> SZ; // SZ DESC tiap orang
    vector<vector<int>> DESC;
    vector<int> Parent;
    void InputFormat() {
        LINE(N);
        LINES(SZ, DESC) % SIZE(N);
    }

    void OutputFormat() {
        LINE(Parent %  SIZE(N));
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(128);
    }

    void Constraints() {
        CONS(1 <= N && N <= NMAX);
        noSelfDescendant(DESC);
        for (int i = 0; i < DESC.size(); i++) {
            eachElementBetween(DESC[i], 0, N);
        }
        eachElementBetween(Parent, 0, N);
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

    bool noSelfDescendant(const vector<vector<int>> v) {
        for (int i = 0; i < v.size(); i++) {
            int pers = i + 1;
            for (int desc: v[i]) {
                if (pers == desc) {
                    return false;
                }
            }
        }
        return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "3",
            "2 2 3",
            "1 3",
            "0"
        });
        Output({
            "0 1 2"
        });
    }

    void SampleTestCase2() {
        Input({
            "4",
            "1 3",
            "1 4",
            "0",
            "0"
        });
        Output({
            "0 0 1 2"
        });
    }

    void BeforeTestCase() {
        Parent.clear();
        DESC.clear();
        SZ.clear();
    }

    void TestCases() {
        // Case manual
        // mager lol

        // Case single tree (random, nodes shuffled)
        //! Tambah tree selain random (?). keknya random aja dah cukup
        CASE(N = 10, makeSingleTree(N, SZ, DESC));
        CASE(N = 100, makeSingleTree(N, SZ, DESC));
        for (int i = 0; i < 5; i++) {
            CASE(N = NMAX / 4, makeSingleTree(N, SZ, DESC));
        }
        for (int i = 0; i < 5; i++) {
            CASE(N = NMAX / 2, makeSingleTree(N, SZ, DESC));
        }
        for (int i = 0; i < 10; i++) {
            CASE(N = NMAX, makeSingleTree(N, SZ, DESC));
        }

        // Case line tree (nodes suffled)
        CASE(N = 10, makeLineTree(N, SZ, DESC));
        CASE(N = 100, makeLineTree(N, SZ, DESC));
        for (int i = 0; i < 5; i++) {
            CASE(N = NMAX / 4, makeLineTree(N, SZ, DESC));
        }
        for (int i = 0; i < 5; i++) {
            CASE(N = NMAX / 2, makeLineTree(N, SZ, DESC));
        }
        for (int i = 0; i < 5; i++) {
            CASE(N = NMAX, makeLineTree(N, SZ, DESC));
        }

        // Case multiple tree
        // CASE(N = 10, makeForest(N, rnd.nextInt(1, (N + 2 / 3))));
        CASE(N = 10, makeForest(N, 2, SZ, DESC));
        CASE(N = 100, makeForest(N, 5, SZ, DESC));
        CASE(N = 100, makeForest(N, 10, SZ, DESC));
        for (int i = 0; i < 5; i++) {
            CASE(N = NMAX, makeForest(N, rnd.nextInt(10, NMAX / 5), SZ, DESC));
        }

        // Case N tree (tiap i no parent)
        CASE(N = 100, SZ.assign(N, 0), DESC.assign(N, {}));
        CASE(N = NMAX / 2, SZ.assign(N, 0), DESC.assign(N, {}));
        CASE(N = NMAX, SZ.assign(N, 0), DESC.assign(N, {}));
    }

private:
    void makeSingleTree(int n, vector<int>& sz, vector<vector<int>>& desc, bool reorder = true) {
        vector<int> U, V;
        // U parent, V anak
        for (int i = 2; i <= n; i++) {
            U.push_back(rnd.nextInt(1, i - 1));
            V.push_back(i);
        }
        vector<vector<int>> adj(n + 1);
        for (int i = 0; i < n - 1; i++) {
            adj[U[i]].push_back(V[i]);
        }
        // for (int i = 1; i <= n; i++) {
        //     cout << i << ' ';
        //     for (int j: adj[i]) cout << j << ' ';
        //     cout << '\n'; 
        // }
        vector<vector<bool>> is_anc(n + 1, vector<bool>(n + 1));
        for (int i = 1; i <= n; i++) {
            queue<int> q;
            q.push(i);
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                if (u != i) {
                    is_anc[i][u] = true;
                }
                for (int v: adj[u]) {
                    q.push(v);
                }
            }
        }
        if (reorder) {
            reorderMatrix(n, is_anc);
        }
        matrixToDesc(n, is_anc, sz, desc);
    }

    void matrixToDesc(int n, vector<vector<bool>>& is_anc, vector<int>& sz, vector<vector<int>>& desc) {
        desc.resize(n);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (is_anc[i][j]) {
                    if (is_anc[j][i]) {
                        cout << "EUY" << '\n';
                        exit(0);
                    }
                    desc[i - 1].push_back(j);
                }
            }
            sz.push_back(desc[i - 1].size());
        }
    }

    vector<int> randomOrder(int n) {
        vector<int> ret;
        for (int i = 1; i <= n; i++) {
            ret.push_back(i);
        }
        rnd.shuffle(ret.begin(), ret.end());
        return ret;
    }

    void reorderMatrix(int n, vector<vector<bool>>& is_anc) {
        vector<int> order = randomOrder(n);
        vector<vector<bool>> shuffled_is_anc(n + 1, vector<bool>(n + 1));
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                if (is_anc[i][j]) {
                    int ni = order[i - 1], nj = order[j - 1];
                    shuffled_is_anc[ni][nj] = true;
                }
            }
        }
        is_anc = shuffled_is_anc;
    }

    void makeLineTree(int n, vector<int>& sz, vector<vector<int>>& desc) {
        vector<vector<bool>> is_anc(n + 1, vector<bool>(n + 1));
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                is_anc[i][j] = true;
            }
        }
        reorderMatrix(n, is_anc);
        matrixToDesc(n, is_anc, sz, desc);
    }

    void makeForest(int n, int k, vector<int>& sz, vector<vector<int>>& desc) { // make k tree from n nodes
        vector<int> treeSz;
        int rest = n - k;
        for (int i = 0; i < k; i++) {
            int add = rnd.nextInt(0, rest);
            rest -= add;
            treeSz.push_back(1 + add);
        }
        if (rest != 0) {
            treeSz.back() += rest;
        }

        for (int i = 0; i < k; i++) {
            vector<int> curSz;
            vector<vector<int>> curDesc;
            makeSingleTree(treeSz[i], curSz, curDesc);
            for (auto it: curSz) {
                sz.push_back(it);
            }
            for (auto it: curDesc) {
                desc.push_back(it);
            }
        }
        int idStart = treeSz[0];
        for (int i = 1; i < k; i++) {
            for (int id = idStart; id  < idStart + treeSz[i]; id++) {
                for (auto& x: desc[id]) {
                    x += idStart;
                }
            }
            idStart += treeSz[i];
        }
    }
};