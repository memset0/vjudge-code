#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,m,pos,fa[N],siz[N],son[N],dep[N],dfn[N],top[N],idfn[N];
vector<int> G[N];
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
inline int lca(int u,int v){
  while(top[u]!=top[v]){
    if(dep[top[u]]>dep[top[v]])swap(u,v);
    v=fa[top[v]];
  }
  return dep[u]<dep[v]?u:v;
}
struct segment{
  int l,r,mid,col,tag;
}p[N<<2];
inline int merge(int x,int y){return x==y?x:-1;}
inline void pushup(int u,int x){p[u].tag=p[u].col=x;}
inline void pushdown(int u){
  if(p[u].tag){
    pushup(u<<1,p[u].tag);
    pushup(u<<1|1,p[u].tag);
    p[u].tag=0;
  }
}
void build(int u,int l,int r){
  p[u].l=l,p[u].r=r,p[u].mid=(l+r)>>1;
  if(l==r)return;
  build(u<<1,l,p[u].mid);
  build(u<<1|1,p[u].mid+1,r);
}
void modify(int u,int l,int r,int x){
  if(p[u].l==l&&p[u].r==r)return pushup(u,x);
  pushdown(u);
  if(r<=p[u].mid)modify(u<<1,l,r,x);
  else if(l>p[u].mid)modify(u<<1|1,l,r,x);
  else modify(u<<1,l,p[u].mid,x),modify(u<<1|1,p[u].mid+1,r,x);
  p[u].col=merge(p[u<<1].col,p[u<<1|1].col);
}
int query(int u,int l,int r){
  if(p[u].l==l&&p[u].r==r)return p[u].col;
  pushdown(u);
  if(r<=p[u].mid)return query(u<<1,l,r);
  if(l>p[u].mid)return query(u<<1|1,l,r);
  return merge(query(u<<1,l,p[u].mid),query(u<<1|1,p[u].mid+1,r));
}
struct query{
  int u,v,dis;
  inline bool operator<(const query &rhs)const{
    return dis>rhs.dis;
  }
}e[N];
inline int query(int u,int v){
  int res=query(1,dfn[v],dfn[v]);
  while(top[u]!=top[v]){
    if(dep[top[u]]>dep[top[v]])swap(u,v);
    res=merge(res,query(1,dfn[top[v]],dfn[v]));
    v=fa[top[v]];
  }
  if(dep[u]>dep[v])swap(u,v);
  return merge(res,query(1,dfn[u],dfn[v]));
}
inline void modify(int u,int v,int x){
  while(top[u]!=top[v]){
    if(dep[top[u]]>dep[top[v]])swap(u,v);
    modify(1,dfn[top[v]],dfn[v],x);
    v=fa[top[v]];
  }
  if(dep[u]>dep[v])swap(u,v);
  modify(1,dfn[u],dfn[v],x);
}
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>n>>m;
  for(int u,v,i=1;i<n;i++){
    cin>>u>>v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  dep[1]=1,dfs(1),dfs(1,1);
  for(int i=1;i<=m;i++){
    cin>>e[i].u>>e[i].v;
    e[i].dis=dep[e[i].u]+dep[e[i].v]-(dep[lca(e[i].u,e[i].v)]<<1);
  }
  sort(e+1,e+m+1);
  build(1,1,n);
  for(int i=1;i<=m;i++){
    // printf("> %d %d %d\n",e[i].u,e[i].v,query(e[i].u,e[i].v));
    if(~query(e[i].u,e[i].v)){
      modify(e[i].u,e[i].v,i);
    }else{
      puts("No");
      return 0;
    }
  }
  puts("Yes");
}
//adfsafdasdf