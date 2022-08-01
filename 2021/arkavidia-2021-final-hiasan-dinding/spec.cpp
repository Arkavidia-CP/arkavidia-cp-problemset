#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

const int MAXN = 1e5, MAXQ = 1e5;
const long long MINXY = -1e9, MAXXY = 1e9;

class ProblemSpec : public BaseProblemSpec {
protected:

	int N, Q;
    vector<long long> PolygonX, PolygonY, QueriesL, QueriesR;
    vector<string> ans;

	void InputFormat() {
	  LINE(N);
	  LINES(PolygonX, PolygonY) % SIZE(N);
	  LINE(Q);
      LINES(QueriesL, QueriesR) % SIZE(Q);
	}

    void OutputFormat() {
    	LINES(ans);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(3 <= N && N <= MAXN);
        CONS(1 <= Q && Q <= MAXQ);
        CONS(rangeCheckPolygon(PolygonX, PolygonY, MINXY, MAXXY));
        CONS(isValidPolygon(PolygonX, PolygonY));
        CONS(rangeCheckQueries(QueriesL, QueriesR, MINXY, MAXXY));
    }

private:
    bool rangeCheckPolygon(vector<long long> x, vector<long long> y, long long mn, long long mx){
        for(int i = 0; i < x.size(); i++){
            if(x[i] < mn || x[i] > mx || y[i] < mn || y[i] > mx)
                return false;
        }
        return true;
    }
    bool rangeCheckQueries(vector<long long> l, vector<long long> r, long long mn, long long mx){
        for(int i = 0; i < l.size(); i++){
            if(l[i] < mn || l[i] > mx || r[i] < mn || r[i] > mx || l[i] > r[i])
                return false;
        }
        return true;
    }
    bool cw(long long xa, long long ya, long long xb, long long yb, long long xc, long long yc){
        return xa*(yb-yc)+xb*(yc-ya)+xc*(ya-yb) <= 0;
    }
    bool isValidPolygon(vector<long long> x, vector<long long> y){
        // valid polygon itu convex, clockwise, mulai dari kiri-bawah, dan semua titiknya distinct
        // cek convex & clockwise 
        int n = x.size();
        for (int i = 0; i < n; i++){
            if (!cw(x[i],y[i],x[(i+1)%n],y[(i+1)%n],x[(i+2)%n],y[(i+2)%n]))
                return false;
        }
        // cek mulai dari kiri-bawah
        for (int i = 1; i < n; i++){
            if (x[i] < x[0] || (x[i] == x[0] && y[i] < y[0]))
                return false;
        }
        // cek titik distinct
        set<pair<long long, long long>> udah;
        for (int i = 0; i < n; i++){
            if (udah.count(make_pair(x[i],y[i])))
                return false;
            udah.insert(make_pair(x[i],y[i]));
        }
        return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
        	"9",
            "0 -1",
            "0 0",
            "1 1",
            "3 2",
            "5 1",
            "6 0",
            "5 -2",
            "3 -3",
            "1 -2",
            "6",
            "0 6",
            "1 5",
            "0 3",
            "5 6",
            "7 9",
            "4 4"
        });
        Output({
        	"19.5",
            "16.0",
            "10.0",
            "1.5",
            "0.0",
            "0.0"
        });
    }

    void BeforeTestCase(){
    	PolygonX.clear();
        PolygonY.clear();
        QueriesL.clear();
        QueriesR.clear();
    }

    void TestCases() {
    	// random small dense
        for (int i=1; i<=10; i++){
            CASE(N = 100, Q = 100, randomConvexPolygon(PolygonX,PolygonY,N,0,N), randomQueries(QueriesL,QueriesR,Q,0,N));
        }
        // random small sparse
        for (int i=1; i<=10; i++){
            CASE(N = 100, Q = 100, randomConvexPolygon(PolygonX,PolygonY,N,MINXY,MAXXY), randomQueries(QueriesL,QueriesR,Q,MINXY,MAXXY));
        }
        // corner cases
        // min area
        CASE(N = 3, Q = 1,
             PolygonX = {0,0,1},
             PolygonY = {0,1,0},
             QueriesL = {0},
             QueriesR = {1});
        // max area
        CASE(N = 4, Q = 1,
             PolygonX = {MINXY,MINXY,MAXXY,MAXXY},
             PolygonY = {MINXY,MAXXY,MAXXY,MINXY},
             QueriesL = {MINXY},
             QueriesR = {MAXXY});
        // max area - 0.5
        CASE(N = 5, Q = 2,
             PolygonX = {MINXY,MINXY,MAXXY-1,MAXXY,MAXXY},
             PolygonY = {MINXY,MAXXY,MAXXY,MAXXY-1,MINXY},
             QueriesL = {MINXY,MAXXY-1},
             QueriesR = {MAXXY,MAXXY});
        CASE(N = 5, Q = 2,
             PolygonX = {MINXY,MINXY,MAXXY,MAXXY,MINXY+1},
             PolygonY = {MINXY+1,MAXXY,MAXXY,MINXY,MINXY},
             QueriesL = {MINXY,MINXY},
             QueriesR = {MAXXY,MINXY+1});
        // collinear points
        CASE(N = 8, Q = 3,
             PolygonX = {0,0,0,0,1,1,1,1},
             PolygonY = {0,1,2,3,3,2,1,0},
             QueriesL = {0,1,0},
             QueriesR = {0,1,1});
        CASE(N = 8, Q = 3,
             PolygonX = {0,0,1,2,3,3,2,1},
             PolygonY = {0,1,1,1,1,0,0,0},
             QueriesL = {0,3,0},
             QueriesR = {0,3,3});
        // random big dense
        for (int i=1; i<=3; i++){
            CASE(N = MAXN, Q = 5, randomConvexPolygon(PolygonX,PolygonY,N,-N,N), randomQueries(QueriesL,QueriesR,Q,MINXY,MAXXY));
        }  
        for (int i=1; i<=3; i++){
            CASE(N = MAXN, Q = MAXQ, randomConvexPolygon(PolygonX,PolygonY,N,-N,N), randomQueries(QueriesL,QueriesR,Q,MINXY,MAXXY));
        }
        // random big sparse
        for (int i=1; i<=3; i++){
            CASE(N = MAXN, Q = MAXQ, randomConvexPolygon(PolygonX,PolygonY,N,MINXY,MAXXY), randomQueries(QueriesL,QueriesR,Q,MINXY,MAXXY));
        }
    }

private:
    void randomConvexPolygon(vector<long long> &px, vector<long long> &py, int n, long long mn, long long mx){
        // https://cglab.ca/~sander/misc/ConvexGeneration/convex.html: convex polygon randomizer
        vector<long long> x, y;
        set<long long> udah_x, udah_y;
        for (int i=0; i<n; i++){
            long long gacha;
            do{
                gacha = rnd.nextLongLong(mn,mx);
            } while (udah_x.count(gacha));
            udah_x.insert(gacha);
            x.push_back(gacha);
        }
        for (int i=0; i<n; i++){
            long long gacha;
            do{
                gacha = rnd.nextLongLong(mn,mx);
            } while (udah_y.count(gacha));
            udah_y.insert(gacha);
            y.push_back(gacha);
        }
        sort(x.begin(),x.end());
        sort(y.begin(),y.end());
        vector<long long> xvec, yvec;
        long long lx = x[0], rx = x[0], ly = y[0], ry = y[0];
        for (int i=1; i+1<n; i++){
            if (rnd.nextInt(0,1)){
                xvec.push_back(x[i]-rx);
                rx = x[i];
            }
            else{
                xvec.push_back(lx-x[i]);
                lx = x[i];
            }
            if (rnd.nextInt(0,1)){
                yvec.push_back(y[i]-ry);
                ry = y[i];
            }
            else{
                yvec.push_back(ly-y[i]);
                ly = y[i];
            }
        }
        xvec.push_back(x[n-1]-rx);
        xvec.push_back(lx-x[n-1]);
        yvec.push_back(y[n-1]-ry);
        yvec.push_back(ly-y[n-1]);
        rnd.shuffle(yvec.begin(),yvec.end());
        vector<pair<long long, long long>> vec;
        for (int i=0; i<n; i++) vec.emplace_back(xvec[i],yvec[i]);
        sort(vec.begin(),vec.end(),[](pair<long long, long long> a, pair<long long, long long> b){
            return atan2(a.second,a.first) > atan2(b.second,b.first);
        });
        vector<pair<long long, long long>> pts;
        long long cur_x = 0, cur_y = 0, mnx = 0, mny = 0;
        for (int i=0; i<n; i++){
            pts.emplace_back(cur_x,cur_y);
            cur_x += vec[i].first;
            cur_y += vec[i].second;
            mnx = min(mnx,cur_x);
            mny = min(mny,cur_y);
        }
        for (int i=0; i<n; i++){
            pts[i].first += x[0] - mnx;
            pts[i].second += y[0] - mny;
        }
        pair<long long, long long> kiri_bawah = {1e18,1e18};
        int start;
        for (int i=0; i<n; i++){
            if (pts[i].first < kiri_bawah.first || (pts[i].first == kiri_bawah.first && pts[i].second < kiri_bawah.second)){
                kiri_bawah = pts[i];
                start = i;
            }
        }
        for (int i=0; i<n; i++){
            px.push_back(pts[(start+i)%n].first);
            py.push_back(pts[(start+i)%n].second);
        }
    }
    void randomQueries(vector<long long> &px, vector<long long> &py, int q, long long mn, long long mx){
        for (int i=0; i<q; i++){
            long long l = rnd.nextLongLong(mn,mx);
            long long r = rnd.nextLongLong(l,mx);
            px.push_back(l);
            py.push_back(r);
        }
    }
};