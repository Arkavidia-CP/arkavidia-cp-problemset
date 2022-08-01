#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;

const int NMAX = 1e5;
const long long VMAX = 1e9;
class ProblemSpec : public BaseProblemSpec
{
protected:
    int N;
    vector<long long> VecA, VecB;
    long long Res;

    void InputFormat()
    {
        LINE(N);
        LINE(VecA % SIZE(N));
        LINE(VecB % SIZE(N));
    }

    void OutputFormat()
    {
        LINE(Res);
    }

    void GradingConfig()
    {
        TimeLimit(2);
        MemoryLimit(64);
    }

    void Constraints()
    {
        CONS(1 <= N && N <= NMAX);
        CONS(eachElementBetween(VecA, 1, VMAX));
        CONS(eachElementBetween(VecB, 1, VMAX));
    }

private:
    bool eachElementBetween(vector<long long> &V, long long low, long long high)
    {
        for (long long x : V)
        {
            if (x < low || x > high)
                return false;
        }
        return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec>
{
protected:
    void SampleTestCase1()
    {
        Input({
            "4",
            "1 2 3 4",
            "8 7 6 5",
        });
        Output({"0"});
    }

    void BeforeTestCase()
    {
        VecA.clear();
        VecB.clear();
    }

    void TestCases()
    {
        CASE(N = 5, generateRandomArray(VecA, N, 1, 10000), generateRandomArray(VecB, N, 1, 10000));
        CASE(N = 50, generateRandomArray(VecA, N, 1, 10000), generateRandomArray(VecB, N, 1, 10000));
        CASE(N = 200, generateRandomArray(VecA, N, 1, 10000), generateRandomArray(VecB, N, 1, 10000));
        for (int i = 0; i < 5; i++){
            CASE(N = 200, generateRandomArrayWithDuplicates(VecA, VecB, N, N, N, 1, 10000));
            CASE(N = 200, generateRandomArrayWithDuplicates(VecA, VecB, N, 1, N/2, 1, N/2));
        }
        for (int i = 0; i < 5; i++)
        {
            CASE(N = rnd.nextInt(1000, NMAX),
                 generateRandomArray(VecA, N, 1, VMAX),
                 generateRandomArray(VecB, N, 1, VMAX));
        }
        for (int i = 0; i < 10; i++)
        {
            CASE(N = NMAX,
                 generateRandomArray(VecA, N, 1, VMAX),
                 generateRandomArray(VecB, N, 1, VMAX));
        }
        for (int i = 0; i < 10; i++)
        {
            CASE(N = NMAX,
                 generateRandomArray(VecA, N, VMAX / 2, VMAX),
                 generateRandomArray(VecB, N, VMAX / 2, VMAX));
        }
        for (int i = 0; i < 1; i++) {
            CASE(N = NMAX, generateSameArray(VecA, N, VMAX), generateSameArray(VecB, N, VMAX));
            CASE(N = NMAX, generateRandomArrayWithDuplicates(VecA, VecB, N, N, N, VMAX, VMAX));
        }
        for (int i = 0; i < 5; i++){
            CASE(N = NMAX, generateRandomArrayWithDuplicates(VecA, VecB, N, N, N, 1, VMAX));
            CASE(N = NMAX, generateRandomArrayWithDuplicates(VecA, VecB, N, 1, N/2, 1, N/2));
        }
        CASE(N = 5, VecA = {5,5,5,7,8}, VecB = {1,1,1,3,2});
    }

private:
    void generateRandomArray(vector<long long> &V, int n, long long low, long long high)
    {
        for (int i = 0; i < n; i++)
        {
            long long value = rnd.nextLongLong(low, high);
            V.emplace_back(value);
        }
    }
    void generateSameArray(vector<long long> &V, int n, long long x) {
        for (int i = 0; i < n; i++) {
            V.emplace_back(x);
        }
    }
    void generateRandomArrayWithDuplicates(vector<long long> &a, vector<long long> &b, int n, int size_low, int size_high, long long low, long long high){
        while (a.size() < n){
            int gacha_size = rnd.nextInt(size_low, size_high);
            long long gacha_a = rnd.nextLongLong(low, high);
            long long gacha_b = rnd.nextLongLong(low, high);
            for (int i = 0; a.size() < n && i < gacha_size; i++){
                a.push_back(gacha_a);
                b.push_back(gacha_b);
            }
        }
    }
};