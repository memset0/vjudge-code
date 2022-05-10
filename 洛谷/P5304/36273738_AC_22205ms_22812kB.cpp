#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
const int N=4e5+10;
int T,n,m,k,s,e,u[N],v[N],w[N];
bool tag[N],vis[N],ins[N];
long long ans,dis[N];
std::vector<std::pair<int,int>> G[N];
std::priority_queue<std::pair<int,int>> q;
inline void add(int u,int v,int w){
	// printf("add %d %d %d\n",u,v,w);
	G[u].push_back(std::make_pair(v,w));
}
long long solve(){
	for(int i=1;i<=e;i++)G[i].clear();
	for(int i=1;i<=n;i++)if(ins[i])tag[i]?add(s,i,0):add(i,e,0);
	for(int i=1;i<=m;i++)if(!(ins[u[i]]&&ins[v[i]]))add(u[i],v[i],w[i]);
	for(int i=1;i<=m;i++)if(ins[u[i]]&&ins[v[i]]&&tag[u[i]]^tag[v[i]])add(u[i],v[i],w[i]);
	memset(dis+1,63,e<<3),memset(vis+1,0,e),dis[s]=0,q.push(std::make_pair(0,s));
	while(q.size()){
		int u=q.top().second; q.pop();
		if(vis[u])continue; vis[u]=1;
		for(std::pair<int,int> e:G[u]){
			int v=e.first,w=e.second;
			if(dis[u]+w<dis[v]){
				dis[v]=dis[u]+w,q.push(std::make_pair(-dis[v],v));
				// printf("%d -> %d : %d\n",u,v,w);
			}
		}
	}
	// printf("> %lld\n",dis[e]);
	return dis[e];
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	for(read(T);T--;){
		read(n),read(m),read(k),memset(ins+1,0,n);
		for(int i=1;i<=m;i++)read(u[i]),read(v[i]),read(w[i]);
		for(int i=1,x;i<=k;i++)read(x),ins[x]=1;
		s=n+1,e=n+2,ans=LLONG_MAX;
		for(int i=0;(1<<i)<=(n<<1);i++){
			for(int j=1;j<=n;j++)tag[j]=(j>>i)&1;
			ans=std::min(ans,solve());
			for(int j=1;j<=n;j++)tag[j]=(j>>i)&1^1;
			ans=std::min(ans,solve());
		}
		printf("%lld\n",ans);
	}
}