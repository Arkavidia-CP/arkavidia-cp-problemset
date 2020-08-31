#include <tcframe/spec.hpp>
using namespace tcframe;

#define sz(a) (int)(a).size()
using ll = long long;

const int MAXN = 1e5;
const int MAXSZ = 50;

class ProblemSpec : public BaseProblemSpec {
protected:
    int N;
    vector<string> S;
    string ans;

    void InputFormat() {
        LINE(N);
        LINES(S) % SIZE(N);
    }

    void OutputFormat() {
        RAW_LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(1); // jangan lupa diganti
        MemoryLimit(64); // jangan lupa diganti
    }

    void Constraints() {
        CONS(1 <= N && N <= MAXN);
        CONS(eachStringValid(S));
    }
private:
    bool eachStringValid(vector<string> S) {
        for (int i = 0; i < sz(S); i++) {
            if (!validSize(S[i])) {
                return false;
            }
            for (int j = 0; j < sz(S[i]); j++) {
                if (S[i][j] != '0' && S[i][j] != '1') {
                    return false;
                }
            }
        }
        return true;
    }

    bool validSize(string s) {
        return (1 <= sz(s) && sz(s) <= MAXSZ);
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "2",
            "0",
            "11111"
        });
        Output({
            "Tidak memiliki solusi"
        });
    }

    map<ll, bool> vis[2];
    void BeforeTestCase() {
        S.clear();
        vis[0].clear();
        vis[1].clear();
    }

    void TestCases() {
        for (int i = 1; i <= 5; i++) {
            CASE(N = 1, randomArray(i, i));
        }

        for (int i = 1; i <= 5; i++) {
            CASE(N = 10, randomArray(1, 5));
        }

        CASE(N = 1, S = {"0"});
        CASE(N = 1, S = {"1"});
        CASE(N = 2, S = {"0", "1"});
        
        for (int i = 1; i <= 10; i++) {
            int mn = rnd.nextInt(1, MAXSZ);
            int mx = rnd.nextInt(mn, MAXSZ);
            ll lo = (ll) ((ll) 1 << (mn - 1));
            ll hi = (ll) ((ll) 1 << mx);
            hi--;
            ll maxN = (hi - lo + 1) * 2;
            maxN = min(maxN, (ll)MAXN);
            CASE(N = rnd.nextInt(1, (int)maxN), randomArray(mn, mx));
        }

        for (int i = 1; i <= 5; i++) {
            CASE(N = MAXN, randomArray(MAXSZ, MAXSZ));
        }
    }
private:
    ll shift(int x) {
        return (ll) ((ll)1 << x);
    }

    string numToString(ll num, int type) {
        string ret = "";
        int startBit;
        for (int i = 49; i >= 0; i--) {
            if (shift(i) & num) {
                startBit = i;
                break;
            }
        }
        while (startBit >= 0) {
            if (shift(startBit) & num) {
                if (type == 0) {
                    ret += "0";
                } else {
                    ret += "1";
                }
            } else {
                if (type == 0) {
                    ret += "1";
                } else {
                    ret += "0";
                }
            }
            startBit--;
        }
        return ret;
    }

    string makeString(int mnSz, int mxSz, int type) {
        ll num = rnd.nextLongLong(shift(mnSz - 1), shift(mxSz) - 1);
        while (vis[type][num]) {
            num = rnd.nextLongLong(shift(mnSz - 1), shift(mxSz) - 1);
        }
        vis[type][num] = true;
        return numToString(num, type);
    }

    void randomArray(int mnSz, int mxSz) {
        ll lo = (ll) ((ll) 1 << (mnSz - 1));
        ll hi = (ll) ((ll) 1 << mxSz);
        hi--;
        ll maxN = (hi - lo + 1);
        for (int i = 0; i < N; i++) {
            int rng = rnd.nextInt(0, 1);
            if (vis[rng].size() == maxN) rng = !rng;
            S.push_back(makeString(mnSz, mxSz, rng));
        }
    }
};