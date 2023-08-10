#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

#define MAXN 1e5
#define MAXNUM 1e9
#define MAXZ 300

class ProblemSpec: public BaseProblemSpec {
protected:
    int n,k,l,x,y,z;
    vector<int> a;
    int ans;

    void InputFormat() {
        LINE(n,k,l,x,y,z);
        LINE(a);
    }

    void OutputFormat() {
        LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(2);
        MemoryLimit(512);
    }

    void Constraints() {
        CONS(1<=n && n<=MAXN);
        CONS(1<=k && k<=MAXNUM);
        CONS(1<=l && l<=MAXNUM);
        CONS(1<=x && x<=MAXNUM);
        CONS(1<=y && y<=MAXNUM);
        CONS(1<=z && z<=MAXZ);
        CONS(eachElementBetween(a,1,MAXNUM));
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

class TestSpec: public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "6 100 2 5 50 6",
            "6 14 40 60 61 90",      
        });
        Output({
            "2"
        });
    }

    void BeforeTestCase() {
        a.clear();
    }

    void TestCases() {
        for(int i=0;i<10;i++) {
            CASE(n=20,k=100,l = rnd.nextInt(1,5),x=rnd.nextInt(1,10),y=rnd.nextInt(20,75),z=rnd.nextInt(1,10),rand_T(n,a,100));
        }
        for(int i=0;i<10;i++) {
            CASE(n=100,k=1000,l = rnd.nextInt(1,10),x=rnd.nextInt(1,100),y=rnd.nextInt(100,750),z=rnd.nextInt(1,100),rand_T(n,a,1000));
        }
        for(int i=0;i<15;i++) {
            CASE(n=rnd.nextInt(100,10000),k=MAXN,l = rnd.nextInt(1,100),x=rnd.nextInt(1,100),y=rnd.nextInt(10000,50000),z=rnd.nextInt(1,MAXZ),rand_T(n,a,MAXN));
        }
        // Case ans = -1
        for(int i=0;i<10;i++){
            CASE(n=MAXN,k=MAXNUM,l=rnd.nextInt(1,50),x=rnd.nextInt(1,50),y=MAXNUM/10,z=rnd.nextInt(MAXZ-50,MAXZ),rand_not_possible(n,a));
        }
        // Case with high possibility ans!=-1 and good variance for ans
        for(int i=0;i<10;i++) {
            CASE(n=MAXN,k=MAXNUM,l = rnd.nextInt(1,1000),x=rnd.nextInt(1,10000),y=rnd.nextInt(MAXNUM/100,MAXNUM/10),z=MAXZ,rand_T(n,a,MAXNUM));
        }
        // Case with all input set randomly to max constraint
        for(int i=0;i<5;i++) {
            CASE(n=MAXN,k=MAXNUM,l = rnd.nextInt(1,MAXN),x=rnd.nextInt(1,MAXNUM),y=rnd.nextInt(1,MAXNUM),z=MAXZ,rand_T(n,a,MAXNUM));
        }        
    }

private:
    void rand_T(int n, vector<int>& t, int maks) {
        set<int>num;
        for(int i=0;i<n;i++) {
            bool found=false;
            while(!found){
                int temp = rnd.nextInt(1,maks);
                if(num.count(temp))continue;
                found=true;
                num.insert(temp);
                t.push_back(temp);
            }
        }
        sort(t.begin(),t.end());    
    }
    void rand_not_possible(int n,vector<int>&t){
        int cur=1;
        int maxdist=500;
        for(int i=0;i<n;i++){
            int temp=rnd.nextInt(1,maxdist);
            cur+=temp;
            t.push_back(cur);
        }
    }
};