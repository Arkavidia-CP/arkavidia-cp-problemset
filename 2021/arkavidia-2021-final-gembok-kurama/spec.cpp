#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

const int MAXQ = 100;
const int MAXN = 1e4;

class ProblemSpec : public BaseProblemSpec {
protected:
    int Q;
    vector<string> quers;
    vector<string> ans;

    void InputFormat() {
        LINE(Q);
        LINES(quers) % SIZE(2 * Q);
    }

    void OutputFormat() {
        RAW_LINES(ans) % SIZE(Q);
    }

    void GradingConfig() {
        TimeLimit(5);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(1 <= Q && Q <= MAXQ);
        CONS(valid_query(quers, Q));
    }

private:
    bool valid_query(const vector<string>& quers, const int& Q){
        for (int i=0;i<Q;i++){
            int len = stoi(quers[i * 2]);
            string s = quers[i * 2 + 1];
            if (s.size() != len || len <= 0 || len > MAXN) return 0;
        }
        return 1;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "3",
            "4",
            "1234",
            "5",
            "11114",
            "3",
            "100"
        });
        Output({
            "0123",
            "00003",
            "001"
        });
    }
    void BeforeTestCase() {
        quers.clear();
        ans.clear();
    }

    void TestCases() {
        for (int i=0;i<5;i++){
            CASE(Q = rnd.nextInt(1, 10), make_random_query(Q, quers));
        }
        for (int i=0;i<5;i++){
            CASE(Q = rnd.nextInt(11, MAXQ), make_random_query(Q, quers));
        }
        for (int i=0;i<5;i++){
            CASE(Q = MAXQ, make_random_query(Q, quers, MAXN, MAXN));
        }
        CASE(Q = MAXQ, corner_case1(Q, quers));
        CASE(Q = MAXQ, corner_case2(Q, quers));
        CASE(Q = MAXQ, corner_case3(Q, quers));
    }

private:
    void make_random_query(int q, vector<string>& quers, int A = 1, int B = MAXN){
        for (int i=0;i<q;i++){
            int len = rnd.nextInt(A, B);
            string s = "";
            for (int j=0;j<len;j++){
                int dig = rnd.nextInt(0, 9);
                s.push_back((char)(dig + '0'));
            }
            quers.push_back(to_string(len));
            quers.push_back(s);
        }
    }
    void corner_case1(int q, vector<string>& quers){
        for (int i=0;i<q;i++){
            int len = MAXN;
            string s = "";
            for (int j=0;j<len;j++){
                s.push_back((char)('0' + i % 10));
            }
            quers.push_back(to_string(len));
            quers.push_back(s);
        }
    }
    void corner_case2(int q, vector<string>& quers){
        for (int i=0;i<q;i++){
            int len = 1;
            string s = "";
            for (int j=0;j<len;j++){
                s.push_back((char)('0' + i % 10));
            }
            quers.push_back(to_string(len));
            quers.push_back(s);
        }
    }
    void corner_case3(int q, vector<string>& quers){
        for (int i=0;i<q;i++){
            int len = MAXN;
            string s = "";
            for (int j=0;j<len;j++){
                s.push_back((char)('0' + (i + j) % 10));
            }
            quers.push_back(to_string(len));
            quers.push_back(s);
        }
    }
};
// #include <tcframe/spec.hpp>
// #include <bits/stdc++.h>

// using namespace std;
// using namespace tcframe;

// class ProblemSpec : public BaseProblemSpec {
// protected:
//     int T;
//     int N;
//     string S;
//     string ans;

//     void InputFormat() {
//         LINE(N);
//         LINE(S);
//     }

//     void OutputFormat() {
//         LINE(ans);
//     }

//     void GradingConfig() {
//         TimeLimit(2);
//         MemoryLimit(128);
//     }

//     void MultipleTestCasesConfig() {
//         Counter(T);
//         OutputPrefix("Kasus ke- %d:\n");
//     }

//     void MultipleTestCasesConstraints() {
//         CONS(1 <= T && T <= 100);
//     }

//     void Constraints() {
//         CONS(1 <= N && N <= 2000);
//         CONS(S.size() == N);
//     }
// };

// class TestSpec : public BaseTestSpec<ProblemSpec> {
// protected:
//     void BeforeTestCase(){
//         S = "";
//     }
//     void TestGroup1() {
//         for (int i=0;i<10;i++){
//             CASE(make_random_query(N, S));
//         }
//     }
//     void TestGroup2() {
//         for (int i=0;i<100;i++){
//             CASE(make_random_query(N, S));
//         }
//     }

// private:
//     void make_random_query(int& n, string& s){
//         n = rnd.nextInt(1, 2000);
//         for (int i=0;i<n;i++){
//             int dig = rnd.nextInt(0, 9);
//             s.push_back((char)(dig + '0'));
//         }
//     }
// };