#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000

queue<pair<int,pair<int,int> > > q;
vector<vector<int> > visited, arr, prefHori, prefVer;
int n,m,a,b;
int awalx, awaly, akhirx, akhiry;

void init(){
	visited.resize(n);
	arr.resize(n);
	prefHori.resize(n);
	prefVer.resize(n);
	for(int i = 0; i < n; i++){
		visited[i].resize(m);
		arr[i].resize(m);
		prefHori[i].resize(m);
		prefVer[i].resize(m);
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			visited[i][j] = -1;
		}
	}
}

void precompute(){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			prefHori[i][j] = arr[i][j];
			if(j > 0)
				prefHori[i][j] += prefHori[i][j-1];
			prefVer[i][j] = arr[i][j];
			if(i > 0)
				prefVer[i][j] += prefVer[i-1][j];
		}
	}
}

bool valid(int x, int y, int prevx, int prevy){
	if(x < 0 || x >= n || y < 0 || y >= m || arr[x][y]){
		return false;
	}
	if(prefVer[x][y] == prefVer[prevx][y] && prefHori[prevx][y] == prefHori[prevx][prevy] && !arr[prevx][y]){
		return true;
	} else if (prefHori[x][y] == prefHori[x][prevy] && prefVer[x][prevy] == prefVer[prevx][prevy] && !arr[x][prevy]){
		return true;
	} else {
		return false;
	}
}

void solve(){
	q.push(make_pair(0, make_pair(awalx, awaly)));

	pair<int,int> dx[4] = {make_pair(-1, -1), make_pair(-1, 1), make_pair(1, -1), make_pair(1, 1)};
	while(!q.empty()){
		pair<int, pair<int,int> > top = q.front();
		q.pop();

		int nowstep = top.first;
		int nowx = top.second.first;
		int nowy = top.second.second;
		if(visited[nowx][nowy] != -1)
			continue;

		visited[nowx][nowy] = nowstep;
		//cout<<nowx<<" "<<nowy<<endl;
		for(int k = 0; k < 2; k++){
			for(int i = 0; i < 4; i++){
				int targetx = nowx + dx[i].first * a;
				int targety = nowy + dx[i].second * b;
				if(valid(targetx, targety, nowx, nowy)){
					q.push(make_pair(nowstep + 1, make_pair(targetx, targety)));
				}
			}
			swap(a, b);
		}
	}
	printf("%d\n", visited[akhirx][akhiry]);
}

int main(){
	scanf("%d %d", &n, &m);
	init();
	getchar();
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			char temp;
			if(j < m-1) {
				scanf("%c", &temp);
			} else {
				scanf("%c", &temp);
				getchar();
			}
			if(temp == '-'){
				arr[i][j] = 0;
			} else if(temp == 'X'){
				arr[i][j] = 1;
			} else if(temp == 'K'){
				awalx = i;
				awaly = j;
				arr[i][j] = 0;
			} else {
				akhirx = i;
				akhiry = j;
				arr[i][j] = 0;
			}
		}
	}
	scanf("%d %d", &a, &b);
	precompute();
	solve();
}