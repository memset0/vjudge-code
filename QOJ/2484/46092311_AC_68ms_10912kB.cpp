#include "bits/stdc++.h"
typedef long long ll;
const int MAXN = 200011;
struct LCT
{
	int fa[MAXN],son[MAXN][2];
	bool rev[MAXN];
	bool not_root(int x){return son[fa[x]][0]==x||son[fa[x]][1]==x;}
	void reverse(int x)
	{
		if(!x)return;
		std::swap(son[x][0],son[x][1]);
		rev[x]^=1;
	}
	void pushdown(int x)
	{
		if(rev[x])
		{
			reverse(son[x][0]),reverse(son[x][1]);
			rev[x]=0;
		}
	}
	void rotate(int x)
	{
		int y=fa[x],z=fa[y],k=(son[y][1]==x);
		if(not_root(y))son[z][son[z][1]==y]=x;
		fa[x]=z,fa[y]=x;
		fa[son[x][!k]]=y,son[y][k]=son[x][!k];
		son[x][!k]=y;
	}
	int s[MAXN];
	void splay(int x)
	{
		int top=0,y=x;
		s[++top]=y;
		while(not_root(y))s[++top]=y=fa[y];
		while(top)pushdown(s[top--]);
		while(not_root(x))
		{
			int y=fa[x];
			if(not_root(y))
				rotate((son[y][1]==x)==(son[fa[y]][1]==y)?y:x);
			rotate(x);
		}
	}
	void access(int x)
	{
		for(int y=0;x;y=x,x=fa[x])
			splay(x),son[x][1]=y;
	}
	int get_root(int x)
	{
		access(x),splay(x),pushdown(x);
		while(son[x][0])pushdown(x=son[x][0]);
		splay(x);
		return x;
	}
	bool check(int x,int y)
	{
		// printf("check(%d,%d)\n",x,y);
		return get_root(x)==get_root(y);
	}
	void make_root(int x)
	{
		access(x),splay(x);
		reverse(x);
	}
	void link(int x,int y)
	{
		// printf("link (%d,%d)\n",x,y);
		make_root(x);
		fa[x]=y;
	}
	void cut(int x,int y)
	{
		// printf("cut(%d,%d)\n",x,y);
		make_root(x),get_root(y);
		// printf("y=%d,fa=%d,ls=%d,rs=%d\n",y,fa[y],son[y][0],son[y][1]);
		pushdown(x);
		if(son[x][1]==y&&!son[y][0]&&!son[y][1])
		{
			son[x][1]=0,fa[y]=0;
		}
		else fprintf(stderr,"Error: Cut (%d,%d) failed!\n",x,y);
	}
}t;
typedef std::pair<int,int> pii;
pii ed[MAXN];
int f[MAXN];
ll sum[MAXN];
int main()
{
	//freopen("K.in","r",stdin);
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i)scanf("%d%d",&ed[i].first,&ed[i].second);
	int l=1,r=1;
	while(l<=m)
	{
		while(r<=m&&!t.check(ed[r].first,ed[r].second))
		{
			t.link(ed[r].first,ed[r].second);
			++r;
		}
		f[l]=r-1;
		// printf("F[%d]=%d\n",l,r-1);
		t.cut(ed[l].first,ed[l].second);
		++l;
	}
	for(int i=1;i<=m;++i)sum[i]=sum[i-1]+f[i];
	int q;
	scanf("%d",&q);
	while(q--)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		int p=std::lower_bound(f+1,f+m+1,r)-f;
		ll dec=ll(r-l+1)*(l-1+r-1)/2;
		if(p<=l)printf("%lld\n",ll(r-l+1)*r-dec);
		else
		{
			ll ans=sum[p-1]-sum[l-1];
			ans+=ll(r-p+1)*r;
			printf("%lld\n",ans-dec);
		}
	}
	return 0;
}