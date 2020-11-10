#include<iostream>
#include<string>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;

const int N=350+15;
const int inf=1e9+7;
int n,m,tot,cnt;
int vis[N*N],fa[N];
struct EDGE
{
	int from,to,w;
}edge[N*N],path[N*N];
vector<pair<int,int> > r[N];
inline int read()
{
	char ch=getchar();
	int s=0,f=1;
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9') {s=(s<<3)+(s<<1)+ch-'0';ch=getchar();}
	return s*f;
}
bool cmp(EDGE a,EDGE b){return a.w<b.w;}
inline void add(EDGE &a)
{
    int u = a.from,v = a.to,w = a.w;
    r[u].push_back({v,w});
    r[v].push_back({u,w});
}
bool find_path(int fa,int u,int ed)
{
	if (u == ed) return true;
	for(int i = 0;i < r[u].size();++i)
	{
		int v = r[u][i].first,w = r[u][i].second;
		if (v==fa) continue;
		path[++cnt]={u,v,w};
		if (find_path(u,v,ed)) return true;
		cnt--;
	}
	return false;
}
inline void del(EDGE &a)
{
    int u = a.from,v = a.to;
    for(vector<pair<int,int> >::iterator it = r[u].begin();it != r[u].end();++it){
        if (it->first == v){
            r[u].erase(it);
            break;
        }
    }
    for(vector<pair<int,int> >::iterator it = r[v].begin();it != r[v].end();++it){
        if (it->first == u){
            r[v].erase(it);
            break;
        }
    }
}
void update(int u,int f,int &mx,int &mi)
{
	for (int i=0;i<r[u].size();i++)
	{
		int v=r[u][i].first,w=r[u][i].second;
		if (v==f) continue;
		mx=max(mx,w);
		mi=min(mi,w);
		update(v,u,mx,mi);
	}
}
int find(int x)
{
	if (fa[x]!=x) fa[x]=find(fa[x]);
	return fa[x];
}
void kruskal()
{
	memset(vis,0,sizeof(vis));
	for (int i=0;i<n;i++) fa[i]=i;
	int sum=0,ans=inf;
	for (int i=1;i<=m;i++)
	{
		int a=edge[i].from,b=edge[i].to;
		a=find(a);b=find(b);
		if (a!=b)
		{
			fa[a]=b;
			vis[i]=1;
			add(edge[i]);
			++sum;
		}
		if (sum==n-1)
		{
			ans=edge[i].w-edge[1].w;
			break;
		}
	}
	for (int i=1;i<=m;i++)
	{
		if (vis[i]) continue;
		int u=edge[i].from,v=edge[i].to;
		int mx=0,mi=inf;
		cnt=0;
		find_path(u,u,v);
		sort(path+1,path+1+cnt,cmp);
		del(path[1]);
		add(edge[i]);
		update(0,0,mx,mi);
		ans=min(ans,mx-mi);
	}
	printf("%d\n",ans);
}
void work()
{
	for (int i=0;i<n;i++) r[i].clear();
	for (int i=1,u,v,w;i<=m;i++)
	{
		u=read();v=read();w=read();
		edge[i]=(EDGE){u,v,w};
	}
	sort(edge+1,edge+1+m,cmp);
	kruskal();
}
int main()
{
	while (cin>>n&&n)
	{
		m=read();
		work();	
	}
	return 0;
}