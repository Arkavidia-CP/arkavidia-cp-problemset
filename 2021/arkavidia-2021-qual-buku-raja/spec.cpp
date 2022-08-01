#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

#define MAXN 100000
#define MAXM 100000


class ProblemSpec : public BaseProblemSpec {
protected:
	int N, M;
    vector<int> B;
    vector<int> X;
    long long ans;

	void InputFormat() {
	  LINE(N,M);
	  LINE(B % SIZE(N));
      LINES(X) % SIZE(M);
	}

    void OutputFormat() {
    	LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(1.5);
        MemoryLimit(128);
    }

    void Constraints() {
        CONS(1 <= N && N <= MAXN);
        CONS(1 <= M && M <= MAXM);
        CONS(isPermutation(B, N));
        CONS(rangeCheck(X, 1, N));
    }

private:
    bool isPermutation(vector<int> v, int n){
        if (v.size()!=n){
            return false;
        }
        sort(v.begin(),v.end());
        for (int i = 0; i < n; i++){
            if (v[i] != i+1){
                return false;
            }
        }
        return true;
    }

    bool rangeCheck(vector<int> v, int a, int b){
        for(int i = 0; i < v.size(); i++){
            if(v[i] < a || v[i] > b)
                return false;
        }
        return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
        	"5 4",
            "1 5 4 3 2",
            "3",
            "5",
            "4",
            "4"
        });
        Output({
        	"16"
        });
    }

    void BeforeTestCase(){
    	B.clear();
    	X.clear();
    }

    void TestCases() {
        CASE(N = 5, M = 5, B = {1,2,3,4,5}, X = {2,1,2,1,2});
        CASE(N = 10, M = 10, B = {1,2,3,4,5,6,7,8,9,10}, X = {1,1,1,1,1,1,1,1,1,1});
        for (int i = 1; i <= 10; i++){
            CASE(N = rnd.nextInt(100,1000), M = rnd.nextInt(100,1000), generateRandomB(N,B), generateRandomX(N,M,X));
        }
        for (int i = 1; i <= 3; i++){
            int dec = rnd.nextInt(0,60);
            CASE(N = MAXN - dec, M = MAXM, generateMaxAnsB(N,B), generateMaxAnsX(N,M,X));
        }
        for (int i = 1; i <= 10; i++){
            CASE(N = MAXN, M = MAXM, generateRandomB(N,B), generateRandomX(N,M,X));
        }
    }

private:
    void generateRandomB(int n, vector<int> &B){
        B.clear();
        for (int i = 1; i <= n; i++){
            B.push_back(i);
        }
        rnd.shuffle(B.begin(),B.end());
    }

    void generateRandomX(int n, int m, vector<int> &X){
        X.clear();
        for (int i = 1; i <= m; i++){
            X.push_back(rnd.nextInt(1,n));
        }
    }

    void generateMaxAnsB(int n, vector<int> &B){
        B.clear();
        for (int i = n; i > 0; i--){
            B.push_back(i);
        }
    }

    void generateMaxAnsX(int n, int m, vector<int> &X){
        X.clear();
        for (int i = 0; i < m; i++){
            X.push_back((i%n)+1);
        }
    }
};