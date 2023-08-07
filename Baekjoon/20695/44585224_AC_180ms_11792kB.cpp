#include<bits/stdc++.h>
using namespace std;
const int N=1e5+9,stp=131131,mod=998244353;
int n,m,a[N];
struct h{
	int x;
	inline h operator*(const h &rhs){
		return {(int)((long long)x*rhs.x%mod)};
	}
	friend inline h operator+(const h &a,const h &b){
		return {(a.x+b.x)%mod};
	}
	friend inline h operator-(const h &a,const h &b){
		return {(a.x-b.x)%mod};
	}
};
inline int fpow(int a,int b){
	int s=1;
	for(;b;b>>=1,a=(long long)a*a%mod)
		if(b&1)s=(long long)s*a%mod;
	return s;
}
inline h get_hash(int x){
	return {fpow(stp,x)};
}
inline h get_range_hash(int x,int n){
	if(x==0)return {n};
	int b=fpow(stp,x);
	int s=((long long)fpow(b,n)-1)*fpow(b-1,mod-2)%mod;
	return {(s+mod)%mod};
}
struct segment{
	int l,r,mid;
	h hsh;
	array<int,2> mns;
	inline void init(int x){
		hsh=get_hash(x);
		mns[0]=x;
		mns[1]=INT_MAX;
	}
}p[N<<2];
inline array<int,2> mergemns(const array<int,2> &a,const array<int,2> &b){
	static array<int,4> c;
	for(int i=0;i<2;i++)c[i]=a[i];
	for(int i=0;i<2;i++)c[i+2]=b[i];
	sort(c.begin(),c.end());
	array<int,2> d;
	for(int i=0;i<2;i++)d[i]=c[i];
	return d;
}
inline void maintain(int u){
	p[u].mns=mergemns(p[u<<1].mns,p[u<<1|1].mns);
	p[u].hsh=p[u<<1].hsh+p[u<<1|1].hsh;
}
void build(int u,int l,int r){
	// cerr<<"build "<<u<<" "<<l<<" "<<r<<endl;
	p[u].l=l,p[u].r=r,p[u].mid=(l+r)>>1;
	if(l==r){
		p[u].init(a[l]);
		return;
	}
	build(u<<1,l,p[u].mid);
	build(u<<1|1,p[u].mid+1,r);
	maintain(u);
}
void modify(int u,int k,int x){
	if(p[u].l==p[u].r){
		p[u].init(x);
		return;
	}
	if(k<=p[u].mid){
		modify(u<<1,k,x);
	}else{
		modify(u<<1|1,k,x);
	}
	maintain(u);
}
array<int,2> query_mns(int u,int l,int r){
	// cerr<<"query mns "<<u<<" "<<l<<" "<<r<<" : "<<p[u].l<<" "<<p[u].r<<endl;
	if(p[u].l==l&&p[u].r==r)return p[u].mns;
	if(r<=p[u].mid)return query_mns(u<<1,l,r);
	if(l>p[u].mid)return query_mns(u<<1|1,l,r);
	return mergemns(query_mns(u<<1,l,p[u].mid),query_mns(u<<1|1,p[u].mid+1,r));
}
h query_hsh(int u,int l,int r){
	if(p[u].l==l&&p[u].r==r)return p[u].hsh;
	if(r<=p[u].mid)return query_hsh(u<<1,l,r);
	if(l>p[u].mid)return query_hsh(u<<1|1,l,r);
	return query_hsh(u<<1,l,p[u].mid)+query_hsh(u<<1|1,p[u].mid+1,r);
}
inline bool query(int l,int r){
	if(r-l+1<3)return true;
	// fprintf(stderr,"query[%d,%d]\n",l,r);
	auto mns=query_mns(1,l,r);
	// fprintf(stderr,"query[%d,%d]->%d,%d\n",l,r,mns[0],mns[1]);
	int x=mns[1]-mns[0];
	h tar=get_hash(mns[0])*get_range_hash(x,r-l+1);
	h cur=query_hsh(1,l,r);
	// fprintf(stderr,"query[%d,%d]-> %d || %d\n",l,r,cur.x,tar.x);
	return tar.x==cur.x;
}
int main(){
#ifdef memset0
	freopen("J.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	build(1,1,n);
	for(int op,x,y,l,r,i=1;i<=m;i++){
		cin>>op;
		if(op==1){
			cin>>x>>y;
			modify(1,x,y);
		}else{
			cin>>l>>r;
			cout<<(query(l,r)?"YES":"NO")<<'\n';
		}
	}
}