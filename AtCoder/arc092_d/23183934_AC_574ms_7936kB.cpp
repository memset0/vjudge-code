#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0;register char c=getchar();register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();if(f)x=-x;
}
const int N=1e3+10,M=2e5+10;
int n,m,f[N],g[N],id[N][N];
bool ans[M],vis[N][N];
std::vector<int> G[N];
void dfs(int u,bool *vis){vis[u]=1;for(int v:G[u])if(!vis[v])dfs(v,vis);}
void search(int u,int *f){for(int v:G[u])if(!f[v])f[v]=f[u],search(v,f);}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n),read(m);
	for(int u,v,i=1;i<=m;i++)read(u),read(v),G[u].push_back(v),id[u][v]=i;
	for(int i=1;i<=n;i++)dfs(i,vis[i]);
	for(int u=1;u<=n;u++){
		for(int i=1;i<=n;i++)f[i]=g[i]=0; f[u]=g[u]=-1;
		for(int v:G[u])if(!f[v])f[v]=v,search(v,f); std::reverse(G[u].begin(),G[u].end());
		for(int v:G[u])if(!g[v])g[v]=v,search(v,g); std::reverse(G[u].begin(),G[u].end());
		for(int v:G[u])if(vis[v][u]^(f[v]!=v||g[v]!=v))ans[id[u][v]]=true;
	}
	for(int i=1;i<=m;i++)puts(ans[i]?"diff":"same");
}