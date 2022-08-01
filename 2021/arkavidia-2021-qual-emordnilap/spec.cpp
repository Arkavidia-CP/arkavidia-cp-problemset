#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
    const int NMAX = 100;

    string S, ans;

    void InputFormat() {
        LINE(S);
    }

    void OutputFormat1() {
        LINE(ans);
    }

    void OutputFormat2() {
        RAW_LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(32);
    }

    void Constraints() {
        CONS(1 <= S.length() && S.length() <= NMAX);
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:

    vector<char> chars;

    void SampleTestCase1() {
        Input({
            "Kasur"
        });
        Output({
            "rusak"
        });
    }
    void SampleTestCase2() {
        Input({
            "Aku%"
        });
        Output({
            "Emor tidak beruntung :("
        });
    }
    void SampleTestCase3() {
        Input({
            "beRuntung123"
        });
        Output({
            "321gnutnureb"
        });
    }

    void TestCases() {
        chars.clear();
        for(int i=0; i<10; i++){
            chars.push_back('0' + i);
        }
        for(int i=0; i<26; i++){
            chars.push_back('A' + i);
        }
        for(int i=0; i<26; i++){
            chars.push_back('a' + i);
        }
        for (int i=0;i<50;i++){
            make_random_query(chars);
        }
    }

private:
    void make_random_query(vector<char>& chars){
        int length, potent;
        string s;
        length = rnd.nextInt(1, 100);
            potent = rnd.nextInt(length);
            s = "";
            for(int j=0; j<length; j++){
                s += " ";
                if(j==potent){
                    s[j] = rnd.nextInt(47, 124);
                }else{
                    s[j] = chars[rnd.nextInt(62)];
                }
            }
        CASE(S = s);
    }
};