#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;

const int NMax = 100;
const int HMax = 2e6;
const long long INF = 1e18;

class ProblemSpec : public BaseProblemSpec {
protected:
    int N;
	vector<int> H;
	long long K;
	long long res;

    void InputFormat() {
        LINE(N);
		LINE(H % SIZE(N));
		LINE(K);
    }

    void OutputFormat() {
        LINE(res);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(64);
    }

    void Constraints() {
        CONS(1 <= N && N <= NMax);
		CONS(eachElementBetween(H, 2, HMax));
		CONS(1 <= K && K <= INF);
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
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
	vector<int> primes;
	int lenPrimes;
	vector<bool> isPrime;
	
    void SampleTestCase1() {
        Input({
            "2",
			"2 3",
			"9"
        });
        Output({
            "6"
        });
    }
	
	void BeforeTestCase() {
		H.clear();
		isPrime.assign(HMax + 1, true);
		isPrime[1] = false;
		for (long long i = 2; i <= HMax; i++) {
			if (isPrime[i]) {
				primes.push_back(i);
				for (long long j = i * i; j <= HMax; j += i)
					isPrime[j] = false;			
			}
		}
		lenPrimes = (int) primes.size() - 1;
	}	

    void TestCases() {
        CASE(N = 2, H = {2, 3}, K = 9);
		CASE(N = 1, H = {2}, K = 64);
		CASE(N = 3, H = {3, 5, 7}, K = 21);
		CASE(N = 1, H = {3}, K = 3);
		CASE(N = 2, H = {2, 3}, K = 3);
		for (int i = 0; i < 5; i++) {
			CASE(N = rnd.nextInt(1, 50), randomPrimes(N, rnd.nextInt(1, 999), H), K = randomK(rnd.nextInt(1, 15), H));
		}
		for (int i = 0; i < 5; i++) {
			CASE(N = rnd.nextInt(50 + 1, NMax), randomPrimes(N, rnd.nextInt(1000, 100000), H), K = randomK(rnd.nextInt(16, 62), H));
		}
		for (int i = 0; i < 3; i++) {
			CASE(N = NMax, randomPrimes(N, lenPrimes, H), K = randomK(63, H));
		}
		CASE(N = 2, H = {2, 5}, K = INF);
		CASE(N = 5, H = {2, 3, 5, 7, 11}, K = INF);
    }

private:
    void randomPrimes(const int & N, int num, vector<int> & H) {
		num = max(num, N + 5);
		assert(num <= lenPrimes);
		map<int, int> mp;
		for (int i = 0; i < N; i++) {
			int cur = primes[rnd.nextInt(0, num)];
			while (mp.find(cur) != mp.end()) cur = primes[rnd.nextInt(0, num)];
			mp[cur]++;
			H.push_back(cur);
		}
        sort(H.begin(), H.end());
    }

	long long randomK(int num, const vector<int> & H) {
		assert(63 >= num && num >= 1);
		long long K = 1;		
		for (int i = 0; i < num; i++) {
			long long cur = H[rnd.nextInt(0, (int) H.size() - 1)];			
			if (K >= INF / cur) break;
			K *= cur;
		}
		return K;
	}
};

