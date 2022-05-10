#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10); putchar(x%10+'0');
}
const int N=2e5+10;
int T,n,m,cnt,hed[N],a[N],b[N],t[N],u[N],v[N],fa[N],fa2[N],bel[N],col[N];
bool flag,vis[N];
long long ssum,sum[N];
std::vector<int> vet[N];
struct edg{
	int nxt,to;
}e[N<<1];
inline int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
inline int find2(int x){return x==fa2[x]?x:fa2[x]=find2(fa2[x]);}
inline void addedge(int x,int y){e[++cnt]=(edg){hed[x],y},hed[x]=cnt;}
inline void merge(int x,int y){
	int a=find(x),b=find(y);
	if(a!=b)sum[b]+=sum[a],fa[a]=b;
}
inline void merge2(int x,int y){
	int a=find2(x),b=find2(y);
	fa2[a]=b;
}
void work_dfs(int u){
	vis[u]=true;
	ssum+=sum[u];
	for(std::vector<int>::iterator it=vet[u].begin();it!=vet[u].end();it++)
		if(!vis[*it])work_dfs(*it);
}
void work(int u){
	ssum=0;
	work_dfs(u);
	if(ssum&1)flag=false;
}
void dfs(int u){
	for(std::vector<int>::iterator it=vet[u].begin();it!=vet[u].end();it++){
		int to=*it;
		if(col[u]==col[to]){
			work(u);
			return;
		}
		if(col[to]==-1){
			col[to]=col[u]^1;
			dfs(to);
			if(vis[u])return;
		}
	}
}
void dfs2(int u,int fa)
{
	vis[u]=true;
	for(int i=hed[u];i;i=e[i].nxt){
		int to=e[i].to;
		if(to!=fa){
			dfs2(to,u);
			sum[u]-=sum[to];
		}
	}
}
int main()
{
#ifdef memset0
	freopen("sequence.in","r",stdin);
	// freopen("sequence2.out","w",stdout);
#else
	// freopen("sequence.in","r",stdin),freopen("sequence.out","w",stdout);
#endif
	for(scanf("%d",&T);T--;){
		flag=1,cnt=0;
		memset(hed,0,sizeof(hed));
		memset(vis,0,sizeof(vis));
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)fa[i]=fa2[i]=i,col[i]=-1,vet[i].clear();
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		for(int i=1;i<=n;i++)scanf("%d",&b[i]);
		for(int i=1;i<=n;i++)sum[i]=a[i] - b[i];
		for(int i=1;i<=m;i++){
			scanf("%d%d%d",&t[i],&u[i],&v[i]);
			if(t[i]==2)merge(u[i],v[i]);
		}
		for(int i=1;i<=n;i++)bel[i]=find(i);
		for(int i=1;i<=m;i++)if(t[i]==1){
			vet[bel[u[i]]].push_back(bel[v[i]]);
			vet[bel[v[i]]].push_back(bel[u[i]]);
		}
		for(int i=1;i<=n;i++)if(bel[i]==i&&!vis[bel[i]]&&col[bel[i]]==-1){
			col[bel[i]]=0;
			dfs(bel[i]);
		}
		for(int u=1;u<=n;u++)if(bel[u]==u&&!vis[u])
			for(std::vector<int>::iterator it=vet[u].begin();it!=vet[u].end();it++){
				int v=*it;
				if(find2(u)!=find2(v))addedge(u,v),addedge(v,u),merge2(u,v);
			}
		for(int i=1;i<=n;i++)if(bel[i]==i&&!vis[i]){
			dfs2(i,0);
			if(sum[i])flag=0;
		}
		puts(flag?"YES":"NO");
	}
	return 0;
}
