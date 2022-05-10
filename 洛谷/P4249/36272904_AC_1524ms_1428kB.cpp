#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0;register char c=getchar();register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();if(f)x=-x;
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}
const int K=110,N=11000,M=100000;
int n,m,s,e,ans,deg[K],G[K][K],res[K][K];
int cnt,tot=2,inq[N],hed[N],to[M],val[M],cst[M],nxt[M],pre[N],dis[N],flow,cost,max_flow,max_cost;
namespace mcmf{ // older code
	inline void add(int u, int v, int w, int c) {
		nxt[tot] = hed[u], to[tot] = v, val[tot] = w, cst[tot] =  c, hed[u] = tot++;
		nxt[tot] = hed[v], to[tot] = u, val[tot] = 0, cst[tot] = -c, hed[v] = tot++;
	}
	bool spfa() {
		static int q[N];
		memset(pre, 0, (cnt + 1) << 2);
		memset(dis, 0x3f, (cnt + 1) << 2);
		int l = 0, r = 0, u; q[0] = s, dis[s] = 0;
		while (l <= r) {
			u = q[(l++) % cnt], inq[u] = 0;
			for (int i = hed[u], v; v = to[i], i; i = nxt[i])
				if (val[i] && dis[u] + cst[i] < dis[v]) {
					// printf("%d -> %d\n", u, v);
					dis[v] = dis[u] + cst[i], pre[v] = i;
					if (!inq[v]) inq[q[(++r) % cnt] = v] = 1;
				}
		}
		return pre[e];
	}
	void main() {
		while (spfa()) {
			flow = 1000000000, cost = 0;
			for (int i = pre[e]; i; i = pre[to[i ^ 1]]) flow = std::min(flow, val[i]);
			for (int i = pre[e]; i; i = pre[to[i ^ 1]]) val[i] -= flow, val[i ^ 1] += flow, cost += flow * cst[i];
			max_flow += flow, max_cost += cost;
		}
	}
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n);
	for(int x,u=1;u<=n;u++)for(int v=1;v<=n;v++){
	    if(read(x),x!=1)continue;
		++deg[u],res[u][v]=1,G[u][v]=G[v][u]=-1;
	}
	cnt=n<<1,s=++cnt,e=++cnt;
	for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++)if(~G[i][j]){
		G[i][j]=G[j][i]=++cnt;
		mcmf::add(s,G[i][j],1,0);
		mcmf::add(G[i][j],i,1,0);
		mcmf::add(G[i][j],j,1,0);
	}
	ans=n*(n-1)*(n-2)/2/3;
	for(int i=1;i<=n;i++){
		ans-=deg[i]*(deg[i]-1)/2;
		for(int j=1;j<=n;j++)mcmf::add(i,i+n,1,deg[i]+j-1);
	}
	for(int i=1;i<=n;i++)mcmf::add(i+n,e,n,0);
	mcmf::main();
	// printf("> %d %d\n",max_flow,max_cost);
	for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++)if(~G[i][j]){
		// printf("> %d %d | %d %d\n",i,j,G[i][j],hed[G[i][j]]);
		for(int k=hed[G[i][j]];k;k=nxt[k]){
			// printf(">> %d %d\n",k,to[k]);
			if(to[k]!=s&&!val[k])res[to[k]][i+j-to[k]]=1;
		}
	}
	print(ans-=max_cost,'\n');
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)print(res[i][j]," \n"[j==n]);
	}
}