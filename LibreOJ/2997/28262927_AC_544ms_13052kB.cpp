#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0; char c=getchar(); bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
const int N=5e5+10;
int n,m,a,b,c,d,e;
bool vis[N];
long long ans,dis[N];
std::vector<int> G[N];
std::priority_queue<std::pair<long long,int>> q;
long long dij(int s,int e){
	memset(dis+1,0x3f,m<<3),memset(vis+1,0,m);
	dis[s]=0,q.push(std::make_pair(0,s));
	while(q.size()){
		int u=q.top().second; q.pop();
		if(vis[u])continue; vis[u]=1;
		for(int v:G[u])if(dis[v]>dis[u]+std::abs(u-v)){
			dis[v]=dis[u]+std::abs(u-v);
			// printf("%d[%lld] -> %d[%lld]\n",u,dis[u],v,dis[v]);
			q.push(std::make_pair(-dis[v],v));
		}
	}
	// for(int i=1;i<=m;i++)printf("%lld%c",dis[i]," \n"[i==m]);
	// printf("dij %d %d >> %lld\n",s,e,dis[e]);
	return dis[e];
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif	
	read(a),read(b),read(c),read(d),read(e),read(n),m=a+b+c+d+e+1;
	// printf("[%d %d %d %d %d] >> %d\n",a,b,c,d,e,n);
	for(int l,r,i=1;i<=n;i++){
		read(l),read(r);
		// printf("edge %d %d\n",l,r+1);
		G[l].push_back(r+1),G[r+1].push_back(l);
	}
	ans=std::min(std::min(dij(a+1,a+b+1)+dij(a+b+c+1,a+b+c+d+1),dij(a+1,a+b+c+d+1)+dij(a+b+1,a+b+c+1)),dij(a+1,a+b+c+1)+dij(a+b+1,a+b+c+d+1));
	printf("%lld\n",ans>1e18?-1:ans);
}