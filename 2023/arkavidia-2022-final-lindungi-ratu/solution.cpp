#include <bits/stdc++.h>
using namespace std;
 
// Define Template          Python++
// Data Structure and Algorithm
#define all(vec)            (vec).begin(),(vec).end() 
#define arrsize(arr)        sizeof(arr)/sizeof(int)
#define sortarr(arr)        sort(arr,arr+arrsize(arr));
#define sortvec(vec)        sort(all(vec));
#define minarr(arr)         *min_element(arr,arr+arrsize(arr))
#define minvec(vec)         *min_element(all(vec))
#define maxarr(arr)         *max_element(arr,arr+arrsize(arr))
#define maxvec(vec)         *max_element(all(vec))
#define sumarr(arr)         accumulate(arr,arr+arrsize(arr),0LL)
#define sumvec(vec)         accumulate(all(vec),0LL)
#define reversearr(arr)     reverse(arr,arr+arrsize(arr));
#define reversevec(vec)     reverse(all(vec));
#define range(i,s,e)        for(int i=s;i<e;i++)
#define range2(i,s,e)       for(int i=s;i>=e;i--)
#define fors(var,arr)       for(auto &var:arr)
// Input Output Manage
#define debug(x)    cout<<(#x)<<" : "<<(x)<<endl;
#define test        cout<<"test"<<endl;
#define fastIO              ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define floatprecision      cout<<fixed<<setprecision(9);
#define fileread            freopen("input.txt","r",stdin);
#define fileout             freopen("output.txt","w",stdout);
#define query               cin>>QUERY;while(QUERY--)
#define inputarr(arr,am)    int arr[am];fors(num,arr)cin>>num;
#define inputvec(vec,am)    vector<int> vec(am);fors(num,vec)cin>>num;
#define input(var)          int var;cin>>var;
#define input2(a,b)         int a,b;cin>>a>>b;
#define inputs(var)         string var;cin>>var;
#define print(var)          cout<<(var)<<endl;
#define prints(var)         cout<<(var)<<' ';
#define print2(var1,var2)   cout<<(var1)<<' '<<(var2)<<endl;
#define printp(paired)      cout<<(paired.first)<<' '<<(paired.second)<<endl;
#define printyes(cond)      cout<<((cond)?"YES":"NO")<<endl;
#define printarr(arr)       fors(num,arr){cout<<num<<' ';};cout<<endl;
#define printmap(hashmap)   for(auto[x,y]:hashmap)cout<<x<<":"<<y<<endl;
#define endline             cout<<endl;
// Macro
#define ll long long
#define pii pair<int,int>
#define vi vector<int>
#define vvi vector<vector<int>>
#define mii map<int,int>
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define pq priority_queue
#define ms multiset
// Oneliner Function
ll sigma(ll num){return num*(num+1)/2;}
ll gcd(ll a, ll b){return (a==0?b:gcd(b%a,a));}
ll lcm(ll a, ll b){return (a*b)/gcd(a,b);}
ll binpow(ll a,ll b,ll m=INT64_MAX){ll r=1;a%=m;while(b){if(b&1)r=(r*a)%m;a=(a*a)%m;b>>=1;}return r;}
ll invmod(ll a,ll m){return gcd(a,m)==1?binpow(a,m-2,m):0;}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#define int long long
#define float long double
int QUERY;
// Constant
const int MOD = 1e9+7;
const long long INF = 1e18;
const int maxn = 1e3+5;
const int m = maxn * 2 + 2; // maxn, n for worker, n for machine, 2 for sink and source
int job[maxn][maxn];
int flow[m][m] = {}; // flow
int source = m - 2; // source
int sink = m - 1; // sink
int cost = 0; // total cost
int pre[m]; // previous of vertex i
vector<int> dist(m); // distance, set to INF at first
bool in_queue[m];
queue<int> q;
int mat[maxn][maxn];
int mn, mm;

void reset(){
    range(i,0,m){
        pre[i] = 0;
        dist[i] = INF;
        in_queue[i] = false;
    }
    dist[source] = 0;
    pre[source] = -1; // no previous from sink
    q.push(source);
}

void pushqueue(int i, int j, int d){
    dist[i] = d;
    pre[i] = j;
    if (!in_queue[i]) {
        q.push(i);
        in_queue[i] = true;
    }
}

int popqueue(){
    int fr = q.front();
    q.pop();
    in_queue[fr] = false;
    return fr;
}


int isPerimeter(int x, int y){
    return x == 0 || y == 0 || x == mn-1  || y == mm-1;
}

int matdist(pair<int,int> a, pair<int,int> b){
    int dx = abs(a.first - b.first);
    int dy = abs(a.second - b.second);
    return max(dx,dy);
}

int32_t main(){
    cin>>mn>>mm;
    
    char x;
    for(int i=0;i<mn;i++)
        for(int j=0;j<mm;j++){
            cin>>x;
            mat[i][j] = (x == '*');
            // cin>>mat[i][j];
        }
    vector<pair<int,int>> coordinate0; // coordinate for 0 cell in perimeter
    vector<pair<int,int>> coordinate1; // coordinate for 1 cell inside matrix (excluding perimeter)
    for(int i=0;i<mn;i++)
        for(int j=0;j<mm;j++){
            if(isPerimeter(i,j)){
                if(mat[i][j] == 0)coordinate0.push_back({i,j});
            }else{
                if(mat[i][j] == 1)coordinate1.push_back({i,j});
            }
        }

    int n = coordinate1.size();
    mm = coordinate0.size();
    if(mm > n){ // if cell that need to fill is more than available point, no solution   
        cout << -1 << endl;
        return 0;
    }

    // job assignment problem min cost solution O(n^3)
    for(int i=0;i<n;i++){
        for(int j=0;j<mm;j++){
            job[i][j] = matdist(coordinate1[i], coordinate0[j]);
        }       
    }

    while(true){
        reset();
        while (!q.empty()) {
            int v = popqueue();
            if (v == source){  // if we process source
                range(i,0,n)  // go to all worker
                    if (flow[source][i] == 0)  // if no flow we insert to queue
                        pushqueue(i, source, 0);
            }else if (v < n){ // worker
                range(j,n,2*n) // iterate all machine 
                    if (flow[v][j] < 1 && dist[j] > dist[v] + job[v][j - n])  // if no flow and dist is lower
                        pushqueue(j, v, dist[v] + job[v][j-n]);
            }else{ // machine
                range(j,0,n) // iterate all worker (reverse path)
                    if (flow[v][j] < 0 && dist[j] > dist[v] - job[j][v - n])  // if there is reverse path
                        pushqueue(j, v, dist[v] - job[j][v-n]);
            }
        }

        int curcost = INF;
        range(i,n,2*n) // iterate all machine
            if (flow[i][sink] == 0 && dist[i] < curcost){ // if no flow to sink from machine i and cost minimize
                curcost = dist[i]; // set new cost using this machine
                pre[sink] = i; // set path to sink from machine i
            }

        if (curcost == INF)break; // if no machine can go from sink or all worker already assign to an machine so no flow
        
        cost += curcost;
        for (int cur = sink; cur != -1; cur = pre[cur]) {
            int previous = pre[cur];
            if (previous != -1){ // set flow
                flow[previous][cur] = 1; // set flow prev to cur 
                flow[cur][previous] = -1; // set reverse path
            }
        }
    }

    vector<int> pick(n); // what machine worker i pick
    range(i,0,n)
        range(j,0,n)
            if(flow[i][j + n] == 1) // if there is a flow from worker i to machine j
                pick[i] = j;
    
    print(cost)

    return 0;
}

