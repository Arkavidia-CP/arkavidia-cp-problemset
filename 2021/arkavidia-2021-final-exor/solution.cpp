#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define MOD 1000000007
#define INF 1234567890
#define pii pair<LL, LL>
#define LL long long
using namespace std;

int main()
{
    //clock_t start = clock();
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    LL n;
    cin >> n;
    LL a[n + 5][n + 5];
    for (LL i = 1; i <= n; i++)
    {
        for (LL j = 1; j <= n; j++)
        {
            cin >> a[i][j];
        }
    }

    bool can = 1;

    // fill in diagonals (must be 0)
    for (LL i = 1; i <= n; i++)
    {
        if (a[i][i] == -1)
            a[i][i] = 0;
        else if (a[i][i] > 0)
            can = 0;
    }

    // reflection (a[i][j] == a[j][i])
    for (LL i = 1; i <= n; i++)
    {
        for (LL j = 1; j <= n; j++)
        {
            if (a[i][j] != -1 && a[j][i] != -1)
            {
                if (a[i][j] != a[j][i])
                    can = 0;
            }
            else if (a[i][j] != -1)
            {
                a[j][i] = a[i][j];
            }
            else if (a[j][i] != -1)
            {
                a[i][j] = a[j][i];
            }
        }
    }

    // "floyd warshall" to fill in the gaps and check if there is no solution
    for (LL k = 1; k <= n; k++)
    {
        for (LL i = 1; i <= n; i++)
        {
            for (LL j = 1; j <= n; j++)
            {
                if (a[i][k] != -1 && a[k][j] != -1)
                {
                    if (a[i][j] == -1)
                    {
                        a[i][j] = (a[i][k] ^ a[k][j]); // tambal
                    }
                    else if (a[i][j] == (a[i][k] ^ a[k][j]))
                    {
                        continue; // filled. no changes.
                    }
                    else
                    {
                        can = 0; // no solution
                    }
                }
            }
        }
    }

    // for (LL i=1;i<=n;i++) {
    //     for YES1;j<=n;j++) {
    //         cerr << a[i][j] << "\t";
    //     }
    //     cerr << endl;
    // }

    if (!can)
    {
        cout << "NO" << endl;
        return 0;
    }

    LL ans[n + 5];
    memset(ans, -1, sizeof(ans));
    // place 0 in front, then make all elements connected to i = 0^a[i][j], which is a[i][j]
    for (LL i = 1; i <= n; i++)
    {
        if (ans[i] != -1)
            continue;
        ans[i] = 0;
        for (LL j = i + 1; j <= n; j++)
        {
            if (a[i][j] != -1 && ans[j] == -1)
            {
                ans[j] = a[i][j];
            }
        }
    }

    cout << "YES" << endl;
    for (LL i = 1; i <= n; i++)
    {
        cout << ans[i];
        if (i != n)
            cout << " ";
    }
    cout << endl;
    //cerr << fixed << setprecision(3) << (clock()-start)*1./CLOCKS_PER_SEC << endl;
    return 0;
}