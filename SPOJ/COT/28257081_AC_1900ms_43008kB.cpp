#include<bits/stdc++.h>
using namespace std;
#define N 100009
int read()
{
	int res=0,f=1;
	char c=getchar();
	while(c<'0' || c>'9') f=(c=='-')?-1:1,c=getchar();
	while('0'<=c && c<='9') res=res*10+c-'0',c=getchar();
	return res*f;
}
struct node
{
	int to,nxt;
}h[N<<1];
int head[N],tot,deep[N],fa[N][26];
void add(int u,int v)
{
	h[++tot].to=v;
	h[tot].nxt=head[u];
	head[u]=tot;
}
int sum[N<<5],T[N],cnt,lc[N<<5],rc[N<<5];
int a[N],b[N],size;
int modify(int rt,int l,int r,int pos)
{
	int root=++cnt;
	lc[root]=lc[rt],rc[root]=rc[rt],sum[root]=sum[rt]+1;
	if(l==r) return root;
	int mid=(l+r)>>1;
	if(pos<=mid) lc[root]=modify(lc[root],l,mid,pos);
	else rc[root]=modify(rc[root],mid+1,r,pos);
	return root;
}
void dfs(int u,int fat)
{
	int pos=lower_bound(b+1,b+size+1,a[u])-b;
	T[u]=modify(T[fat],1,size,pos);
	for(int i=head[u];i!=-1;i=h[i].nxt)
	{
		int v=h[i].to;
		if(v==fat) continue;
		deep[v]=deep[u]+1;
		fa[v][0]=u;
		dfs(v,u);
	}
}
int lca(int x,int y)
{
	if(deep[x]<deep[y]) swap(x,y);
	for(int i=23;i>=0;i--)
		if(deep[fa[x][i]]>=deep[y]) 
			x=fa[x][i];
	if(x==y) return x;
	for(int i=23;i>=0;i--)
		if(fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
int query(int rt1,int rt2,int rt3,int rt4,int l,int r,int k)
{
	int summ=sum[lc[rt1]]+sum[lc[rt2]]-sum[lc[rt3]]-sum[lc[rt4]];
	if(l==r) return l;
	int mid=l+r>>1;
	if(summ>=k) return query(lc[rt1],lc[rt2],lc[rt3],lc[rt4],l,mid,k);
	else return query(rc[rt1],rc[rt2],rc[rt3],rc[rt4],mid+1,r,k-summ);
}

int main()
{
	memset(head,-1,sizeof(head));
	int n=read(),m=read();
	for(int i=1;i<=n;i++) a[i]=read(),b[i]=a[i];
	for(int i=1;i<n;i++) 
	{
		int x=read(),y=read();
		add(x,y),add(y,x);
	}
	sort(b+1,b+n+1);
	size=unique(b+1,b+n+1)-b-1;
	deep[1]=1,dfs(1,0);
	for(int i=1;i<=23;i++)
		for(int j=1;j<=n;j++)
			fa[j][i]=fa[fa[j][i-1]][i-1];
	while(m--)
	{
		int u=read(),v=read(),k=read();
		int LCA=lca(u,v);
		printf("%d\n",b[query(T[v],T[u],T[LCA],T[fa[LCA][0]],1,size,k)]);
	}
	return 0;
}