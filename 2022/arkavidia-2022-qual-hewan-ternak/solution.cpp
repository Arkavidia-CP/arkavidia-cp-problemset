#include <bits/stdc++.h>
using namespace std;
#define f(i,n) for (int i = 0;i < n;i++)
#define fc(i,s,n) for (int i = s;i < n;i++)
#define pll Point<long long>

template<class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x=0, T y=0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
    P operator+(P p) const { return P(x+p.x, y+p.y); }
    P operator-(P p) const { return P(x-p.x, y-p.y); }
    T cross(P p) const { return x*p.y - y*p.x; }
    T cross(P a, P b) const { return (a-*this).cross(b-*this); }
    T dist2() const { return x*x + y*y; }
    double dist() const { return sqrt((double)dist2()); }
    friend ostream& operator<<(ostream& os, P p) {
        return os << "(" << p.x << "," << p.y << ")"; }
};

int main(){
    int n;
    cin >> n;
    vector<pll> inp(n);
    f(i,n){
        cin >> inp[i].x >> inp[i].y;
    }
    pll minP = inp[0];
    f(i,n){
        minP = min(minP,inp[i]);
    }
    sort(inp.begin(),inp.end(),
            [minP](pll a, pll b) -> bool {
                return ((minP.cross(a,b) == 0 && (a-minP).dist2() < (b-minP).dist2()) || minP.cross(a,b) > 0);
            }
        );
    int idxLastColl = n-2;
    while (minP.cross(inp[idxLastColl],inp[n-1]) == 0) idxLastColl--;
    idxLastColl++;
    reverse(inp.begin()+idxLastColl,inp.end());

    vector<pll> convP;
    f(i,n){
        while (convP.size() > 1 && convP[convP.size()-2].cross(convP[convP.size()-1],inp[i]) < 0){
            convP.pop_back();
        }
        convP.push_back(inp[i]);
    }
    long long best1,best2;
    long long luasTotal = 0;
    fc(i,1,convP.size()-1){
        luasTotal += convP[0].cross(convP[i],convP[i+1]);
    }
    best1 = 0; best2 = luasTotal;
    f(base,convP.size()-2){
        long long luas1,luas2;
        luas1 = luasTotal;
        luas2 = 0;
        fc(i, base+1, convP.size()-1){
            long long tmpLuas = convP[base].cross(convP[i],convP[i+1]);
            luas1 -= tmpLuas;
            luas2 += tmpLuas;
            if (llabs(luas1-luas2) < llabs(best1-best2)){
                best1 = luas1;
                best2 = luas2;
            }
        }
    }
    if (best1 > best2) swap(best1,best2);
    printf("%.3Lf %.3Lf\n",best1/(long double)2.0,best2/(long double)2.0);
}