#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
#define ll long long
const int NMAX = 500;
const ll MATMAX = 1e18;
const ll MATMAX2 = (1LL<<59)-1; // biggest power of 2 less than 1e18 minus one
class ProblemSpec : public BaseProblemSpec
{
protected:
    int N;
    string bools;
    vector<ll> Ans;
    vector<vector<ll>> Mat;
    void InputFormat()
    {
        LINE(N);
        GRID(Mat) % SIZE(N, N);
    }

    void OutputFormat1()
    {
        RAW_LINE(bools);
        LINE(Ans % SIZE(N));
    }

    void OutputFormat2()
    {
        RAW_LINE(bools);
    }

    void GradingConfig()
    {
        TimeLimit(1);
        MemoryLimit(512);
    }

    void Constraints()
    {
        CONS(1 <= N && N <= NMAX);
        CONS(eachElementBetweenMatrix(Mat, -1, 1e18));
    }

private:
    bool eachElementBetweenMatrix(vector<vector<ll>> &V, ll low, ll high)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (V[i][j] < low || V[i][j] > high)
                    return false;
            }
        }
        return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec>
{
protected:
    void SampleTestCase1()
    {
        Input({"4",
               "0 6 -1 -1",
               "-1 0 -1 5",
               "11 -1 0 -1",
               "-1 -1 8 0"});
        Output({"YES",
                "0 6 11 3"});
    }
    void SampleTestCase2()
    {
        Input({"3",
               "0 2 0",
               "0 2 -1",
               "0 1 0"});
        Output({"NO"});
    }

    void BeforeTestCase()
    {
        Mat.clear();
        Ans.clear();
    }

    void TestCases()
    {
        // 1
        for (int i = 0; i < 5; i++)
        {
            CASE(N = 5, generateRandomArray(Mat, N, -1, 100));
        }
        for (int i = 0; i < 5; i++)
        {
            CASE(N = 50, generateRandomArray(Mat, N, -1, 100));
        }
        for (int i = 0; i < 3; i++)
        {
            CASE(N = NMAX, generateRandomArray(Mat, N, -1, MATMAX));
        }
        CASE(N = 10, generateRandomArray(Mat, N, -1, -1));
        CASE(N = NMAX, generateRandomArray(Mat, N, -1, -1));

        // 16
        for (int i = 0; i < 5; i++)
        {
            CASE(N = 5, generateRandomArrayMirror(Mat, N, 0, 100));
        }
        for (int i = 0; i < 5; i++)
        {
            CASE(N = 50, generateRandomArrayMirror(Mat, N, 0, 100));
        }
        for (int i = 0; i < 3; i++)
        {
            CASE(N = NMAX,
                 generateRandomArrayMirror(Mat, N, 0, MATMAX));
        }

        // 29
        for (int i = 0; i < 5; i++)
        {
            CASE(N = 5, generateRandomArrayMirrorYes(Mat, N, 0, 100));
        }
        for (int i = 0; i < 5; i++)
        {
            CASE(N = 50, generateRandomArrayMirrorYes(Mat, N, 0, 100));
        }
        for (int i = 0; i < 3; i++)
        {
            CASE(N = NMAX,
                 generateRandomArrayMirrorYes(Mat, N, 0, MATMAX2));
        }

        // 42
        for (int i = 0; i < 5; i++)
        {
            CASE(N = 10,
                 generateRandomArrayBolong(Mat, N, 0, 100));
        }
        for (int i = 0; i < 5; i++)
        {
            CASE(N = 10,
                 generateRandomArrayBolong(Mat, N, 0, MATMAX));
        }
        for (int i = 0; i < 3; i++)
        {
            CASE(N = NMAX,
                 generateRandomArrayBolong(Mat, N, 0, MATMAX));
        }

        // 55
        for (int i = 0; i < 5; i++)
        {
            CASE(N = 10,
                 generateRandomArrayBolongYes(Mat, N, 0, 100));
        }
        for (int i = 0; i < 5; i++)
        {
            CASE(N = 10,
                 generateRandomArrayBolongYes(Mat, N, 0, MATMAX2));
        }
        for (int i = 0; i < 3; i++)
        {
            CASE(N = NMAX,
                 generateRandomArrayBolongYes(Mat, N, 0, MATMAX2));
        }
    }

private:
    void generateRandomArray(vector<vector<ll>> &V, int n, ll low, ll high)
    {
        vector<ll> trow;
        for (int i = 0; i < n; i++)
        {
            trow.clear();
            for (int j = 0; j < n; j++)
                trow.push_back(-1);
            Mat.push_back(trow);
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                ll value = rnd.nextLongLong(low, high);
                V[i][j] = value;
            }
        }
    }
    void generateRandomArrayMirror(vector<vector<ll>> &V, int n, ll low, ll high)
    {
        V.resize(n);
        for (int i = 0; i < n; i++){
            V[i].resize(n);
            V[i][i] = rnd.nextLongLong(-1,0);
        }
        int ratio_minus_one = rnd.nextInt(1,50);
        for (int i = 0; i < n; i++){
            for (int j = 0; j < i; j++){
                long long val = rnd.nextLongLong(low,high);
                int gacha = rnd.nextInt(1,100);
                if (gacha <= ratio_minus_one) V[i][j] = -1;
                else V[i][j] = val;
                gacha = rnd.nextInt(1,100);
                if (gacha <= ratio_minus_one) V[j][i] = -1;
                else V[i][j] = val;
            }
        }
    }
    void generateRandomArrayMirrorYes(vector<vector<ll>> &V, int n, ll low, ll high)
    {
        vector<long long> ans(n);
        for (int i = 0; i < n; i++) ans[i] = rnd.nextLongLong(low,high);
        int ratio_minus_one = rnd.nextInt(1,50);
        V.resize(n);
        for (int i = 0; i < n; i++) V[i].resize(n);
        for (int i = 0; i < n; i++){
            int gacha = rnd.nextInt(0,100);
            if (gacha <= ratio_minus_one) V[i][i] = -1;
            else V[i][i] = 0;
            for (int j = 0; j < i; j++){
                gacha = rnd.nextInt(0,100);
                if (gacha <= ratio_minus_one) V[i][j] = -1;
                else V[i][j] = ans[i]^ans[j];
                gacha = rnd.nextInt(0,100);
                if (gacha <= ratio_minus_one) V[j][i] = -1;
                else V[j][i] = ans[i]^ans[j];
            }
        }
    }
    void generateRandomArrayBolong(vector<vector<ll>> &V, int n, ll low, ll high)
    {
        int ratio_minus_one = rnd.nextInt(1,50);
        V.resize(n);
        for (int i = 0; i < n; i++) V[i].resize(n);
        for (int i = 0; i < n; i++){
            int gacha = rnd.nextInt(0,100);
            if (gacha <= ratio_minus_one) V[i][i] = -1;
            else V[i][i] = 0;
            for (int j = 0; j < i; j++){
                long long val = rnd.nextLongLong(low,high);
                gacha = rnd.nextInt(0,100);
                if (gacha <= ratio_minus_one) V[i][j] = -1;
                else V[i][j] = val;
                gacha = rnd.nextInt(0,100);
                if (gacha <= ratio_minus_one) V[j][i] = -1;
                else V[j][i] = val;
            }
        }
        vector<int> bolong(n);
        for (int i = 0; i < n; i++) bolong[i] = i;
        rnd.shuffle(bolong.begin(),bolong.end());
        int cnt_bolong = rnd.nextInt(1,n/2);
        for (int i = 0; i < cnt_bolong; i++){
            for (int c = 0; c < n; c++) V[bolong[i]][c] = -1;
            for (int r = 0; r < n; r++) V[r][bolong[i]] = -1;
        }
    }
    void generateRandomArrayBolongYes(vector<vector<ll>> &V, int n, ll low, ll high)
    {
        vector<long long> ans(n);
        for (int i = 0; i < n; i++) ans[i] = rnd.nextLongLong(low,high);
        int ratio_minus_one = rnd.nextInt(1,50);
        V.resize(n);
        for (int i = 0; i < n; i++) V[i].resize(n);
        for (int i = 0; i < n; i++){
            int gacha = rnd.nextInt(0,100);
            if (gacha <= ratio_minus_one) V[i][i] = -1;
            else V[i][i] = 0;
            for (int j = 0; j < i; j++){
                gacha = rnd.nextInt(0,100);
                if (gacha <= ratio_minus_one) V[i][j] = -1;
                else V[i][j] = ans[i]^ans[j];
                gacha = rnd.nextInt(0,100);
                if (gacha <= ratio_minus_one) V[j][i] = -1;
                else V[j][i] = ans[i]^ans[j];
            }
        }
        vector<int> bolong(n);
        for (int i = 0; i < n; i++) bolong[i] = i;
        rnd.shuffle(bolong.begin(),bolong.end());
        int cnt_bolong = rnd.nextInt(1,n/2);
        for (int i = 0; i < cnt_bolong; i++){
            for (int c = 0; c < n; c++) V[bolong[i]][c] = -1;
            for (int r = 0; r < n; r++) V[r][bolong[i]] = -1;
        }
    }
};