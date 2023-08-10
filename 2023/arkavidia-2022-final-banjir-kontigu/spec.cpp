#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

const int minn = 1;
const int maxn = 100000;
const int minm = 0;
const int maxm = 100000;
const int minq = 1;
const int maxq = 100000;
const long long mina = 1;
const long long maxa = 1000000000;

class ProblemSpec : public BaseProblemSpec {
protected:
	int n, m, q;
    vector<long long> a;
    vector<int> u, v;
    vector<int> t, x, y;
    vector<long long> ans;

	void InputFormat() {
        LINE(n, m, q);
        LINE(a % SIZE(n));
        LINES(u, v) % SIZE(m);
        LINES(t, x, y) % SIZE(q);
	}

    void OutputFormat() {
    	LINES(ans);
    }

    void GradingConfig() {
        TimeLimit(3);
        MemoryLimit(512);
    }

    void Constraints() {
        CONS(minn <= n && n <= maxn);
        CONS(minm <= m && m <= min(1LL*n*(n-1)/2, 1LL*maxm));
        CONS(minq <= q && q <= maxq);
        CONS(eachElementBetween(a, mina, maxa));
        CONS(validGraph(n, u, v));
        CONS(validQueries(n, t, x, y, mina, maxa));
    }

private:
    bool eachElementBetween(vector<long long> v, long long a, long long b){
        for(int i = 0; i < v.size(); i++){
            if(v[i] < a || v[i] > b)
                return false;
        }
        return true;
    }
    bool validGraph(int n, vector<int> u, vector<int> v) {
        if (u.size() != v.size()) return false;
        set<pair<int, int>> uv;
        for (int i=0; i<(int)u.size(); i++) {
            if (u[i] == v[i]) return false;
            auto p = make_pair(u[i], v[i]);
            if (uv.count(p)) return false;
            uv.insert(p);
            swap(p.first,p.second);
            uv.insert(p);
        }
        return true;
    }
    bool validQueries(int n, vector<int> t, vector<int> x, vector<int> y, int mny, int mxy) {
        bool ada = false;
        if (t.size() != x.size() || t.size() != y.size()) return false;
        for (int i=0; i<(int)t.size(); i++) {
            if (t[i] == 1) {
                if (x[i] < 1 || x[i] > n || y[i] < mny || y[i] > mxy) {
                    return false;
                }
            } else {
                ada = true;
                if (x[i] > y[i] || x[i] < 1 || y[i] > n) {
                    return false;
                }
            }
        }
        return ada;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
        	"8 6 5",
            "8 7 6 5 4 3 2 1",
            "3 4",
            "6 4",
            "3 7",
            "8 5",
            "6 3",
            "1 8",
            "2 3 4",
            "2 1 7",
            "1 7 7",
            "2 1 7",
            "2 1 2"
        });
        Output({
        	"0",
            "9",
            "10",
            "7"
        });
    }

    void BeforeTestCase(){
    	a.clear();
        u.clear();
        v.clear();
        t.clear();
        x.clear();
        y.clear();
        ans.clear();
    }

    void TestCases() {
        // ans = 1, 2
        CASE(n = 1, m = 0, q = 3, a = {1}, u = {}, v = {}, t = {2, 1, 2}, x = {1, 1, 1}, y = {1, 2, 1});
        // ans = 1, 1, 0
        CASE(n = 2, m = 1, q = 4, a = {1, 1}, u = {1}, v = {2}, t = {2, 1, 2, 2}, x = {1, 1, 1, 1}, y = {2, 2, 2, 1});
        // tc kecil, bisa dicek pake tangan
        for (int i=0; i<2; i++) {
            CASE(
                n = rnd.nextInt(minn, 10), 
                m = rnd.nextInt(minm, n*(n-1)/2), 
                q = rnd.nextInt(minq, 10), 
                randomArray(n, a, mina, 10), 
                randomGraph(n, m, u, v), 
                randomQueries(n, q, t, x, y, 1, 1, mina, 10)
            );
        }
        for (int i=0; i<8; i++) {
            CASE(
                n = 10, 
                q = 10, 
                randomArray(n, a, mina, 10),
                segmentedGraph(n, m, u, v, i/2+1), 
                randomQueries(n, q, t, x, y, 1, 1, mina, 10)
            );
        }
        // O(NQ)
        for (int i=0; i<2; i++) {
            CASE(
                n = 1000, 
                m = rnd.nextInt(minm, 1000), 
                q = 1000,
                randomArray(n, a, mina, maxa), 
                randomGraph(n, m, u, v), 
                randomQueries(n, q, t, x, y, 1, 1, mina, maxa)
            );
        }
        for (int i=0; i<2; i++) {
            CASE(
                n = 1000, 
                q = 1000,
                randomArray(n, a, mina, maxa), 
                segmentedGraph(n, m, u, v, 200), 
                randomQueries(n, q, t, x, y, 1, 1, mina, maxa)
            );
        }
        // max ans
        CASE(n = maxn, m = 0, q = 1, a = vector<long long>(n, maxa), u = {}, v = {}, t = {2}, x = {1}, y = {n});
        // O(Q log^2 N)
        CASE(
            n = maxn, 
            m = maxm, 
            q = maxq, 
            randomArray(n, a, mina, maxa),
            randomGraph(n, m, u, v), 
            randomQueries(n, q, t, x, y, 1, 1, mina, maxa)
        );
        CASE(
            n = maxn, 
            m = n, 
            q = maxq, 
            randomArray(n, a, mina, maxa),
            randomGraph(n, m, u, v), 
            randomQueries(n, q, t, x, y, 1, 1, mina, maxa)
        );
        CASE(
            n = maxn, 
            q = maxq,
            randomArray(n, a, mina, maxa), 
            segmentedGraph(n, m, u, v, sqrt(n)), 
            randomQueries(n, q, t, x, y, 1, 1, mina, maxa)
        );
        CASE(
            n = maxn, 
            q = maxq,
            randomArray(n, a, mina, maxa), 
            segmentedGraph(n, m, u, v, n/2), 
            randomQueries(n, q, t, x, y, 1, 1, mina, maxa)
        );
        CASE(
            n = maxn, 
            q = maxq,
            randomArray(n, a, mina, maxa), 
            segmentedGraph(n, m, u, v, n), 
            randomQueries(n, q, t, x, y, 1, 1, mina, maxa)
        );
        // stress test
        CASE(
            n = maxn, 
            m = 0, 
            q = maxq,
            randomArray(n, a, mina, maxa),  
            u = {}, 
            v = {},
            randomQueries(n, q, t, x, y, 1, 0, mina, maxa);
        );
        CASE(
            n = maxn, 
            m = 0, 
            q = maxq, 
            randomArray(n, a, mina, maxa),  
            u = {}, 
            v = {},
            stressAskQueries(n, q, t, x, y);
        );
    }

private:
    void randomArray(int n, vector<long long> &a, long long mn, long long mx) {
        for (int i=0; i<n; i++) a.push_back(rnd.nextInt(mn, mx));
    }

    void randomGraph(int n, int m, vector<int> &u, vector<int> &v) {
        // pake random, worst case O(n^2)
        set<pair<int, int>> edgl;
        while (edgl.size() < m){
            int uu = rnd.nextInt(1, n);
            int vv = rnd.nextInt(1, n);
            if (uu != vv && !edgl.count(make_pair(uu, vv)) && !edgl.count(make_pair(vv, uu))) {
                edgl.insert(make_pair(uu, vv));
            }
        }

        for (set<pair<int, int>>::iterator it=edgl.begin(); it!=edgl.end(); it++) {
            u.push_back(it->first);
            v.push_back(it->second);
        }
    }

    void segmentedGraph(int n, int &m, vector<int> &u, vector<int> &v, int numsegs) {
        vector<int> partitions;
        for (int i=1; i<=n; i++) partitions.push_back(i);
        rnd.shuffle(partitions.begin(), partitions.end());
        partitions.resize(numsegs);
        sort(partitions.begin(), partitions.end());

        for (int i=0; i<numsegs; i++) {
            int l = (i == 0 ? 1 : partitions[i-1]+1);
            int r = partitions[i];
            int groupsize = rnd.nextInt(1, r-l+1);
            for (int j=0; j<groupsize; j++) {
                for (int k=l+j; k+groupsize<=r; k+=groupsize) {
                    u.push_back(k);
                    v.push_back(k+groupsize);
                }
            }
        }

        m = u.size();

        vector<int> permutation;
        for (int i=0; i<m; i++) permutation.push_back(i);
        rnd.shuffle(permutation.begin(), permutation.end());
        vector<int> cu(m), cv(m);
        for (int i=0; i<m; i++) {
            cu[i] = u[permutation[i]];
            cv[i] = v[permutation[i]];
        }
        u = cu, v = cv;

        for (int i=0; i<m; i++) {
            int gacha = rnd.nextInt(0, 1);
            if (gacha) swap(u[i], v[i]);
        }
    }

    void randomQueries(int n, int q, vector<int> &t, vector<int> &x, vector<int> &y, int pu, int pq, long long mn, long long mx) { // rasio update:query = pu:pq
        { 
            int l = rnd.nextInt(1, n);
            int r = rnd.nextInt(1, n);
            if (l > r) swap(l, r);
            t.push_back(2); x.push_back(l); y.push_back(r);
        }
        for (int i=1; i<q; i++) {
            int gacha = rnd.nextInt(1, pu+pq);
            if (gacha <= pu) {
                // update
                t.push_back(1);
                x.push_back(rnd.nextInt(1, n));
                y.push_back(rnd.nextInt(mn, mx));
            } else {
                // query
                int l = rnd.nextInt(1, n);
                int r = rnd.nextInt(1, n);
                if (l > r) swap(l, r);
                t.push_back(2); x.push_back(l); y.push_back(r);
            }
        }

        vector<int> permutation;
        for (int i=0; i<q; i++) permutation.push_back(i);
        rnd.shuffle(permutation.begin(), permutation.end());
        vector<int> ct(q), cx(q), cy(q);
        for (int i=0; i<q; i++) {
            ct[i] = t[permutation[i]];
            cx[i] = x[permutation[i]];
            cy[i] = y[permutation[i]];
        }
        t = ct, x = cx, y = cy;
    }

    void stressAskQueries(int n, int q, vector<int> &t, vector<int> &x, vector<int> &y) {
        for (int i=0; i<q; i++) {
            // query
            t.push_back(2); x.push_back(1+rnd.nextInt(0, 5)); y.push_back(n-rnd.nextInt(0, 5));
        }
    }
};