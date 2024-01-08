#include<bits/stdc++.h>
using namespace std;
const int N=1e5+9,INF=1e9;
int n,tot,a[N],fa[N],dfn[N],siz[N],idfn[N];
vector<int> ch[N],ans;
void dfs(int u){
	dfn[u]=++tot;
	idfn[dfn[u]]=u;
	siz[u]=1;
	for(int v:ch[u]){
		dfs(v);
		siz[u]+=siz[v];
	}
}
struct node{
	int l,r,mid,x;
}p[N<<2];
int merge(int u,int v){
	if(!u||!v)return u|v;
	return a[u]<a[v]?u:v;
}
void build(int u,int l,int r){
	p[u].l=l,p[u].r=r,p[u].mid=(l+r)>>1;
	if(l==r){
		p[u].x=idfn[l];
		return;
	}
	build(u<<1,l,p[u].mid);
	build(u<<1|1,p[u].mid+1,r);
	p[u].x=merge(p[u<<1].x,p[u<<1|1].x);
}
void update(int u,int k){
	if(p[u].l==p[u].r){
		p[u].x=0;
		return;
	}
	if(k<=p[u].mid){
		update(u<<1,k);
	}else{
		update(u<<1|1,k);
	}
	p[u].x=merge(p[u<<1].x,p[u<<1|1].x);
}
int query(int u,int l,int r){
	if(p[u].l==l&&p[u].r==r)return p[u].x;
	if(r<=p[u].mid)return query(u<<1,l,r);
	if(l>p[u].mid)return query(u<<1|1,l,r);
	return merge(query(u<<1,l,p[u].mid),query(u<<1|1,p[u].mid+1,r));
}
void solve(int u){
	// fprintf(stderr,">> solve %d\n",u);
	int t;
	if(siz[u]>1){
		while(t=query(1,dfn[u]+1,dfn[u]+siz[u]-1)){
			solve(t);
		}
	}
	// fprintf(stderr,"<< push %d\n",u);
	update(1,dfn[u]);
	ans.push_back(u);
}
int main(){
#ifdef memset0
	freopen("E.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n;
	for(int i=2;i<=n;i++){
		cin>>fa[i];
		ch[fa[i]].push_back(i);
	}
	for(int i=1;i<=n;i++)cin>>a[i];
	dfs(1);
	// for(int i=1;i<=n;i++)cerr<<dfn[i]<<" \n"[i==n];
	// for(int i=1;i<=n;i++)cerr<<idfn[i]<<" \n"[i==n];
	// for(int i=1;i<=n;i++)cerr<<siz[i]<<" \n"[i==n];
	build(1,1,n);
	solve(1);
	for(int i=0;i<ans.size();i++)cout<<ans[i]<<" \n"[i+1==ans.size()];
}