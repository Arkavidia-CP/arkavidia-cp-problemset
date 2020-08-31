#include <tcframe/spec.hpp>
using namespace tcframe;

#define fi first
#define se second
#define pii pair<int,int>
#define MAXR 100000
#define MAXC 100000
#define MAXRC 100000

class ProblemSpec : public BaseProblemSpec {
private:
    bool ValidCell(const vector<vector<char>> &X) {
        for (auto r : X) {
            for (char x : r) {
                if (x != '-' && x != 'X' && x != 'K' && x != 'O') return false;
            }
        }
        return true;
    }
    bool CheckStartEnd(const vector<vector<char>> &X) {
        bool start = false, end = false;
        for (auto r : X) {
            for (char x : r) {
                if (x == 'K') start = true;
                if (x == 'O') end = true;
            }
        }
        return start && end;
    }

protected:
    int R, C;
    vector<vector<char>> G;
    int A, B;
    int ans;

    void InputFormat() {
        LINE(R, C);
        GRID(G) % SIZE(R, C);
        LINE(A, B);
    }

    void OutputFormat() {
        LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(2);
        MemoryLimit(512);
    }

    void Constraints() {
        CONS(1 <= R <= MAXR);
        CONS(1 <= C <= MAXC);
        CONS(1 <= R*C <= MAXRC);
        CONS(ValidCell(G));
        CONS(CheckStartEnd(G));
        CONS(1 <= A <= R);
        CONS(1 <= B <= C);
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
private:
    void InitGrid() {
        G.resize(R);
        for (int i=0;i<R;i++) {
            G[i].resize(C);
        }
        for (int i=0;i<R;i++) {
            for (int j=0;j<C;j++) {
                G[i][j] = '-';
            }
        }
    }

    bool Inside(pii next) {
        return next.fi >= 0 && next.fi < R && next.se >= 0 && next.se < C;
    }

    void GenerateGrid(bool obstacle) {
        InitGrid();
        // pilih start point
        pii start = {rnd.nextInt(0, R - 1), rnd.nextInt(0, C - 1)};
        G[start.fi][start.se] = 'K';

        // BFS biasa
        int dx[] = {A,A,-A,-A,B,B,-B,-B};
        int dy[] = {B,-B,B,-B,A,-A,A,-A};
        int vis[R][C];
        memset (vis,-1,sizeof(vis));
        vis[start.fi][start.se] = 0;
        queue<pii> q;
        q.push(start);
        while (!q.empty()) {
            pii cur = q.front();
            q.pop();
            for (int i=0;i<8;i++) {
                pii next = {cur.fi + dx[i], cur.se + dy[i]};
                if (Inside(next) && vis[next.fi][next.se] == -1) {
                    vis[next.fi][next.se] = vis[cur.fi][cur.se] + 1;
                    q.push(next);
                }
            }
        }

        // pilih end point
        vector<pii> list[R*C+5];  // list point dengan distance tertentu
        int maxi = 0;   // max dist
        bool ada = false;
        for (int i=0;i<R;i++) {
            for (int j=0;j<C;j++) {
                maxi = max(maxi, vis[i][j]);
                if (vis[i][j] > 0) {
                    ada = true;
                    list[vis[i][j]].push_back({i,j});
                }
            }
        }
        pii end;
        int dist;
        while (ada) {
            dist = rnd.nextInt(1, maxi);
            // std::cerr << list[dist].size() << endl;
            int elmt = rnd.nextInt(0, list[dist].size()-1);
            end = list[dist][elmt];
            if (vis[end.fi][end.se] > 0) break;
        }
        if (!ada) {
            end = start;
            while (end == start) {
                end = {rnd.nextInt(0, R-1), rnd.nextInt(0, C-1)};
            }
        }
        G[end.fi][end.se] = 'O';

        // std::cerr << vis[end.fi][end.se] << endl;

        if (obstacle) {
            bool lewat[R+5][C+5];
            memset (lewat, 0, sizeof(lewat));
            pii cur = end;
            while (vis[cur.fi][cur.se] > 0) {
                lewat[cur.fi][cur.se] = 1;
                for (int i=0;i<8;i++) {
                    pii next = {cur.fi + dx[i], cur.se + dy[i]};
                    if (Inside(next) && vis[next.fi][next.se] == vis[cur.fi][cur.se] - 1) {
                        int mode = rnd.nextInt(0, 2);
                        if (mode == 0) {
                            for (int x = min(cur.fi, next.fi); x <= max(cur.fi, next.fi); x++) {
                                lewat[x][cur.se] = 1;
                                lewat[x][next.se] = 1;
                            }
                            for (int y = min(cur.se, next.se); y <= max(cur.se, next.se); y++) {
                                lewat[next.fi][y] = 1;
                                lewat[cur.fi][y] = 1;
                            }
                        } else if (mode == 1) {
                            for (int x = min(cur.fi, next.fi); x <= max(cur.fi, next.fi); x++) {
                                lewat[x][next.se] = 1;
                            }
                            for (int y = min(cur.se, next.se); y <= max(cur.se, next.se); y++) {
                                lewat[cur.fi][y] = 1;
                            }
                        } else if (mode == 2) {
                            for (int x = min(cur.fi, next.fi); x <= max(cur.fi, next.fi); x++) {
                                lewat[x][cur.se] = 1;
                            }
                            for (int y = min(cur.se, next.se); y <= max(cur.se, next.se); y++) {
                                lewat[next.fi][y] = 1;
                            }
                        }
                        cur = next;
                        break;
                    }
                }
            }
            lewat[end.fi][end.se] = 1;
            lewat[start.fi][start.se] = 1;
            for (int i=0;i<R;i++) {
                for (int j=0;j<C;j++) {
                    if (!lewat[i][j]) {
                        int x = rnd.nextInt(0, 1);
                        if (x == 1) G[i][j] = 'X';
                    }
                }
            }
        }
    }

    void GenerateToxicGrid(int x) {
        InitGrid();
        if (x == 1) {
            G[0][0] = 'X';
            G[0][1] = 'K';
            G[1][0] = 'O';
            G[1][1] = 'X';
        } else if (x == 2) {
            G[0][0] = 'X';
            G[0][1] = 'O';
            G[1][0] = 'K';
            G[1][1] = 'X';
        } else if (x == 3) {
            G[0][0] = 'X';
            G[0][2] = 'K';
            G[2][0] = 'O';
            G[2][2] = 'X';
        } else if (x == 4) {
            G[0][0] = 'O';
            G[0][1] = 'X';
            G[1][0] = 'X';
            G[1][1] = 'K';
        } else if (x == 5) {
            G[0][13518] = 'K';
            G[0][86519] = 'O';
        } else if (x == 6) {
            G[0][0] = 'O';
            G[99999][0] = 'K';
        }
    }

protected:
    void BeforeTestCase() {
        G.clear();
    }

    void SampleTestCase1() {
        Input({"6 5",
            "X----",
            "--X--",
            "-K---",
            "O-X--",
            "----X",
            "-----",
            "3 1"});

        Output({"3"});
    }

    // no obstacle
    void TestGroup1() {
        // (hampir) kotak
        for (int i=1;i<=2;i++) {
            int p = rnd.nextInt(16, 300);
            CASE(R = rnd.nextInt(p - 15, p + 15), C = rnd.nextInt(p - 15, p + 15), A = rnd.nextInt(1, sqrt(R)), B = rnd.nextInt(1, sqrt(C)), GenerateGrid(false));
        }
        // agak panjang
        for (int i=1;i<=2;i++) {
            CASE(R = rnd.nextInt(1, 1000), C = rnd.nextInt(1, 100), A = rnd.nextInt(1, sqrt(R)), B = rnd.nextInt(1, sqrt(C)), GenerateGrid(false));
        }
        // gepeng
        for (int i=1;i<=2;i++) {
            CASE(R = rnd.nextInt(1, 5), C = rnd.nextInt(1000, 100000 / R), A = rnd.nextInt(1, 5), B = rnd.nextInt(1, 5), GenerateGrid(false));
        }
    }

    // ada obstacle
    void TestGroup2() {
        // (hampir) kotak
        for (int i=1;i<=4;i++) {
            int p = rnd.nextInt(16, 300);
            CASE(R = rnd.nextInt(p - 15, p + 15), C = rnd.nextInt(p - 15, p + 15), A = rnd.nextInt(1, sqrt(R)), B = rnd.nextInt(1, sqrt(C)), GenerateGrid(true));
        }
        // agak panjang
        for (int i=1;i<=4;i++) {
            CASE(R = rnd.nextInt(1, 1000), C = rnd.nextInt(1, 100), A = rnd.nextInt(1, sqrt(R)), B = rnd.nextInt(1, sqrt(C)), GenerateGrid(true));
        }
        // gepeng
        for (int i=1;i<=4;i++) {
            CASE(R = rnd.nextInt(1, 5), C = rnd.nextInt(1000, 100000 / R), A = rnd.nextInt(1, min(3, R)), B = rnd.nextInt(1, 3), GenerateGrid(true));
        }
    }

    // kecil
    void TestGroup3() {
        for (int i=1;i<=3;i++) {
            CASE(R = rnd.nextInt(5, 15), C = rnd.nextInt(5, 15),  A = rnd.nextInt(1, sqrt(R)), B = rnd.nextInt(1, sqrt(C)), GenerateGrid(false));
        }
        for (int i=1;i<=3;i++) {
            CASE(R = rnd.nextInt(5, 15), C = rnd.nextInt(5, 15),  A = rnd.nextInt(1, sqrt(R)), B = rnd.nextInt(1, sqrt(C)), GenerateGrid(true));
        }
        for (int i=1;i<=3;i++) {
            CASE(R = rnd.nextInt(2, 10), C = rnd.nextInt(2, 10),  A = rnd.nextInt(1, sqrt(R)), B = rnd.nextInt(1, sqrt(C)), GenerateGrid(true));
        }
    }

    // tc corner kejam
    void TestGroup4() {
        CASE(R = 2, C = 2, A = 1, B = 1, GenerateToxicGrid(1));
        CASE(R = 2, C = 2, A = 1, B = 1, GenerateToxicGrid(2));
        CASE(R = 3, C = 3, A = 2, B = 2, GenerateToxicGrid(3));
        CASE(R = 2, C = 2, A = 1, B = 1, GenerateToxicGrid(4));
        CASE(R = 1, C = 100000, A = 1, B = C - 1, GenerateToxicGrid(5));
        CASE(R = 100000, C = 1, A = 1, B = C - 1, GenerateToxicGrid(6));
    }

};