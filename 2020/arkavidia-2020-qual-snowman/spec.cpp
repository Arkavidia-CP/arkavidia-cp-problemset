#include <tcframe/spec.hpp>
#include <assert.h>

using namespace tcframe;
using namespace std;

const int MAXN = 100000;
const int MAXQ = 100000;
const int MAXB = 1000000000;
const int MAXD = 10000;

class ProblemSpec : public BaseProblemSpec {
protected:
    int N;
    vector<int> arr;
    int Q;
    vector<int> L, R;
    vector<int> ans;
    
    void InputFormat() {
        LINE(N);
		LINE(arr % SIZE(N));
		LINE(Q);
        LINES(L, R) % SIZE(Q);
    }

    void OutputFormat() {
        LINES(ans) % SIZE(Q);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(64);
    }

    void Constraints() {
        CONS(1 <= N && N <= MAXN);
        CONS(eachElementBetween(arr, -MAXB, MAXB));
        CONS((int)arr.size() == N);
        CONS(1 <= Q && Q <= MAXQ);
        CONS((int)L.size() == Q);
        CONS((int)R.size() == Q);
        CONS(eachElementBetween(L, 1, N));
        CONS(eachElementBetween(R, 1, N));
        CONS(validRangeQuery(L, R));
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

    bool validRangeQuery(const vector<int>& L, const vector<int>& R){
        assert((int)L.size() == (int)R.size());
        for (int i = 0; i < (int)L.size(); ++i){
            if (L[i] > R[i]) return false;
        }
        return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
	
	
    void SampleTestCase1() {
        Input({
            "8",
			"1 3 5 6 7 8 10 12",
			"3",
            "1 8",
            "2 4",
            "6 6"
        });
        Output({
            "4",
            "2",
            "1"
        });
    }
	
	void BeforeTestCase() {
        arr.clear();
		L.clear();
        R.clear();
	}	

    void TestCases() {
       CASE(
           N = 5,
           arr = {1, 2, 3, 4, 5},
           Q = 6,
           L = {1, 2, 2, 3, 4, 4},
           R = {5, 5, 4, 4, 4, 5}
       );

       CASE(
           N = 1,
           arr = {1},
           Q = 1,
           L = {1},
           R = {1}
       );

       CASE(
           N = 3,
           arr = {1, 9, 16},
           Q = {3},
           L = {1, 1, 1},
           R = {3, 3, 2}
       );

        for (int i = 0; i < 1; ++i){
            CASE(
                N = rnd.nextInt(1, 1000),
                randomAllArithmeticSeqInc(N, arr),
                Q = rnd.nextInt(1, 1000),
                randomRange(Q, L, R, N)
            );
            CASE(
                N = rnd.nextInt(1, 1000),
                randomAllArithmeticSeqDec(N, arr),
                Q = rnd.nextInt(1, 1000),
                randomRange(Q, L, R, N)
            );
        }

        for (int i = 0; i < 1; ++i){
            CASE(
                N = rnd.nextInt(10001, MAXN),
                randomAllArithmeticSeqInc(N, arr),
                Q = rnd.nextInt(10001, MAXQ),
                randomRange(Q, L, R, N)
            );
            CASE(
                N = rnd.nextInt(10001, MAXN),
                randomAllArithmeticSeqDec(N, arr),
                Q = rnd.nextInt(10001, MAXQ),
                randomRange(Q, L, R, N)
            );
        }

        for (int i = 0; i < 10; ++i){
            CASE(
                N = rnd.nextInt(10001, MAXN),
                randomPartialArithmeticSeq(N, arr),
                Q = rnd.nextInt(10001, MAXQ),
                randomRange(Q, L, R, N)
            );
        }

        for (int i = 0; i < 5; ++i){
            CASE(
                N = rnd.nextInt(10001, MAXN),
                randomPartialArithmeticSeqDec(N, arr),
                Q = rnd.nextInt(10001, MAXQ),
                randomRange(Q, L, R, N)
            );
        }

        for (int i = 0; i < 5; ++i){
            CASE(
                N = rnd.nextInt(10001, MAXN),
                fullRandom(N, arr),
                Q = rnd.nextInt(10001, MAXQ),
                randomRange(Q, L, R, N)
            );
        }

        for (int i = 0; i < 3; ++i){
            CASE(
                N = MAXN, 
                randomPartialArithmeticSeq(N, arr),
                Q = rnd.nextInt(1, MAXQ),
                randomRange(Q, L, R, N)
            );
        }

        CASE(
            N = MAXN,
            randomAllArithmeticSeqInc(N, arr),
            Q = MAXQ,
            randomRange(Q, L, R, N)
        );
        CASE(
            N = MAXN, 
            randomPartialZeroDiff(N, arr),
            Q = MAXQ, 
            randomRange(Q, L, R, N)
        );
    }

private:
    pair<int,int> generateNumber(int sz, int mini, int maks, int mind, int maksd){
        int a = rnd.nextInt(mini, maks);
        int b = rnd.nextInt(mind, maksd);
        long long last = 1LL*(a + 1LL * (sz-1) * b);
        while (last > 1LL*maks || last < 1LL*mini){
            a = rnd.nextInt(mini, maks);
            b = rnd.nextInt(mind, maksd);
            last = 1LL*(a + 1LL * (sz-1) * b);
        }
        return make_pair(a, b);
    }

    void randomPartialArithmeticSeq(int sz, vector<int>& arr){
        pair<int,int> tmp = generateNumber(sz, -MAXB, MAXB, -MAXD, MAXD);
        int a = tmp.first;
        int b = tmp.second;
        arr.push_back(a);
        a+=b;
        arr.push_back(a);
        a+=b;
        for (int i = 0; i < sz-2; ++i){
            int rd = rnd.nextInt(0, 1);
            if (rd == 0){
                arr.push_back(a);
                a += b;
            }else {
                arr.push_back(a+1);
                a = a+1; a += b;
            }
        }
    }

    void randomPartialArithmeticSeqDec(int sz, vector<int>& arr){
        pair<int,int> tmp = generateNumber(sz, -MAXB, 0, -MAXD, 0);
        int a = tmp.first;
        int b = tmp.second;
        arr.push_back(a);
        a+=b;
        arr.push_back(a);
        a+=b;
        for (int i = 0; i < sz-2; ++i){
            int rd = rnd.nextInt(0, 1);
            if (rd == 0){
                arr.push_back(a);
                a += b;
            }else {
                arr.push_back(a+1);
                a = a+1; a += b;
            }
        }
    }

    void randomAllArithmeticSeqInc(int sz, vector<int>& arr){
        int a = rnd.nextInt(-MAXB, MAXB);
        int b = rnd.nextInt(0, MAXD);
        long long last = 1LL*(a + 1LL * (sz-1) * b);
        while (last > 1ll*MAXB){
            a = rnd.nextInt(-MAXB, MAXB);
            b = rnd.nextInt(0, MAXD);
            last = 1LL*(a + 1LL * (sz-1) * b);
        }
        for (int i = 0; i < sz; ++i){
            arr.push_back(a);
            a += b;
        }
    }

    void randomAllArithmeticSeqDec(int sz, vector<int>& arr){
        int a = rnd.nextInt(-MAXB, MAXB);
        int b = rnd.nextInt(-MAXB, 0);
        long long last = 1LL*(a + 1LL * (sz-1) * b);
        while (last < 1ll*-MAXB){
            a = rnd.nextInt(-MAXB, MAXB);
            b = rnd.nextInt(0, MAXD);
            last = 1LL*(a + 1LL * (sz-1) * b);
        }
        for (int i = 0; i < sz; ++i){
            arr.push_back(a);
            a += b;
        }
    }

    void randomRange(int sz, vector<int> & L, vector<int> & R, int maks){
        for (int i = 0; i < sz; ++i){
            int l = rnd.nextInt(1, maks);
            int r = rnd.nextInt(l, maks);
            L.push_back(l);
            R.push_back(r);
        }
    }

    void randomPartialZeroDiff(int sz, vector<int>& arr){
        int a = rnd.nextInt(-MAXB, MAXB);
        arr.push_back(a);
        for (int i = 1; i < sz; ++i){
            if (rnd.nextInt(0, 1) == 0){
                arr.push_back(arr[i-1]);
            }else {
                a = rnd.nextInt(-MAXB, MAXB);
                arr.push_back(a);
            }
        }
    }

    void fullRandom(int sz, vector<int>& arr){
        pair<int,int> tmp = generateNumber(sz, -MAXB, MAXB, -MAXD, MAXD);
        int a = tmp.first;
        int b = tmp.second;
        arr.push_back(a);
        a+=b;
        arr.push_back(a);
        a+=b;
        for (int i = 0; i < sz-2; ++i){
            if (rnd.nextInt(0, 1) == 0){
                arr.push_back(a);
                a += b;
            }else {
                pair<int,int> tmp = generateNumber(sz, -MAXB, MAXB, -MAXD, MAXD);
                a = tmp.first;
                b = tmp.second;
                arr.push_back(a);
            }
        }
    }
};

