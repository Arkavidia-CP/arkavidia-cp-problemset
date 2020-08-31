#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

#define MAXVAL 1000000000
#define MAXN 20000
#define MAXQ 30000

class ProblemSpec : public BaseProblemSpec {
protected:
    int N, Q, askCount;
    vector<int> score, ans;
    vector<pair<int,int> > query;
    vector<int> tipe, value;

    void BeforeOutputFormat(){
        askCount = 0;
        for(int i = 0; i < tipe.size(); i++){
            if(tipe[i] == 2){
                askCount++;
            }
        }
    }

    void InputFormat() {
        LINE(N);
        LINE(score % SIZE(N));
        LINE(Q);
        LINES(tipe, value) % SIZE(Q);
    }

    void OutputFormat() {
        LINES(ans) % SIZE(askCount);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(64);
    }

    void Constraints() {
        CONS(1 <= N && N <= MAXN);
        CONS(1 <= Q && Q <= MAXQ);
        CONS(rangeCheck(score, 1, MAXVAL));
        CONS(queryCheck(tipe, value, N, 1, MAXVAL));
        CONS(tipe.size() == Q && value.size() == Q && score.size() == N);
    }

private:
    bool rangeCheck(vector<int> v, int a, int b){
        for(int i = 0; i < v.size(); i++){
            if(v[i] < a || v[i] > b)
                return false;
        }
        return true;
    }

    bool queryCheck(vector<int> tipe, vector<int> value, int participant, int a, int b){
        bool isAskExist = false;
        for(int i = 0; i < tipe.size(); i++){
            if(tipe[i] == 1){
                participant++;
                if(value[i] < a || value[i] > b)
                    return false;
            } else {
                isAskExist = true;
                if(value[i] < 1 || value[i] > participant)
                    return false;
            }
        }
        return isAskExist;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "6",
            "98 66 59 57 34 12",
            "6",
            "2 3",
            "1 61",
            "2 3",
            "1 98",
            "2 1",
            "2 2"
        });
        Output({
            "59",
            "61",
            "98",
            "98"
        });
    }

    void BeforeTestCase(){
        score.clear();
        query.clear();
        tipe.clear();
        value.clear();
    }

    void TestCases() {
        for(int i = 0; i < 6; i++){
            CASE(N = rnd.nextInt(1, MAXN), Q = rnd.nextInt(1, MAXQ), initScore(N, score), heavyUpdate(N, Q, query));
        }

        for(int i = 0; i < 6; i++){
            CASE(N = rnd.nextInt(1, MAXN), Q = rnd.nextInt(1, MAXQ), initScore(N, score), heavyQuery(N, Q, query));
        }

        for(int i = 0; i < 8; i++){
            CASE(N = rnd.nextInt(1, MAXN), Q = rnd.nextInt(1, MAXQ), initScore(N, score), alternateQuery(N, Q, query));
        }
    }

    void AfterTestCase(){
        for(int i = 0; i < Q; i++){
            tipe.push_back(query[i].first);
            value.push_back(query[i].second);
        }
    }

private:
    void initScore(int N, vector<int> &score){
        for(int i = 0; i < N; i++){
            score.push_back(rnd.nextInt(1, MAXVAL));
        }
        sort(score.begin(), score.end(), greater<int>());
    }

    void heavyUpdate(int N, int Q, vector<pair<int,int> > &query){
        for(int i = 0; i < Q-1; i++){
            int chance = rnd.nextInt(5);
            if(chance == 0){
                query.push_back(make_pair(2, rnd.nextInt(1, N)));
            } else {
                query.push_back(make_pair(1, rnd.nextInt(1, MAXVAL)));
                N++;
            }
        }
        query.push_back(make_pair(2, rnd.nextInt(1, N)));
    }

    void heavyQuery(int N, int Q, vector<pair<int,int> > &query){
        for(int i = 0; i < Q-1; i++){
            int chance = rnd.nextInt(5);
            if(chance > 0){
                query.push_back(make_pair(2, rnd.nextInt(1, N)));
            } else {
                query.push_back(make_pair(1, rnd.nextInt(1, MAXVAL)));
                N++;
            }
        }
        query.push_back(make_pair(2, rnd.nextInt(1, N)));
    }

    void alternateQuery(int N, int Q, vector<pair<int,int> > &query){
        for(int i = 0; i < Q; i++){
            if(i % 2){
                query.push_back(make_pair(2, rnd.nextInt(1, N)));
            } else {
                query.push_back(make_pair(1, rnd.nextInt(1, MAXVAL)));
                N++;
            }
        }
    }
};