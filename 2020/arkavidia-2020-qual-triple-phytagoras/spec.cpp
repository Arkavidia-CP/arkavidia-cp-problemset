#include <tcframe/spec.hpp>
#include <algorithm>
using namespace tcframe;

typedef long long ll;

const ll MAXN = 1e18;
const ll LIM = 2e6;

class ProblemSpec : public BaseProblemSpec {
protected:
    ll N, ANS;

    void InputFormat() {
        LINE(N);
    }

    void OutputFormat() {
        LINE(ANS);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(64);
    }

    void Constraints() {
        CONS(1 <= N && N <= MAXN);
        CONS(isOdd(N));
    }

private:
    bool isOdd(ll x) {
        return (x & 1);
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    vector<int> primes;
    int sz_prime;
    vector<bool> isPrime;
    map<int, vector<ll>> bigPrimes; // primes with digit >= 7. baru digit 7 - 10, 17-18
    map<ll, bool> vis;

    void SampleTestCase1() {
        Input({
            "3"
        });
        Output({
            "1"
        });
    }

    void BeforeTestCase() {
		isPrime.assign(LIM + 1, true);
		isPrime[0] = isPrime[1] = false;
		for (ll i = 2; i <= LIM; i++) {
			if (isPrime[i]) {
				primes.push_back(i);
				for (ll j = i * i; j <= LIM; j += i) {
					isPrime[j] = false;			
                }
			}
		}
        sz_prime = primes.size();

        // bigprimes.org
        bigPrimes[7] = {
            6171719,
            3721489,
            8370673,
            5995783,
            4511359
        };
        bigPrimes[8] = {
            89482979,
            99627313,
            43006319,
            89421169,
            90922369
        };
        bigPrimes[9] = {
            375817009,
            451422523,
            583261711,
            258863287,
            877582847
        };
        bigPrimes[10] = {
            6265877659,
            4881355691,
            2587800407,
            7581302759,
            8038703119
        };
        bigPrimes[17] = {
            63343274992169129,
            47146252877352841,
            22636999438935137,
            24922865713067633,
            81189988142526161,
            71652070271607377,
            22797312194041361,
            89974847561296171,
            82770485597997697,
            14173133140153553
        };
        bigPrimes[18] = {
            434962058169494329,
            770158542645541471,
            350181419397386131,
            546353091746733769,
            711081299063207953,
            216284664811929913,
            591097573201855849,
            184738237144951801,
            925755983913931259,
            214159616919506521
        };

        map<int, vector<ll>>::iterator it = bigPrimes.begin();
        while (it != bigPrimes.end()) {
            sort((it->second).begin(), (it->second).end());
            it++;
        }
    }

    void TestCases() {
        // generate
        for (int i = 0; i < 2; i++) {
            CASE(N = randomOdd(1, 100));
        }
        for (int i = 0; i < 3; i++) {
            CASE(N = randomOdd(101, 1000));
        }
        
        // large nums   
        for (int i = 0; i < 3; i++) {
            CASE(N = randomOdd(1001, 1000000000));
        }

        for (int i = 0; i < 7; i++) {
            CASE(N = randomOdd(1000000001, MAXN));
        }

        // primes (1 <= p <= 1e6)
        for (int i = 0; i < 3; i++) {
            CASE(N = primes[i + 1]);
        }
        for (int i = 0; i < 3; i++) {
            CASE(N = randomPrime(10, 100));
        }
        for (int i = 0; i < 3; i++) {
            CASE(N = randomPrime(101, 1000));
        }
        for (int i = 0; i < 5; i++) {
            CASE(N = randomPrime(1001, LIM));
        }

        // large primes
        for (int i = 0; i < 3; i++) {
            CASE(N = randomBigPrime(7));
        }
        for (int i = 0; i < 3; i++) {
            CASE(N = randomBigPrime(8));
        }
        for (int i = 0; i < 3; i++) {
            CASE(N = randomBigPrime(9));
        }
        for (int i = 0; i < 3; i++) {
            CASE(N = randomBigPrime(10));
        }
        for (int i = 0; i < 10; i++) {
            CASE(N = bigPrimes[17][i]);
        }
        for (int i = 0; i < 10; i++) {
            CASE(N = bigPrimes[18][i]);
        }
        
        // mult
        for (int i = 0; i < 3; i++) {
            CASE(N = bigPrimes[8][randomID(bigPrimes[7])] * bigPrimes[8][randomID(bigPrimes[8])]);
        }
        for (int i = 0; i < 3; i++) {
            CASE(N = bigPrimes[8][randomID(bigPrimes[8])] * bigPrimes[9][randomID(bigPrimes[8])]);
        }
        for (int i = 0; i < 3; i++) {
            CASE(N = bigPrimes[9][randomID(bigPrimes[9])] * bigPrimes[9][randomID(bigPrimes[9])]);
        }

        // other
        CASE(N = 1);

        // max
        CASE(N = MAXN - 1);
    }

private:
    ll getLimit(ll x) {
        return ((x - 2) / 2);
    }

    int randomID(vector<ll> a) {
        return rnd.nextInt(0, a.size() - 1);
    }

    ll randomOdd(ll lo, ll hi) {
        ll num = rnd.nextLongLong(lo, getLimit(hi));
        while (vis[2 * num + 1]) {
            num = rnd.nextLongLong(lo, getLimit(hi));
        }
        vis[2 * num + 1] = true;
        return (2*num + 1);
    }

    ll randomPrime(ll lo, ll hi) {
        int st = lower_bound(primes.begin(), primes.end(), lo) - primes.begin();
        int en = (upper_bound(primes.begin(), primes.end(), hi) - primes.begin()) - 1;
        int id = 1;
        st = max(st, id);
        if (st >= 1 && en < sz_prime) {
            id = rnd.nextInt(st, en);
            while (vis[primes[id]]) id = rnd.nextInt(st, en);
            vis[primes[id]] = true;
        }
        return primes[id];
    }

    ll randomBigPrime(int digit) {
        ll ret = bigPrimes[digit][randomID(bigPrimes[digit])];
        while (vis[ret]) ret = bigPrimes[digit][randomID(bigPrimes[digit])];
        vis[ret] = true;
        return ret;
    }
};