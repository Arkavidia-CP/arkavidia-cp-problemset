/*
 * Solution arkavidia-2021-hiasan-dinding
 * Author: Jauhar Wibisono
 */

#include <bits/stdc++.h>
using namespace std;

int n, q;
vector<long long> ux, uy, lx, ly; // upper xy, lower xy
long long prev_x = -1e10, prev_y = -1e10;
vector<long long> up, lp; // upper prefix, lower prefix

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);
	cin >> n;

	bool is_upper = 1;
	for (int i=0; i<n; i++){
		long long x, y;
		cin >> x >> y;
		if (is_upper && (x < prev_x || (x == prev_x && y < prev_y))){
			lx.push_back(prev_x);
			ly.push_back(prev_y);
			is_upper = 0;
		}
		if (is_upper){
			ux.push_back(x);
			uy.push_back(y);
		}
		else{
			lx.push_back(x);
			ly.push_back(y);
		}
		prev_x = x;
		prev_y = y;
	}
	if (lx.empty()){
		lx.push_back(prev_x);
		ly.push_back(prev_y);
	}
	lx.push_back(ux[0]);
	ly.push_back(uy[0]);
	reverse(lx.begin(),lx.end());
	reverse(ly.begin(),ly.end());

	/*
	cout << "upper: ";
	for (int i=0; i<(int)ux.size(); i++) cout << "(" << ux[i] << " " << uy[i] << ")";
	cout << "\n";
	cout << "lower: ";
	for (int i=0; i<(int)lx.size(); i++) cout << "(" << lx[i] << " " << ly[i] << ")";
	cout << "\n";
	*/

	up.resize(1+ux.size());
	lp.resize(1+lx.size());
	up[0] = lp[0] = up[1] = lp[1] = 0;
	for (int i=2; i<=(int)ux.size(); i++) up[i] = up[i-1] + ux[i-2]*uy[i-1] - ux[i-1]*uy[i-2];
	for (int i=2; i<=(int)lx.size(); i++) lp[i] = lp[i-1] + lx[i-2]*ly[i-1] - lx[i-1]*ly[i-2];

	/*
	cout << "upper prefix: ";
	for (int i=1; i<(int)up.size(); i++) cout << up[i] + ux[i-1]*uy[0] - ux[0]*uy[i-1] << " ";
	cout << "\n";
	cout << "lower prefix: ";
	for (int i=1; i<(int)lp.size(); i++) cout << lp[i] + lx[i-1]*ly[0] - lx[0]*ly[i-1] << " ";
	cout << "\n";
	*/

	cin >> q;
	while (q--){
		long long l, r;
		cin >> l >> r;
		int ul = lower_bound(ux.begin(),ux.end(),l) - ux.begin(); // upper l
		int ur = upper_bound(ux.begin(),ux.end(),r) - ux.begin(); // upper r
		int ll = lower_bound(lx.begin(),lx.end(),l) - lx.begin(); // lower l
		int lr = upper_bound(lx.begin(),lx.end(),r) - lx.begin(); // lower r

		/*
		cout << "upper: ";
		for (int i=ul; i<ur; i++) cout << "(" << ux[i] << "," << uy[i] << ")";
		cout << "\n";
		cout << "lower: ";
		for (int i=ll; i<lr; i++) cout << "(" << lx[i] << "," << ly[i] << ")";
		cout << "\n";
		*/
		// cout << "upper = [" << ul << "," << ur-1 << "], lower = [" << ll << "," << lr-1 << "]\n";
		long long ua = ((ul < ur && ul < (int)ux.size()) ? up[ur] - up[ul+1] + ux[ur-1]*uy[ul] - ux[ul]*uy[ur-1] : 0); // upper area
		long long la = ((ll < lr && ll < (int)lx.size()) ? lp[lr] - lp[ll+1] + lx[lr-1]*ly[ll] - lx[ll]*ly[lr-1] : 0); // lower area
		long long ma = 0; // middle area
		if (ul < ur && ll < lr){
			// ada middle area
			ma += ux[ul]*uy[ur-1] - ux[ur-1]*uy[ul];
			ma += ux[ur-1]*ly[lr-1] - lx[lr-1]*uy[ur-1];
			ma += lx[lr-1]*ly[ll] - lx[ll]*ly[lr-1];
			ma += lx[ll]*uy[ul] - ux[ul]*ly[ll]; 
		}
		// cout << "upper lower mid = " << ua << " " << la << " " << ma << "\n";
		long long ans = abs(ua) + abs(la) + abs(ma);
		cout << ans/2 << ((ans&1) ? ".5" : ".0") << "\n";
	}		
}