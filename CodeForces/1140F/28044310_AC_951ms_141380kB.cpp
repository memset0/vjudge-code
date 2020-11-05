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
const int N=3e5+10;
int n; long long ans,out[N];
std::map<std::pair<int,int>,int> map;
struct info{int x,y,l,r;}; std::vector<info> q;
struct node{int u,l,r,mid; std::vector<std::pair<int,int>> vet;}p[N<<2];
struct atom{int f,a,b; long long s(){return (long long)a*b;}}f[N<<1];
int find(int x){return f[x].f==x?x:find(f[x].f);}
void merge(int u,int v,std::vector<std::pair<int,atom>> &rub){ // $u merge to $v
	// printf("merge %d[%d] %d[%d]\n",u,find(u),v,find(v));
	u=find(u),v=find(v); if(u==v)return; if(f[u].a+f[u].b>f[v].a+f[v].b)std::swap(u,v);
	ans-=f[u].s(),rub.push_back(std::make_pair(u,f[u]));
	ans-=f[v].s(),rub.push_back(std::make_pair(v,f[v]));
	f[u].f=v,f[v].a+=f[u].a,f[v].b+=f[u].b,ans+=f[v].s();
	// printf("-> %d %d : %lld\n",f[v].a,f[v].b,f[v].s());
}
void build(int u,int l,int r){
	p[u].l=l,p[u].r=r,p[u].mid=(l+r)>>1; if(l==r)return;
	build(u<<1,l,p[u].mid),build(u<<1|1,p[u].mid+1,r);
}
void insert(int u,int l,int r,std::pair<int,int> v){
	// if(u==1)printf("insert %d[%d %d] %d %d : %d %d\n",u,p[u].l,p[u].r,l,r,v.first,v.second);
	if(p[u].l==l&&p[u].r==r){p[u].vet.push_back(v);return;}
	if(r<=p[u].mid)insert(u<<1,l,r,v);
	else if(l>p[u].mid)insert(u<<1|1,l,r,v);
	else insert(u<<1,l,p[u].mid,v),insert(u<<1|1,p[u].mid+1,r,v);
}
void dfs(int u){
	// printf("dfs %d[%d %d]\n",u,p[u].l,p[u].r);
	std::vector<std::pair<int,atom>> rub; long long rubans=ans;
	for(const auto &x:p[u].vet)merge(x.first,x.second+N,rub);
	if(p[u].l==p[u].r)out[p[u].l]=ans; else dfs(u<<1),dfs(u<<1|1);
	for(const auto &x:(std::reverse(rub.begin(),rub.end()),rub))f[x.first]=x.second; ans=rubans;
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	for(int i=0;i<N;i++)f[i]={i,1,0},f[i+N]={i+N,0,1};
	read(n);
	for(int x,y,i=1;i<=n;i++){
		read(x),read(y); auto it=std::make_pair(x,y);
		map[it]?(q.push_back({x,y,map[it],i-1}),map[it]=0):(map[it]=i);
	}
	for(const auto &it:map)if(it.second)q.push_back({it.first.first,it.first.second,it.second,n});
	build(1,1,n);
	for(const auto &it:q)insert(1,it.l,it.r,std::make_pair(it.x,it.y));
	dfs(1);
	for(int i=1;i<=n;i++)print(out[i]),putchar(' ');
}