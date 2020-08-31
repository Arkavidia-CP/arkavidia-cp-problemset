#include <bits/stdc++.h>


#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define MOD 1000000007
#define pii pair<int,int>
#define pli pair<long long,int>
#define pil pair<int,long long>
#define ll long long
#define el '\n'

using namespace std;


struct Trie{
    struct Node{
        int depth;
        int cnt;
        
        Node * child[2];
        Node(){
            depth = cnt = 0;
            child[0] = child[1] = 0;
        }
        Node(int dep){
            depth = dep;
            cnt = 0;
            child[0] = child[1] = 0;
        }
    };

    set <pair<int, Node*>> setdah;
    Node * head;
    Trie(){
        head = new Node();
    }
    
    void insert(string s){
        Node * cur = head;
        int len = s.length();
        for (int i=0;i<len;i++){
            bool cek_b = (s[i] == 'B');

            (cur -> cnt)++;
            if (cur -> cnt == 2){
                setdah.insert(mp(cur -> depth, cur));
            }
            if (cur -> child[cek_b] == 0){
                cur -> child[cek_b] = new Node(cur -> depth + 1);
            }
            cur = cur -> child[cek_b];
        }
        (cur -> cnt)++;
        if (cur -> cnt == 2){
            setdah.insert(mp(cur -> depth, cur));
        }
    }

    void erase(string s){
        Node * cur = head;
        int len = s.length();
        for (int i=0;i<len;i++){
            bool cek_b = (s[i] == 'B');

            (cur -> cnt)--;
            if (cur -> cnt == 1){
                setdah.erase(mp(cur -> depth, cur));
            }
            cur = cur -> child[cek_b];
        }
        (cur -> cnt)--;
        if (cur -> cnt == 1){
            setdah.erase(mp(cur -> depth, cur));
        }
    }

    int ask(){
        if (setdah.empty()) return 0;
        auto ret = *setdah.rbegin();
        return ret.fi;
    }
};

int q;
Trie trie;

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> q;
    while (q--){
        int tipe;
        string s;
        cin >> tipe >> s;

        if (tipe == 1){
            trie.insert(s);
        } else{
            trie.erase(s);
        }

        cout << trie.ask() << el;
    }

    return 0;
}
