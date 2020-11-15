#include<bits/stdc++.h>
#define walk(u,v,w,x) for(auto it:G[u]){int v=it.first,w=it.second;x;}
template<class T> inline void read(T &x){
	x=0;register char c=getchar();register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();if(f)x=-x;
}
const int N=2e5+10;
int n,rt,nod,root,full,a[N],siz[N],vis[N],maxp[N],lc[N<<2],rc[N<<2];
long long sum,res[N];
std::vector<std::pair<int,int>> G[N];
struct line{
	int k; long long b;
	inline long long operator[](int x){
		return (long long)x*k+b;
	}
}p[N<<2];
struct info{
	int u; long long dis;
};
std::vector<info> cur;
std::vector<std::vector<info>> set;
void findroot(int u,int fa){
	// printf("find root %d %d\n",u,fa);
	siz[u]=1,maxp[u]=0;
	walk(u,v,w,if(v!=fa&&!vis[v]){
		findroot(v,u);
		siz[u]+=siz[v];maxp[u]=std::max(maxp[u],siz[v]);
	})
	maxp[u]=std::max(maxp[u],full-siz[u]);
	if(maxp[u]<maxp[root])root=u;
}
void search(int u,int fa,long long dis){
	set.back().push_back((info){u,dis});
	walk(u,v,w,if(v!=fa&&!vis[v]){
		search(v,u,dis+w);
	})
}
void modify(int &u,line x,int l,int r){
	if(!u){u=++nod,lc[u]=rc[u]=0,p[u]=x;return;}
	if(x[l]>=p[u][l]&&x[r]>=p[u][r])return;
	if(x[l]<=p[u][l]&&x[r]<=p[u][r]){p[u]=x;return;}
	int mid=(l+r)>>1;
	if(x[mid]<p[u][mid])std::swap(x,p[u]);
	if(l!=r)x[l]<p[u][l]?modify(lc[u],x,l,mid):modify(rc[u],x,mid+1,r);
}
long long query(int u,int k,int l,int r){
	if(!u)return 1e18;
	if(l==r)return p[u][k];
	int mid=(l+r)>>1;
	return std::min(p[u][k],k<=mid?query(lc[u],k,l,mid):query(rc[u],k,mid+1,r));
}
void solve(){
	nod=rt=0;
	for(auto vet:set){
		for(auto it:vet)res[it.u]=std::min(res[it.u],it.dis+query(rt,a[it.u],1,1000000));
		for(auto it:vet)modify(rt,(line){a[it.u],it.dis},1,1000000);
	}
}
void solve(int u){
	// printf("=== solve %d ===\n",u);
	vis[u]=1;
	set.clear();
	set.push_back(std::vector<info>{(info){u,0}});
	walk(u,v,w,if(!vis[v]){
		set.push_back(std::vector<info>{});
		search(v,u,w);
	})
	// for(auto vet:set){for(auto it:vet)printf("[%d %lld] ",it.u,it.dis);puts("");}
	solve();
	std::reverse(set.begin(),set.end());
	solve();
	walk(u,v,w,if(!vis[v]){
		maxp[root=0]=full=siz[v];findroot(v,u);
		solve(root);
	})
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n);
	for(int i=1;i<=n;i++)read(a[i]),res[i]=(long long)a[i]*a[i];
	for(int u,v,w,i=1;i<n;i++){
		read(u),read(v),read(w);
		G[u].push_back(std::make_pair(v,w));
		G[v].push_back(std::make_pair(u,w));
	}
	maxp[root=0]=full=n,findroot(1,0);
	solve(root);
	for(int i=1;i<=n;i++)sum+=res[i];
	// for(int i=1;i<=n;i++)printf("%lld%c",res[i]," \n"[i==n]);
	printf("%lld\n",sum);
}