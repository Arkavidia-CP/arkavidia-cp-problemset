/* Author: Jauhar Wibisono
 * Solution arkavidia-2021-kinon-dan-stack
 */

#include <bits/stdc++.h>
using namespace std;

const int maxq=1e5+4, maxx=1e5+4, maxt=1e9;
int q, x[maxq], t[maxq];
stack<int>st1[maxq];
stack<int>st2[maxx];
map<int,int>active_t; // maps t to idx of st2
set<int>st2_kosong;
int ans;

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);
	cin >> q;
	for (int i=0;i<q;i++) cin >> x[i];
	// tentuin waktu keluar tiap elemen, greedy
	for (int i=0;i<q;i++) t[i]=maxt-i;
	for (int i=0;i<q;i++){
		if (x[i]>0) st1[x[i]].push(i);
		else{
			t[st1[-x[i]].top()]=i;
			st1[-x[i]].pop();		
		}
	}
	// simulasiin add-remove elemen, greedy
	ans=0;
	for (int i=0;i<q;i++){
		if (x[i]>0){
			auto it=active_t.lower_bound(t[i]);
			if (it==active_t.end()){
				// add elemen ke stack kosong
				if (st2_kosong.empty()){
					st2[ans].push(t[i]);
					active_t[t[i]]=ans;
					ans++;
				}
				else{
					st2[*st2_kosong.begin()].push(t[i]);
					active_t[t[i]]=(*st2_kosong.begin());
					st2_kosong.erase(st2_kosong.begin());
				}
			}
			else{
				// add elemen ke stack berisi
				st2[(*it).second].push(t[i]);
				active_t[t[i]]=(*it).second;
				active_t.erase((*it).first);
			}
		}
		else{
			// remove elemen
			int idx=active_t[i];
			active_t.erase(i);
			st2[idx].pop();
			if (st2[idx].empty()) st2_kosong.insert(idx);
			else active_t[st2[idx].top()]=idx;
		}
		// debug
		/*
		for (int j=0;j<ans;j++) cout << st2[j].size() << " ";
		cout << " | ";
		for (int j=0;j<ans;j++){
			if (st2[j].empty()) cout << "- ";
			else cout << st2[j].top() << " ";
		}
		cout << "\n";
		*/
	}
	cout << ans << "\n";
}