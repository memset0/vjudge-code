#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int T,n,t,cnt,w[N],fa[N],siz[N],dfn[N],idfn[N];
bool vis[N];
long long life;
vector<int> G[N];
namespace a{
	long long src[N];
	struct Segment{
		int l,r,mid,maxk;
		bool vis;
		long long sum,maxv;
	}p[N<<2];
	inline void maintain(int u){
		if(p[u].l==p[u].r){
			if(p[u].vis){
				p[u].maxv=p[u].sum;
				p[u].maxk=p[u].l;
			}else{
				p[u].maxv=-5e12;
				p[u].maxk=-1;
			}
		}else{
			if(p[u<<1].maxv>p[u<<1|1].maxv){
				p[u].maxv=p[u<<1].maxv;
				p[u].maxk=p[u<<1].maxk;
			}else{
				p[u].maxv=p[u<<1|1].maxv;
				p[u].maxk=p[u<<1|1].maxk;
			}
			p[u].maxv+=p[u].sum;
		}
	}
	void build(int u,int l,int r){
		p[u].l=l,p[u].r=r,p[u].mid=(l+r)>>1;
		if(p[u].l==p[u].r){
			p[u].sum=src[l];
			p[u].vis=false;
			return maintain(u);
		}
		p[u].sum=0;
		build(u<<1,l,p[u].mid);
		build(u<<1|1,p[u].mid+1,r);
		maintain(u);
	}
	void update(int u,int k){
		if(p[u].l==p[u].r){
			p[u].vis^=1;
			return maintain(u);
		}
		update(k<=p[u].mid?u<<1:u<<1|1,k);
		maintain(u);
	}
	void modify(int u,int l,int r,int w){
//		printf("a::modify %d %d %d %d\n",u,l,r,w);
		if(p[u].l==l&&p[u].r==r){
			p[u].sum+=w;
			return maintain(u);
		}
		if(r<=p[u].mid)modify(u<<1,l,r,w);
		else if(l>p[u].mid)modify(u<<1|1,l,r,w);
		else modify(u<<1,l,p[u].mid,w),modify(u<<1|1,p[u].mid+1,r,w);
		maintain(u);
	}
}
namespace b{
	long long src[N];
	struct Segment{
		int l,r,mid,mink;
		long long sum,minv;
	}p[N<<2];
	inline void maintain(int u){
		if(p[u].l==p[u].r){
			p[u].minv=p[u].sum;
			p[u].mink=p[u].l;
		}else{
			if(p[u<<1].minv<p[u<<1|1].minv){
				p[u].minv=p[u<<1].minv;
				p[u].mink=p[u<<1].mink;
			}else{
				p[u].minv=p[u<<1|1].minv;
				p[u].mink=p[u<<1|1].mink;
			}
			p[u].minv+=p[u].sum;
		}
	}
	void build(int u,int l,int r){
		p[u].l=l,p[u].r=r,p[u].mid=(l+r)>>1;
		if(p[u].l==p[u].r){
			p[u].sum=src[l];
			return maintain(u);
		}
		p[u].sum=0;
		build(u<<1,l,p[u].mid);
		build(u<<1|1,p[u].mid+1,r);
		maintain(u);
	}
	void update(int u,int k){
//		printf("b::update %d[%d %d] %d\n",u,p[u].l,p[u].r,k);
		if(p[u].l==p[u].r){
			p[u].sum=5e12;
			return maintain(u);
		}
		update(k<=p[u].mid?u<<1:u<<1|1,k);
		maintain(u);
	}
	void modify(int u,int l,int r,int w){
		if(p[u].l==l&&p[u].r==r){
			p[u].sum+=w;
			return maintain(u);
		}
		if(r<=p[u].mid)modify(u<<1,l,r,w);
		else if(l>p[u].mid)modify(u<<1|1,l,r,w);
		else modify(u<<1,l,p[u].mid,w),modify(u<<1|1,p[u].mid+1,r,w);
		maintain(u);
	}
}
void init(){
	life=cnt=0;
	for(int i=1;i<=n;i++)G[i].clear();
}
void dfs(int u){
	siz[u]=1;
	dfn[u]=++cnt;
	idfn[dfn[u]]=u;
	a::src[dfn[u]]=a::src[dfn[fa[u]]]+w[u];
	b::src[dfn[u]]=max(b::src[dfn[fa[u]]],-w[u]-a::src[dfn[fa[u]]]);
//	printf("DFS %d :: %lld %lld\n",u,a::src[dfn[u]],b::src[dfn[u]]);
	for(int v:G[u])if(v!=fa[u]){
		fa[v]=u;
		dfs(v);
		siz[u]+=siz[v];
	}
}
inline void open(int u){
	life+=w[u];
//	printf("> open %d => life=%lld\n",u,life);
	vis[u]=true;
	a::update(1,dfn[u]);
	a::modify(1,dfn[u],dfn[u]+siz[u]-1,-w[u]);
	b::modify(1,dfn[u],dfn[u]+siz[u]-1,-w[u]);
}
inline void maintain(){
	while(b::p[1].minv<=life){
//		printf("> update [%d] %d %lld\n",idfn[b::p[1].mink],b::p[1].mink,b::p[1].minv);
		a::update(1,b::p[1].mink);
		b::update(1,b::p[1].mink);
	}
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T-->0){
		cin>>n>>t;
		init();
		for(int i=1;i<=n;i++){
			cin>>w[i];
		}
		for(int u,v,i=1;i<n;i++){
			cin>>u>>v;
			G[u].push_back(v);
			G[v].push_back(u);
		}
		dfs(1);
//		for(int i=1;i<=n;i++)printf("%d%c",dfn[i]," \n"[i==n]);
//		for(int i=1;i<=n;i++)printf("%d%c",siz[i]," \n"[i==n]);
		a::build(1,1,n);
		b::build(1,1,n);
		maintain();
		while(true){
			if(a::p[1].maxv<0||a::p[1].maxk==-1){
				break;
			}
			int u=a::p[1].maxk;
//			printf("u=%d :: %d %lld\n",idfn[u],u,a::p[1].maxv);
			while(!vis[u]&&u){
				open(u);
				u=fa[u];
			}
			maintain();
			if(vis[t]){
				puts("escaped");
				goto next;
			}
		}
		puts("trapped");
	next:
		continue;
	}
}