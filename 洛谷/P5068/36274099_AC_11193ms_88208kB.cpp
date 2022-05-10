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
int n,m,q,t,fst[N],a[M],rt[M],ans[M];
std::vector<int> todo[M];
struct query{int l,r,t;}b[M];
std::vector<query> toquery[M];
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
	int cnt,sum[M<<2];
	void build(int u,int l,int r){
		u=++cnt;
		if(l==r)return;
		int mid=(l+r)>>1;
		build(u<<1,l,mid),build(u<<1|1,mid+1,r);
	}
	void modify(int u,int x,int l,int r){
		sum[u]++;
		if(l==r)return;
		int mid=(l+r)>>1;
		if(x<=mid)modify(u<<1,x,l,mid);
		else modify(u<<1|1,x,mid+1,r);
	}
	int query(int u,int ql,int qr,int l,int r){
		if(ql==l&&qr==r)return sum[u];
		int mid=(l+r)>>1;
		if(qr<=mid)return query(u<<1,ql,qr,l,mid);
		if(ql>mid)return query(u<<1|1,ql,qr,mid+1,r);
		return query(u<<1,ql,mid,l,mid)+query(u<<1|1,mid+1,qr,mid+1,r);
	}
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	memset(fst,63,sizeof(fst));
	read(n),read(m);
	for(int l,r,o,i=1;i<=m;i++)if(read(o),o==1){
		read(a[++t]);
	}else{
		read(l),read(r),b[++q]={l,r,t};
	}
	for(int i=1;i<=t;i++)fst[a[i]]=std::min(i,fst[a[i]]);
	f::build(1,1,n);
	for(int i=1;i<=n;i++){
		int max=0;
		for(int l=1,r=i;l<=n;l+=i,r=std::min(n,r+i)){
			int x=std::max(f::query(1,l,r,1,n),max);
			max=x;
			if(x<=t)todo[x].push_back(i);
		}
	}
	for(int i=1;i<=q;i++)toquery[b[i].t].push_back({b[i].l,b[i].r,i});
	g::build(1,1,n);
	for(int i=0;i<=t;i++){
		for(int x:todo[i])g::modify(1,x,1,n);
		for(const auto &q:toquery[i]){
			ans[q.t]=q.r-q.l+1+g::query(1,q.l,q.r,1,n);
		}
	}
	for(int i=1;i<=q;i++)print(ans[i],'\n');
}