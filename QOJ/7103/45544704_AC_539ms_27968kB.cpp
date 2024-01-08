#include<bits/stdc++.h>
#ifndef memset0
  #define endl '\n'
#endif
using namespace std;
const int N=1e5+9;
int T,n,m,q,tot,anc[N],fa[N],dfn[N],dep[N],a[N],b[N],top[N],cur[N],siz[N],son[N],rnkl[N],rnkr[N];
long long len[N],dp[N][2],pre[N],suf[N],dis[N];
bool col[N],foc[N];
vector<int> red,F[N];
vector<pair<int,int>> G[N];
template<class T> inline void updmin(T &x,T y){
  if(y<x)x=y;
}
template<class T> inline void updmax(T &x,T y){
  if(y>x)x=y;
}
inline int cmp_by_dfn(int u,int v){
  return dfn[u]<dfn[v];
}
void dfs(int u,int u_anc){
  if(col[u]){
    u_anc=u;
  }
  dfn[u]=++tot;
  anc[u]=u_anc;
  siz[u]=1;
  son[u]=0;
  // cerr<<"!!! dfs "<<u<<" "<<u_anc<<endl;
  for(auto [v,w]:G[u])
    if(v!=fa[u]){
      // cerr<<u<<" >> "<<v<<endl;
      fa[v]=u;
      dep[v]=dep[u]+1;
      len[v]=len[u]+w;
      dfs(v,u_anc);
      siz[u]+=siz[v];
      if(siz[v]>siz[son[u]]){
        son[u]=v;
      }
    }
}
void dfs2(int u,int tpt){
  top[u]=tpt;
  if(siz[u]==1)return;
  dfs2(son[u],tpt);
  for(auto [v,w]:G[u])
    if(v!=fa[u]&&v!=son[u]){
      dfs2(v,v);
    }
}
inline int lca(int u,int v){
  while(top[u]!=top[v]){
    if(dep[top[u]]>dep[top[v]])swap(u,v);
    v=fa[top[v]];
  }
  return dep[u]<dep[v]?u:v;
}
int main(){
#ifdef memset0
  freopen("B.in","r",stdin);
#endif
  ios::sync_with_stdio(0),cin.tie(0);
  cin>>T;
  while(T--){
    cin>>n>>m>>q;
    fill_n(col+1,n,false);
    for(int i=1;i<=n;i++){
      G[i].clear();
    }
    for(int x,i=1;i<=m;i++){
      cin>>x;
      red.push_back(x);
      col[x]=true;
    }
    for(int u,v,w,i=1;i<n;i++){
      cin>>u>>v>>w;
      G[u].emplace_back(v,w);
      G[v].emplace_back(u,w);
    }
    tot=0;
    dep[1]=1;
    dfs(1,1);
    dfs2(1,1);
    for(int i=1;i<=n;i++){
      dis[i]=len[i]-len[anc[i]];
    }
    for(int k,i=1;i<=q;i++){
      cin>>k;
      for(int i=1;i<=k;i++)cin>>b[i];
      sort(b+1,b+k+1,[&](int u,int v){
        return dis[u]>dis[v];
      });
      int lc=b[1];
      long long max_len=0;
      b[k+1]=0;
      long long ans=dis[b[1]];
      for(int i=1;i<=k;i++){
        lc=lca(lc,b[i]);
        updmax(max_len,len[b[i]]);
        updmin(ans,max(max_len-len[lc],dis[b[i+1]]));
      }
      cout<<ans<<endl;
    }
  }
}