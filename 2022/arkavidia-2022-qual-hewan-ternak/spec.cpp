#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:

    int N;
    const int maxN = 5000;
    const int maxCoor = 1000000000;
    vector<int> x,y;
    double area1,area2;
    void InputFormat() {
        LINE(N);
        LINES(x,y)%SIZE(N);
    }

    void OutputFormat() {
        LINE(area1,area2);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(4 <= N && N <= 5000);
        CONS(eachElementBetween(x,-maxCoor,maxCoor));
        CONS(eachElementBetween(y,-maxCoor,maxCoor));
        CONS(noDuplicate(x,y));
        CONS(notAllInline(x,y));
    }
private:
    bool eachElementBetween(vector<int> arr, int MIN, int MAX){
        for(int i=0;i<arr.size();i++){
            if(arr[i] < MIN || MAX < arr[i]) return false;
        }
        return true;
    }
    bool noDuplicate(vector<int> x, vector<int> y){
        for (int i = 0;i < x.size()-1;i++){
            for (int j = i+1;j < x.size();j++){
                if (x[i] == x[j] && y[i] == y[j]){
                    return false;
                }
            }
        }
        return true;
    }
    bool notAllInline(vector<int> x, vector<int> y){
        int a1,b1;
        a1 = y[1]-y[0];
        b1 = x[1]-x[0];
        for (int i = 2;i < x.size();i++){
            int a2,b2;
            a2 = y[i]-y[0];
            b2 = x[i]-x[0];
            if (a1 * b2 != a2 * b1){
                return true;
            }
        }
        return false;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "15",
            "-4 -1",
            "-3 1",
            "-3 3",
            "-2 2",
            "-2 -3",
            "-1 -1",
            "-1 3",
            "0 -4",
            "1 -2",
            "1 0",
            "1 2",
            "1 4",
            "2 3",
            "3 1",
            "4 -1"
        });
        Output({
            "20.500 21.000"
        });
    }
    
    void BeforeTestCase() {
        x.clear();
        y.clear();
    }

    void TestCases(){
        CASE(N = 4, randomPoints(N,x,y,-10,10));
        CASE(N = 100, randomPoints(N,x,y,-100,100));
        CASE(N = 5000, randomPoints(N,x,y,-10000,10000));
        CASE(N = 100, randomPoints(N,x,y,-maxCoor,maxCoor));
        CASE(N = 5000, randomPoints(N,x,y,-maxCoor,maxCoor));
        CASE(N = 16, randomCorner(N,x,y,0,0));
        CASE(N = 100, randomCorner(N,x,y,0,0));
        CASE(N = 5000, randomCorner(N,x,y,0,0));
        CASE(N = 5000, randomCorner(N,x,y,-maxCoor,-maxCoor));
        for (int i = 0;i < 11;i++){
            CASE(N = rnd.nextInt(4,maxN), randomPoints(N,x,y,rnd.nextInt(-maxCoor,maxCoor),rnd.nextInt(-maxCoor,maxCoor)));
        }
        for (int i = 0;i < 10;i++){
            CASE(N = rnd.nextInt(8,maxN), randomCorner(N,x,y,rnd.nextInt(-maxCoor,maxCoor),rnd.nextInt(-maxCoor,maxCoor)));
        }
    }

private:
    void randomPoints(int N, vector<int> &x, vector<int> &y, int MIN, int MAX){
        if (MIN > MAX) swap(MIN,MAX);
        for (int i = 0;i < N;i++){
            x.push_back(rnd.nextInt(MIN,MAX));
            y.push_back(rnd.nextInt(MIN,MAX));
        }
    }
    void randomCorner(int N, vector<int> &x, vector<int> &y, int x1, int y1){
        x.push_back(x1);
        y.push_back(y1);
        int ver = rnd.nextInt(2,N-3);
        int hor = rnd.nextInt(2,N-1-ver);
        for (int i = 0;i < ver;i++){
            x.push_back(x1);
            y.push_back(rnd.nextInt(y1+1,maxCoor));
        }
        for (int i = 0;i < hor;i++){
            x.push_back(rnd.nextInt(x1+1,maxCoor));
            y.push_back(y1);
        }
        for (int i = 0;i < N-hor-ver-1;i++){
            x.push_back(rnd.nextInt(x1+1,maxCoor));
            y.push_back(rnd.nextInt(y1+1,maxCoor));
        }
    }
};