#include "bits/stdc++.h"
typedef long long ll;
const int mod = 1e9+7;
const int MAXN = 511;
struct one
{
	int ans,cnt;
};
one f[MAXN][MAXN];

int cal(int n,int m,int i,int j)
{
	return ll(n-i+1)*(m-j+1)%mod;
}
int main()
{
	int n,m;
	std::cin>>n>>m;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
		{
			f[i][j]=one{i*j,1};
			for(int w=1;w<=i-2;++w)
				for(int r=1;r<=j-2;++r)
				{
					one cur=f[w][r];
					cur.ans=ll(cur.ans)*cal(i-2,j-2,w,r)%mod;
					cur.cnt=ll(cur.cnt)*cal(i-2,j-2,w,r)%mod;
					f[i][j].ans=(ll(f[i][j].ans)+cur.ans+ll(i)*j%mod*cur.cnt)%mod;
					f[i][j].cnt=(f[i][j].cnt+cur.cnt)%mod;
				}
				//printf("F[%d,%d]=(%d,%d)\n",i,j,f[i][j].ans,f[i][j].cnt);
		}
	printf("%d\n",f[n][m].ans);
	return 0;
}