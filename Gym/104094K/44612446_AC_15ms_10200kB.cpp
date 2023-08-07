#include "bits/stdc++.h"
typedef long long ll;
const int mod = 1e9+7;
const int MAXN = 511;
struct one
{
	int ans,cnt;
	one(int _ans=0,int _cnt=0){ans=_ans,cnt=_cnt;}
	one(ll _ans,ll _cnt){ans=_ans%mod,cnt=_cnt%mod;}
	one operator* (int k)
	{
		return one(ll(ans)*k%mod,ll(cnt)*k%mod);
	}
};
one f[MAXN][MAXN],s0[MAXN][MAXN],sw[MAXN][MAXN],sr[MAXN][MAXN],swr[MAXN][MAXN];

int cal(int n,int m,int i,int j)
{
	return ll(n-i+1)*(m-j+1)%mod;
}
one ask(one a[MAXN][MAXN],int n,int m)
{
	if(n<=0||m<=0)return one{0,0};
	return a[n][m];
}
int main()
{
	int n,m;
	std::cin>>n>>m;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
		{
			//printf("consider (%d,%d)\n",i,j);
			f[i][j]=one{i*j,1};
			one f0=ask(s0,i-2,j-2)*(i-1)*(j-1);
			one fr=ask(sr,i-2,j-2)*(i-1);
			one fw=ask(sw,i-2,j-2)*(j-1);
			one fwr=ask(swr,i-2,j-2);
			one tot((ll(f0.ans)-fr.ans-fw.ans+fwr.ans)%mod,(ll(f0.cnt)-fr.cnt-fw.cnt+fwr.cnt)%mod);
			//printf("tot=(%d,%d)\n",tot.ans,tot.cnt);
			f[i][j].ans=(ll(f[i][j].ans)+tot.ans+ll(tot.cnt)*i%mod*j%mod)%mod;
			f[i][j].cnt=(ll(f[i][j].cnt)+tot.cnt)%mod;
			s0[i][j]=one((ll(s0[i-1][j].ans)+ s0[i][j-1].ans-s0[i-1][j-1].ans+f[i][j].ans)%mod,(ll(s0[i-1][j].cnt)+ s0[i][j-1].cnt-s0[i-1][j-1].cnt+f[i][j].cnt)%mod);
			sw[i][j]=one((ll(sw[i-1][j].ans)+ sw[i][j-1].ans-sw[i-1][j-1].ans+ll(i)*f[i][j].ans)%mod,(ll(sw[i-1][j].cnt)+ sw[i][j-1].cnt-sw[i-1][j-1].cnt+ll(i)*f[i][j].cnt)%mod);
			sr[i][j]=one((ll(sr[i-1][j].ans)+ sr[i][j-1].ans-sr[i-1][j-1].ans+ll(j)*f[i][j].ans)%mod,(ll(sr[i-1][j].cnt)+ sr[i][j-1].cnt-sr[i-1][j-1].cnt+ll(j)*f[i][j].cnt)%mod);
			swr[i][j]=one((ll(swr[i-1][j].ans)+ swr[i][j-1].ans-swr[i-1][j-1].ans+ll(i)*j%mod*f[i][j].ans)%mod,(ll(swr[i-1][j].cnt)+ swr[i][j-1].cnt-swr[i-1][j-1].cnt+ll(i)*j%mod*f[i][j].cnt)%mod);
			//printf("F[%d,%d]=(%d,%d)\n",i,j,f[i][j].ans,f[i][j].cnt);
		}
	printf("%d\n",(f[n][m].ans+mod)%mod);
	return 0;
}