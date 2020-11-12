
#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
template<class T> inline void readc(T &x){
	x=getchar(); while(!isalpha(x))x=getchar();
}
 
const int N=2.5e5+10;
int n,m,a[N];
 
struct node{
	int l,r,mid;
	bool mrk;
	double sum,tag;
}p[N<<2];
 
void pushup(int u,double v){
	p[u].mrk=1,p[u].tag=v,p[u].sum=(p[u].r-p[u].l+1)*v;
}
 
void pushdown(int u){
	if(p[u].mrk){
		pushup(u<<1,p[u].tag);
		pushup(u<<1|1,p[u].tag);
		p[u].mrk=0;
	}
}
 
void build(int u,int l,int r){
	p[u].l=l,p[u].r=r,p[u].mid=(l+r)>>1;
	if(l==r){p[u].sum=a[l];return;}
	build(u<<1,l,p[u].mid),build(u<<1|1,p[u].mid+1,r);
	p[u].sum=p[u<<1].sum+p[u<<1|1].sum;
}
 
void modify(int u,int l,int r,double v){
	if(p[u].l==l&&p[u].r==r)return void(pushup(u,v));
	pushdown(u);
	if(r<=p[u].mid)modify(u<<1,l,r,v);
	else if(l>p[u].mid)modify(u<<1|1,l,r,v);
	else modify(u<<1,l,p[u].mid,v),modify(u<<1|1,p[u].mid+1,r,v);
	p[u].sum=p[u<<1].sum+p[u<<1|1].sum;
}
 
double query(int u,int l,int r){
	// printf("query %d[%d %d] %d %d => %.2lf\n",u,p[u].l,p[u].r,l,r,p[u].sum);
	if(p[u].l==l&&p[u].r==r)return p[u].sum;
	pushdown(u);
	if(r<=p[u].mid)return query(u<<1,l,r);
	if(l>p[u].mid)return query(u<<1|1,l,r);
	return query(u<<1,l,p[u].mid)+query(u<<1|1,p[u].mid+1,r);
}
 
int main(){
#ifdef memset0	
	freopen("1.in","r",stdin);
#endif
	read(n),read(m);
	for(int i=1;i<=n;i++)read(a[i]);
	build(1,1,n);
	for(int i=1,o,k,l,r;i<=m;i++){
		readc(o);
		if(o=='g'){
			read(k);
			printf("%.10lf\n",query(1,k,k));
		}else{
			read(l),read(r);
			modify(1,l,r,query(1,l,r)/(r-l+1));
		}
	}
}