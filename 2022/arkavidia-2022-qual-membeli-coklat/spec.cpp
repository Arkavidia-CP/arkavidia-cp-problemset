#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

struct DSU{
    vector<int> link, size;
    int n;
    int component;
    DSU(int length){
        n = length;
        component = length;
        link = vector<int>(n+1);
        size = vector<int>(n+1, 1);
        for (int i = 1; i <= n; i++) link[i] = i;
    }
    
    int find(int x){ // O(log(n))
        int temp=x; 
        while(x!=link[x])x=link[x]; 
        link[temp]=x; 
        return x;
    }

    void unite(int a,int b){ // O(log(n))
        a=find(a); 
        b=find(b);
        if(a==b)return; 
        if(size[a]<size[b])swap(a,b); 
        size[a]+=size[b]; 
        link[b]=a; 
        component--;
    }
};

class ProblemSpec : public BaseProblemSpec {
protected:
    const int NMAX = 1e5;
    const int AMAX = 1e9;
    int N, root;
    vector<int> value;
    vector<int> edgesA;
    vector<int> edgesB;

    vector<int> ans;
    void InputFormat() {
        LINE(N, root);
        LINE(value % SIZE(N));
        LINES(edgesA, edgesB) % SIZE(N-1);
    }

    void OutputFormat1() {
        LINE(ans % SIZE(N));
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(1 <= N <= NMAX);
        CONS(1 <= root <= N);
        CONS(value_cons(value));
        CONS(edges_cons(edgesA, edgesB));
    }

private:
    bool value_cons(vector<int> value){
        if(value.size() != N)return false;
        int pos = 1;
        for(int val : value){
            if(val > AMAX || val < 0)pos = 0;
        }
        return pos;
    }

    bool edges_cons(vector<int> edgesA, vector<int> edgesB){
        if(edgesA.size() != N-1 && edgesB.size() != edgesA.size())return false;
        DSU comps(N);
        for(int i=0;i<N-1;i++){
            int a = edgesA[i];
            int b = edgesB[i];
            if(a < 1 || a > N || b < 1 || b > N)return 0;
            if(comps.find(a) == comps.find(b)){
                return 0;
            }
            comps.unite(a,b);
        }
        return 1;        
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:

    void SampleTestCase() {
        Input({
            "5 3",
            "90 99 5 1 8",
            "1 2",
            "2 3",
            "3 4",
            "4 5"
        });
        Output({
            "5 5 5 1 1"
        });
    }

    void BeforeTestCase(){
        value.clear();
        edgesA.clear();
        edgesB.clear();
    }

    void TestCases() {
        CASE(N = 1, root = 1, random_value(value, 1000, N)); // edge case only one node
        for(int i=0;i<10;i++)CASE(N = 100, root = rnd.nextInt(1,N), random_value(value, 1000, N), random_tree(N, edgesA, edgesB));
        for(int i=0;i<10;i++)CASE(N = 1000, root = rnd.nextInt(1,N), random_value(value, AMAX, N), random_tree(N, edgesA, edgesB));
        for(int i=0;i<10;i++)CASE(N = NMAX, root = rnd.nextInt(1,N), random_value(value, AMAX, N), random_tree(N, edgesA, edgesB));
        for(int i=0;i<10;i++)CASE(N = NMAX, root = 1, random_value(value, AMAX, N), tree_line(N, edgesA, edgesB));
        for(int i=0;i<10;i++)CASE(N = NMAX, root = 1, random_value(value, AMAX, N), tree_star(N, edgesA, edgesB));
    }

private:
    void random_value(vector<int>& value, int maxn, int n){
        for(int i=0;i<n;i++){
            value.push_back(rnd.nextInt(1, maxn));
        }
    }
    void random_tree(int n, vector<int>& edgesA, vector<int>& edgesB){
        DSU container(n);
        for(int i=1;i<n;i++){
            int a,b;
            do{
                a = rnd.nextInt(1, n);
                b = rnd.nextInt(1, n);
            }while(container.find(a) == container.find(b));
            // edges.push_back(make_pair(a,b));
            edgesA.push_back(a);
            edgesB.push_back(b);
            container.unite(a,b);
        }
    }
    void tree_star(int n, vector<int>& edgesA, vector<int>& edgesB){
        for(int i=2;i<=n;i++){
            // edges.push_back(make_pair(1,i));
            edgesA.push_back(1);
            edgesB.push_back(i);
        }
    }
    void tree_line(int n, vector<int>& edgesA, vector<int>& edgesB){
        vector<int> permut(n);
        for(int i=0;i<n;i++)permut[i] = i + 1;
        random_shuffle(permut.begin(), permut.end());
        for(int i=1;i<n;i++){
            // edges.push_back(make_pair(permut[i], permut[i-1]));
            edgesA.push_back(permut[i]);
            edgesB.push_back(permut[i-1]);
        }
    }
};
