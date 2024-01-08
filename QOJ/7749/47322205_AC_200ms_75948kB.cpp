#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 1000011;
vector<int>fac[MAXN];
int cnt[MAXN],mul[MAXN];
void sieve(int n)
{
	cnt[1]=0;
	for(int i=2;i<=n;++i)
		if(fac[i].empty())
		{
			cnt[i]=cnt[i-1]+1;
			fac[i].emplace_back(i);
			for(int j=i<<1;j<=n;j+=i)
				fac[j].emplace_back(i);
		}
		else cnt[i]=cnt[i-1];
		
	for(int i=1;i<=n;++i)
	{
		mul[i]=1;
		for(auto x:fac[i])mul[i]*=x;
	}
}
bool is_prime(int n){return cnt[n]!=cnt[n-1];}
struct edge
{
	int u,v,w;
	bool operator< (const edge& you)const{return w<you.w;}
}e[MAXN];
struct DSU
{
	int fa[MAXN];
	void init(int n)
	{
		for(int i=1;i<=n;++i)fa[i]=i;
	}
	void init_range(int l,int r)
	{
		for(int i=l;i<=r;++i)fa[i]=i;
	}
	int find(int x)
	{
		if(fa[x]==x)return x;
		return fa[x]=find(fa[x]);
	}
	bool uni(int x,int y)
	{
		x=find(x),y=find(y);
		if(x==y)return 0;
		return fa[x]=y,1;
	}
}s;
int rest[MAXN];
int have[MAXN];
int main()
{
	//freopen("D.in","r",stdin);
	cin.tie(0)->sync_with_stdio(0);
	int task;
	cin>>task;
	sieve(1000000);
	while(task--)
	{
		int l,r;
		cin>>l>>r;
		if(cnt[r]==cnt[l-1])
		{
			s.init_range(l,r);
			int eg=0;
			ll ans=0;
			for(int i=l;i<=r;++i)
				for(int j=i+1;j<=r;++j)
				{
					int w=fac[i].size();
					for(auto p:fac[j])
						if(i%p)++w;
					e[++eg]=edge{i,j,w};
				}
			sort(e+1,e+eg+1);
			for(int i=1;i<=eg;++i)
			{
				if(s.uni(e[i].u,e[i].v))ans+=e[i].w;
			}
			cout<<ans<<'\n';
		}
		else if(l==1)
		{
			ll ans=0;
			for(int i=2;i<=r;++i)ans+=fac[i].size();
			cout<<ans<<'\n';
		}
		else
		{
			//cout<<"Type2 "<<l<<" "<<r<<'\n';
			for(int i=1;i<=r;++i)rest[i]=have[i]=0;
			//p must be a prime
			ll ans=0;
			for(int i=l;i<=r;++i)++rest[mul[i]],++have[mul[i]];
			for(int i=1;i<=r;++i)
				if(have[i])
				{
					//cout<<"i="<<i<<'\n';
					if(rest[i])ans+=ll(fac[i].size())*rest[i]+1;//,cout<<"add "<<ll(fac[i].size())*rest[i]+1<<'\n';
					for(int j=i<<1;j<=r;j+=i)
						if(rest[j])ans+=ll(fac[j].size())*rest[j],rest[j]=0;
				}
			cout<<ans-2<<'\n';
		}
	}
	return 0;
}