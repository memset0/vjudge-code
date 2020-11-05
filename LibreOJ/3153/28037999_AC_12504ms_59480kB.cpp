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
const int N=5e5+10;
int n,m,top,a[N],ans[N],stk[N];
std::vector<int> b[N];
std::vector<std::pair<int,int>> q[N];
struct node{int l,r,mid,max,flag,local;}p[N<<2];
inline void pushup(int u,int w){
	p[u].flag=std::max(p[u].flag,w);
	p[u].max=std::max(p[u].max,p[u].local+w);
}
inline void pushdown(int u){
	if(p[u].flag==-1||p[u].l==p[u].r)return;
	pushup(u<<1,p[u].flag),pushup(u<<1|1,p[u].flag),p[u].flag=-1;
}
void build(int u,int l,int r){
	p[u].l=l,p[u].r=r,p[u].mid=(l+r)>>1,p[u].max=p[u].flag=-1;
	if(l==r){p[u].local=a[l];return;}
	build(u<<1,l,p[u].mid);
	build(u<<1|1,p[u].mid+1,r);
	p[u].local=std::max(p[u<<1].local,p[u<<1|1].local);
}
void modify(int u,int l,int r,int w){
	// printf("modify %d %d %d %d\n",u,l,r,w);
	pushdown(u);
	if(p[u].l==l&&p[u].r==r){pushup(u,w);return;}
	if(r<=p[u].mid)modify(u<<1,l,r,w);
	else if(l>p[u].mid)modify(u<<1|1,l,r,w);
	else modify(u<<1,l,p[u].mid,w),modify(u<<1|1,p[u].mid+1,r,w);
	p[u].max=std::max(p[u<<1].max,p[u<<1|1].max);
}
int query(int u,int l,int r){
	// printf("query %d %d %d\n",u,l,r);
	pushdown(u);
	if(p[u].l==l&&p[u].r==r)return p[u].max;
	if(r<=p[u].mid)return query(u<<1,l,r);
	if(l>p[u].mid)return query(u<<1|1,l,r);
	return std::max(query(u<<1,l,p[u].mid),query(u<<1|1,p[u].mid+1,r));
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n);
	for(int i=1;i<=n;i++)read(a[i]);
	for(int i=1;i<=n;i++){
		while(top&&a[stk[top]]<a[i])b[stk[top--]].push_back(i);
		b[stk[top]].push_back(i),stk[++top]=i;
	}
	// for(int i=1;i<=n;i++)for(int j:b[i])printf("> %d %d\n",i,j);
	read(m);
	for(int l,r,i=1;i<=m;i++){
		read(l),read(r);
		q[l].push_back(std::make_pair(r,i));
	}
	build(1,1,n);
	for(int i=n;i>=1;i--){
		// printf("=== %d ===\n",i);
		for(int j:b[i])if(j*2-i<=n)modify(1,j*2-i,n,a[i]+a[j]);
		for(auto it:q[i])ans[it.second]=query(1,i,it.first);
	}
	for(int i=1;i<=m;i++)print(ans[i],'\n');
}
