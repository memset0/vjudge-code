#ifndef memset0
  #include"swap.h"
#endif
#include<bits/stdc++.h>
const int N=2e5+10;
int n,m,pos,l[N],r[N],lnk[N],anc[N],son[N],dep[N],siz[N],fa[N],top[N],cst[N];
std::vector<int> G[N],nod[N];
std::vector<std::tuple<int,int,int>> e;
int find(int x){return anc[x]==x?x:anc[x]=find(anc[x]);}
inline void add(int u,int v){
  // printf("add %d %d\n",u,v);
  G[u].push_back(v),G[v].push_back(u);
}
void dfs(int u){
  siz[u]=1;
  for(int v:G[u])if(v!=fa[u]){
    fa[v]=u,dep[v]=dep[u]+1;
    // printf("%d -> %d\n",u,v);
    dfs(v);
    siz[u]+=siz[v];
    if(siz[v]>siz[son[u]])son[u]=v;
  }
}
void dfs(int u,int tpt){
  top[u]=tpt;
  if(siz[u]==1)return;
  dfs(son[u],tpt);
  for(int v:G[u])if(v!=fa[u]&&v!=son[u])dfs(v,v);
}
int lca(int u,int v){
  while(top[u]!=top[v]){
    if(dep[top[u]]>dep[top[v]])std::swap(u,v);
    v=fa[top[v]];
  }
  return dep[u]<dep[v]?u:v;
}
void init(int N,int M,std::vector<int> U,std::vector<int> V,std::vector<int> W){
  int u,v,w;
  n=N,m=M;
  for(int i=0;i<M;i++){
    u=U[i],v=V[i],w=W[i],++u,++v;
    e.push_back({u,v,w});
  }
  std::sort(e.begin(),e.end(),[](const std::tuple<int,int,int> &a,const std::tuple<int,int,int> &b){
    return std::get<2>(a)<std::get<2>(b);
  });
  for(int i=1;i<=n;i++){
    anc[i]=l[i]=r[i]=i,lnk[i]=1;
    nod[i].push_back(i);
  }
  int cnt=n;
  for(const auto &it:e){
    std::tie(u,v,w)=it;
    int fu=find(u),fv=find(v);
    if(fu!=fv){
      // printf("> %d %d %d\n",u,v,w);
      if(lnk[fu]&&lnk[fv]&&((l[fu]==u&&l[fv]==v)||(l[fu]==u&&r[fv]==v)||(r[fu]==u&&l[fv]==v)||(r[fu]==u&&r[fv]==v))){
        int nl,nr;
        if(l[fu]==u&&l[fv]==v)nl=r[fu],nr=r[fv];
        if(l[fu]==u&&r[fv]==v)nl=r[fu],nr=l[fv];
        if(r[fu]==u&&l[fv]==v)nl=l[fu],nr=r[fv];
        if(r[fu]==u&&r[fv]==v)nl=l[fu],nr=l[fv];
        l[fv]=nl,r[fv]=nr;
        if(nod[fu].size()>nod[fv].size()){
          std::swap(nod[fu],nod[fv]);
        }
        nod[fv].insert(nod[fv].end(),nod[fu].begin(),nod[fu].end());
        nod[fu].clear();
      }else{
        lnk[fu]=lnk[fv]=0,cst[++cnt]=w;
        // printf("new node %d %d\n",cnt,w);
        for(int x:nod[fu])add(x,cnt);
        for(int x:nod[fv])add(x,cnt);
        nod[fu].clear(),nod[fv].clear();
        nod[fv].push_back(cnt);
      }
      anc[fu]=fv;
    }else{
      if(lnk[fu]){
        lnk[fu]=0,cst[++cnt]=w;
        for(int x:nod[fu])add(x,cnt);
        nod[fu].clear(),nod[fu].push_back(cnt);
      }
    }
  }
  cst[++cnt]=-1;
  // printf("new node %d %d\n",cnt,-1);
  for(int i=1;i<=n;i++)if(find(i)==i){
    for(int x:nod[i])add(x,cnt);
  }
  dfs(cnt);
  dfs(cnt,cnt);
}
int getMinimumFuelCapacity(int u,int v){
  ++u,++v;
  // printf("lca %d %d => %d %d\n",u,v,lca(u,v),cst[lca(u,v)]);
  return cst[lca(u,v)];
}
#ifdef memset0
int main() {
  freopen("../examples/01.in","r",stdin);
  int N, M;
  assert(2 == scanf("%d %d", &N, &M));
  
  std::vector<int> U(M), V(M), W(M);
  for (int i = 0; i < M; ++i) {
    assert(3 == scanf("%d %d %d", &U[i], &V[i], &W[i]));
  }

  int Q;
  assert(1 == scanf("%d", &Q));

  std::vector<int> X(Q), Y(Q);
  for (int i = 0; i < Q; ++i) {
    assert(2 == scanf("%d %d", &X[i], &Y[i]));
  }

  init(N, M, U, V, W);
  
  std::vector<int> minimum_fuel_capacities(Q);
  for (int i = 0; i < Q; ++i) {
    minimum_fuel_capacities[i] = getMinimumFuelCapacity(X[i], Y[i]);
  }

  for (int i = 0; i < Q; ++i) {
    printf("%d\n", minimum_fuel_capacities[i]);
  }
  
  return 0;
}
#endif