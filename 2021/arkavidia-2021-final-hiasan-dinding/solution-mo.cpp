/*
 * Alternate Solution arkavidia-2021-hiasan-dinding
 * Author: Jauhar Wibisono
 */

// mo's algorithm
#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5+3, maxq = 2e5+3, sqrtn = sqrt(maxn);
const long long dummy = 1e10;
int n, q;
vector<pair<pair<long long, long long>, bool>> p;
long long prev_x, prev_y;
bool lower;
pair<pair<int, int>, int> queries[maxq];
long long cur_area, cur_l, cur_r;
deque<pair<long long, long long>> ud, ld;
long long ans[maxq];

int lb(long long x){
	int l = 0, r = p.size()-1, ret = p.size();
	while (l <= r){
		int mid = (l+r)/2;
		if (p[mid].first.first >= x){
			ret = mid;
			r = mid-1;
		}
		else l = mid+1;
	}
	return ret;
}

int ub(long long x){
	int l = 0, r = p.size()-1, ret = -1;
	while (l <= r){
		int mid = (l+r)/2;
		if (p[mid].first.first <= x){
			ret = mid;
			l = mid+1;
		}
		else r = mid-1;
	}
	return ret;
}

bool cmp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b){
	if (a.first.first/sqrtn != b.first.first/sqrtn) return a.first.first/sqrtn < b.first.first/sqrtn;
	return a.first.second < b.first.second;
}

long long triangle_area(pair<long long, long long> a, pair<long long, long long> b, pair<long long, long long> c){
	return a.first*b.second - a.second*b.first + b.first*c.second - b.second*c.first + c.first*a.second - c.second*a.first;
}

void cek(){
	cout << cur_l << " " << cur_r << " " << cur_area << "\n";
}

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);
	cin >> n;
	lower = 0;
	prev_x = prev_y = -1e18;
	for (int i=0; i<n; i++){
		long long x, y;
		cin >> x >> y;
		if (!lower && (x < prev_x || (x == prev_x && y < prev_y))){
			lower = 1;
			p.push_back({{prev_x,prev_y},lower});
		}
		p.push_back({{x,y},lower});
		prev_x = x;
		prev_y = y; 
	}
	p.push_back({p[0].first,1});
	sort(p.begin(),p.end());
	cin >> q;
	for (int i=0; i<q; i++){
		long long l, r;
		cin >> l >> r;
		queries[i] = {{lb(l),ub(r)},i};
	}
	sort(queries,queries+q,cmp);
	cur_area = 0;
	cur_l = cur_r = 0;
	if (!p[0].second) ud.push_back(p[0].first);
	else ld.push_back(p[0].first);
	for (int i=0; i<q; i++){
		int l = queries[i].first.first, r = queries[i].first.second;
		if (l >= p.size() || r < 0 || l > r){
			ans[queries[i].second] = 0;
			continue;
		}
		while (cur_r < r){
			cur_r++;
			if (!p[cur_r].second && ud.empty()){
				ud.push_back(p[cur_r].first);
				if (!ld.empty()) cur_area += abs(triangle_area(ud.front(),ld.back(),ld.front()));
			}
			else if (p[cur_l].second && ld.empty()){
				ld.push_back(p[cur_r].first);
				if (!ud.empty()) cur_area += abs(triangle_area(ld.front(),ud.back(),ud.front()));
			}
			else{
				if (ud.empty()) cur_area += abs(triangle_area(ld.front(),p[cur_r].first,ld.back()));
				else if (ld.empty()) cur_area += abs(triangle_area(ud.front(),ud.back(),p[cur_r].first));
				else cur_area += abs(triangle_area(ud.back(),p[cur_r].first,ld.back()));
				if (!p[cur_r].second) ud.push_back(p[cur_r].first);
				else ld.push_back(p[cur_r].first);
			}
			// cek();
		}
		while (cur_r > r){
			if (!p[cur_r].second) ud.pop_back();
			else ld.pop_back();
			if (ud.empty() && !ld.empty()) cur_area -= abs(triangle_area(ld.front(),p[cur_r].first,ld.back()));
			else if (ld.empty() && !ud.empty()) cur_area -= abs(triangle_area(ud.front(),ud.back(),p[cur_r].first));
			else cur_area -= abs(triangle_area(ud.back(),p[cur_r].first,ld.back()));
			cur_r--;
			// cek();
		}
		while (cur_l < l){
			if (!p[cur_l].second) ud.pop_front();
			else ld.pop_front();
			if (ud.empty() && !ld.empty()) cur_area -= abs(triangle_area(ld.front(),p[cur_l].first,ld.back()));
			else if (ld.empty() && !ud.empty()) cur_area -= abs(triangle_area(ud.front(),ud.back(),p[cur_l].first));
			else cur_area -= abs(triangle_area(ud.front(),ld.front(),p[cur_l].first));
			cur_l++;
			// cek();
		}
		while (cur_l > l){
			cur_l--;
			if (!p[cur_l].second && ud.empty()){
				ud.push_front(p[cur_l].first);
				if (!ld.empty()) cur_area += abs(triangle_area(ud.front(),ld.back(),ld.front()));
			}
			else if (p[cur_l].second && ld.empty()){
				ld.push_front(p[cur_l].first);
				if (!ud.empty()) cur_area += abs(triangle_area(ld.front(),ud.back(),ud.front()));
			}
			else{
				if (ud.empty()) cur_area += abs(triangle_area(ld.front(),p[cur_l].first,ld.back()));
				else if (ld.empty()) cur_area += abs(triangle_area(ud.front(),ud.back(),p[cur_l].first));
				else cur_area += abs(triangle_area(ud.front(),ld.front(),p[cur_l].first));
				if (!p[cur_l].second) ud.push_front(p[cur_l].first);
				else ld.push_front(p[cur_l].first);
			}
			// cek();
		}
		ans[queries[i].second] = cur_area;
	}
	for (int i=0; i<q; i++) cout << ans[i]/2 << ((ans[i]&1) ? ".5" : ".0") << "\n";
}