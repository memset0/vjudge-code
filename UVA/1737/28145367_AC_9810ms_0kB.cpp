#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <queue>
#include <cstring>
using namespace std;
#define res register int
typedef long long LL;
inline LL read()
{
	LL x=0,f=1; char ch;
	while(!isdigit(ch=getchar())) if(ch=='-') f=-1;
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return f*x;
}
const int N=50000+10,M=5010;
int head[M],ver[N],nxt[N];
LL edge[N],Z[N];
int X[N],Y[N];
int tot,n,m,s,p;
inline void add(int x,int y,LL z)
{ver[++tot]=y; nxt[tot]=head[x]; head[x]=tot; edge[tot]=z;}

LL f[M][M];
LL d[N],dis[N];
bool vis[N];
struct node
{
	int u; LL d;
	bool operator <(const node &a)const
	{
		return d>a.d;
	}
};

inline void bfs()
{
	priority_queue<node> q;
	memset(d,0x3f,sizeof(d));
	q.push((node){p+1,0});
	d[p+1]=0; 
	while(q.size())
	{
		int x=q.top().u; q.pop();
		if(vis[x]) continue; vis[x]=1;
		for(res i=head[x] ; i ; i=nxt[i])
		{
			int y=ver[i]; 
			if(d[y]>d[x]+(LL)edge[i])
			{
				d[y]=d[x]+(LL)edge[i];
				q.push((node){y,d[y]});
			}
		}
	}
}
LL sum[M];

int main()
{
//	freopen("assignment.in","r",stdin);
//	freopen("assignment.out","w",stdout);
	while(cin>>n && n)
	{
		p=read(); s=read(); m=read();
		tot=0;
		memset(head,0,sizeof(head));
		memset(vis,0,sizeof(vis));
		for(res i=1 ; i<=m ; ++i)
		{	
			X[i]=read(),Y[i]=read(),Z[i]=read();
			add(X[i],Y[i],Z[i]); 
		}	
		bfs();
		tot=0;
		memset(head,0,sizeof(head));
		memset(vis,0,sizeof(vis));
		for(res i=1 ; i<=p ; ++i) dis[i]=d[i];
		for(res i=1 ; i<=m ; ++i)
			add(Y[i],X[i],Z[i]);
		bfs();
		
		for(res i=1 ; i<=p ; ++i) dis[i]+=d[i];
		sort(dis+1,dis+p+1);	
		for(res i=1 ; i<=p ; ++i) 
			sum[i]=sum[i-1]+dis[i];
		
		for(res i=0 ; i<=p ; ++i)
			for(res j=0 ;j<=s ; ++j) f[i][j]=1e17;
		f[0][0]=0;
		for(res i=1 ; i<=p ; ++i)	
			for(res j=1 ; j<=s ; ++j)
				for(res k=i-i/j ; k<i ; ++k)
					f[i][j]=min(f[i][j],f[k][j-1]+(sum[i]-sum[k])*(i-k-1));
		cout<<f[p][s]<<endl;
		
	}
	return 0;
}