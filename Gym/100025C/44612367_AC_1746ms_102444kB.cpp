#include "bits/stdc++.h"
void umax(int& a,int p){if(p>a)a=p;}
const int MAXN = 500011;
std::vector<int>g[MAXN],d[MAXN];
int res[MAXN],fa[MAXN],maxl[MAXN];
void dfs1(int u)
{
	maxl[u]=1;
	for(auto v:g[u])
	{
		if(v==fa[u])continue;
		fa[v]=u,dfs1(v);
		d[u].emplace_back(maxl[v]+1);
		umax(maxl[u],maxl[v]+1);
	}
}
void dfs2(int u,int pre)
{
	//printf("u=%d(pre=%d):",u,pre+1);
	d[u].emplace_back(pre+1);
	std::sort(d[u].begin(),d[u].end());
	//for(auto x:d[u])printf("%d ",x);
	//puts("");
	int m=d[u].size();
	for(int i=0;i<m;++i)
		umax(res[d[u][i]],m-i);
	std::vector<int>pr,su;
	pr.emplace_back(0);
	for(auto v:g[u])
		if(v!=fa[u])pr.emplace_back(maxl[v]+1);
	pr.emplace_back(0);
	su=pr;
	for(int i=1;i<int(pr.size());++i)umax(pr[i],pr[i-1]);
	for(int i=int(su.size())-2;i>=0;--i)umax(su[i],su[i+1]);
	int i=0;
	for(auto v:g[u])
		if(v!=fa[u])
		{
			//printf("u=%d,v=%d,%d %d\n",u,v,pr[i],su[i+2]);
			dfs2(v,std::max(pre+1,std::max(pr[i],su[i+2])));
			++i;
		}
}
int main()
{
	freopen("amoeba.in","r",stdin);
	freopen("amoeba.out","w",stdout);
	int n,A,B;
	scanf("%d%d%d",&n,&A,&B);
	for(int i=1;i<n;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		g[u].emplace_back(v),g[v].emplace_back(u);
	}
	dfs1(1),dfs2(1,0);
	for(int i=n;i;--i)umax(res[i],res[i+1]);
	for(int i=A+1;i<=B+1;++i)printf("%d\n",res[i]);
	return 0;
}