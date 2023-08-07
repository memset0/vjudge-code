#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=(l),i##end=(r);i<=i##end;i++)
#define per(i,l,r) for(int i=(l),i##end=(r);i>=i##end;i--)
using namespace std;
const int N=2e5+9,mod=1e9+7;
int n,m,s,t,f[N],g[N],p[N];
long long L,dis[N];
vector<pair<int,int>> G[N];
priority_queue<pair<long long,int>> q;
inline void add(int &x,int y){
	x+=y;
	if(x>=mod)x-=mod;
}
int main(){
#ifdef memset0
	freopen("B.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>m>>s>>t>>L;
	for(int u,v,w,i=1;i<=m;i++){
		cin>>u>>v>>w;
		G[u].emplace_back(v,w);
		G[v].emplace_back(u,w);
	}
	memset(dis,-1,sizeof(dis));
	dis[t]=0;
	q.push({0,t});
	while(q.size()){
		auto [d,u]=q.top();
		q.pop();
		if(d+dis[u])continue;
		for(const auto &[v,w]:G[u]){
			if(dis[v]==-1||dis[u]+w<dis[v]){
				dis[v]=dis[u]+w;
				q.push({-dis[v],v});
			}
		}
	}
	// rep(i,1,n)cerr<<dis[i]<<" \n"[i==n];
	assert(dis[s]!=-1);
	long long D=L-dis[s];
	rep(i,1,n)p[i]=i;
	sort(p+1,p+n+1,[&](int a,int b){return dis[a]<dis[b];});
	g[t]=1;
	for(int i=1;i<=n;i++){
		int u=p[i];
		for(const auto &[v,w]:G[u])
			if(dis[u]!=-1&&dis[v]!=-1&&dis[v]+w==dis[u]){
				// fprintf(stderr,"%d,%d,%d\n",u,v,w);
				add(g[u],g[v]);
			}
	}
	sort(p+1,p+n+1,[&](int a,int b){return dis[a]>dis[b];});
	f[s]=1;
	for(int i=1;i<=n;i++){
		int u=p[i];
		for(const auto &[v,w]:G[u])
			if(dis[u]!=-1&&dis[v]!=-1&&dis[v]+w==dis[u]){
				add(f[v],f[u]);
			}
	}
	// rep(i,1,n)cerr<<f[i]<<" \n"[i==n];
	// rep(i,1,n)cerr<<g[i]<<" \n"[i==n];
	// cerr<<"D="<<D<<endl;
	if(D==0){
		cout<<f[t]<<endl;
		return 0;
	}
	if(D<0){
		cout<<0<<endl;
		return 0;
	}
	int ans=0;
	for(int u=1;u<=n;u++)
		for(const auto &[v,w]:G[u])
			if(u!=t&&dis[u]!=-1&&dis[v]!=-1&&dis[v]+w-dis[u]==D){
				add(ans,1ll*f[u]*g[v]%mod);
				// fprintf(stderr,"%d,%d,%d : %lld %lld : %d %d : %d\n",u,v,w,dis[u],dis[v],f[u],g[v],ans);
			}
	cout<<ans<<endl;
}