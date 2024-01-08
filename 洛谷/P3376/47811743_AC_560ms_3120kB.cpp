#include<bits/stdc++.h>
const int N=1e4+10,M=1e5+10;
int n,m,s,t,u,v,w;
template<int N,int M> struct MaxFlow{ // Dinic 网络流
	int tot,s,t,hed[N],dep[N],to[M<<1],val[M<<1],nxt[M<<1];
	MaxFlow(){tot=0,memset(hed,-1,sizeof(hed));}
	inline void add(int u,int v,int w){
		nxt[tot]=hed[u],to[tot]=v,val[tot]=w,hed[u]=tot++;
		nxt[tot]=hed[v],to[tot]=u,val[tot]=0,hed[v]=tot++;
	}
	bool bfs(){
		static int l,r,q[N]; memset(dep+1,0,t<<2),l=r=dep[s]=1,q[1]=s;
		while(l<=r&&(u=q[l++]))for(int i=hed[u];~i;i=nxt[i])
			if(val[i]&&!dep[to[i]])dep[to[i]]=dep[u]+1,q[++r]=to[i];
		return dep[t];
	}
	int dfs(int u,int d){
		if(u==t)return d;
		for(int i=hed[u];~i;i=nxt[i])if(val[i]&&dep[to[i]]==dep[u]+1)
			if(int e=dfs(to[i],std::min(d,val[i]))){val[i]-=e,val[i^1]+=e;return e;}
		return 0;
	}
	int solve(){int r=0;while(bfs()){while(int d=dfs(s,1e9))r+=d;}return r;}
};
MaxFlow<N,M> flow;
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	scanf("%d%d%d%d",&n,&m,&s,&t);
	flow.add(flow.s=++n,s,1e9);
	flow.add(t,flow.t=++n,1e9);
	while(m--)scanf("%d%d%d",&u,&v,&w),flow.add(u,v,w);
	printf("%lld\n",flow.solve());
}