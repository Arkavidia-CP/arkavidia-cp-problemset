/* Author: Jauhar Wibisono
 *
 */

#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

// ganti constraintnya kalau mau
const int minn = 1, maxn = 17, minab = 1, maxab = 1000000000;

class ProblemSpec : public BaseProblemSpec {
protected:
    int n;
    vector<int> k, a, b;
    long long ans;

	void InputFormat() {
        LINE(n);
        LINES(k, a, b) % SIZE(1<<n);
	}

    void OutputFormat() {
    	LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(minn <= n && n <= maxn);
        CONS(isPermutation(k));
        CONS(eachElementBetween(a, minab, maxab));
        CONS(eachElementBetween(b, minab, maxab));
    }

private:
    bool isPermutation(vector<int> v){
        sort(v.begin(), v.end());
        for (int i=0; i<(int)v.size(); i++) {
            if (v[i] != i+1) return false;
        }
        return true;
    }

    bool eachElementBetween(vector<int> v, int mn, int mx) {
        for (int x : v) {
            if (x < mn || x > mx) return false;
        }
        return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "2",
            "1 2 1",
            "3 4 4",
            "4 2 1",
            "2 4 1"
        });
        Output({
        	"19"
        });
    }

    void SampleTestCase2() {
        Input({
            "1",
            "2 1 1",
            "1 1 1"
        });
        Output({
            "2"
        });
    }

    void SampleTestCase3() {
        Input({
            "3",
            "5 5 7",
            "3 5 1",
            "2 1 9",
            "1 4 7",
            "6 5 9",
            "7 8 2",
            "8 9 8",
            "4 1 2"
        });
        Output({
            "81"
        });
    }

    void BeforeTestCase(){
    	k.clear();
        a.clear();
        b.clear();
    }

    void TestCases() {
        CASE(n = 1, k = {1, 2}, a = {1, 1}, b = {1, 1}); // smallest answer
        for (int i=0; i<20; i++) CASE(n = rnd.nextInt(minn, 5), generateRandomTeams(n, k, a, b));
        CASE(n = maxn, generateBigAnswer(n, k, a, b)); // biggest answer
        for (int i=0; i<3; i++) CASE(n = min(maxn/2+i, maxn), generateRandomTeams(n, k, a, b));
        for (int i=0; i<2; i++) CASE(n = maxn, generateRandomTeams(n, k, a, b));
    }

private:
    void generateRandomTeams(int n, vector<int> &k, vector<int> &a, vector<int> &b){
        k.resize(1<<n); a.resize(1<<n); b.resize(1<<n);
        for (int i=0; i<(1<<n); i++) {
            k[i] = i+1;
            a[i] = rnd.nextInt(minab, maxab);
            b[i] = rnd.nextInt(minab, maxab);
        }

        rnd.shuffle(k.begin(), k.end());
    }

    void generateBigAnswer(int n, vector<int> &k, vector<int> &a, vector<int> &b){
        k.resize(1<<n); a.resize(1<<n); b.resize(1<<n);
        for (int i=0; i<(1<<n); i++) {
            k[i] = i+1;
            a[i] = maxab;
            b[i] = maxab;
        }
    }
};