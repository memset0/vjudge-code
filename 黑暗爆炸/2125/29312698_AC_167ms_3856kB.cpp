#include<bits/stdc++.h>
using namespace std;
const int N=10005<<1,M=N<<2;
int n,m,Q,tot,Index,dfn[N],low[N],fa[N],dis[N],cdis[N],sz[N],son[N],dep[N],top[N],idfn[N],cnt;
struct Graph{
  int Enum,H[N],nxt[M],to[M],val[M];
  inline void add(int u,int v,int w){
    to[++Enum]=v,nxt[Enum]=H[u],val[Enum]=w,H[u]=Enum;
    to[++Enum]=u,nxt[Enum]=H[v],val[Enum]=w,H[v]=Enum;
  }
}g,t;
void build(int u,int v,int d){
  for(int i=v;i!=u;i=fa[i])cdis[i]=d,d+=dis[i];
  cdis[++tot]=d,t.add(tot,u,0);
  for(int i=v;i!=u;i=fa[i])t.add(tot,i,min(cdis[i],d-cdis[i]));
}
void tarjan(int x){
  dfn[x]=low[x]=++Index;
  for(int v,i=g.H[x];i;i=g.nxt[i])
    if(g.to[i]!=fa[x]){
      if(!dfn[v=g.to[i]])fa[v]=x,dis[v]=g.val[i],tarjan(v),low[x]=min(low[x],low[v]);
      else low[x]=min(low[x],dfn[v]);
      if(low[v]>dfn[x])t.add(x,v,g.val[i]);
    }
  for(int v,i=g.H[x];i;i=g.nxt[i])
    if(fa[v=g.to[i]]!=x&&dfn[v]>dfn[x])build(x,v,g.val[i]);
}
void dfs1(int x){
  int mx=0;
  sz[x]=1;
  for(int v,i=t.H[x];i;i=t.nxt[i])
    if((v=t.to[i])!=fa[x]){
      dep[v]=dep[x]+1,dis[v]=dis[x]+t.val[i],fa[v]=x,dfs1(v),sz[x]+=sz[v];
      if(sz[v]>mx) mx=sz[v],son[x]=v;
    }
}
void dfs2(int x,int tp){
  top[x]=tp,idfn[dfn[x]=++cnt]=x;
  if(son[x]){
    dfs2(son[x],tp);
    for(int i=t.H[x];i;i=t.nxt[i])
      if(t.to[i]!=fa[x]&&t.to[i]!=son[x])dfs2(t.to[i],t.to[i]);
  }
}
int LCA(int u,int v){
  while(top[u]!=top[v]) dep[top[u]]>dep[top[v]]?u=fa[top[u]]:v=fa[top[v]];
  return dep[u]<dep[v]?u:v;
}
int getP(int u,int lca){
  int las=u;
  while(top[u]!=top[lca]) u=fa[las=top[u]];
  return u==lca?las:idfn[dfn[lca]+1];
}
int main(){
#ifdef memset0
  freopen("A_cactus.in","r",stdin);
#endif
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>n>>m>>Q,tot=n;
  for(int u,v,w,i=1;i<=m;i++)cin>>u>>v>>w,g.add(u,v,w);
  tarjan(1),dis[1]=fa[1]=0,dfs1(1),dfs2(1,1);
  for(int k,u,v,w,p1,p2;Q;--Q){
    cin>>u>>v,w=LCA(u,v);
    if(w<=n)printf("%d\n",dis[u]+dis[v]-(dis[w]<<1));
    else{
      p1=getP(u,w),p2=getP(v,w);
      printf("%d\n",dis[u]-dis[p1]+dis[v]-dis[p2]+min(std::abs(cdis[p2]-cdis[p1]),cdis[w]-std::abs(cdis[p2]-cdis[p1])));
    }
  }
}