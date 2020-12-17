#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,q;
struct edge{
  int v,nxt;
}c[N];
int front[N],edge_cnt;
inline void addedge(int u,int v){
  c[++edge_cnt]=(edge){v,front[u]};
  front[u]=edge_cnt;
}
int B,bel[N];
int siz[N],dep[N],son[N],Fa[N],top[N],val[N],dfn[N],tree_id;
void dfs(int x){
  bel[x]=B;
  if(!front[x]) val[x]=1;
  for(int i=front[x];i;i=c[i].nxt){
    int v=c[i].v;
    dfs(v);
    val[x]+=val[v];
  }
}
void dfs1(int x,int fa){
  Fa[x]=fa,dep[x]=dep[fa]+1,siz[x]=1;
  for(int i=front[x];i;i=c[i].nxt){
    int v=c[i].v;
    dfs1(v,x);
    siz[x]+=siz[v];
    if(siz[v]>siz[son[x]]) son[x]=v;
  }
}
void dfs2(int x,int topf){
  top[x]=topf,dfn[x]=++tree_id;
  if(!son[x]) return;
  dfs2(son[x],topf);
  for(int i=front[x];i;i=c[i].nxt) if(!top[c[i].v]) dfs2(c[i].v,c[i].v);
}
int lca(int x,int y){
  while(top[x]!=top[y]){
    if(dep[top[x]]>dep[top[y]]) x=Fa[top[x]];
    else y=Fa[top[y]];
  }
  return dep[x]<dep[y]?x:y;
}
bool mark[N];
struct node{
  int x;
  inline bool operator<(const node &o) const{
    return dfn[x]<dfn[o.x];
  }
};
std::set<node> S[N];
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#else
  freopen("gangsters.in","r",stdin);
  freopen("gangsters.out","w",stdout);
#endif
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>n>>q;
  for(int x,i=2;i<=n;++i)cin>>x,addedge(x,i);
  for(int i=front[1];i;i=c[i].nxt)++B,dfs(c[i].v);
  dfs1(1,0),dfs2(1,1);
  int sum1=0,sum2=0,cnt=0;
  while(q-->0){
    char op;int x;cin>>op>>x;
    if(!mark[x]){
      ++cnt;
      if(S[bel[x]].empty()) ++sum1;
      else sum2-=val[lca(S[bel[x]].begin()->x,S[bel[x]].rbegin()->x)];
      S[bel[x]].insert({x});
      sum2+=val[lca(S[bel[x]].begin()->x,S[bel[x]].rbegin()->x)];
    }else{
      --cnt;
      sum2-=val[lca(S[bel[x]].begin()->x,S[bel[x]].rbegin()->x)];
      S[bel[x]].erase({x});
      if(S[bel[x]].empty()) --sum1;
      else sum2+=val[lca(S[bel[x]].begin()->x,S[bel[x]].rbegin()->x)];
    }
    printf("%d %d\n",sum1,sum2-cnt);
    mark[x]^=1;
  }
  return 0;
}//