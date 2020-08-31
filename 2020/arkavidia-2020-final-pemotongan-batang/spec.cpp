#include <tcframe/spec.hpp>
#include <bits/stdc++.h>

using namespace std;
using namespace tcframe;

typedef long long LL;

const LL MAXT = 1e18;
const int MAXQ = 1e5; 

class ProblemSpec : public BaseProblemSpec{
    protected:
        LL T;
        int Q;
        vector<vector<LL> > query;
        vector<int> op;
        vector<LL> ans;

        void InputFormat(){
            LINE(T, Q);
            LINES(op, query) % SIZE(Q);
        }

        void OutputFormat(){
            LINES(ans);
        }

        void GradingConfig(){
            TimeLimit(1);
            MemoryLimit(128);
        }

        void Constraints(){
            CONS(1 <= T && T <= MAXT);
            CONS(1 <= Q && Q <= MAXQ);
            CONS(eachElementBetween(query, 1, T));
            CONS(checkQueryTwo(op, query));
        }

    private:
        bool eachElementBetween(const vector<vector<LL>> & a, LL lo, LL hi){
            for (int i = 0; i < (int)a.size(); ++i){
                for (int j = 0; j < (int)a[i].size(); ++j){
                    if (a[i][j] < lo || a[i][j] > hi) {
                        return false;
                    }
                }
            }
            return true;
        }

        bool checkQueryTwo(const vector<int> & op, const vector<vector<LL> > & query){
            set<LL> st;
            for (int i = 0; i < op.size(); ++i){
                if (op[i] == 1){
                    st.insert(query[i][0]);
                }else if (op[i] == 2){
                    if (st.find(query[i][0]) == st.end()) {
                        return false;
                    }
                    st.erase(query[i][0]);
                }
            }
            return true;
        }

};

class TestSpec : public BaseTestSpec<ProblemSpec>{
    protected:

        void SampleTestCase1(){
            Input({
                "6 6",
                "3",
                "1 3",
                "1 5",
                "3",
                "2 5",
                "3"
            });
            Output({
                "6",
                "3",
                "3"
            });
        }

        void BeforeTestCase(){
            op.clear();
            for (int i = 0; i < query.size(); ++i){
                query[i].clear();
            }
            query.clear();
        }

        void TestCases(){
            CASE(T = 5, Q = 4, op = {1, 3, 2, 3}, query={{4},{},{4},{}});
            CASE(T = 6, Q = 8, op = {1, 1, 1, 3, 3, 2, 2, 3}, query={{2},{3},{3},{},{},{2},{3},{}});

            for (int i = 0; i < 3; ++i){
                CASE(
                    T = rnd.nextLongLong(1, MAXQ),
                    Q = rnd.nextInt(5, MAXQ),
                    randomQuery1(T, Q, op, query)
                );
            }

            for (int i = 0; i < 3; ++i){
                CASE(
                    T = rnd.nextLongLong(MAXQ*100, MAXQ*10000),
                    Q = rnd.nextInt(MAXQ/10, MAXQ),
                    randomQuery2(T, Q, op, query, 100)
                );
            }

            for (int i = 0; i < 2; ++i){
                CASE(
                    T = rnd.nextLongLong(MAXT/1000, MAXT),
                    Q = rnd.nextInt(MAXQ/10, MAXQ),
                    randomQuery2(T, Q, op, query, 1000)
                );
            }

            
            for (int i = 0; i < 2; ++i){
                CASE(
                    T = rnd.nextLongLong(MAXT/10, MAXT),
                    Q = rnd.nextInt(MAXQ/10, MAXQ),
                    randomQuery2(T, Q, op, query, 100)
                );
            }

            CASE(
                T = rnd.nextLongLong(MAXT/10, MAXT),
                Q = rnd.nextInt(MAXQ/10, MAXQ),
                randomQuery2(T, Q, op, query, 1000)
            );

            CASE(
                T = MAXT,
                Q = MAXQ,
                randomQuery2(T, Q, op, query, 100)
            );
        }

    private:
        void randomQuery1(const LL &T, const int & Q, vector<int> &op, vector<vector<LL> > &query){
            set<LL> st;
            query.resize(Q);
            for (int i = 0; i < 4; ++i){
                op.push_back(1);
                LL bil = rnd.nextLongLong(1, T);
                st.insert(bil);
                query[i].push_back(bil);
            }
            for (int i = 4; i < Q; ++i){
                int opr = rnd.nextInt(1, 3);
                if (opr == 1 || (opr == 2 && st.empty())){
                    LL bil = rnd.nextLongLong(1, T);
                    st.insert(bil);
                    op.push_back(1);
                    query[i].push_back(bil);
                }else if (opr == 2){
                    int sz = rnd.nextInt(1, st.size());
                    sz = min(sz, 100);
                    LL bil = *(st.begin());
                    for (set<LL>::iterator it = st.begin(); it != st.end() && sz > 0; ++it){
                        --sz;
                        if (sz == 0){
                            bil = *it;
                            break;
                        }
                    }
                    st.erase(bil);
                    query[i].push_back(bil);
                    op.push_back(2);
                }else{
                    op.push_back(3);
                }
            }
        }

        void randomQuery2(const LL &T, const int & Q, vector<int> &op, vector<vector<LL> > &query, int limit){
            set<LL> st;
            query.resize(Q);
            for (int i = 0; i < Q/3; ++i){
                op.push_back(1);
                LL bil = rnd.nextLongLong(1, T);
                query[i].push_back(bil);
                st.insert(bil);
            }
            int cnt = 0;
            for (int i = Q/3; i < Q; ++i){
                if (cnt < (2*limit)/3){
                    op.push_back(1);
                    LL bil = rnd.nextLongLong(1, T);
                    query[i].push_back(bil);
                    st.insert(bil);
                }else{
                    if ((cnt-(2*limit)/3) % 2 == 0){
                        int sz = rnd.nextInt(1, st.size());
                        sz = min(sz, 1000);
                        LL bil = *(st.begin());
                        for (set<LL>::iterator it = st.begin(); it != st.end() && sz > 0; ++it){
                            --sz;
                            if (sz == 0){
                                bil = *it;
                                break;
                            }
                        }
                        st.erase(bil);
                        query[i].push_back(bil);
                        op.push_back(2);
                    }else {
                        op.push_back(3);
                    }
                }
                ++cnt;
                if (cnt > limit) cnt = 0;
            }
        }
};