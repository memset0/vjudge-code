#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#define mod 998244353

using namespace std;
typedef long long ll;
const int MAXN = 105, MAXM = 2005;
int n,m,a[MAXN][MAXM],sum[MAXN][MAXM];
ll f[MAXN][MAXN*2],g[MAXN][MAXN];

int main()
{
	cin >> n >> m;
	for(int i = 1; i<=n; i++)
	    for(int j = 1; j<=m; j++)
	    {
	        scanf("%d",&a[i][j]);
	        sum[i][0] = (sum[i][0]+a[i][j])%mod;
		}
    for(int i = 1; i<=n; i++)
        for(int j = 1; j<=m; j++)
            sum[i][j] = (sum[i][0]-a[i][j]+mod)%mod;
    ll ans = 0;
    for(int col = 1; col<=m; col++)
    {
        memset(f,0,sizeof(f));
        f[0][n] = 1;
        for(int i = 1; i<=n; i++)
            for(int j = n-i; j<=n+i; j++) 
                f[i][j] = (f[i-1][j]+f[i-1][j-1]*a[i][col]%mod+f[i-1][j+1]*sum[i][col]%mod)%mod;
        for(int j = 1; j<=n; j++)
            ans = (ans+f[n][n+j])%mod;
	}
	g[0][0] = 1;
	for(int i = 1; i<=n; i++)
	    for(int j = 0; j<=n; j++) 
		    g[i][j] = (g[i-1][j]+(j>0?g[i-1][j-1]*sum[i][0]%mod:0))%mod;
    for(int j = 1; j<=n; j++)
	    ans = (ans-g[n][j]+mod)%mod;  
	cout << ans*(mod-1)%mod << endl;
	return 0;
}
// dafdsfadf adf ad a dfadsf adsf a d 