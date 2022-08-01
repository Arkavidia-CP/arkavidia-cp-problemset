#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

const int NMAX = 700;
const int CMAX = 1e6;
const int ALP = 26;
class ProblemSpec : public BaseProblemSpec
{
protected:
    int N;
    string S;
    int K;
    vector<int> C;

    int ANS;

    void InputFormat()
    {
        LINE(N);
        LINE(S);
        LINE(K);
        LINE(C % SIZE(ALP));
    }

    void OutputFormat()
    {
        LINE(ANS);
    }

    void GradingConfig()
    {
        TimeLimit(3);
        MemoryLimit(256);
    }

    void Constraints()
    {
        CONS(1 <= N && N <= NMAX);
        CONS(checkString(S, N));
        CONS(1 <= K && K <= CMAX);
        CONS(C.size() == ALP);
        CONS(eachElementBetween(C, 1, CMAX));
    }

private:
    bool eachElementBetween(const vector<int> &V, int low, int high)
    {
        for (int x : V)
        {
            if (x < low || x > high)
                return false;
        }
        return true;
    }
    bool checkString(const string& s, int n){
        if (s.size() != n) return 0;
        for (auto x : s){
            if (x < 'a' || 'z' < x) return 0;
        }
        return 1;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec>
{
protected:
    void SampleTestCase1()
    {
        Input({
            "13",
            "aaabaaabaaabc",
            "2",
            "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1"
        });
        Output({
            "7"
        });
    }

    void BeforeTestCase()
    {
        S.clear();
        C.clear();
    }

    void TestCases()
    {   
        for (int i=1;i<=3;i++){
            CASE(N = rnd.nextInt(1, NMAX), generateS(S, N, 26), generateC(C, K));
        }
        for (int i=1;i<=5;i++){
            CASE(N = NMAX, generateS(S, N, 26), generateC(C, K));
        }
        for (int i=2;i<=5;i++){
            for (int j=0;j<3;j++){
                CASE(N = NMAX, generateS(S, N, i), generateC(C, K, 1, rnd.nextInt(1, 10), 1, rnd.nextInt(1, 10)));
            }
        }
        for (int i=1;i<=3;i++){
            CASE(N = NMAX, generateS(S, N, 26), generateC(C, K, 1, 10, 1, CMAX));
        }
        for (int i=1;i<=3;i++){
            CASE(N = NMAX, generateS(S, N, 26, 1, 4, 9, 7, 50), generateC(C, K, 1, CMAX, 1, CMAX / 2));
        }
        for (int i=1;i<=3;i++){
            CASE(N = NMAX, generateS(S, N, 26, 1, 4, 9, 7, NMAX), generateC(C, K, 1, CMAX, 1, CMAX / 2));
        }
        for (int i=1;i<=3;i++){
            CASE(N = NMAX, generateS(S, N, 26, 1, 4, 9, 7, 50), generateC(C, K, CMAX / 2, CMAX, CMAX / 2, CMAX));
        }
        for (int i=1;i<=3;i++){
            CASE(N = NMAX, generateS(S, N, 26, 1, 4, 9, 7, NMAX), generateC(C, K, CMAX / 2, CMAX, CMAX / 2, CMAX));
        }
        CASE(N = 1, cornerCase1(S, N, rnd.nextInt(1, 26)), generateC(C, K));
        CASE(N = NMAX, cornerCase1(S, N, rnd.nextInt(1, 26)), generateC(C, K));
    }

private:
    string generateRandomString(int n, int dig){
        string ret;
        for (int i=1;i<=n;i++){
            ret += char(rnd.nextInt(0, dig - 1) + 'a');
        }
        return ret;
    }
    void generateS(string& s, int n, int dig, int mn = 1, int mx = 10, int mxul = 9, int mixChance = 5, int mxFrag = 100){
        int tot = 0;
        vector<string> temp;
        mxFrag = min(mxFrag, n);
        mx = min(mx, n);
        mn = min(mn, mx);
        while (tot < n){
            if (temp.size() > 1){
                int chance = rnd.nextInt(1, 10);
                if (chance <= mixChance){
                    string temp2 = temp.back();
                    temp.pop_back();
                    temp.back() += temp2;
                } else{
                    temp.push_back(generateRandomString(rnd.nextInt(mn, mx), dig));
                    tot += temp.back().size();
                }
            } else{
                temp.push_back(generateRandomString(rnd.nextInt(mn, mx), dig));
                tot += temp.back().size();
            }
            if (tot < n){
                int bates = min((n - tot) / temp.back().size(), (mxFrag - temp.back().size()) / temp.back().size());
                int ul = rnd.nextInt(0, min(mxul, bates));
                string nw = temp.back();
                while (ul--){
                    for (auto x : temp.back()){
                        nw += x;
                    }
                    tot += temp.back().size();
                }
                temp.back() = nw;
            }
        }
        for (auto x : temp){
            for (auto y : x){
                if (s.size() < n) s += y;
            }
        }
    }
    void cornerCase1(string& s, int n, int dig){
        for (int i=1;i<=n;i++){
            s += char('a' + dig - 1);
        }
    }
    void generateC(vector<int>& c, int& k, int mnc = 1, int mxc = CMAX, int mnk = 1, int mxk = CMAX){
        for (int i=1;i<=ALP;i++){
            c.push_back(rnd.nextInt(mnc, mxc));
        }
        k = rnd.nextInt(mnk, mxk);
    }
};