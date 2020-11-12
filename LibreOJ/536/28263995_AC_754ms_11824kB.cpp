#include<bits/stdc++.h>
// #define log(...) (void(0))
#define log(...) fprintf(stderr,__VA_ARGS__)
#define debug log("\33[2mPassing [%s] in LINE %d\33[0m\n",__FUNCTION__,__LINE__);
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
template<int N,int M> struct Dinic{ // Dinic 网络流
	int tot,s,t,cur[N],hed[N],dep[N],to[M<<1],val[M<<1],nxt[M<<1];
	Dinic(){tot=0,memset(hed,-1,sizeof(hed));}
	inline void add(int u,int v,int w){
		nxt[tot]=hed[u],to[tot]=v,val[tot]=w,hed[u]=tot++;
		nxt[tot]=hed[v],to[tot]=u,val[tot]=0,hed[v]=tot++;
	}
	bool bfs(){
		static int u,l,r,q[N]; memset(dep+1,0,t<<2),l=r=dep[s]=1,q[1]=s;
		while(l<=r&&(u=q[l++]))for(int i=hed[u];~i;i=nxt[i])
			if(val[i]&&!dep[to[i]])dep[to[i]]=dep[u]+1,q[++r]=to[i];
		return dep[t];
	}
	int dfs(int u,int d){
		if(u==t)return d; int s=0;
		for(int &i=cur[u];~i;i=nxt[i])if(val[i]&&dep[to[i]]==dep[u]+1)
			if(int e=dfs(to[i],std::min(d-s,val[i]))){s+=e,val[i]-=e,val[i^1]+=e;if(s==d)return s;}
		return s;
	}
	int dinic(){int r=0;while(bfs())memcpy(cur+1,hed+1,t<<2),r+=dfs(s,1e9);return r;}
};
const int N=4e5+10,M=1e6+10,E=2.4e6+10;
int n,m,w,h;
std::pair<int,int> a[N],b[N];
struct :Dinic<M,E>{
	bool vis[M];
	void solve(){
		s=n+m+w+h+1,t=s+1;
		memset(vis+1,1,t);
		for(int i=1;i<=n;i++){
			add(s,i,1);
			add(i,n+m+a[i].first,1);
			add(i,n+m+w+a[i].second,1);
		}
		for(int i=1;i<=m;i++){
			add(n+i,t,1);
			add(n+m+b[i].first,n+i,1);
			add(n+m+w+b[i].second,n+i,1);
		}
		dinic();
		const std::function<void(int)> dfs=[&](int u){
			vis[u]=0;
			for(int i=hed[u];~i;i=nxt[i])if(val[i]&&vis[to[i]])vis[to[i]]=1,dfs(to[i]);
		};
		dfs(s);
		for(int i=hed[s];~i;i=nxt[i])vis[to[i]]&=!val[i];
		for(int i=1;i<=n;i++)putchar(vis[i]+'0'),putchar('\n');
	}
}flow;
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(w),read(h),read(n);
	for(int i=1;i<=n;i++)read(a[i].first),read(a[i].second);
	read(m);
	for(int i=1;i<=m;i++)read(b[i].first),read(b[i].second);
	flow.solve();
	fprintf(stderr,"clocks: %.4lf\n",clock()/(double)CLOCKS_PER_SEC);
}