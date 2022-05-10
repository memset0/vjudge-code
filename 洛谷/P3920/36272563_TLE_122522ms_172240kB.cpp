#include<bits/stdc++.h>
#define walk(u,v,w,f) for(auto _it:G[u]){int v=_it.first,w=_it.second; f;}
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10); putchar(x%10+'0');
}
const int N=1e5+10,M=4e6;
int T,n,a[N],c[N],r[N];
std::vector<std::pair<int,int>> G[N];
namespace sgt{
#define lc(u) (e[u].ch[0])
#define rc(u) (e[u].ch[1])
	int nod,top,len,q[N],stk[M];
	struct node{
		long long val; int siz,ch[2];
		inline void clear(){ch[0]=ch[1]=0;}
	}e[M];
	inline int newnode(){return top?stk[--top]:++nod;}
	inline void delnode(int u){e[stk[top++]=u].clear();}
	struct tree{
		int rt;
		void deltree(int u){if(!u)return; deltree(lc(u)),deltree(rc(u)),delnode(u);}
		void pia(int u){if(!u)return; pia(lc(u)),q[len++]=e[u].val,pia(rc(u)),delnode(u);}
		void build(int &u,int l,int r){
			if(l>r)return; int mid=(l+r)>>1; u=newnode();
			e[u].val=q[mid],e[u].siz=r-l+1,build(lc(u),l,mid-1),build(rc(u),mid+1,r);
		}
		void insert(int &u,int x){
			if(!u){u=newnode(),e[u].val=x,e[u].siz=1;return;}
			insert(e[u].ch[x>e[u].val],x),e[u].siz=e[lc(u)].siz+e[rc(u)].siz+1;
			// if(e[lc(u)].siz*5>e[u].siz*4||e[rc(u)].siz*5>e[u].siz*4)pia(u),build(u,0,len-1);
		}
		int query(int u,int x){if(!u)return 0; return x<=e[u].val?query(lc(u),x)+(e[u].val==x):query(rc(u),x)+e[lc(u)].siz+1;}
		inline void insert(int x){this->insert(this->rt,x);}
		inline int query(int x){return this->query(this->rt,x);}
		inline void clear(){deltree(rt),rt=0;}
	};
	// struct tree{
	// 	std::vector<long long> rt;
	// 	inline void clear(){rt.clear();}
	// 	inline void insert(long long x){rt.push_back(x);}
	// 	inline int query(long long x){int s=0;for(long long y:rt)s+=y<=x;return s;}
	// };
} // namespace sgt
namespace vdc{
	struct atom{int nod; long long val; int src;};
	bool vis[N];
	long long ans;
	int nxt,ful,fa[N],siz[N],mxp[N];
	sgt::tree ut[N],ft[N];
	std::vector<int> son[N];
	std::vector<atom> bkt,vet[N];
	void debug(int n){
		puts("====================");
		for(int i=1;i<=n;i++)if(fa[i])printf("%d %d\n",fa[i],i);
		puts("--------------------");
		for(int i=1;i<=n;i++){
			printf("%4d | fa=%3d | ",i,fa[i]);
			for(auto j:vet[i])printf("{%d,%lld,%d},",j.nod,j.val,j.src); printf("\n     | ");
			// for(auto j:ut[i].a)printf("%lld,",j); printf("   |   ");
			// for(auto j:ft[i].a)printf("%lld,",j); putchar('\n');
		}
		puts("====================");
	}
	void dfs(int u,int fa,long long dis,int src,std::vector<atom> &q){
		// printf("DFS %d %d %lld %d\n",u,fa,dis,src);
		q.push_back({u,dis-r[u],src});
		walk(u,v,w,if(!vis[v]&&v!=fa)dfs(v,u,dis+w,src,q));
	}
	void findroot(int u,int fa=0){
		siz[u]=1,mxp[u]=0;
		walk(u,v,w,if(!vis[v]&&v!=fa){findroot(v,u);siz[u]+=siz[v];mxp[u]=std::max(mxp[u],siz[v]);});
		mxp[u]=std::max(mxp[u],ful-siz[u]); if(mxp[u]<mxp[nxt])nxt=u;
	}
	void solve(int u){
		// printf("SOLVE %d\n",u);
		std::vector<int> tmp; std::vector<atom> q;
		vis[u]=1,ut[u].insert(-r[u]),vet[u].push_back({u,-r[u],0});
		walk(u,v,w,if(!vis[v]){
			mxp[nxt=0]=ful=siz[v];findroot(v);tmp.push_back(nxt);
			q.clear();dfs(v,u,w,nxt,q);
			for(auto x:q){ut[u].insert(x.val);ft[nxt].insert(x.val);vet[x.nod].push_back({u,x.val,nxt});}
		})
		for(int v:tmp)fa[v]=u,son[u].push_back(v),solve(v);
	}
	void allnode(int u,int fa,std::vector<int> &q){q.push_back(u); for(int v:son[u])allnode(v,u,q);}
	void rebuild(int u){
		// printf("REBUILD %d\n",u);
		std::vector<int> q; allnode(u,0,q);
		for(int x:q)vis[x]=0,son[x].clear(),ut[x].clear();
		for(int x:q)if(x!=u)fa[x]=0,ft[x].clear();
		for(int x:q){while(vet[x].back().nod!=u)vet[x].pop_back(); vet[x].pop_back();}
		mxp[nxt=0]=ful=q.size(),findroot(u);
		if(nxt!=u){
			// printf("REBUILD %d <=> %d\n",u,nxt);
			// printf("  => | "); for(int x:son[fa[u]])printf("%d ",x); putchar('\n');
			for(int &x:son[fa[u]])if(x==u){x=nxt; break;}
			// printf("  => | "); for(int x:son[fa[u]])printf("%d ",x); putchar('\n');
			std::swap(fa[u],fa[nxt]);
			std::swap(ft[u].rt,ft[nxt].rt);
			for(int x:q)if(vet[x].size())vet[x].back().src=nxt;
			// for(int x:q){
			// 	printf("%4d | ",x);
			// 	for(auto y:vet[x])printf("{%d,%lld,%d} ",y.nod,y.val,y.src); putchar('\n');
			// }
		}
		solve(nxt);
	}
	void insert(int u){
		// printf("INSERT %d %d %d\n",a[u],c[u],r[u]);
		vis[u]=1,fa[u]=a[u],son[a[u]].push_back(u);
		for(auto x:vet[a[u]]){
			int val=x.val+r[a[u]]-r[u]+c[u]; if(!x.src)x.src=u;
			vet[u].push_back({x.nod,val,x.src}),++siz[x.nod];
			// printf("{%d %lld %d} => %d %d\n",x.nod,x.val,x.src,ut[x.nod].query(-val+1),ft[x.src].query(-val+1));
			ans+=ut[x.nod].query(-val),ut[x.nod].insert(val);
			ans-=ft[x.src].query(-val),ft[x.src].insert(val);
		}
		vet[u].push_back({u,-r[u],0}),ut[u].insert(-r[u]),siz[u]=1;
		for(auto x:vet[a[u]])if(fa[x.nod]&&siz[x.nod]*5>siz[fa[x.nod]]*4){
			rebuild(fa[x.nod]); break;
		}
	}
	inline void init(){vis[1]=1,ut[1].insert(-r[1]),vet[1].push_back({1,-r[1],0});}
} // namespace vdc
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(T),read(n),read(a[1]),read(c[1]),read(r[1]),puts("0"),vdc::init();
	for(int i=2;i<=n;i++){
		read(a[i]),read(c[i]),read(r[i]); a[i]=a[i]^(vdc::ans%1000000000);
		G[a[i]].push_back(std::make_pair(i,c[i])),G[i].push_back(std::make_pair(a[i],c[i]));
		vdc::insert(i),print(vdc::ans),putchar('\n');
		// vdc::debug(i);
	}
}