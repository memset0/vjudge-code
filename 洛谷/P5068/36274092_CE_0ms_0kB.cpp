#include<bits/stdc++.h>
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
const int N=1e5+10,M=1e6+10;
int n,m,q,t,fst[N],a[M],rt[M];
std::vector<int> todo[M];
struct query{
	int l,r,t;
}b[M];
namespace f{
	int min[N<<2];
	void build(int u,int l,int r){
		if(l==r){min[u]=fst[l]; return;}
		int mid=(l+r)>>1;
		build(u<<1,l,mid),build(u<<1|1,mid+1,r);
		min[u]=std::min(min[u<<1],min[u<<1|1]);
	}
	int query(int u,int ql,int qr,int l,int r){
		if(ql==l&&qr==r)return min[u];
		int mid=(l+r)>>1;
		if(qr<=mid)return query(u<<1,ql,qr,l,mid);
		if(ql>mid)return query(u<<1|1,ql,qr,mid+1,r);
		return std::min(query(u<<1,ql,mid,l,mid),query(u<<1|1,mid+1,qr,mid+1,r));
	}
}
namespace g{
	const int L=M*20;
	int cnt,sum[L];
	int_fast16_t lc[L],rc[L];
	void build(int &u,int l,int r){
		u=++cnt;
		if(l==r)return;
		int mid=(l+r)>>1;
		build(lc[u],l,mid),build(rc[u],mid+1,r);
	}
	void modify(int &u,int v,int x,int l,int r){
		u=++cnt,lc[u]=lc[v],rc[u]=rc[v],sum[u]=sum[v]+1;
		if(l==r)return;
		int mid=(l+r)>>1;
		if(x<=mid)modify(lc[u],lc[v],x,l,mid);
		else modify(rc[u],rc[v],x,mid+1,r);
	}
	int query(int u,int ql,int qr,int l,int r){
		if(ql==l&&qr==r)return sum[u];
		int mid=(l+r)>>1;
		if(qr<=mid)return query(lc[u],ql,qr,l,mid);
		if(ql>mid)return query(rc[u],ql,qr,mid+1,r);
		return query(lc[u],ql,mid,l,mid)+query(rc[u],mid+1,qr,mid+1,r);
	}
}
int main(){
#ifdef memset0
	freopen("B.in","r",stdin);
#endif
	memset(fst,63,sizeof(fst));
	read(n),read(m);
	for(int l,r,o,i=1;i<=m;i++)if(read(o),o==1){
		read(a[++t]);
	}else{
		read(l),read(r),b[++q]={l,r,t};
	}
	for(int i=1;i<=t;i++)fst[a[i]]=std::min(i,fst[a[i]]);
	// for(int i=1;i<=n;i++)print(fst[i]," \n"[i==n]);
	f::build(1,1,n);
	for(int i=1;i<=n;i++){
		int max=0;
		for(int l=1,r=i;l<=n;l+=i,r=std::min(n,r+i)){
			int x=std::max(f::query(1,l,r,1,n),max);
			max=x;
			if(x<=t)todo[x].push_back(i);
			// if(x<=t)printf("%d[%d %d] : %d\n",i,l,r,x);
		}
	}
	g::build(rt[0],1,n);
	for(int i=1;i<=t;i++){
		rt[i]=rt[i-1];
		for(int x:todo[i])g::modify(rt[i],rt[i],x,1,n);
	}
	for(int i=1;i<=q;i++){
		print(g::query(rt[b[i].t],b[i].l,b[i].r,1,n)+b[i].r-b[i].l+1,'\n');
	}
}