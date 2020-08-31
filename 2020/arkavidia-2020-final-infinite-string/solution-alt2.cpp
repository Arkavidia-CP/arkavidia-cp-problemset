#include <bits/stdc++.h>
using namespace std;

set<pair<long long, int> > bannedSet;
map<pair<long long, int>, set<pair<long long, int> > > catalystList;
int t;
long long val[55];
bool check;
string s;

void simplify(pair<long long, int> &word){
	word.first >>= 1;
	word.second--;
}

vector<pair<long long, int> > getCatalystList(pair<long long, int> word){
	vector<pair<long long, int> > catalystList;
	for(int i = word.second; i >= 1; i--){
		catalystList.push_back(make_pair((word.first ^ 1) % (1LL << i), i));
	}	
	return catalystList;
}

bool insertBanned(long long s, int sz){
	if(sz == 0){
		return false;
	}
	pair<long long, int> word = make_pair(s, sz);
	//Check if word can simplify something
	while(catalystList[word].size()){
		pair<long long, int> beforeSimplify = *catalystList[word].begin();
		catalystList[word].erase(catalystList[word].begin());
		bannedSet.erase(beforeSimplify);
		vector<pair<long long, int> > wordList = getCatalystList(beforeSimplify);
		for(int i = 0; i < wordList.size(); i++){
			catalystList[wordList[i]].erase(beforeSimplify);
		}
		simplify(beforeSimplify);
		if(!insertBanned(beforeSimplify.first, beforeSimplify.second)){
			return false;
		}
	}
	//Check if word can be simplified
	vector<pair<long long, int> > wordList = getCatalystList(word);
	for(int i = 0; i < wordList.size(); i++){
		if(bannedSet.find(wordList[i]) != bannedSet.end()){
			simplify(word);
			return insertBanned(word.first, word.second);
		}
	}
	//Insert all catalyst of word
	for(int i = 0; i < wordList.size(); i++){
		catalystList[wordList[i]].insert(word);
	}
	bannedSet.insert(word);
	return true;
}

long long convertToInt(string s){
	long long res = 0;
	for(int i = 0; i < s.size(); i++){
		res <<= 1;
		if(s[i] == '1'){	
			res++;
		}
	}
	return res;
}

void solve(){
	string res = "";
	for(int i = 0; i < 10; i++){
		bool valid = true;
		for(int j = 0; j < 50; j++){
			val[j] = (val[j] << 1) % (1LL<<(j+1));
			if(j <= i && bannedSet.find(make_pair(val[j], j+1)) != bannedSet.end()){
				valid = false;
			}
		}
		if(!valid){
			for(int j = 0; j < 50; j++){
				val[j]++;
			}
			res += "1";
		} else {
			res += "0";
		}
	}
	cout<<res<<endl;
}


int main(){
	cin>>t;
	check = true;
	for(int tc = 0; tc < t; tc++){
		cin>>s;
		check &= insertBanned(convertToInt(s), s.size());
	}
	if(!check){
		cout<<"Tidak memiliki solusi"<<endl;
	} else {
		solve();
	}
}