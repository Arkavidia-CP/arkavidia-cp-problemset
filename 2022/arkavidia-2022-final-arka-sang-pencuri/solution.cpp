#include <bits/stdc++.h>
#define int long long
using namespace std;

const int MOD = 1e9 + 7;

class Matrix {
    public:
    vector<vector<int>> mem;
    int getRow() {
        return mem.size();
    }
    int getCol() {
        if(!getRow()) return 0;
        return mem[0].size();
    }
    Matrix operator*(Matrix& o) {
        assert(getCol() == o.getRow());
        Matrix ret;
        ret.mem = vector<vector<int>>(getRow(), vector<int>(o.getCol(), 0));

        for(int i = 0; i < getRow(); i++) {
            for(int j = 0; j < o.getCol(); j++) {
                ret.mem[i][j] = 0;
                for(int k = 0; k < getCol(); k++) {
                    ret.mem[i][j] += mem[i][k] * o.mem[k][j];
                    ret.mem[i][j] %= MOD;
                    ret.mem[i][j] = (ret.mem[i][j] + MOD) % MOD;
                }
            }
        }
        return ret;
    }

    static Matrix one(int sz) {
        Matrix ret;
        ret.mem = vector<vector<int>>(sz, vector<int>(sz, 0));
        for(int i = 0; i < sz; i++) ret.mem[i][i] = 1;
        return ret;
    }
};

Matrix fastexp(Matrix x, int e) {
    if(!e) return Matrix::one(x.getRow());
    Matrix ret = fastexp(x, e >> 1);
    ret = ret * ret;
    if(e & 1) ret = ret * x;
    return ret;
}

int32_t main() {
    Matrix p;
    p.mem = vector<vector<int>>(4, vector<int>(4,0));
    int n, k;
    cin >> n >> k;
    p.mem[0][0] = n % MOD;
    p.mem[0][1] = 1;
    p.mem[1][1] = 1;
    p.mem[1][2] = -2;
    p.mem[1][3] = 1;
    p.mem[2][2] = 1;
    p.mem[2][3] = -1;
    p.mem[3][3] = 1;

    p = fastexp(p, k);
    Matrix q;
    q.mem = vector<vector<int>>(4, vector<int>(1, 0));
    q.mem[1][0] = (((k - 1) % MOD) * ((k - 1) % MOD)) % MOD;
    q.mem[2][0] = (k-1)%MOD;
    q.mem[3][0] = 1;

    cout << (p*q).mem[0][0] << '\n';
}
