#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;

const int NMAX = 1e5;
const int MMAX = 1e5;
const int QMAX = 1e5;

class ProblemSpec : public BaseProblemSpec {
protected:

    int N, M, Q;
    vector<int> P;
    vector<vector<int>> T;
    vector<vector<int>> Query;
    vector<pair<int, int>> bap;
    vector<pair<int, int>> bat;
    vector<string> Answer;

    void InputFormat() {
        LINE(N, M, Q);
        LINES(T) % SIZE(M);
        LINES(Query);
    }

    void OutputFormat() {
        RAW_LINES(Answer);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(2 <= N && N <= NMAX);
        CONS(2 <= M && M <= N);
        CONS(1 <= Q && Q <= QMAX);
        CONS(eachElementBetween(T, 0, N));
    }

private:
    bool eachElementBetween(vector<vector<int>>& v, int low, int high) {
        for (vector<int>& x : v) {
            for (int y : x) {
                if (y < low || y > high)
                    return false;
            }
        }
        return true;
    }

};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "10 5 5",
            "3 3 1 5",
            "2 2 4",
            "3 6 7 9",
            "1 8",
            "1 10",
            "2 4",
            "2 5",
            "3 3 1",
            "1 8 5",
            "1 10 5"
        });
        Output({
            "1: 3 1 5 6 7 9",
            "2: 2 4",
            "5: 8 10",
        });
    }

    void BeforeTestCase() {
    	 P.clear();
         T.clear();
         Query.clear();
         Answer.clear();
         bap.clear(); bat.clear();
    }

    void TestCases() {
        CASE(N = 5, M = 5, Q = 3, generateRandomInit(N, M, 1), generateRandomQuery(Q, M));
        CASE(N = 5, M = 5, Q = 4, generateRandomInit(N, M, 1), generateRandomQuery(Q, M));
        CASE(N = 5, M = 5, Q = 5, generateRandomInit(N, M, 1), generateRandomQuery(Q, M));
        for (int rep = 0; rep < 5; rep++) {
            CASE(N = rnd.nextInt(2, NMAX / 2), M = rnd.nextInt(2, N), Q = rnd.nextInt(1, QMAX / 2), 
                generateRandomInit(N, M, 1), generateRandomQuery(Q, M));
        }
        for (int rep = 0; rep < 5; rep++) {
            CASE(N = rnd.nextInt(NMAX / 2 + 1, NMAX), M = rnd.nextInt(2, N), Q = rnd.nextInt(QMAX / 2 + 1, QMAX), 
                generateRandomInit(N, M, NMAX / 2), generateRandomQuery(Q, M));
        }
        for (int rep = 0; rep < 10; rep++) {
            CASE(N = NMAX, M = MMAX, Q = QMAX, generateRandomInit(N, M, N), generateRandomQuery(Q, M));
        }
        for (int rep = 0; rep < 5; rep++) {
            CASE(N = NMAX, M = 2, Q = QMAX, generateRandomInit(N, M, N), generateMovePlate(Q));
        }
    }

private:

    void put_plate(int idp, int idt) {
        assert(bap[idp].first == -1);
        if (bat[idt].first == -1) {
            bat[idt].first = idp;
            bap[idp].first = idt;
        } else {
            int up = bat[idt].second;
            bap[up].second = idp;
            bap[idp].first = up;
        }
        bat[idt].second = idp;
    }

    void pop_stack(int idt) {
        assert(bat[idt].first != -1);
        if (bat[idt].first == bat[idt].second) {
            int up = bat[idt].second;
            bap[up] = make_pair(-1, -1);
            bat[idt] = make_pair(-1, -1);
            return;
        }
        int up = bat[idt].second;
        int new_up = bap[up].first;
        assert(new_up != -1);
        assert(bap[new_up].second == up);
        bap[up] = make_pair(-1, -1);
        bap[new_up].second = -1;
        bat[idt].second = new_up;
    }

    void move_plate(int id_1, int id_2) {
        if (bat[id_1].first == -1)
            return;
        if (bat[id_2].first == -1) {
            int down = bat[id_1].first;
            bap[down].first = id_2;
            bat[id_2] = bat[id_1];
        } else {
            int up_1 = bat[id_1].second;
            int down_1 = bat[id_1].first;
            int up_2 = bat[id_2].second;
            bap[up_2].second = down_1;
            bap[down_1].first = up_2;
            bat[id_2].second = up_1;
        }
        bat[id_1] = make_pair(-1, -1);
    }
    
    void generateRandomInit(int N, int M, int low) {
        P.resize(N);
        iota(P.begin(), P.end(), 1);
        rnd.shuffle(P.begin(), P.end());
        T.resize(M);
        bap.assign(N + 1, make_pair(-1, -1));
        bat.assign(M + 1, make_pair(-1, -1));
        for (int i = 0; i < rnd.nextInt(low, N); i++) {
            int cur = P.back();
            P.pop_back();
            int idx = rnd.nextInt(1, M);
            put_plate(cur, idx);
            T[idx - 1].emplace_back(cur);
        }
        for (int i = 0; i < M; i++) {
            int len = T[i].size();
            T[i].insert(T[i].begin(), len);
        }
    }

    void generateRandomQuery(int Q, int M) {
        for (int q = 0; q < Q; q++) {
            int tp = -1;
            int idx = rnd.nextInt(1, M);
            if (P.empty()) {
                if (bat[idx].first == -1) {
                    tp = 3;
                } else {
                    tp = rnd.nextInt(2, 3);
                }
            } else {
                tp = rnd.nextInt(1, 3);
                if (bat[idx].first == -1 && tp == 2) {
                    tp = (rnd.nextInt(1, 2) == 1 ? 1 : 3);
                }
            }
            if (tp == 1) {
                int cur = P.back();
                P.pop_back();
                put_plate(cur, idx);
                Query.emplace_back(vector<int>{1, cur, idx});
            } else if (tp == 2) {
                pop_stack(idx);
                Query.emplace_back(vector<int>{2, idx});
            } else if (tp == 3) {
                int idx_2 = rnd.nextInt(1, M);
                if (idx_2 == idx) {
                    idx_2 = (idx == M ? idx - 1 : idx + 1);
                }
                move_plate(idx, idx_2);
                Query.emplace_back(vector<int>{3, idx, idx_2});
            }
        }
    }

    void generateMovePlate(int Q) {
        for (int q = 0; q < Q; q++) {
            int x = 1, y = 2;
            if (q & 1) {
                x = 2, y = 1;
            }
            Query.emplace_back(vector<int>{3, x, y});
        }
    }
};