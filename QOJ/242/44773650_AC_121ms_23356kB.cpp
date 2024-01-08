#include "bits/stdc++.h"
typedef long long ll;
const int MAXN = 1000011,mod = 1e9+7;
int a[MAXN],s[MAXN],top;
int ls[MAXN],rs[MAXN];
int inv[MAXN];
void init()
{
	int n=MAXN-5;
	inv[1]=1;
	for(int i=2;i<=n;++i)inv[i]=ll(mod-mod/i)*inv[mod%i]%mod;
}
int ans=1;
void dfs(int l,int r,int p)
{
	if(l>=r)return;
	// std::cerr<<"DFS "<<l<<" "<<r<<" "<<p<<"\n";
	ans=ll(ans)*inv[r-l+1]%mod;
	dfs(l,p-1,ls[p]),dfs(p+1,r,rs[p]);
}
int fl,lst;
int main()
{
	std::ios::sync_with_stdio(0),std::cin.tie(0);
	init();
	int task;std::cin>>task;
	while(task--)
	{
		ans=1;
		int n;std::cin>>n;
		for(int i=1;i<=n;++i)std::cin>>a[i],ls[i]=rs[i]=0;
		top=0;
		for(int i=1;i<=n;++i)
		{
			// std::cerr<<"i="<<i<<"\n";
			fl=0;
			while(top&&a[s[top]]<a[i]){
				// std::cerr<<"top="<<top<<"\n";
				if(fl)rs[s[top]]=lst;
				fl=1,lst=s[top];
				--top;
			}
			if(fl)ls[i]=lst;
			s[++top]=i;
		}
		for(int i=1;i<top;++i)rs[s[i]]=s[i+1];
		// for(int i=1;i<=n;++i)printf("i=%d,ls=%d,rs=%d\n",i,ls[i],rs[i]);
		dfs(1,n,s[1]);
		printf("%lld\n",1ll*n*ans%mod*inv[2]%mod);
	}
	return 0;
}