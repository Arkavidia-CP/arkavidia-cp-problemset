#include<bits/stdc++.h>
#define pb push_back
#define mp make_pair
using namespace std;
typedef long long ll;
typedef pair<ll, string> pl;

ll n,m,x,y;
ll arr[30][30];
vector<pl> vals[30];

ll maxi=0;
string blank="";
string pathMaxi="";
string pathX="";

void dfs(ll r, ll cur, ll b, ll sum, string st){
	if(cur==b){
		for(int i=-1; i<2; i++){
			ll temp = r+i;
			if(temp<1)temp+=m;
			if(temp>m)temp-=m;
			// X
			auto lb = lower_bound(vals[temp].begin(), vals[temp].end(), mp(x-sum, blank));
			if(lb!=vals[temp].end()){
				auto idx=lb-vals[temp].begin();
				if(vals[temp][idx].first+sum==x){
					string tempS = vals[temp][idx].second + " " + st;
					if(pathX=="") pathX=tempS;
					else pathX=min(pathX, tempS);
				}
			} 
			// maxi
			ll val=vals[temp][vals[temp].size()-1].first;
			if(val+sum<maxi)continue;
			auto idx = lower_bound(vals[temp].begin(), vals[temp].end(), mp(val, blank))-vals[temp].begin();
			string tempS = vals[temp][idx].second + " " + st;
			if(val+sum>maxi){
				pathMaxi=tempS;
			}else{
				pathMaxi=min(pathMaxi, tempS);
				if(pathMaxi=="")pathMaxi=tempS;
			}
			maxi=val+sum;
		}
		return;
	}
	for(int i=-1; i<2; i++){
		ll temp = r+i;
		if(temp<1)temp+=m;
		if(temp>m)temp-=m;
		dfs(temp, cur-1, b, sum+arr[cur-1][temp], to_string(temp)+" "+st);
	}
}

int main(){
	cin>>n>>m>>x>>y;
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m ;j++){
			cin>>arr[i][j];
		}
	}
	// left
	for(int j=1; j<=m; j++){
		vals[j].pb(mp(arr[1][j], to_string(j)));
	}
	for(int i=2; i*2<=n; i++){
		vector<pl> newvals[30];
		for(int j=1; j<=m; j++){
			ll ch[3]={j-1, j, j+1};
			if(j==1) ch[0]=1, ch[1]=2, ch[2]=m;
			if(j==m) ch[0]=m-1, ch[1]=m, ch[2]=1;
			for(auto c:ch){
				for(auto p: vals[c]){
					newvals[j].pb(mp(p.first+arr[i][j],p.second+" "+to_string(j)));
				}
			}
		}
		for(int j=1; j<=m; j++){
			vals[j].clear();
			for(auto p: newvals[j])vals[j].pb(p);
		}
	}
	for(int j=1; j<=m; j++)sort(vals[j].begin(),vals[j].end());
	// right
	for(int i=1; i<=m; i++){
		dfs(i, n, n/2+1, arr[n][i], to_string(i));
	}
	if(pathX=="" || maxi>x+y)cout<<maxi<<endl;
	else cout<<x+y<<endl;
	if(maxi>x+y||pathX=="")cout<<pathMaxi<<endl;
	else cout<<pathX<<endl;
}