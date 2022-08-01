// Tumpukan Piring Pizza

#include<bits/stdc++.h>
using namespace std;

int main(){
    int N,M,Q,op,i,j,k,j1,j2,i1,i2;
    int P[150][150]; 
    cin >> N >> M >> Q; // N unused

    for ( i = 1; i <= M; i++) // Init M Stacks
    {
        cin>>P[i][0];
        for( j = 1;j <= P[i][0];j++) cin>>P[i][j];
    }

    for (k = 1; k <= Q; k++) 
    {
        cin>>op;
        if(op==1){ // Create new stack j, push i to the stack j
            cin>>i>>j;
            if(j>M) M=j;
            P[j][P[j][0]+1] = i;
            P[j][0]++;
        }
        if(op==2){ // Pop j top
            cin>>j;
            if(P[j][0]!=0){
                P[j][P[j][0]] = 0;
                P[j][0]--;
            }
        }
        if(op==3){ // Push stack j1 to j2 , empty j1
            cin>>j1>>j2;
            i1 = 1; i2 = P[j2][0]+1;
            if(j2>M) M=j2;
            if(P[j1][0] != 0){
                while(P[j1][i1]!=0){
                    P[j2][i2] = P[j1][i1]; i2++; P[j2][0]++;
                    P[j1][i1] = 0; i1++; P[j1][0]--;
                }
            }

        }
    }
    for(i=1;i<=M;i++){ //Output
        if(P[i][0]!=0){
            cout<<i<<" : ";
            for(j=1;j<=P[i][0];j++) cout<< P[i][j]<<" ";
            cout<<endl;
        }
    }

    return 0;

    
    
    
}

