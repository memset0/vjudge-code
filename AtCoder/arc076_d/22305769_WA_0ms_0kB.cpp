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
const int N=2e5+10;
int n,m,ans,l[N],r[N];
std::pair<int,int> a[N];
struct node{
	int l,r,mid,max,res,tag;
}p[N<<2];
inline void maintain(int u){
	p[u].max=std::max(p[u<<1].max,p[u<<1|1].max);
	p[u].res=std::max(p[u<<1].res,p[u<<1|1].res);
}
inline void pushup(int u,int v){
	p[u].res+=v,p[u].max+=v,p[u].tag+=v;
}
inline void pushdown(int u){
	if(p[u].tag&&p[u].l!=p[u].r){
		pushup(u<<1,p[u].tag);
		pushup(u<<1|1,p[u].tag);
		p[u].tag=0;
	}
}
void build(int u,int l,int r){
	p[u].l=l,p[u].r=r,p[u].mid=(l+r)>>1;
	if(l==r){p[u].max=p[u].res=-1000000000;return;}
	build(u<<1,l,p[u].mid);
	build(u<<1|1,p[u].mid+1,r);
	maintain(u);
}
void modify(int u,int k,int v){
	pushdown(u);
	if(p[u].l==p[u].r){p[u].max=v,p[u].res=v-m+k-1;return;}
	modify(k<=p[u].mid?(u<<1):(u<<1|1),k,v);
	maintain(u);
}
void modify(int u,int l,int r,int x){
	pushdown(u);
	if(p[u].l==l&&p[u].r==r){pushup(u,x);return;}
	if(r<=p[u].mid)modify(u<<1,l,r,x);
	else if(l>p[u].mid)modify(u<<1|1,l,r,x);
	else modify(u<<1,l,p[u].mid,x),modify(u<<1|1,p[u].mid+1,r,x);
	maintain(u);
}
int query_max(int u,int l,int r){
	pushdown(u);
	if(p[u].l==l&&p[u].r==r)return p[u].max;
	if(r<=p[u].mid)return query_max(u<<1,l,r);
	if(l>p[u].mid)return query_max(u<<1|1,l,r);
	return std::max(query_max(u<<1,l,p[u].mid),query_max(u<<1|1,p[u].mid+1,r));
}
int query_res(int u,int l,int r){
	pushdown(u);
	if(p[u].l==l&&p[u].r==r)return p[u].res;
	if(r<=p[u].mid)return query_res(u<<1,l,r);
	if(l>p[u].mid)return query_res(u<<1|1,l,r);
	return std::max(query_res(u<<1,l,p[u].mid),query_res(u<<1|1,p[u].mid+1,r));
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n),read(m);
	for(int i=1;i<=n;i++)read(a[i].first),read(a[i].second);
	std::sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)l[i]=a[i].first,r[i]=a[i].second;
	build(1,1,m+1);
	for(int i=1;i<=n;i++){
		// printf("=== i = %d : %d %d ===\n",i,l[i],r[i]);
		ans=std::max(ans,1-l[i]-m+r[i]-1);
		if(l[i]>=1)ans=std::max(ans,query_max(1,1,l[i])+1-n)/*,printf("[1] %d\n",query_max(1,1,l[i])+1-n)*/;
		ans=std::max(ans,query_max(1,r[i],m+1)+1-l[i]-m+r[i]-1)/*,printf("[2] %d\n",query_max(1,r[i],m+1)+1-l[i]-m+r[i]-1)*/;
		if(r[i]-l[i]>1)ans=std::max(ans,query_res(1,l[i]+1,r[i]-1)-l[i]+1)/*,printf("[3] %d\n",query_res(1,l[i]+1,r[i]-1)-l[i]+1)*/;
		if(r[i]>1)modify(1,1,r[i]-1,1);
		modify(1,r[i],std::max(1,1+query_max(1,r[i],m+1)));
	}
	print(ans,'\n');
}