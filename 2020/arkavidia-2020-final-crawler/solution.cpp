#include <bits/stdc++.h>
using namespace std;

constexpr long long PMOD = 1e9 + 7;

int N;

struct Matrix {
    vector<vector<long long>> data;
    static Matrix zeros() {
        Matrix x;
        for (int i = 0; i < N; ++i)
            x.data.push_back(vector<long long>(N, 0));
        return x;
    }

    Matrix operator+(const Matrix& m) const {
        Matrix res = zeros();
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                res.data[i][j] = (res.data[i][j] + data[i][j] + m.data[i][j]) % PMOD;
        return res;
    }

    Matrix operator*(const Matrix& m) const {
        Matrix res = zeros();
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                for (int k = 0; k < N; ++k)
                    res.data[i][j] = (res.data[i][j] + (data[i][k] * m.data[k][j]) % PMOD) % PMOD;
        return res;
    }
};

int M, K, x, y;
Matrix P, Q, I, O;

Matrix pow(const Matrix& m, int k) {
    if (k == 0)
        return I;
    if (k == 1)
        return m;
    Matrix D = pow(m, k / 2);
    return D * D * pow(m, k % 2);
}

Matrix calcRec(int n, int k) {
    Matrix D;
    if (k == 1) {
        return O;
    } else if (k % 2 == 0) {
        D = calcRec(n, k / 2);
        return pow(Q, k / 2) * D + D * pow(P, k / 2);
    } else {
        return Q * calcRec(n, k - 1) + O * pow(P, k - 1);
    }
}

long long calcVisit(int n) {
    Matrix D = calcRec(n, K) * P;
    long long ans = 0;
    for (int i = 0; i < N; ++i)
        ans = (ans + D.data[i][0]) % PMOD;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M >> K;
    P = Matrix::zeros();
    for (int i = 0; i < M; ++i) {
        cin >> x >> y;
        --x;
        --y;
        P.data[y][x] = 1;
    }
    Q = P;
    for (int i = 0; i < N; ++i) {
        bool isZero = true;
        for (int j = 0; j < N; ++j) {
            if (Q.data[j][i] == 1) {
                isZero = false;
                break;
            }
        }
        if (isZero)
            Q.data[i][i] = 1;
    }
    I = Matrix::zeros();
    for (int i = 0; i < N; ++i)
        I.data[i][i] = 1;
    O = Matrix::zeros();
    for (int i = 0; i < N; ++i) {
        O.data[i][i] = 1;
        cout << calcVisit(i) << (i == N-1 ? '\n' : ' ');
        O.data[i][i] = 0;
    }
}