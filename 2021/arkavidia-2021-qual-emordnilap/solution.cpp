// cw dibalik wc

#include<bits/stdc++.h>
using namespace std;
int main(){
	string s;
	bool c = true;
	getline(cin,s);
	for (int i=0;i<s.length();i++){
		if (int(s[i]) >= 65 && int(s[i]) <= 90){
			s[i] += 32;
		}
		
		if (int(s[i]) < 48 || (int(s[i]) > 57 && int(s[i]) < 65) || (int(s[i]) > 90 && int(s[i]) < 97) || int(s[i]) > 122)
		c = false;
	}
	
	if (c){
		for (int i=s.length()-1;i>=0;i--){
			cout<<s[i];
		}
		cout<<endl;
	}
	else {
		cout<<"Emor tidak beruntung :("<<endl;
	}
	return 0;
}
