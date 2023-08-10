#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
    const int NMAX = 1e3;
    const int innerMax = 400;
    int N, M;
    vector<string> matrix;
    int ans;

    void InputFormat() {
        LINE(N, M);
        LINES(matrix) % SIZE(N);
    }

    void OutputFormat1() {
        LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(1 <= N <= NMAX);
        CONS(1 <= M <= NMAX);
        CONS(matrix_cons(matrix, N, M));
    }

private:
    bool is_perimeter(int n, int m, int x, int y){
        return x == 0 || y == 0 || x == n-1  || y == m-1;
    }
    bool matrix_cons(vector<string>& matrix, int n, int m){
        if(matrix.size() != n || matrix[0].size() != m)return false;
        int cnt = 0;
        for(int i=0;i<n;i++){
            if(matrix[i].size() != m)return false;
            for(int j=0;j<m;j++){
                if((matrix[i][j] != '*' && matrix[i][j] != '-'))return false;
                if(!is_perimeter(n, m, i, j)&&matrix[i][j]=='*')cnt++;
            }
        }
        return cnt <= innerMax;
    }

};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:

    void SampleTestCase1() {
        Input({
            "3 3",
            "***",
            "*-*",
            "***"
        });
        Output({
            "0"
        });
    }
    void SampleTestCase2() {
        Input({
            "3 3",
            "---",
            "-*-",
            "---"
        });
        Output({
            "-1"
        });
    }
    void SampleTestCase3() {
        Input({
            "4 4",
            "****",
            "---*",
            "*-**",
            "****"
        });
        Output({
            "2"
        });
    }

    void BeforeTestCase(){
        matrix.clear();
    }

    void TestCases() {
        for(int i=0;i<5;i++)CASE(random_matrix(N=10,M=10,matrix,{10,10}));
        for(int i=0;i<5;i++)CASE(random_matrix(N=10,M=10,matrix,{10,9}));
        for(int i=0;i<5;i++)CASE(random_matrix(N=10,M=10,matrix,{9,10}));
        for(int i=0;i<5;i++)CASE(random_matrix(N=50,M=50,matrix,haveAnsPair(200)));
        for(int i=0;i<5;i++)CASE(random_matrix(N=100,M=100,matrix,haveAnsPair(innerMax)));
        for(int i=0;i<5;i++)CASE(random_matrix(N=200,M=200,matrix,haveAnsPair(innerMax)));
        for(int i=0;i<5;i++)CASE(random_matrix(N=500,M=500,matrix,haveAnsPair(innerMax)));
        for(int i=0;i<5;i++)CASE(random_matrix(N=NMAX,M=NMAX,matrix,haveAnsPair(innerMax)));
        for(int i=0;i<5;i++)CASE(random_matrix(N=rnd.nextInt(15,NMAX),M=rnd.nextInt(15,NMAX),matrix,haveAnsPair(min(N*M - 3*(M+N), innerMax))));
        for(int i=0;i<5;i++)CASE(random_matrix(N=rnd.nextInt(15,NMAX),M=rnd.nextInt(15,NMAX),matrix,noAnsPair(min(N*M - 3*(M+N), innerMax))));
        edgeCase();
    }

private:
    bool is_perimeter(int n, int m, int x, int y){
        return x == 0 || y == 0 || x == n-1  || y == m-1;
    }
    pair<int,int> haveAnsPair(int lim){
        int cnt0 = rnd.nextInt(1, lim - 1);
        int cnt1 = rnd.nextInt(cnt0, lim);
        return make_pair(cnt0, cnt1);
    }
    pair<int,int> noAnsPair(int lim){
        int cnt0 = rnd.nextInt(1, lim - 1);
        int cnt1 = rnd.nextInt(cnt0, lim);
        return make_pair(cnt1, cnt0);
    }
    void random_matrix(int n, int m, vector<string>& matrix, pair<int,int> cnt){
        int cnt0 = cnt.first; // how many empty slot in perimeter
        int cnt1 = cnt.second; // how many available piece inside

        // for perimeter 0 = *, 1 = -
        int perimetersize = 2 * (m + n - 2);
        vector<int> perimeter(perimetersize);
        for(int i=0;i<cnt0;i++)perimeter[i] = 1;

        // for inside 0 = -, 1 = *
        vector<int> inside(n * m - perimetersize);
        for(int i=0;i<cnt1;i++)inside[i] = 1;

        // random
        random_shuffle(perimeter.begin(), perimeter.end());
        random_shuffle(inside.begin(), inside.end());

        // create matrix
        string tmp(m, '.');
        for(int i=0;i<n;i++)matrix.push_back(tmp);

        // fill perimeter
        int j = 0;
        for(int i=0;i<m;i++){
            if(perimeter[j++] == 0)matrix[0][i] = '*';
            else matrix[0][i] = '-';
        }
        for(int i=1;i<n-1;i++){
            if(perimeter[j++] == 0)matrix[i][m-1] = '*';
            else matrix[i][m-1] = '-';
        }
        for(int i=m;i>=0;i--){
            if(perimeter[j++] == 0)matrix[n-1][i] = '*';
            else matrix[n-1][i] = '-';
        }
        for(int i=n-2;i>=1;i--){
            if(perimeter[j++] == 0)matrix[i][0] = '*';
            else matrix[i][0] = '-';
        }

        // fill inside
        for(int i=0;i<inside.size();i++){
            int c = (i % (m-2)) + 1;
            int r = (i / (m-2)) + 1;
            if(inside[i] == 0)matrix[r][c] = '-';
            else matrix[r][c] = '*';
        }
    }
    void edgeCase(){
        vector<string> case1 = {{"*"}};
        vector<string> case2 = {{"-"}};
        vector<string> case3 = {{"**"},
                                {"**"}};
        vector<string> case4 = {{"*-"},
                                {"**"}};
        vector<string> case5 = {{"*-"}};
        vector<string> case6 = {{"**"}};
        vector<string> case7 = {{"******-*****"}};
        vector<string> case8 = {{"***"},
                                {"**-"}};
        vector<string> case9 = {{"***"},
                                {"***"}};
        packCase(case1);
        packCase(case2);
        packCase(case3);
        packCase(case4);
        packCase(case5);
        packCase(case6);
        packCase(case7);
        packCase(case8);
        packCase(case9);
    }
    void packCase(vector<string>& mat){
        CASE(N = mat.size(), M = mat[0].size(), matrix = mat);
    }
};
