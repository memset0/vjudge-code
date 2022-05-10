#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0;register char c=getchar();register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();if(f)x=-x;
}
const int N=2e2+10,M=5e2+10,inf=20040725;
int T,n,m,min,ans,fa[N],fb[N],dep[N],vis[N],f[N][2];
std::vector<int> G[N];
inline int find(int x){return x==fb[x]?x:fb[x]=find(fb[x]);}
void solve1(int u){
	printf("solve 1 %d\n",u);
	vis[u]=1; bool fl=false;
	for(int v:G[u])if(vis[v]){
		if(v==fa[u]&&!fl){fl=true;continue;}
		int cur=dep[u]+dep[v]-dep[find(u)];
		// printf("%d -> %d\n",u,v);
		ans=std::min(ans,cur+min),min=std::min(min,cur);
	}
	for(int v:G[u])if(!vis[v]){
		fa[v]=u,dep[v]=dep[u]+1,solve1(v);
	}
	fb[u]=fa[u]; 
}
inline void update(int u,int v){
	if(v<f[u][0])f[u][1]=f[u][0],f[u][0]=v;
	else if(v<f[u][1])f[u][1]=v;
}
void solve2(int u){
	printf("solve 2 %d\n",u);
	vis[u]=1; bool fl=false;
	for(int v:G[u])if(vis[v]){
		if(v==fa[u]&&!fl){fl=true;continue;}
		int cur=dep[u]+dep[v]-1;
		update(u,cur);
	}
	for(int v:G[u])if(!vis[v]){
		fa[v]=u,dep[v]=dep[u]+1,solve2(v);
		update(u,f[v][0]),update(u,f[v][1]);
	}
	if(f[u][0]!=inf&&f[u][1]!=inf)printf("%d %d : %d %d\n",u,dep[u],f[u][0],f[u][1]);
	ans=std::min(ans,f[u][0]+f[u][1]-dep[u]+1);
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	for(read(T);T--;){
		read(n),read(m),ans=inf;
		for(int u,v,i=1;i<=m;i++){
			read(u),read(v);
			G[u].push_back(v),G[v].push_back(u);
		}
		for(int i=1;i<=n;i++){
			printf("=== [1] %d ===\n",i);
			for(int i=1;i<=n;i++)fb[i]=i,vis[i]=0;
			min=inf,fa[i]=0,dep[i]=1,solve1(i);
			printf(">> %d\n",ans);
		}
		for(int i=1;i<=n;i++){
			printf("=== [2] %d ===\n",i);
			for(int i=1;i<=n;i++)vis[i]=0,f[i][0]=f[i][1]=inf;
			fa[i]=0,dep[i]=1,solve2(i);
			printf(">> %d\n",ans);
		}
		printf("%d\n",ans==inf?m:ans-1);
		// orz zx2003
		for(int i=1;i<=n;i++)G[i].clear();
		break;
	}
}