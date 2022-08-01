#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

#define MAXN 100000
#define MAXM 1000000000000000LL

class ProblemSpec : public BaseProblemSpec {
protected:
	int N;
	long long M;
	vector<long long>R, C;
	long long ans;

	void InputFormat() {
	  LINE(M,N);
	  LINE(R % SIZE(N));
	  LINE(C % SIZE(N));
	}

    void OutputFormat() {
    	LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(64);
    }

    void Constraints() {
        CONS(1 <= M && M <= MAXM);
        CONS(2 <= N && N <= MAXN);
        CONS(rangeCheck(R, 1, M));
        CONS(rangeCheck(C, 1, M));
    }

private:
    bool rangeCheck(vector<long long> v, long long a, long long b){
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
        	"10 5",
			"9 1 6 7 2",
			"4 10 4 8 3"
        });
        Output({
        	"1"
        });
    }

    void SampleTestCase2(){
    	Input({
    		"2 2",
    		"2 1",
    		"1 2"
    	});
    	Output({
    		"1"
    	});
    }

    void SampleTestCase3(){
    	Input({
    		"5 3",
    		"1 2 1",
    		"4 4 5"
    	});
    	Output({
    		"0"
    	});
    }

    void SampleTestCase4(){
    	Input({
    		"200 3",
    		"17 130 55",
    		"187 23 79"
    	});
    	Output({
    		"56"
    	});
    }

    void BeforeTestCase(){
    	R.clear();
    	C.clear();
    }

    void TestCases() {
    	// M besar, N kecil
    	for (int i = 1; i <= 5; i++){
    		CASE(M = MAXM, N = rnd.nextInt(1,100), randomArrayRange(N,R,1,M), randomArrayRange(N,C,1,M));
    	}
    	// M kecil, N besar
    	for (int i = 1; i <= 5; i++){
    		CASE(M = rnd.nextInt(1,100), N = rnd.nextInt(1,MAXN), randomArrayRange(N,R,1,M), randomArrayRange(N,C,1,M));
    	}
    	// Ri Ci sama semua
    	for (int i = 1; i <= 3; i++){
    		long long r = rnd.nextLongLong(1,MAXM);
    		long long c = rnd.nextLongLong(1,MAXM);
    		CASE(M = MAXM, N = MAXN, randomArrayRange(N,R,r,r), randomArrayRange(N,C,c,c));
    	}
    	// M besar, N besar, Ri Ci unik
    	for (int i = 1; i <= 10; i++){
    		CASE(M = MAXM, N = MAXN, randomUniqueArrayRange(N,R,1,M), randomUniqueArrayRange(N,C,1,M));
    	}
    }

private:
    void randomArrayRange(int N, vector<long long> &v, long long lb, long long rb){
    	v.clear();
    	for (int i = 0; i < N; i++){
    		v.push_back(rnd.nextLongLong(lb,rb));
    	}
    }
    void randomUniqueArrayRange(int N, vector<long long> &v, long long lb, long long rb){
    	v.clear();
    	set<long long> ada;
    	for (int i = 0; i < N; i++){
    		long long tmp;
    		do{
    			tmp = rnd.nextLongLong(lb,rb);
    		} while (ada.count(tmp));
    		ada.insert(tmp);
    		v.push_back(tmp);
    	}
    }
};