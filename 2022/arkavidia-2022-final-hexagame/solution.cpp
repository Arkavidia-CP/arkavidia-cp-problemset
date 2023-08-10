#include <bits/stdc++.h>
using namespace std;
#define pll pair<long long, long long>

const long long maxn = 1024, maxk = 1048576, maxm = (1LL<<60), mod = 1e9+7;
long long n, k, ans;

// ys buat linesweep y
// xs buat catet tiap daerah di linesweep
long long area[maxn][7], ys[maxn*4];

// line sweep purposes
pll rectIs[4*maxn], rectNot[4*maxn], rectNot2[4*maxn];
long long triUpIn[4*maxn], triDoIn[4*maxn], trapNot[4*maxn][3];
long long nbRectIs, nbTriUp, nbTriDo;
long long nbRectNot, nbRectNot2, nbTrapNot;

// init queens game
long long queeny[maxk], dp[maxk];
set<pll> queen0, queen1;
pll templl;
void init(){
    //cout << "Init queen game:";
    queen0.insert({0,0}); queen1.insert({0,0});
    dp[0] = 0;
    dp[1] = 1;
    for(int i=1; i<maxk-1; i++){
        dp[i+1] = dp[i];
        if(queeny[i] == 0){
            dp[i+1]++;
            if(queeny[i-1] < 0){
                queeny[i] = queeny[i-2] + 3;
            }else{
                queeny[i] = queeny[i-1] + 2;
            }
            if(queeny[i] < maxk){
                queeny[queeny[i]] = -1;
            }
            queen0.insert({queeny[i], i});
            queen1.insert({queeny[i]-i, i});
        }
        if(i<15){
            //cout << " " << queeny[i];
        }
    }
    //cout << endl;
}

long long getRectSpecial(pll ld, pll ru){
    long long res = 0;
    if(ru.first > k){
        if(ru.second > k){
            res = (getRectSpecial(ld, {k,k}) + res) % mod;
            res += (ru.second/(k+1)-1) % mod * getRectSpecial({ld.first, 0}, {k,k});
            res %= mod;
            res = (getRectSpecial({ld.first,0}, {k,ru.second%(k+1)}) + res) % mod;
            res += (ru.first/(k+1)-1) % mod * getRectSpecial({0,0}, {k,ru.second%(k+1)});
            res %= mod;
            res = (getRectSpecial({0,0},{ru.first%(k+1),ru.second%(k+1)}) + res) % mod;
            res += (ru.second/(k+1)-1) % mod * getRectSpecial({0,0}, {ru.first%(k+1),k});
            res %= mod;
            res = (getRectSpecial({0,ld.second}, {ru.first%(k+1),k}) + res) % mod;
            res += (ru.first/(k+1)-1) % mod * getRectSpecial({0,ld.second}, {k,k});
            res %= mod;
            res += (ru.first/(k+1)-1) % mod * (ru.second/(k+1)-1) % mod * getRectSpecial({0,0},{k,k});
            res %= mod;
        }else{
            res = (getRectSpecial({ld.first, ld.second}, {k, ru.second%(k+1)}) + res) % mod;
            res += (ru.first/(k+1)-1) % mod * getRectSpecial({0,ld.second}, {k,ru.second%(k+1)});
            res %= mod;
            res = (getRectSpecial({0, ld.second}, {ru.first%(k+1), ru.second%(k+1)}) + res) % mod;
        }
    }else{
        if(ru.second > k){
            res = (getRectSpecial({ld.first, ld.second}, {ru.first%(k+1),k}) + res) % mod;
            res += (ru.second/(k+1)-1) % mod * getRectSpecial({ld.first,0}, {ru.first%(k+1),k});
            res %= mod;
            res = (getRectSpecial({ld.first, 0}, {ru.first%(k+1), ru.second%(k+1)}) + res) % mod;
        }else{ // base
            long long lo = ld.first, hi = ru.first+1;
            templl = *(queen0.lower_bound({ld.second, -1}));
            lo = max(templl.second, lo);
            templl = *(queen0.lower_bound({ru.second+1, -1}));
            hi = min(templl.second, hi);
            res = (res + dp[max(hi, lo)] - dp[lo]) % mod;

            lo = ld.second; hi = ru.second+1;
            templl = *(queen0.lower_bound({ld.first, -1}));
            lo = max(templl.second, lo);
            templl = *(queen0.lower_bound({ru.first+1, -1}));
            hi = min(templl.second, hi);
            res = (res + dp[max(hi, lo)] - dp[lo]) % mod;

            if(ld.first == 0 && ld.second == 0){
                res = (res+mod-1) % mod;
            }
        }
    }
    return res % mod;
}
long long getRect(pll ld, pll ru){
    if(ld.first > ru.first || ld.second > ru.second){
        return 0;
    }
    long long hor = ru.first - ld.first, ver = ru.second - ld.second;
    long long area = ((hor+1)%mod) * ((ver+1)%mod) % mod;
    ld.first %= (k+1); ld.second %= (k+1);
    ru.first = ld.first + hor; ru.second = ld.second + ver;

    return (area + mod - getRectSpecial(ld, ru) % mod) % mod;
}

long long getTriSpecial(pll ld, long long len){ // asumsi triangle up
    //cout << "ld len: " << ld.first << " " << ld.second << " " << len << endl;
    if(len == 0){
        return 0;
    }
    long long res = 0;
    if(ld.first > ld.second){

        if(ld.first + len - 1 <= k){
            long long hi, lo = ld.first;
            templl = *(queen0.lower_bound({ld.second+len-1, -1}));
            hi = templl.second;
            if(queen1.lower_bound({ld.second-ld.first, -1}) != queen1.end()){
                templl = *(queen1.lower_bound({ld.second-ld.first, -1}));
                lo = max(templl.second, lo);
                res = (res + dp[max(hi, lo)] - dp[lo]) % mod;
            }

            hi = ld.second - ld.first;
            templl = *(queen0.lower_bound({ld.first, -1}));
            lo = templl.second;
            if(queen1.lower_bound({ld.first-ld.second+1, -1}) != queen1.end()){
                templl = *(queen1.lower_bound({ld.first-ld.second+1, -1}));
                hi = min(templl.second, hi);
                res = (res + dp[max(hi, lo)] - dp[lo]) % mod;
            }

            if(ld.first == 0 && ld.second == 0){
                res = (res+mod-1) % mod;
            }
        }else{
            res = (getTriSpecial(ld, k+1-ld.first) + res) % mod;
            res = (getRectSpecial({ld.first, ld.second+k+1-ld.first}, {k, ld.second+len-1}) + res) % mod;
            res = (getTriSpecial({0,ld.second+k+1-ld.first}, len-(k+1-ld.first)) + res) % mod;

        }
    }else if(ld.first < ld.second){
        if(ld.second + len - 1 <= k){
            long long hi, lo = ld.first;
            //if(queen0.lower_bound({ld.second+len-1, -1}) != queen0.end()){
            templl = *(queen0.lower_bound({ld.second+len-1, -1}));
            hi = templl.second;
            if(queen1.lower_bound({ld.second-ld.first, -1}) != queen1.end()){
                templl = *(queen1.lower_bound({ld.second-ld.first, -1}));
                lo = max(templl.second, lo);
                res = (res + dp[max(hi, lo)] - dp[lo]) % mod;
            }
            //}

            hi = ld.second - ld.first;
            //if(queen0.lower_bound({ld.first, -1}) != queen0.end()){
            templl = *(queen0.lower_bound({ld.first, -1}));
            lo = templl.second;
            if(queen1.lower_bound({ld.first-ld.second+1, -1}) != queen1.end()){
                templl = *(queen1.lower_bound({ld.first-ld.second+1, -1}));
                hi = min(templl.second, hi);
                res = (res + dp[max(hi, lo)] - dp[lo]) % mod;
            }
            //}

            if(ld.first == 0 && ld.second == 0){
                res = (res+mod-1) % mod;
            }
        }else if((ld.first+len-1)%(k+1) < (ld.second+len-1)%(k+1)){
            res = (getTriSpecial(ld, k+1-ld.second) + res) % mod;
            res += ((ld.second+len-1)/(k+1)-1) % mod * getRectSpecial({ld.first,0}, {k,k});
            res %= mod;
            res = (getRectSpecial({ld.first,0}, {k,(ld.second+len-1)%(k+1)}) + res) % mod;
            res += ((ld.first+len-1)/(k+1)-1) % mod * getRectSpecial({0,0}, {k,(ld.second+len-1)%(k+1)});
            res %= mod;
            //long long templen = (ld.first+len)%(k+1);
            //res = (getTriSpecial({0,ld.second-ld.first}, (ld.first+len)%(k+1)) + res) % mod;
            long long hi, lo = 0;
            templl = *(queen0.lower_bound({ld.second-ld.first+(ld.first+len)%(k+1)-1, -1}));
            hi = templl.second;
            if(queen1.lower_bound({ld.second-ld.first, -1}) != queen1.end()){
                templl = *(queen1.lower_bound({ld.second-ld.first, -1}));
                lo = max(templl.second, lo);
                res = (res + dp[max(hi, lo)] - dp[lo]) % mod;
            }

            res -= (ld.first+len-1)/(k+1) % mod * getTriSpecial({0,k+2-ld.second+ld.first}, ld.second-ld.first-1);
            res = (res % mod + mod) % mod;
            res += ((ld.second+len-1)/(k+1)-1) % mod * getTriSpecial({0,ld.second-ld.first}, k+1-ld.second+ld.first);
            res %= mod;
            long long top = ld.second+len-1;
            res += ((top/(k+1)-2) % mod) * ((top/(k+1)-1) % mod) / 2 % mod * getRectSpecial({0,0},{k,k});
            res %= mod;
        }else{ // ru.first%(k+1) > ru.second%(k+1)
            res = (getTriSpecial(ld, k+1-ld.second) + res) % mod;
            res += ((ld.second+len-1)/(k+1)-1) % mod * getRectSpecial({ld.first,0}, {k,k});
            res %= mod;
            res = (getRectSpecial({ld.first,0}, {k,(ld.second+len-1)%(k+1)}) + res) % mod;
            res += ((ld.first+len-1)/(k+1)-1) % mod * getRectSpecial({0,0}, {k,(ld.second+len-1)%(k+1)});
            res %= mod;
            res = (getRectSpecial({0,0}, {k - ld.second+ld.first ,(ld.second+len-1)%(k+1)}) + res) % mod;
            res = (getTriSpecial({k+1-ld.second+ld.first, 0}, (ld.second+len) % (k+1)) + res) % mod;
            res -= (ld.first+len-1)/(k+1) % mod * getTriSpecial({0,k+2-ld.second+ld.first}, ld.second-ld.first-1);
            res = (res % mod + mod) % mod;
            res += ((ld.second+len-1)/(k+1)-1) % mod * getTriSpecial({0,ld.second-ld.first}, k+1-ld.second+ld.first);
            res %= mod;
            long long top = ld.second+len-1;
            res += ((top/(k+1)-2) % mod) * ((top/(k+1)-1) % mod) / 2 % mod * getRectSpecial({0,0},{k,k});
            res %= mod;
        }
    }else{
        if(ld.second + len - 1 <= k){
            long long hi, lo = ld.first;
            templl = *(queen0.lower_bound({ld.second+len, -1}));
            hi = templl.second;
            if(queen1.lower_bound({ld.second-ld.first, -1}) != queen1.end()){
                templl = *(queen1.lower_bound({ld.second-ld.first, -1}));
                lo = max(templl.second, lo);
                res = (res + dp[max(hi, lo)] - dp[lo]) % mod;
            }

            hi = ld.second - ld.first + 1;
            templl = *(queen0.lower_bound({ld.first, -1}));
            lo = templl.second;
            if(queen1.lower_bound({ld.first-ld.second+1, -1}) != queen1.end()){
                templl = *(queen1.lower_bound({ld.first-ld.second+1, -1}));
                hi = min(templl.second, hi);
                res = (res + dp[max(hi, lo)] - dp[lo]) % mod;
            }

            if(ld.first == 0 && ld.second == 0){
                res = (res+mod-1) % mod;
            }
        }else{
            long long top = (ld.first+len-1)%(k+1);
            res = (getTriSpecial(ld, k+1-ld.first) + res) % mod;
            res += (top/(k+1)-1) % mod * getRectSpecial({ld.first,0}, {k,k});
            res %= mod;
            res = (getRectSpecial({ld.first,0}, {k,top}) + res) % mod;
            res += (top/(k+1)-1) % mod * getRectSpecial({0,0}, {k,top%(k+1)});
            res %= mod;
            res = (getTriSpecial({0,0}, top%(k+1)+1 ) + res) % mod;
            res += (top/(k+1)-1) % mod * getTriSpecial({0,0}, k+1);
            res %= mod;
            res += ((top/(k+1)-1) % mod) * ((top/(k+1)-2) % mod) /2 % mod * getRectSpecial({0,0},{k,k});
            res %= mod;
        }
    }
    return res % mod;
}
long long getTri(pll ld, long long len, bool up){
    if(len <= 0){
        return 0;
    }
    ld.first %= (k+1); ld.second %= (k+1);
    if(!up){
        long long temp = ld.first; ld.first = ld.second; ld.second = temp;
    }
    long long area = (len+1) % mod * (len%mod) / 2 % mod;
    return (area + mod - getTriSpecial(ld, len) % mod) % mod;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    init();
    // input
    cin >> n >> k;
    for(int i=0; i<n; i++){
        cin >> area[i][0] >> area[i][1] >> area[i][2] >> area[i][3] >> area[i][4] >> area[i][5];
        area[i][6] = area[i][3] + area[i][4] - area[i][2];
        for(int j=0; j<6; j++){
            if(j%2){
                ys[4*i + j/2] = area[i][j];
            }
        }
        ys[4*i] = area[i][1];
        ys[4*i+1] = area[i][3];
        ys[4*i+2] = area[i][5]+1;
        ys[4*i+3] = area[i][6];
    }

    // line sweep y
    sort(ys, ys+4*n);
    ans = 0;
    for(int i=1; i<4*n; i++){
        if(ys[i] > ys[i-1]){
            //cout << ys[i-1] << " sampai " << ys[i]-1 << endl;
            // line sweep x, iterate over area
            nbRectIs = 0; nbTriDo = 0; nbTriUp = 0;
            for(int j=0; j<n; j++){
                if(area[j][6] <= area[j][1]){
                    if(area[j][3] <= ys[i-1] && ys[i-1] < area[j][6]){
                        // rect then triup
                        if(area[j][0] < area[j][2] + (ys[i-1]-area[j][3])){
                            rectIs[nbRectIs] = {area[j][0], area[j][2] + (ys[i-1]-area[j][3])}; nbRectIs++;
                        }
                        triUpIn[nbTriUp] = area[j][2] + (ys[i-1]-area[j][3]); nbTriUp++;

                    }else if(area[j][6] <= ys[i-1] && ys[i-1] < area[j][1]){
                        // rect
                        rectIs[nbRectIs] = {area[j][0], area[j][4]+1}; nbRectIs++;
                    }else if(area[j][1] <= ys[i-1] && ys[i-1] <= area[j][5]){
                        // trido then rect
                        triDoIn[nbTriDo] = area[j][0] + (ys[i-1]-area[j][1]); nbTriDo++;
                        if(area[j][0] + ys[i] - area[j][1] <= area[j][4]){
                            rectIs[nbRectIs] = {area[j][0] + ys[i] - area[j][1], area[j][4]+1}; nbRectIs++;
                        }
                    }
                }else{ // area[j][1] < area[j][6]
                    if(area[j][3] <= ys[i-1] && ys[i-1] < area[j][1]){
                        // rect then triup
                        if(area[j][0] < area[j][2] + (ys[i-1]-area[j][3])){
                            rectIs[nbRectIs] = {area[j][0], area[j][2] + (ys[i-1]-area[j][3])}; nbRectIs++;
                        }
                        triUpIn[nbTriUp] = area[j][2] + (ys[i-1]-area[j][3]); nbTriUp++;
                    }else if(area[j][1] <= ys[i-1] && ys[i-1] < area[j][6]){
                        // trido then rect then triup
                        triDoIn[nbTriDo] = area[j][0] + (ys[i-1]-area[j][1]); nbTriDo++;
                        if(area[j][0] + ys[i] - area[j][1] < area[j][2] + (ys[i-1]-area[j][3])){
                            rectIs[nbRectIs] = {area[j][0] + ys[i] - area[j][1], area[j][2] + (ys[i-1]-area[j][3])};
                            nbRectIs++;
                        }
                        triUpIn[nbTriUp] = area[j][2] + (ys[i-1]-area[j][3]); nbTriUp++;
                    }else if(area[j][6] <= ys[i-1] && ys[i-1] <= area[j][5]){
                        // trido then rect
                        triDoIn[nbTriDo] = area[j][0] + (ys[i-1]-area[j][1]); nbTriDo++;
                        if(area[j][0] + ys[i] - area[j][1] <= area[j][4]){
                            rectIs[nbRectIs] = {area[j][0] + ys[i] - area[j][1], area[j][4]+1}; nbRectIs++;
                        }
                    }
                }
            }
            // linesweep rectangle
            sort(rectIs, rectIs+nbRectIs);

            /*cout << "Rectangles:";
            for(int j=0; j<nbRectIs; j++){
                cout << " (" << rectIs[j].first << "," << rectIs[j].second << ")";
            }cout << endl;*/

            long long leftRectIs = rectIs[0].first, leftRectNot = rectIs[0].second; nbRectNot = 0;
            if(rectIs[0].first>0){
                rectNot[nbRectNot] = {0, rectIs[0].first}; nbRectNot++;
            }
            for(int j=1; j<nbRectIs; j++){
                if(rectIs[j].first > leftRectNot){
                    ans += getRect({leftRectIs, ys[i-1]}, {leftRectNot-1, ys[i]-1});
                    ans %= mod;
                    leftRectIs = rectIs[j].first;
                    rectNot[nbRectNot] = {leftRectNot, leftRectIs}; nbRectNot++;
                    leftRectNot = rectIs[j].second;
                }else{ // nyambung
                    leftRectNot = max(rectIs[j].second, leftRectNot);
                }
            }
            //cout << "leftRectIs, leftRectNot: " << leftRectIs << " " << leftRectNot << endl;
            ans += getRect({leftRectIs, ys[i-1]}, {leftRectNot-1, ys[i]-1});
            rectNot[nbRectNot] = {leftRectNot, maxm}; nbRectNot++;

            /*cout << "RectNots:";
            for(int j=0; j<nbRectNot; j++){
                cout << " (" << rectNot[j].first << "," << rectNot[j].second << ")";
            }cout << endl;*/

            // linesweep triangle down
            sort(triDoIn, triDoIn+nbTriDo);
            /*cout << "Triangle downs:";
            for(int j=0; j<nbTriDo; j++){
                cout << " " << triDoIn[j];
            }cout << endl;

            cout << "ans: " << ans << endl;*/

            long long rectNotIdx = 0; nbRectNot2 = 0; nbTrapNot = 0;
            for(int j=0; j<nbTriDo; j++){
                //cout << nbRectNot << " " << rectNot[rectNotIdx].first << " " << triDoIn[j]+ys[i]-ys[i-1] << endl;
                while(rectNotIdx < nbRectNot && rectNot[rectNotIdx].first < triDoIn[j]+ys[i]-ys[i-1]){
                    // Empty space terisi dengan Trido
                    if(rectNot[rectNotIdx].first < triDoIn[j]){ // add rect
                        rectNot2[nbRectNot2] = {rectNot[rectNotIdx].first, min(triDoIn[j], rectNot[rectNotIdx].second)};
                        nbRectNot2++;
                    }
                    if(triDoIn[j] < rectNot[rectNotIdx].second){ // add trapesium
                        trapNot[nbTrapNot][0] = max(triDoIn[j], rectNot[rectNotIdx].first);
                        trapNot[nbTrapNot][1] = min(triDoIn[j] + ys[i] - ys[i-1] - 1, rectNot[rectNotIdx].second);
                        trapNot[nbTrapNot][2] = ys[i-1] + min(0LL, rectNot[rectNotIdx].first - triDoIn[j]);
                        ans += getTri(
                            {trapNot[nbTrapNot][0], trapNot[nbTrapNot][2]},
                            min(triDoIn[j] + ys[i] - ys[i-1], rectNot[rectNotIdx].second)-trapNot[nbTrapNot][0], false
                        );
                        if(trapNot[nbTrapNot][2] > ys[i-1]){
                            ans += getRect(
                                {trapNot[nbTrapNot][0], ys[i-1]},
                                {trapNot[nbTrapNot][1]-1, trapNot[nbTrapNot][2]-1}
                            );
                        }
                        ans %= mod; nbTrapNot++;
                    }
                    if(rectNot[rectNotIdx].second > triDoIn[j] + ys[i] - ys[i-1]){
                        rectNot[rectNotIdx].first = triDoIn[j] + ys[i] - ys[i-1];
                    }else{
                        rectNotIdx++;
                    }
                }
            }
            while(rectNotIdx < nbRectNot){
                rectNot2[nbRectNot2] = rectNot[rectNotIdx];
                nbRectNot2++; rectNotIdx++;
            }

            /*cout << "RectNot2s:";
            for(int j=0; j<nbRectNot2; j++){
                cout << " (" << rectNot2[j].first << "," << rectNot2[j].second << ")";
            }cout << endl;*/

            // linesweep triangle up
            sort(triUpIn, triUpIn+nbTriUp);
            /*cout << "Triangle ups:";
            for(int j=0; j<nbTriUp; j++){
                cout << " " << triUpIn[j];
            }cout << endl;*/
            // Sekarang sweep dari kanan
            while(nbTriUp--){
                while(nbRectNot2 && (triUpIn[nbTriUp] < rectNot2[nbRectNot2-1].second)){ // Potong ke rectangle
                    long long tempmax = max(rectNot2[nbRectNot2-1].first - triUpIn[nbTriUp], 0LL);
                    long long tempmin = min(rectNot2[nbRectNot2-1].second, triUpIn[nbTriUp] + ys[i] - ys[i-1]);
                    ans += getTri(
                        {triUpIn[nbTriUp] + tempmax, ys[i-1] + tempmax},
                        tempmin - (triUpIn[nbTriUp] + tempmax), true
                    );
                    ans %= mod;

                    if(ys[i-1] + tempmin - triUpIn[nbTriUp] < ys[i]){
                        ans += getRect(
                            {triUpIn[nbTriUp] + tempmax, ys[i-1] + tempmin - triUpIn[nbTriUp]},
                            {tempmin, ys[i]-1}
                        );
                        ans %= mod;
                    }

                    if(rectNot2[nbRectNot2-1].first < triUpIn[nbTriUp]){
                        rectNot2[nbRectNot2-1].second = triUpIn[nbTriUp];
                    }else{
                        nbRectNot2--;
                    }
                }
                while(nbTrapNot && triUpIn[nbTriUp] < trapNot[nbTrapNot-1][1]){ // Potong ke trapesium
                    if(trapNot[nbTrapNot-1][0] < triUpIn[nbTriUp]){
                        ans += getTri(
                            {triUpIn[nbTriUp], trapNot[nbTrapNot-1][2]+1+triUpIn[nbTriUp]-trapNot[nbTrapNot-1][0]},
                            trapNot[nbTrapNot-1][1]-triUpIn[nbTriUp], true
                        );
                        ans %= mod;

                        ans += getRect(
                            {triUpIn[nbTriUp], trapNot[nbTrapNot-1][2]+1+trapNot[nbTrapNot-1][1]-trapNot[nbTrapNot-1][0]},
                            {trapNot[nbTrapNot-1][1]-1, ys[i]-1}
                        );
                        ans %= mod;

                        trapNot[nbTrapNot-1][1] = triUpIn[nbTriUp];
                    }else{
                        long long dif = ys[i-1] + trapNot[nbTrapNot-1][0] - triUpIn[nbTriUp];
                        ans += getTri(
                            {trapNot[nbTrapNot-1][0], max(trapNot[nbTrapNot-1][2]+1, dif)},
                            min(trapNot[nbTrapNot-1][1], triUpIn[nbTriUp]+ys[i]-ys[i-1])-trapNot[nbTrapNot-1][0], true
                        );
                        ans %= mod;

                        if(triUpIn[nbTriUp] + ys[i] - ys[i-1] > trapNot[nbTrapNot-1][1]){
                            ans += getRect(
                                {trapNot[nbTrapNot-1][0], ys[i-1] - triUpIn[nbTriUp] + trapNot[nbTrapNot-1][1]},
                                {trapNot[nbTrapNot-1][1]-1, ys[i]-1}
                            );
                            ans %= mod;
                        }

                        nbTrapNot--;
                    }
                }
            }

            //cout << "ans: " << ans << endl << endl;
        }
    }
    cout << ans << endl;
}
