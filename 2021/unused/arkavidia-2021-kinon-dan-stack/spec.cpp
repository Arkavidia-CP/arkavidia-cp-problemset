#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

#define MAXQ 100000
#define MINX -100000
#define MAXX 100000

class ProblemSpec : public BaseProblemSpec {
protected:
	int Q;
    vector<int> X;
    int ans;

	void InputFormat() {
	  LINE(Q);
	  LINE(X % SIZE(Q));
	}

    void OutputFormat() {
    	LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(2);
        MemoryLimit(128);
    }

    void Constraints() {
        CONS(1 <= Q && Q <= MAXQ);
        CONS(validX(X));
    }

private:
    bool validX(vector<int> v){
        multiset<int> ms;
        for (int i = 0; i < v.size(); i++){
            if (v[i] == 0 || v[i] < MINX || v[i] > MAXX) return false;
            if (v[i] > 0) ms.insert(v[i]);
            else{
                if (ms.count(-v[i]) == 0) return false;
                ms.erase(ms.find(-v[i]));
            }
        }
        return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
        	"6",
            "1 3 5 7 -3 -1"
        });
        Output({
        	"2"
        });
    }

    void SampleTestCase2(){
    	Input({
    		"8",
            "1 2 3 -2 -1 1 -3 2"
    	});
    	Output({
    		"2"
    	});
    }

    void BeforeTestCase(){
    	X.clear();
    }

    void TestCases() {
        CASE(Q = 6, X = {1,2,3,-1,-2,-3});
        CASE(Q = 6, X = {1,2,3,-3,-2,-1});
        CASE(Q = 6, X = {1,6,19,-6,-1,-19});
        CASE(Q = 8, X = {1,-1,1,1,-1,1,-1,-1});
        CASE(Q = MAXQ, generateMaxAnsX(Q,X));
        for (int i = 1; i <= 5; i++){
            CASE(Q = 100, generateRandomX(Q,X,30));
        }
        for (int i = 1; i <= 5; i++){
            CASE(Q = MAXQ, generateRandomX(Q,X,10));
        }
        for (int i = 1; i <= 5; i++){
            CASE(Q = MAXQ, generateRandomX(Q,X,25));
        }
        for (int i = 1; i <= 5; i++){
            CASE(Q = MAXQ, generateRandomX(Q,X,40));
        }
        for (int i = 1; i <= 5; i++){
            CASE(Q = MAXQ, generateRandomX(Q,X,70));
        }
        for (int i = 1; i <= 5; i++){
            CASE(Q = MAXQ, generateRandomX(Q,X,80));
        }
        for (int i = 1; i <= 5; i++){
            CASE(Q = MAXQ, generateRandomX(Q,X,90));
        }
        for (int i = 1; i <= 10; i++){
            CASE(Q = MAXQ, generateToxicX(Q,X));
        }
        for (int i = 1; i <= 10; i++){
            CASE(Q = MAXQ, generateUniqueToxicX(Q,X));
        }
    }

private:
    void generateMaxAnsX(int Q, vector<int> &X){
        X.clear();
        for (int i = 1; i*2 <= Q; i++){
            X.push_back(i);
        }
        for (int i = 1; i*2 <= Q; i++){
            X.push_back(-i);
        }
    }

    void generateRandomX(int Q, vector<int> &X, int erase_ratio){
        X.clear();
        vector<int> pool;
        int nbElmt = rnd.nextInt(50,5000);
        for (int i = 0; i < nbElmt; i++){
            pool.push_back(rnd.nextInt(1,MAXX));
        }
        vector<int> active;
        vector<int> cnt(MAXX+5, 0);
        for (int i = 0; i < Q; i++){
            int type = rnd.nextInt(1,100);
            if (active.empty() || type <= erase_ratio){
                // add
                int idx = rnd.nextInt(0,nbElmt-1);
                X.push_back(pool[idx]);
                if (cnt[pool[idx]] == 0){
                    active.push_back(pool[idx]);
                }
                cnt[pool[idx]]++;
            }
            else{
                // remove
                int idx = rnd.nextInt(0,(int)active.size()-1);
                X.push_back(-active[idx]);
                cnt[active[idx]]--;
                if (cnt[active[idx]] == 0){
                    active.erase(active.begin()+idx);
                }
            }
        }
    }

    void generateToxicX(int Q, vector<int> &X){
        vector<int> add;
        for (int i = 0; i*2 < Q; i++){
            add.push_back(rnd.nextInt(1,MAXX));
        }
        for (int a : add){
            X.push_back(a);
        }
        rnd.shuffle(add.begin(),add.end());
        for (int a : add){
            X.push_back(-a);
        }
    }

    void generateUniqueToxicX(int Q, vector<int> &X){
        vector<int> add;
        set<int> ada;
        for (int i = 0; i*2 < Q; i++){
            int tmp;
            do{
                tmp = rnd.nextInt(1,MAXX);
            }
            while (ada.count(tmp));
            ada.insert(tmp);
            add.push_back(tmp);
        }
        for (int a : add){
            X.push_back(a);
        }
        rnd.shuffle(add.begin(),add.end());
        for (int a : add){
            X.push_back(-a);
        }
    }
};