// 口胡选手鸽了代码

// Author -- xyr2005

#include<bits/stdc++.h>

#define lowbit(x) ((x)&(-(x)))
#define DEBUG fprintf(stderr,"Running on Line %d in Function %s\n",__LINE__,__FUNCTION__)
#define SZ(x) ((int)x.size())
#define mkpr std::make_pair
#define pb push_back

typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef std::pair<int,int> pi;
typedef std::pair<ll,ll> pl;
using std::min;
using std::max;

const int inf=0x3f3f3f3f,Inf=0x7fffffff;
const ll INF=0x3f3f3f3f3f3f3f3f;

std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
template <typename _Tp>_Tp gcd(const _Tp &a,const _Tp &b){return (!b)?a:gcd(b,a%b);}
template <typename _Tp>inline _Tp abs(const _Tp &a){return a>=0?a:-a;}
template <typename _Tp>inline void chmax(_Tp &a,const _Tp &b){(a<b)&&(a=b);}
template <typename _Tp>inline void chmin(_Tp &a,const _Tp &b){(b<a)&&(a=b);}
template <typename _Tp>inline void read(_Tp &x)
{
	char ch(getchar());bool f(false);while(!isdigit(ch)) f|=ch==45,ch=getchar();
	x=ch&15,ch=getchar();while(isdigit(ch)) x=(((x<<2)+x)<<1)+(ch&15),ch=getchar();
	f&&(x=-x);
}
template <typename _Tp,typename... Args>void read(_Tp &t,Args &...args){read(t);read(args...);}
inline int read_str(char *s)
{
	char ch(getchar());while(ch==' '||ch=='\r'||ch=='\n') ch=getchar();
	char *tar=s;*tar++=ch,ch=getchar();while(ch!=' '&&ch!='\r'&&ch!='\n'&&ch!=EOF) *tar++=ch,ch=getchar();
	return *tar=0,tar-s;
}

const int N=5005;
int n,m,p,b[N];
ll a[N],v[65];
bool mark[N];
ll d[65],id[65];
bool ins(ll x,ll y)
{
	for(int i=59;i>=0;--i)if((x>>i)&1)
	{
		if(d[i])x^=d[i],y^=id[i];
		else return d[i]=x,id[i]=y,true;
	}
	return false;
}
bool test(ll x)
{
	for(int i=59;i>=0;--i)if((x>>i)&1)x^=d[i];
	return x==0;
}
struct edge{
	int v,nxt;
}c[600005];
int front[N],edge_cnt;
inline void addedge(int u,int v)
{
	c[++edge_cnt]=(edge){v,front[u]};
	front[u]=edge_cnt;
}
bool used[65],X2[N];
int _q[N],_l,_r,pre[N];
bool check()
{
	memset(front,0,sizeof(front)),edge_cnt=0,memset(d,0,sizeof(d)),memset(used,0,sizeof(used)),_l=1,_r=0,memset(pre,255,sizeof(pre)),memset(X2,0,sizeof(X2)),memset(id,0,sizeof(id));
	std::vector<int> cur;
	for(int i=1;i<=n;++i)ins(v[i],0);
	for(int i=1;i<=p;++i)if(mark[i])ins(a[i],1LL<<SZ(cur)),cur.pb(i),used[b[i]]=true;
	for(int i=1;i<=p;++i)if(!mark[i]&&!used[b[i]])X2[i]=true;
	for(int i=1;i<=p;++i)if(!mark[i]&&!test(a[i]))
	{
		if(X2[i])return mark[i]=true;
		_q[++_r]=i,pre[i]=0;
	}
	for(int i=1;i<=p;++i)if(!mark[i])
	{
		ll x=a[i],y=0;
		for(int j=59;j>=0;--j)if(((x>>j)&1)&&d[j])x^=d[j],y^=id[j];
		if(x)y=(1LL<<SZ(cur))-1;
		for(int j=0;j<SZ(cur);++j)if((y>>j)&1)addedge(cur[j],i);
	}
	for(auto i:cur)
	{
		memset(used,0,sizeof(used));
		for(auto j:cur)if(i!=j)used[b[j]]=true;
		for(int j=1;j<=p;++j)if(!mark[j]&&!used[b[j]])addedge(j,i);
	}
	while(_l!=_r+1)
	{
		int x=_q[_l++];
		for(int i=front[x];i;i=c[i].nxt)
		{
			int v=c[i].v;
			if(pre[v]==-1)
			{
				pre[v]=x,_q[++_r]=v;
				if(X2[v])
				{
					for(;~v;v=pre[v])mark[v]^=1;
					return true;
				}
			}
		}
	}
	return false;
}
int main()
{
	read(n);for(int i=1;i<=n;++i)read(v[i]);
	read(m);
	int k;
	for(int i=1;i<=m;++i)
	{
		read(k);
		for(int j=0;j<k;++j)read(a[++p]),b[p]=i;
	}
	for(int i=1;i<=n;++i)if(!ins(v[i],0))return puts("-1"),0;
	while(check());
	int cnt=0;
	for(int i=1;i<=p;++i)if(mark[i])++cnt;
	if(cnt!=m)return puts("-1"),0;
	for(int i=1;i<=m;++i)for(int j=1;j<=p;++j)if(b[j]==i&&mark[j])printf("%lld\n",a[j]);
	return 0;
}