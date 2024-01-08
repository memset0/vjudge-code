#include<bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define debug(x) cerr<<#x<<": "<<x<<endl
typedef long long ll;
const int N=1e6+9,mod=998244353;
struct DSU
{
	int fa[N],size[N];
	void init(int n)
	{
		for(int i=1;i<=n;++i)fa[i]=i,size[i]=1;
	}
	int find(int x)
	{
		if(fa[x]==x)return x;
		return fa[x]=find(fa[x]);
	}
	int getsz(int x)
	{
		return size[find(x)];
	}
	void uni(int x,int y)
	{
		x=find(x),y=find(y);
		if(x==y)
		{
			fprintf(stderr,"Error! union %d and %d\n",x,y);
		}
		fa[x]=y,size[y]+=size[x];
	}
}s;
std::vector<int>g[N];
int ff[N];
int inv[N];
std::pair<int,int> a[N];
void dfs(int u)
{
	for(auto v:g[u])
		if(v!=ff[u])
		{
			ff[v]=u,dfs(v);
		}
}
int main()
{
	std::ios::sync_with_stdio(0),std::cin.tie(0);
	int n;
	std::cin>>n;
	inv[1]=1;
	for(int i=2;i<=n;++i)inv[i]=ll(mod-mod/i)*inv[mod%i]%mod;
	for(int i=1;i<n;++i)std::cin>>a[i].first>>a[i].second;
	for(int i=1;i<n;++i)
	{
		int x,y;
		std::cin>>x>>y;
		g[x].emplace_back(y),g[y].emplace_back(x);
	}
	dfs(1);
	s.init(n);
	int ans=1;
	for(int i=1;i<n;++i)
	{
		int x=a[i].first,y=a[i].second;
		int p=s.find(x),q=s.find(y);
		if(ff[p]&&s.find(ff[p])==q)
		{
			ans=ll(ans)*inv[s.getsz(p)]%mod*inv[s.getsz(q)]%mod;
			s.uni(p,q);
		}
		else if(ff[q]&&s.find(ff[q])==p)
		{
			ans=ll(ans)*inv[s.getsz(p)]%mod*inv[s.getsz(q)]%mod;
			s.uni(q,p);
		}
		else ans=0;
	}
	std::cout<<ans<<std::endl;
	return 0;
}