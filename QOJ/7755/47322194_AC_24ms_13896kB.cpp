#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int MAXN = 200011;
vector<int>g[MAXN];
int fa[MAXN],sz[MAXN],rt[MAXN];
void dfs(int u,int r)
{
	sz[u]=1,rt[u]=r;
	for(auto v:g[u])
		if(v!=fa[u])fa[v]=u,dfs(v,r),sz[u]+=sz[v];
}
int f(int n){return n&1?1:2;}
int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;++i)
	{
		int u,v;
		cin>>u>>v;
		g[u].emplace_back(v),g[v].emplace_back(u);
	}
	int sg=0;
	for(int u=1;u<=n;++u)
		if(!rt[u])
		{
			dfs(u,u);
			if(sz[u]&1)sg^=1;
			else sg^=2;
		}
	int ans=0;
	for(int u=1;u<=n;++u)
	{
		int p=fa[u],r=rt[u];
		if(p)
		{
			if( (sg^f(sz[r])^f(sz[u])^f(sz[r]-sz[u]) )==0)++ans;
		}
		int x=sg^f(sz[r]);
		for(auto v:g[u])
			if(v==fa[u])x^=f(sz[r]-sz[u]);
			else x^=f(sz[v]);
		if(!x)++ans;
	}
	cout<<ans<<'\n';
	return 0;
}