#include<bits/stdc++.h>
using namespace std;

int N;
long long petak[505][505], ans[505];

int main()
{
	cin >> N;
	for(int i = 1; i <= N; i++)
	{
		ans[i] = -1;
		for(int j = 1; j <= N; j++)
		{
			cin >> petak[i][j];
		}
	}
	
	// cek diagonal, kalau positif, bye
	for(int i = 1; i <= N; i++)
	{
		if(petak[i][i] > 0)
		{
			cout << "NO" << endl;
			return 0;
		}
		petak[i][i] = 0;
	}
	
	// hasil transposenya harus sama.
	for(int i = 1; i <= N; i++)
	{
		for(int j = 1; j <= i; j++)
		{
			if(petak[i][j] == -1)
			{
				if(petak[j][i] == -1) continue;
				
				petak[i][j] = petak[j][i];
			}
			else
			{
				if(petak[j][i] == -1)
				{
					petak[j][i] = petak[i][j];
				}
				
				if(petak[j][i] == petak[i][j]) continue;
				
				cout << "NO" << endl;
				return 0;
			}
		}
	}
	for(int i = 1; i <= N; i++)
	{
//		if(ans[i] == -1) ans[i] = 0;
		
		if(ans[i] == -1)
		{
			for(int j = i + 1; j <= N; j++)
			{
				if(petak[i][j] == -1) continue;
				
				if(ans[j] == -1)
				{
					ans[i] = 0;
					ans[j] = petak[i][j];
				}
				else
				{
					ans[i] = (ans[j] ^ petak[i][j]);
				}
				j = N + 1;
			}
			
			if(ans[i] == -1) ans[i] = 0;
		}
		
		for(int j = i + 1; j <= N; j++)
		{
			if(petak[i][j] == -1) continue;
			
			if(ans[j] == -1)
			{
				ans[j] = (ans[i] ^ petak[i][j]);
			}
			
			if((ans[i] ^ ans[j]) == petak[i][j]) continue;
			
			cout << "NO" << endl;
			return 0;
		}
	}
	// bakalan pasti ketemu jawabannya
	
	
	cout << "YES" << endl;
	for(int i = 1; i <= N; i++)
	{
		if(i == 1) cout << ans[i];
		else cout << " " << ans[i];
	}
	
	cout << endl;
}
