#include<bits/stdc++.h>
#define log(...) (void(0))
// #define log(...) fprintf(stderr,__VA_ARGS__)
#define allof(x) (x).begin(),(x).end()
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10); putchar(x%10+'0');
}
const int N=1e5+10;
int n,m,fa[N];
long long siz[N],ans;
std::set<int> a[N],b[N],c[N];
std::vector<int> d[N];
void link(int,int);
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
void merge(int u,int v){
	log("\e[33mMERGE %d %d\e[0m\n",u,v);
	if(siz[u]<siz[v])std::swap(u,v);
	ans-=siz[u]*(siz[u]-1)+siz[u]*c[u].size();
	ans-=siz[v]*(siz[v]-1)+siz[v]*c[v].size();
	log(">>> %lld\n",ans);
	a[u].erase(v),b[u].erase(v),a[v].erase(u),b[v].erase(u);
	std::vector<int> q;
	for(int x:a[v])if(a[x].count(u))q.push_back(x);
	for(int x:b[v])if(b[x].count(u))q.push_back(x);
	for(int x:a[v])a[u].insert(x),b[x].erase(v),b[x].insert(u);
	for(int x:b[v])a[x].erase(v),a[x].insert(u),b[u].insert(x);
	for(int x:c[v])if(find(x)!=u)c[u].insert(x);
	for(int x:d[v])c[u].erase(x);
	fa[v]=u,siz[u]+=siz[v];
	d[u].insert(d[u].end(),allof(d[v]));
	log("%lld %lld\n",siz[u]*(siz[u]-1),siz[u]*c[u].size());
	ans+=siz[u]*(siz[u]-1)+siz[u]*c[u].size();
	for(int x:q)if(find(x)!=find(u))merge(find(x),find(u));
}
void link(int u,int v){
	int fu=find(u),fv=find(v);
	log("\e[33mLINK %d[%d] %d[%d]\e[0m\n",u,fu,v,fv);
	if(fu==fv)return;
	if(!c[fv].count(u)){
		c[fv].insert(u);
		ans+=siz[fv];
	}
	if(a[fu].count(fv)){
		return;
	}
	if(!a[fv].count(fu)){
		a[fu].insert(fv);
		b[fv].insert(fu);
		return;
	}
	merge(fu,fv);
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n),read(m);
	for(int i=1;i<=n;i++){
		fa[i]=i;
		siz[i]=1;
		d[i].push_back(i);
	}
	for(int i=1,u,v;i<=m;i++){
		read(u),read(v);
		link(u,v);
		print(ans),putchar('\n');
#ifdef local
		log("\e[31m-----------------------\e[0m\n");
		log("FA | "); for(int i=1;i<=n;i++)log("%d%c",fa[i]," \n"[i==n]);
		for(int i=1;i<=n;i++)if(find(i)==i)for(int j:a[i])log("A  | %d -> %d\n",i,j);
		for(int i=1;i<=n;i++)if(find(i)==i)for(int j:b[i])log("B  | %d <- %d\n",i,j);
		for(int i=1;i<=n;i++)if(find(i)==i)for(int j:c[i])log("C  | %d <- %d\n",i,j);
		log("\e[31m-----------------------\e[0m\n");
#endif
	}
}