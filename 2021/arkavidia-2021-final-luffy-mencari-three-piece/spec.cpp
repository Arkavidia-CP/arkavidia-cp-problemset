#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
    const int NMAX = 1e6;
;
    int A, B, C, Q;
    vector<char> s;
    vector<int> t, ans;

    void InputFormat() {
        LINE(A, B, C);
        LINE(Q);
        LINES(s, t) % SIZE(Q);
    }

    void OutputFormat() {
        LINES(ans) % SIZE(Q);
    }

    void GradingConfig() {
        TimeLimit(4);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(0 < A && A < NMAX);
        CONS(0 < B && B < NMAX);
        CONS(0 < C && C < NMAX);
        CONS(0 < Q && Q < NMAX);
    }
private:
    bool valid_query(int sz, const vector<char>& s, const vector<int>& t, int a, int b, int c){
        if (sz != s.size()) return 0;
        if (sz != t.size()) return 0;
        int cur[3];
        cur[0] = a;
        cur[1] = b;
        cur[2] = c;
        for(int i=0; i<sz; i++){
            cur[s[i]-'a'] += t[i];
            if(cur[s[i]-'a'] <= 0 || cur[s[i]-'a'] >= NMAX) return 0;
        }
        return 1;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "1 1 1",
            "4",
            "a 0",
            "b 1",
            "c 1",
            "a 2",
        });
        Output({
            "1",
            "2",
            "2",
            "4",
        });
    }
    void BeforeTestCase() {
        t.clear();
        s.clear();
        ans.clear();
    }

    void TestCases() {
        for (int i=0;i<3;i++){
            CASE(A =  rnd.nextInt(1, 999), B =  rnd.nextInt(1, 999), C =  rnd.nextInt(1, 999), Q = 3, make_random_query(A, B, C, Q, s, t, 1, 999));
        }
        for (int i=0;i<3;i++){
            CASE(A =  rnd.nextInt(1, 999), B =  rnd.nextInt(1, 999), C =  rnd.nextInt(1, 999), Q = 999, make_random_query(A, B, C, Q, s, t, 1, 999));
        }
        for (int i=0;i<3;i++){
            CASE(A =  rnd.nextInt(1, 999), B =  rnd.nextInt(1, 999), C =  rnd.nextInt(1, 999), Q = 999999, make_random_query(A, B, C, Q, s, t, 1, 999));
        }

        for (int i=0;i<3;i++){
            CASE(A =  rnd.nextInt(1, 999999), B =  rnd.nextInt(1, 999999), C =  rnd.nextInt(1, 999999), Q = 3, make_random_query(A, B, C, Q, s, t, 1, 999999));
        }
        for (int i=0;i<3;i++){
            CASE(A =  rnd.nextInt(1, 999999), B =  rnd.nextInt(1, 999999), C =  rnd.nextInt(1, 999999), Q = 999, make_random_query(A, B, C, Q, s, t, 1, 999999));
        }
        for (int i=0;i<3;i++){
            CASE(A =  rnd.nextInt(1, 999999), B =  rnd.nextInt(1, 999999), C =  rnd.nextInt(1, 999999), Q = 999999, make_random_query(A, B, C, Q, s, t, 1, 999999));
        }
    }

private:
    void make_random_query(int a, int b, int c, int q, vector<char>& s, vector<int>& t, int l, int r){
        int cura = a;
        int curb = b;
        int curc = c;
        int nexta, nextb, nextc;
        for(int i=0; i<q/3; i++){
            nexta = rnd.nextInt(l, r);
            nextb = rnd.nextInt(l, r);
            nextc = rnd.nextInt(l, r);
            s.push_back('a');
            s.push_back('b');
            s.push_back('c');
            t.push_back(nexta - cura);
            t.push_back(nextb - curb);
            t.push_back(nextc - curc);
            cura = nexta;
            curb = nextb;
            curc = nextc;
        }
    }
};