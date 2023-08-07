#include "bits/stdc++.h"
const int MAXN = 1011;
int f[MAXN][MAXN*10][2];
int a[MAXN],b[MAXN];
int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int n;
	std::cin>>n;
	for(int i=1;i<=n;++i)std::cin>>a[i];
	for(int i=1;i<=n;++i)std::cin>>b[i];
	memset(f,0x3f,sizeof f);
	f[0][0][0]=0;
	int sumb=0;
	for(int i=1;i<=n;++i)
	{
		sumb+=b[i];
		for(int j=0;j<=sumb;++j)
		{
			if(j>=b[i])f[i][j][1]=std::max(std::min(f[i-1][j-b[i]][0],f[i-1][j-b[i]][1]),j)+a[i];
			f[i][j][0]=f[i-1][j][1]+a[i];
		}
	}
	int ans=2e9;
	for(int j=0;j<=sumb;++j)ans=std::min(ans,f[n][j][1]);
	printf("%d\n",ans);
	return 0;
}