#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;

const int NMAX = 1e5;
const int QMAX = 1e5;
const int LRMAX = 1e7;
class ProblemSpec : public BaseProblemSpec
{
protected:
    int N, Q;
    vector<int> Vec, L, R;
    vector<long long> Res;

    void InputFormat()
    {
        LINE(N);
        LINE(Vec % SIZE(N));
        LINE(Q);
        LINES(L, R) % SIZE(Q);
    }

    void OutputFormat()
    {
        LINES(Res) % SIZE(Q);
    }

    void GradingConfig()
    {
        TimeLimit(2);
        MemoryLimit(64);
    }

    void Constraints()
    {
        CONS(1 <= N && N <= NMAX);
        CONS(1 <= Q && Q <= QMAX);
        CONS(eachElementBetween(Vec, 1, LRMAX));
        CONS(eachElementBetween(L, 0, LRMAX));
        CONS(eachElementBetween(R, 0, LRMAX));
        CONS(checkQueries(L, R));
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
    bool checkQueries(const vector<int>& l, const vector<int>& r){
        int len = l.size();
        if (len != r.size()) return 0;
        for (int i=0;i<len;i++){
            if (l[i] > r[i]) return 0;
        }
        return 1;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec>
{
protected:
    void SampleTestCase1()
    {
        Input({"3",
               "1 5 9",
               "2",
               "1 2",
               "2 19"});
        Output({"2",
                "4"});
    }

    void BeforeTestCase()
    {
        Vec.clear();
        L.clear();
        R.clear();
        Res.clear();
    }

    void TestCases()
    {
        CASE(N = 5, Q = 5, generateTC(Vec, L, R, N, Q, 1, 1000));
        CASE(N = 50, Q = 50, generateTC(Vec, L, R, N, Q, 1, 1000));
        CASE(N = 200, Q = 150, generateTC(Vec, L, R, N, Q, 1, 1000));
        for (int i = 0; i < 5; i++)
        {
            CASE(N = rnd.nextInt(1000, NMAX), Q = QMAX, generateTC(Vec, L, R, N, Q));
        }
        for (int i = 0; i < 15; i++)
        {
            CASE(N = NMAX, Q = QMAX, generateTC(Vec, L, R, N, Q));
        }
        for (int i = 0; i < 5; i++)
        {
            CASE(N = NMAX, Q = QMAX, generateTC(Vec, L, R, N, Q, 1000, 100000, 0, 1000000, 10));
            CASE(N = NMAX, Q = QMAX, generateTC(Vec, L, R, N, Q, 1000, 100000, 0, 1000000, 0));
        }
        
        // CASE(N = 5, Q = 5, generateRandomArray(Vec, N, 1, 1000), generateLR(L, R, Q, 1, 100));
        // CASE(N = 50, Q = 50, generateRandomArray(Vec, N, 1, 1000), generateLR(L, R, Q, 1, 100));
        // CASE(N = 200, Q = 150, generateRandomArray(Vec, N, 1, 1000), generateLR(L, R, Q, 1, 100));
        // for (int i = 0; i < 5; i++)
        // {
        //     CASE(N = rnd.nextInt(1000, NMAX),
        //          Q = rnd.nextInt(1000, QMAX),
        //          generateRandomArray(Vec, N, 1, LRMAX),
        //          generateLR(L, R, Q, 1, 100));
        // }
        // for (int i = 0; i < 20; i++)
        // {
        //     CASE(N = NMAX,
        //          Q = QMAX,
        //          generateRandomArray(Vec, N, 1, LRMAX),
        //          generateLR(L, R, Q, 1, 100));
        // }
        // for (int i = 0; i < 10; i++)
        // {
        //     CASE(N = NMAX,
        //          Q = QMAX,
        //          generateRandomArray(Vec, N, LRMAX / 2, LRMAX),
        //          generateLR(L, R, Q, 1, LRMAX));
        // }
    }

private:
    void generateTC(vector<int>& vec, vector<int>& L, vector<int>& R, int n, int q, int a = 1, int b = LRMAX, int base_a = 0, int base_b = 1e7, int odd = 7){
        int base = rnd.nextInt(base_a, base_b);
        int fpb = rnd.nextInt(a, b);
        int sisa = LRMAX - base + 1;
        int pil = (sisa - 1) / fpb;

        for (int i=0;i<n;i++){
            int temp = base + rnd.nextInt(0, pil) * fpb;
            vec.push_back(temp);
        }
        for (int i=0;i<q;i++){
            int chance = rnd.nextInt(1, 10);
            int range;
            if (chance <= odd){ // r - l + 1 < fpb
                int sq = sqrt(fpb);
                int chance2 = rnd.nextInt(0, 2);
                if (chance2 < 2){
                    range = rnd.nextInt(1, max(sq, 1));
                } else{
                    range = rnd.nextInt(min(sq + 1, max(fpb - 1, 1)), max(fpb - 1, 1));
                }
            } else{
                range = rnd.nextInt(fpb, LRMAX + 1);
            }
            int l = rnd.nextInt(0, LRMAX - range + 1);
            int r = l + range - 1;
            L.push_back(l);
            R.push_back(r);
        }
    }
    // void generateRandomArray(vector<int> &V, int n, int low, int high)
    // {
    //     for (int i = 0; i < n; i++)
    //     {
    //         int value = rnd.nextInt(low, high);
    //         V.emplace_back(value);
    //     }
    // }
    // void generateLR(vector<int> &L, vector<int> &R, int n, int low, int high)
    // {
    //     for (int i = 0; i < n; i++)
    //     {
    //         int value = rnd.nextInt(low, high);
    //         L.emplace_back(value);
    //     }
    //     for (int i = 0; i < n; i++)
    //     {
    //         int value = rnd.nextInt(low, high);
    //         R.emplace_back(value);
    //     }
    // }
};