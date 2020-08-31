#include <tcframe/spec.hpp>
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
    int n, q, cc;
    vector<string> st;
    vector<string> query;
    vector<int> result;

    void InputFormat() {
        LINE(n, q);
        LINE(st % SIZE(2 * n - 1));
        LINES(query) % SIZE(q);
    }

    void BeforeOutputFormat(){
        cc = 0;
        for(auto x : query){
            if(x == "3"){
                cc++;
            }
        }
    }

    void OutputFormat() {
        LINES(result) % SIZE(cc);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(512);
    }

    void Constraints() {
        CONS(1 <= n && n <= 100000);
        CONS(1 <= q && q <= 100000);
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:

    void BeforeTestCase(){
        st.clear();
        query.clear();
    }

    void TestCases() {
        CASE(n = 4, q = 7, st = {"3", "*", "7", "*", "2", "+", "4"}, query = {"3", "1 4 3", "2 3 *", "3", "1 2 5", "2 2 +", "3"});
        CASE(n = 7, q = 5, randomArr(n, st, 32, 100), randomQuery(q, query, n, 0, 100));
        CASE(n = 10, q = 20, randomArr(n, st, 1, 40), randomQuery(q, query, n, 3, 20));
        CASE(n = 20000, q = 1000, randomArr(n, st, 2, 1000000), randomQuery(q, query, n, 0, 100));
        CASE(n = 7, q = 5000, randomArr(n, st, 0, 100), randomQuery(q, query, n, 0, 100));
        CASE(n = 721, q = 35, randomArr(n, st, 11, 101110), randomQuery(q, query, n, 321, 102220));
        for (int i = 0; i < 5; ++i){
            CASE(n = rnd.nextInt(10000, 100000), q = rnd.nextInt(10000, 100000), randomArr(n, st, 0, rnd.nextInt(1000000000)), randomQuery(q, query, n, 0, rnd.nextInt(1000000000)));
        }
        for (int i = 0; i < 2; ++i){
            CASE(n = 100000, q = 100000, randomArr(n, st, 1000000000, 1000000006), randomQuery(q, query, n, 0, 1000000006));
        }
        CASE(n = 100000, q = 100000, randomArr(n, st, 100000, 1000000006), randomQuery(q, query, n, 100000000, 1000000006));
        CASE(n = 100000, q = 100000, randomArr(n, st, 1000000006, 1000000006), randomQuery(q, query, n, 1000000006, 1000000006));
    }

private:

    string conv(int m){
        string res = "";
        while(m > 9){
            res += ((char) (m % 10) + '0');
            m /= 10;
        }
        res += ((char) m + '0');
        reverse(res.begin(), res.end());
        return res;
    }

    void randomArr(int n, vector<string>& x, int minel, int maxel){
        int siz = 2 * n - 1;
        char hehe[2];
        hehe[0] = '+';
        hehe[1] = '*';
        for(int i = 0; i < siz; i++){
            if(i & 1){
                int j = rnd.nextInt(0, 1);
                string hm = "";
                hm += hehe[j];
                x.push_back(hm);
            } else {
                int g = rnd.nextInt(minel, maxel);
                string res = conv(g);
                x.push_back(res);

            }
        }
    }

    void randomQuery(int q, vector<string>& x, int maxpos, int minel, int maxel){
        string hehe[2];
        hehe[0] = "+";
        hehe[1] = "*";
        for(int i = 0; i < q; i++){
            int j = rnd.nextInt(1, 3);
            if(j == 3){
                x.push_back("3");
            } else if(j == 1){
                int pos = rnd.nextInt(1, maxpos);
                int g = rnd.nextInt(0, maxel);
                string res = "1 " + conv(pos) + " " + conv(g);
                x.push_back(res);
            } else {
                int pos = rnd.nextInt(1, maxpos - 1);
                int g = rnd.nextInt(0, 1);
                string res = "2 " + conv(pos) + " " + hehe[g];
                x.push_back(res);
            }
        }
        bool found3 = false;
        for(int i = 0; i < q; i++){
            if(x[i] == "3"){
                found3 = 1;
                break;
            }
        }
        if(!found3){
            x[q - 1] = "3";
        }
    }
};