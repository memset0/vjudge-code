#include<bits/stdc++.h>
typedef long long ll;
const int MAXN = 600011,mod = 998244353;
std::vector<int>g[MAXN];
int pw[MAXN],ans=1;
int dep[MAXN],cover[MAXN],fa[MAXN];
void dfs(int u)
{
	for(auto v:g[u])
		if(!dep[v])
		{
			dep[v]=dep[u]+1,fa[v]=u;
			dfs(v);
		}
		else if(dep[v]<dep[u]-1)
		{
			// cerr<<"! "<<(dep[u]-dep[v]+1)<<endl;
			ans=ll(ans)*(pw[dep[u]-dep[v]+1]-1)%mod;
			int p=u;
			while(p!=v)cover[p]=1,p=fa[p];
		}
}
int main()
{
#ifdef memset0
	freopen("F.in","r",stdin);
#endif
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		g[x].emplace_back(y),g[y].emplace_back(x);
	}
	pw[0]=1;
	for(int i=1;i<=n;++i)pw[i]=pw[i-1]*2%mod;
	for(int u=1;u<=n;++u)
		if(!dep[u])dep[u]=1,dfs(u);
	for(int u=1;u<=n;++u)
		if(!cover[u]&&dep[u]>1)ans=ans*2%mod;
	printf("%d\n",(ans+mod)%mod);
	return 0;
}///