#include <tcframe/spec.hpp>
#include <bits/stdc++.h>

using namespace std;
using namespace tcframe;

typedef int LL;

const int MAXN = 2000;
const LL MAXB = 1e9;

class ProblemSpec : public BaseProblemSpec{
    protected:
        int n, l, r;
        vector<LL> x, y;
        LL ans;

        void InputFormat(){
            LINE(n, l, r);
            LINES(x, y) % SIZE(n);
        }

        void OutputFormat(){
            LINE(ans);
        }

        void GradingConfig(){
            TimeLimit(1);
            MemoryLimit(64);
        }

        void Constraints(){
            CONS(1 <= n && n <= MAXN);
            CONS(eachElementBetween(x, -MAXB, MAXB));
            CONS(eachElementBetween(y, -MAXB, MAXB));
            CONS(-MAXB <= l && l <= MAXB);
            CONS(-MAXB <= r && r <= MAXB);
            CONS(l <= r);
            CONS(validY(y));
            CONS(validXY(x, y));
        }

    private:
        bool eachElementBetween(const vector<LL> &a, LL l, LL r){
            for (LL x : a){
                if (x < l || x > r) return false;
            }
            return true;
        }

        bool validY(const vector<LL> & y){
            for (LL x : y){
                if (x == 0) return false;
            }
            return true;
        }

        bool validXY(const vector<LL> & x, const vector<LL> &y){
            int n = (int)x.size();
            for (int i = 0; i < n; ++i){
                for (int j = i+1; j < n; ++j){
                    if (x[i] == x[j] && y[i] == y[j]){
                        return false;
                    }
                }
            }
            return true;
        }
       
};

class TestSpec : public BaseTestSpec<ProblemSpec>{
    protected:
        void BeforeTestCase(){
            x.clear();
            y.clear();
        }

        void TestCases(){
            CASE(n = 2, l = 2, r = 5, x = {2, 5}, y = {3, -5});
            CASE(n = 5, l = 3, r = 10, x = {2, 4, 5, 6, 100}, y = {-3, 2, -5, -6, 6});
            for (int i = 0; i < 5; ++i){
                CASE(
                    n = rnd.nextInt(1, 10),
                    l = rnd.nextInt(-MAXB, MAXB),
                    r = rnd.nextInt(l, MAXB),
                    generateRandom(n, x, y)
                );
            }
            for (int i = 0; i < 3; ++i){
                CASE(
                    n = rnd.nextInt(10+1, 100),
                    l = rnd.nextInt(-MAXB, MAXB),
                    r = rnd.nextInt(l, MAXB),
                    generateRandom(n, x, y)
                );
            }
            for (int i = 0; i < 3; ++i){
                CASE(
                    n = rnd.nextInt(100+1, 1000),
                    l = rnd.nextInt(-MAXB, MAXB),
                    r = rnd.nextInt(l, MAXB),
                    generateRandom(n, x, y)
                );
            }
            for (int i = 0; i < 5; ++i){
                CASE(
                    n = rnd.nextInt(1000+1, MAXN),
                    l = rnd.nextInt(-MAXB, MAXB),
                    r = rnd.nextInt(l, MAXB),
                    generateRandom(n, x, y)
                );
            }
        }

    private:
        bool isMember(const vector<LL> &arr, LL bil){
            for (LL x : arr){
                if (x == bil){
                    return true;
                }
            }
            return false;
        }

        void generateRandom(const int &n, vector<LL> &x, vector<LL> &y){
            for (int i = 0; i < n; ++i){
                x.push_back(rnd.nextInt(-MAXB, MAXB));
            }
            sort(x.begin(), x.end());
            y.push_back(rnd.nextInt(-MAXB, MAXB));
            for (int i = 1; i < n; ++i){
                int cy = rnd.nextInt(-MAXB, MAXB);
                while (isMember(y, cy)){
                    cy = rnd.nextInt(-MAXB, MAXB);
                }
                y.push_back(cy);
            }
            for (int i = 0; i < 100; ++i){
                rnd.shuffle(x.begin(), x.end());
                rnd.shuffle(y.begin(), y.end());
            }
        }

        
};