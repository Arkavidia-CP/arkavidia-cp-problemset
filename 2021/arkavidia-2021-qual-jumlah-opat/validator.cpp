#include <bits/stdc++.h>
#define LL long long
using namespace std;

const int EXIT_AC = 42;
const int EXIT_WA = 43;

int wa() {
    exit(EXIT_WA);
}

int ac() {
    exit(EXIT_AC);
}

int main(int argc, char* argv[]) {
    ifstream tc_in(argv[1]);
    ifstream tc_out(argv[2]);
    string feedback_path = argv[3];
    feedback_path += "/judgeerror.txt";
    ofstream feedback(feedback_path);

    int tc_ans;
    tc_out >> tc_ans;

    // read contestant output
    int K;
    vector<int> v;
    if (!(cin >> K)) {
        feedback << "no input" << endl;
        return wa();
    }
    for (int i=0;i<K;i++) {
        int x;
        if (!(cin >> x)) {
            feedback << "not enough integers in input" << endl;
            return wa();
        } else {
            v.push_back(x);
        }
    }

    // read tc input
    int N, M;
    tc_in >> N >> M;
    int A[N+5];
    for (int i=1;i<=N;i++) {
        tc_in >> A[i];
    }
    vector<int> adj[N+5];
    for (int i=1;i<=M;i++) {
        int u, v;
        tc_in >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // check if correct output is -1
    if (tc_ans == -1) {
        if (K == -1) return ac();
        else {
            feedback << "judge did not find an answer but contestant found" << endl;
            return wa();
        }
    }

    // check if K >= 1
    if (K <= 1) {
        feedback << "K not greater than 1" << endl;
        return wa();
    }

    // check sum (must be == 0 mod 4)
    int sum = 0;
    for (int i=0;i<K;i++) {
        sum += A[v[i]] % 4;
        sum %= 4;
    }
    if (sum > 0) {
        feedback << "sum not 0 modulo 4" << endl;
        return wa();
    }

    // check subgraph
    bool mark[N+5];
    memset(mark,0,sizeof(mark));
    for (int i=0;i<K;i++) {
        mark[v[i]] = 1;
    }

    bool vis[N+5];
    memset (vis,0,sizeof(vis));
    stack<int> s;
    s.push(v[0]);
    vis[v[0]] = 1;
    while (!s.empty()) {
        int cur = s.top();
        s.pop();
        for (auto next : adj[cur]) {
            if (vis[next] || !mark[next]) continue; // must be marked
            vis[next] = 1;
            s.push(next);
        }
    }
    for (int i=0;i<K;i++) {
        if (!vis[v[i]]) {
            feedback << "chosen nodes not connected" << endl;
            return wa();    // not connected
        }
    }
    return ac();
}