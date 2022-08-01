// CW dibalik wc

#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    string S;int i;bool alnum;
    cin >> S;
    i = 0;
    alnum = true;
    while(alnum && i<S.length()){
        if(!isalnum(S[i])) alnum = false;
        S[i] = tolower(S[i]);
        i++;
    }
    reverse(S.begin(),S.end());
    if(alnum) cout<<S;
    else cout<<"Hokki tidak beruntung :(\n";

    return 0;
    
    

}