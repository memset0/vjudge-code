#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0;register char c=getchar();register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();if(f)x=-x;
}
const int N=3e5+10;
int n,m,a[N];
long long ans,s[N];
struct atom{
	int l,r,w,k;
	inline bool operator<(const atom &other)const{
		return w>other.w;
	}
}x[N];
struct segment_tree{
	struct node{
		int l,r,mid;
		long long tag,max;
	}p[N<<2];
	inline void pushup(int u,long long x){
		p[u].tag+=x,p[u].max+=x;
	}
	inline void pushdown(int u){
		if(p[u].l==p[u].r||!p[u].tag)return;
		pushup(u<<1,p[u].tag),pushup(u<<1|1,p[u].tag),p[u].tag=0;
	}
	void build(int u,int l,int r,long long foo(int)){
		p[u].l=l,p[u].r=r,p[u].mid=(l+r)>>1;
		if(l==r){p[u].max=foo(l);return;}
		build(u<<1,l,p[u].mid,foo);
		build(u<<1|1,p[u].mid+1,r,foo);
		p[u].max=std::max(p[u<<1].max,p[u<<1|1].max);
	}
	void modify(int u,int l,int r,int x){
		pushdown(u);
		if(p[u].l==l&&p[u].r==r)return pushup(u,x);
		if(r<=p[u].mid)modify(u<<1,l,r,x);
		else if(l>p[u].mid)modify(u<<1|1,l,r,x);
		else modify(u<<1,l,p[u].mid,x),modify(u<<1|1,p[u].mid+1,r,x);
		p[u].max=std::max(p[u<<1].max,p[u<<1|1].max);
	}
	long long query(int u,int l,int r){
		pushdown(u);
		if(p[u].l==l&&p[u].r==r)return p[u].max;
		if(r<=p[u].mid)return query(u<<1,l,r);
		if(l>p[u].mid)return query(u<<1|1,l,r);
		return std::max(query(u<<1,l,p[u].mid),query(u<<1|1,p[u].mid+1,r));
	}
}f,g;
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n),read(m);
	for(int i=1;i<=m;i++)read(a[i]),s[i]=s[i-1]+a[i];
	for(int i=1;i<=n;i++)read(x[i].l),read(x[i].r),read(x[i].w),x[i].k=i;
	f.build(1,1,n,[](int k){return s[x[k].l-1];});
	g.build(1,1,n,[](int k){return -s[x[k].r];});
	std::sort(x+1,x+n+1);
	// for(int i=1;i<=m;i++)printf("%lld%c",s[i]," \n"[i==m]);
	for(int i=1;i<=n;i++)if(f.query(1,1,x[i].k)+g.query(1,x[i].k,n)+1<=0){
		// printf("[%d %d %d %d] >> %lld %lld\n",x[i].l,x[i].r,x[i].w,x[i].k,f.query(1,1,x[i].k),g.query(1,x[i].k,n));
		if(x[i].k<n)f.modify(1,x[i].k+1,n,-1);
		g.modify(1,x[i].k,n,1);
		ans+=x[i].w;
		// for(int i=1;i<=n;i++)printf("%lld%c",f.query(1,i,i)," \n"[i==n]);
		// for(int i=1;i<=n;i++)printf("%lld%c",g.query(1,i,i)," \n"[i==n]);
	}
	printf("%lld\n",ans);
}
			 	//  ikmkkk