#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
const int N=4e5+10;
int n,m,q,k,t,pos,x[N],fa[N],anc[N],dep[N],siz[N],son[N],top[N],dfn[N],idfn[N],que[N],dis[N];
std::vector<int> G[N];
void dfs(int u){
	siz[u]=1;
	for(int v:G[u])if(v!=fa[u]){
		fa[v]=u,dep[v]=dep[u]+1,dfs(v),siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
void dfs(int u,int tpt){
	top[u]=tpt,dfn[u]=++pos,idfn[dfn[u]]=u;
	if(siz[u]==1)return; dfs(son[u],tpt);
	for(int v:G[u])if(v!=fa[u]&&v!=son[u])dfs(v,v);
}
int lca(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]>dep[top[v]])std::swap(u,v);
		v=fa[top[v]];
	}
	return dep[u]<dep[v]?u:v;
}
int jump(int u,int k){
	while(dep[u]-dep[top[u]]<k){
		k-=dep[u]-dep[top[u]]+1;
		u=fa[top[u]];
	}
	return idfn[dfn[u]-k];
}
int jump(int u,int t,int v,int k){
	if(k<=dep[u]-dep[t])return jump(u,k);
	return jump(v,dep[v]-dep[t]-(k-(dep[u]-dep[t])));
}
int find(int x){return anc[x]==x?x:anc[x]=find(anc[x]);}
int query(int u,int v){
	int t=lca(u,v);
	if((dep[u]-dep[t])+(dep[v]-dep[t])<=k)return true;
	int x=jump(u,t,v,k>>1);
	int y=jump(v,t,u,k>>1);
	return find(x)==find(y);
}
void init(){
	int l=0,r=-1,u;
	memset(dis,-1,sizeof(dis));
	for(int i=1;i<=t;i++)anc[i]=i;
	for(int i=1;i<=m;i++)que[++r]=x[i],dis[x[i]]=0;
	while(l<=r){
		u=que[l++];
		for(int v:G[u]){
			if(dis[v]==-1){
				dis[v]=dis[u]+1;
				if(dis[v]<(k>>1))que[++r]=v;
			}
			anc[find(v)]=find(u);
		}
	}
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n),read(k),read(m),t=n,k<<=1;
	for(int u,v,i=1;i<n;i++){
		read(u),read(v),++t;
		G[u].push_back(t),G[t].push_back(u);
		G[v].push_back(t),G[t].push_back(v);
	}
	for(int i=1;i<=m;i++)read(x[i]);
	dfs(1);
	dfs(1,1);
	init();
	read(q);
	for(int u,v,i=1;i<=q;i++){
		read(u),read(v);
		puts(query(u,v)?"YES":"NO");
	}
}