#include<bits/stdc++.h>
const int S=1<<21; char ibuf[S],*iS,*iT,obuf[S],*oS=obuf,*oT=oS+S-1;
#define flush() (fwrite(obuf,1,oS-obuf,stdout),oS=obuf,void())
#define getchar() (iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,S,stdin),(iS==iT?EOF:*iS++)):*iS++)
#define putchar(x) (*oS++=(x),oS==oT?flush():void())
struct Flusher_{~Flusher_(){flush();}}flusher_;
std::mt19937 rng(20040725^std::chrono::steady_clock::now().time_since_epoch().count());
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10); putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}
#ifdef memset0
const int N=30;
#else
const int N=3e3+10;
#endif
int T,n,ans,sum;
struct segment{int l,r;};
template<int N,int M> struct Dinic{
	int s,t,tot,cur[N],hed[N],dep[N],to[M<<1],val[M<<1],nxt[M<<1];
	inline Dinic(){memset(hed,-1,sizeof(hed));}
	inline int newnode(){return t++;}
	inline void reset(){tot=0,memset(hed,-1,(t+1)<<2),s=1,t=2;}
	inline void add(int u,int v){
		nxt[tot]=hed[u],to[tot]=v,val[tot]=1,hed[u]=tot++;
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
		return s?s:dep[s]=0;
	}
	void debug(){
		printf("dinic <s=%d> <t=%d> <tot=%d>\n",s,t,tot);
		for(int u=1;u<=t;u++)for(int i=hed[u];~i;i=nxt[i])if(val[i])printf("%d -> %d : %d\n",i,to[i],val[i]);
	}
};
Dinic<N*2,N*N> dinic;
std::vector<int> all;
std::vector<segment> p,a,b;
void solve(int x){
	// printf("solve %d\n",x);
	int ans=0;
	std::vector<segment> a,b;
	for(const auto &p:(::a))if(p.l<=x&&p.r>=x)a.push_back(p);
	for(const auto &p:(::b))if(p.l>x&&p.r<x)b.push_back(p); else ++ans;
	if(ans+a.size()+b.size()<::ans)return;
	std::vector<int> ida(a.size()),idb(b.size());
	dinic.reset();
	for(int &x:ida)x=dinic.newnode();
	for(int &x:idb)x=dinic.newnode();
	for(int i=0;i<a.size();i++)dinic.add(dinic.s,ida[i]);
	for(int i=0;i<b.size();i++)dinic.add(idb[i],dinic.t);
	for(int i=0;i<a.size();i++)for(int j=0;j<b.size();j++){
		if(b[j].r<a[i].l&&a[i].r<b[j].l)dinic.add(ida[i],idb[j]);
	}
	ans+=a.size()+b.size();
	while(dinic.bfs()){
		memcpy(dinic.cur+1,dinic.hed+1,dinic.t<<2);
		ans-=dinic.dfs(dinic.s,1e9);
		if(ans<::ans)return;
	}
	::ans=ans;
}
int main(){
#ifdef memset0
	freopen("D.in","r",stdin);
#endif
	for(read(T);T--;){
		read(n),sum=ans=0,p.resize(n),a.clear(),b.clear(),all.clear();
		for(int i=0,l,r;i<n;i++)read(p[i].l),read(p[i].r);
		for(int i=0;i<n;i++)(p[i].l<=p[i].r?a:b).push_back(p[i]);
		for(int i=0;i<n;i++)all.push_back(p[i].l),all.push_back(p[i].r);
		std::sort(all.begin(),all.end());
		all.erase(std::unique(all.begin(),all.end()),all.end());
		std::shuffle(all.begin(),all.end(),rng);
		for(int x:all)solve(x);
		print(ans+sum,'\n');
	}
}