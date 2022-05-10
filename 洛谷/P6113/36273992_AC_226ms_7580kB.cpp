// test

#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
#define INF 0x7fffffff
#define N 2501

#define M 500010

using namespace std;
inline int read()
{
	int X=0,w=0;char ch=0;
	while('0'>ch||ch>'9'){w|=ch=='-';ch=getchar();}
	while('0'<=ch&&ch<='9')X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
	return w?-X:X;
}
int n,m,h[N],cnt=1,now[N];
int dep[N],vis[N];
struct Edge{
	int to,next,s;
}e[1600001];
inline void AddEdge(int x,int y,int v)
{
	e[++cnt]=(Edge){y,h[x],v};h[x]=cnt;
	e[++cnt]=(Edge){x,h[y],0};h[y]=cnt;
}
bool bfs(int S,int T)
{
	int i,x,y;
	for(i=S;i<=T;++i)now[i]=h[i],vis[i]=dep[i]=0;
	vis[S]=1;dep[S]=0;
	queue<int>q;q.push(S);
	while(!q.empty())
	{
		x=q.front();q.pop();
		for(i=h[x];i;i=e[i].next)
		if(e[i].s)
		{
			int y=e[i].to;
			if(vis[y])continue;
			dep[y]=dep[x]+1;vis[y]=1;
			if(y==T)return true;
			q.push(y);
		}
	}return false;
}
int dfs(int x,int maxf,int t)
{
	if(x==t)return maxf;int y,dlt;
	for(int &i=now[x];i&&maxf;i=e[i].next)
	if(e[i].s)
	{
		y=e[i].to;
		if(dep[y]==dep[x]+1)
		{
			dlt=dfs(y,min(maxf,e[i].s),t);
			if(!dlt){dep[y]=0;continue;}
			e[i].s-=dlt;e[i^1].s+=dlt;return dlt;
		}
	}return 0;
}
int dinic(int s,int t)
{
	int maxflow=0,d=0;
	while(bfs(s,t))
	while(d=dfs(s,INF,t))maxflow+=d;
	return maxflow;
}




int Head[M], Next[M], Go[M], Pre[N], Nxt[N], F[N], ST[N], Q[N], Vis[N], *Top = Q, Cnt = 0, Tim = 0,  x, y;
int find(int x)
{
	return x == F[x] ? x : F[x] = find(F[x]);
}

int lca(int x, int y)
{
	for(Tim++, x = find(x), y = find(y); ; x ^= y ^= x ^= y)
		if(x)
		{
			if(Vis[x] == Tim) return x;
			Vis[x] = Tim;
			x = find(Pre[Nxt[x]]);
		}
}

void blossom(int x, int y, int l)
{
	while(find(x) != l)
	{
		Pre[x] = y, y = Nxt[x];
		ST[*Top = y] = 0, *Top++;
		if(F[x] == x) F[x] = l;
		if(F[y] == y) F[y] = l;
		x = Pre[y];
	}
}

int Match(int x)
{
	for(int i = 1; i <= n; i++) F[i] = i;
	memset(ST, -1, sizeof ST);
	ST[*(Top = Q) = x] = 0, Top++;
	for(int *i = Q; i != Top; *i++)
		for(int T = Head[*i]; T; T = Next[T])
		{
			int g = Go[T];
			if(ST[g] == -1)
			{
				Pre[g] = *i, ST[g] = 1;
				if(!Nxt[g])
				{
					for(int u = g, v = *i, lst; v; u = lst, v = Pre[u])
						lst = Nxt[v], Nxt[v] = u, Nxt[u] = v;
					return 1;
				}
				ST[*Top = Nxt[g]] = 0, *Top++;
			}
			else if(!ST[g] && find(g) != find(*i))
			{
				int l = lca(g, *i);
				blossom(g, *i, l);
				blossom(*i, g, l);
			}
		}
	return 0;
}



inline void addedge(int x, int y)
{
	Go[++Cnt] = y;
	Next[Cnt] = Head[x];
	Head[x] = Cnt;
}

int main(){
	int i,j,S,T,x,y,v;
	n=read();m=read();S=1;T=(n+1)<<1;
	for(i=1;i<=n;i++)AddEdge(S,i<<1,1);
	for(i=1;i<=n;i++)AddEdge(i<<1|1,T,1);
	for(i=1;i<=m;i++)
	{
		x=read();y=read();
		AddEdge(x<<1,y<<1|1,1);
		AddEdge(y<<1,x<<1|1,1);
		
		addedge(x, y);
		addedge(y, x);
	}printf("%d\n",dinic(S,T)>>1);
	
	
	for(int i = n; i >= 1; i--)
	if(!Nxt[i])Match(i);
	
	for(int i = 1; i <= n; i++) printf("%d ", Nxt[i]);
}