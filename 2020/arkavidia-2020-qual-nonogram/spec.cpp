#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;

const int NMax = 5000;
const int KMax = 5000;
const long long INF = 1e18;

class ProblemSpec : public BaseProblemSpec {
protected:
    int N, K;
	vector<int> STAT, ISI;
	long long res;

    void InputFormat() {
        LINE(N);
		LINE(STAT % SIZE(N));
		LINE(K);
        LINE(ISI % SIZE(K));
    }

    void OutputFormat() {
        LINE(res);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(64);
    }

    void Constraints() {
        CONS(1 <= N && N <= NMax);
		CONS(eachElementBetween(STAT, 0, 1));
		CONS(1 <= K && K <= KMax);
        CONS(eachElementBetween(ISI, 1, KMax));
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

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
	
    void SampleTestCase1() {
        Input({
            "8",
			"0 0 0 0 0 1 0 0",
			"2",
            "1 1"
        });
        Output({
            "5"
        });
    }
	
	void BeforeTestCase() {
		STAT.clear();
		ISI.clear();
	}	

    void TestCases() {
        CASE(N = 8, STAT = {0, 0, 0, 0, 0, 1, 0, 0}, K = 2, ISI = {1, 1});
		CASE(N = 1, STAT = {0}, K = 1, ISI = {1});
        CASE(N = 1, STAT = {1}, K = 1, ISI = {1});
        CASE(N = 2, STAT = {1, 1}, K = 1, ISI = {1});
        CASE(N = 4, STAT = {0, 0, 1, 1}, K = 2, ISI = {2, 3});
		for (int i = 0; i < 2; i++) {
			CASE(N = rnd.nextInt(1, 500), randomSTAT(), K = rnd.nextInt(1, 500), randomISI());
		}
        for (int i = 0; i < 2; i++) {
			CASE(N = rnd.nextInt(1, 500), randomSTAT(), K = rnd.nextInt(501, KMax), randomISI());
		}
        for (int i = 0; i < 2; i++) {
			CASE(N = rnd.nextInt(501, NMax), randomSTAT(), K = rnd.nextInt(1, 500), randomISI());
		}
        for (int i = 0; i < 2; i++) {
			CASE(N = rnd.nextInt(501, NMax), randomSTAT(), K = rnd.nextInt(501, KMax), randomISI());
		}
        
        for (int i = 0; i < 2; i++) {
			CASE(N = rnd.nextInt(1000, NMax), randomSTAT(), K = rnd.nextInt(1, KMax), randomISI());
		}
        for (int i = 0; i < 2; i++){
			CASE(N = rnd.nextInt(5000, NMax), randomSTAT(), K = rnd.nextInt(1000, KMax), randomISI());
        }

        // Jawaban > 0
        for (int i = 0; i < 5; i++){
            CASE(N = rnd.nextInt(1, NMax), randomSTAT(), randomSISA());
        }
        for (int i = 0; i < 5; i++){
            CASE(N = rnd.nextInt(1000, NMax), randomSTAT(), randomSISA());
        }
        for (int i = 0; i < 8; i++){
            CASE(N = rnd.nextInt(3000, NMax), randomSTAT(), randomSISA());
        }
        for (int i = 0; i < 5; i++){
            CASE(N = rnd.nextInt(5000, NMax), randomSTAT(), randomSISA());
        }
    }

private:
    void randomSTAT(){
        for (int i = 0; i < N; i++) {
            STAT.push_back(rnd.nextInt(0, 1));
        }
    }

    void allSTAT(int isi){
        assert(0<=isi && isi<=1);
        for (int i = 0; i < N; i++){
            STAT.push_back(isi);
        }
    }

    void randomISI(){
        for (int i = 0; i < K; i++) {
            ISI.push_back(rnd.nextInt(1, N));
        }
    }

    void randomSISA(){
        vector <pair<int, int>> seq;
        int bef = -1;
        int cnt = 0;
        for (int i = 0; i < N; i++){
            if (STAT[i] != bef){
                if (bef!=-1){
                    seq.push_back(make_pair(cnt, bef));
                }
                bef = STAT[i];
                cnt = 1;
            } else{
                cnt++;
            }
        }
        if (cnt){
            seq.push_back(make_pair(cnt, bef));
        }

        int len = seq.size();
        for (int i = 0; i < len; i++){
            if (seq[i].second == 0) continue;
            if (i>0){
                int ambil = rnd.nextInt(0, seq[i-1].first-1);
                seq[i-1].first -= ambil;
                seq[i].first += ambil;
            }
            if (i<len-1){
                int ambil = rnd.nextInt(0, seq[i+1].first-1);
                seq[i+1].first -= ambil;
                seq[i].first += ambil;
            }
        }

        for (int i = 0; i < len; i++){
            if (seq[i].second == 0) continue;
            ISI.push_back(seq[i].first);
        }

        K = ISI.size();
    }
};

