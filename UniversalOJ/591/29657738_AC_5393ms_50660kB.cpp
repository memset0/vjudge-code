#include<bits/stdc++.h>
using namespace std;
const int N=2e5+9;
int n,m,pos,dep[N],fa[N],top[N],son[N],siz[N],dfn[N],idfn[N];
vector<int> G[N];
struct Segment{
  int l,r,mid;
  bool mrk[2];
  long long res,sum,tag;
}p[N<<2];
template<class T> inline vector<T> concat(vector<T> a,const vector<T> &b){
  a.insert(a.end(),b.begin(),b.end());
  return a;
}
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
inline vector<pair<int,int>> jump(int u,int v){
  vector<pair<int,int>> res;
  while(top[u]!=top[v]){
    res.emplace_back(dfn[top[u]],dfn[u]);
    u=fa[top[u]];
  }
  if(u!=v)res.emplace_back(dfn[v]+1,dfn[u]);
  return res;
}
inline void pushup(int u,long long x){
  p[u].tag+=x;
  p[u].sum+=x;
  if(~p[u].res)p[u].res+=x;
}
inline void pushdown(int u){
  if(p[u].tag&&p[u].l!=p[u].r){
    pushup(u<<1,p[u].tag);
    pushup(u<<1|1,p[u].tag);
    p[u].tag=0;
  }
}
inline void maintain(int u){
  p[u].sum=p[u<<1].sum+p[u<<1|1].sum;
  p[u].mrk[0]=p[u<<1].mrk[0]&&p[u<<1|1].mrk[0];
  p[u].mrk[1]=p[u<<1].mrk[1]&&p[u<<1|1].mrk[1];
  if(~p[u<<1].res&&~p[u<<1|1].res)p[u].res=min(p[u<<1].res,p[u<<1|1].res);
  else if(~p[u<<1].res)p[u].res=p[u<<1].res;
  else if(~p[u<<1|1].res)p[u].res=p[u<<1|1].res;
  else p[u].res=-1;
}
void build(int u,int l,int r){
  p[u].l=l,p[u].r=r,p[u].mid=(l+r)>>1,p[u].res=-1;
  if(l==r){
    return; 
  }
  build(u<<1,l,p[u].mid);
  build(u<<1|1,p[u].mid+1,r);
}
void modify(int u,int l,int r,int x){
  if(l>r)return;
  // fprintf(stderr,"modify %d %d %d %d\n",u,l,r,x);
  if(p[u].l==l&&p[u].r==r)return pushup(u,x);
  pushdown(u);
  if(r<=p[u].mid)modify(u<<1,l,r,x);
  else if(l>p[u].mid)modify(u<<1|1,l,r,x);
  else modify(u<<1,l,p[u].mid,x),modify(u<<1|1,p[u].mid+1,r,x);
  maintain(u);
}
void active(int u,int l,int r,bool k){
  if(l>r||p[u].mrk[k])return;
  // fprintf(stderr,"active %d %d %d %d\n",u,l,r,(int)k);
  if(p[u].l==p[u].r){
    p[u].mrk[k]=true;
    if(p[u].mrk[0]&&p[u].mrk[1])p[u].res=p[u].sum;
    // fprintf(stderr,">> %d : %d %d : %lld %lld\n",l,(int)p[u].mrk[0],(int)p[u].mrk[1],p[u].sum,p[u].res);
    return;
  }
  pushdown(u);
  if(r<=p[u].mid)active(u<<1,l,r,k);
  else if(l>p[u].mid)active(u<<1|1,l,r,k);
  else active(u<<1,l,p[u].mid,k),active(u<<1|1,p[u].mid+1,r,k);
  maintain(u);
}
int main(){
#ifdef memset0
  freopen("3.in","r",stdin);
  freopen("3.out","w",stdout);
#endif
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>n>>m;
  for(int u,v,i=1;i<n;i++){
    cin>>u>>v;
    G[u].push_back(v),G[v].push_back(u);
  }
  dep[1]=1,dfs(1),dfs(1,1);
  build(1,1,n);
  for(int u,v,w,t,i=0;i<m;i++){
    cin>>u>>v>>w;
    t=lca(u,v);
    // fprintf(stderr,"%d,%d,%d >> t=%d\n",u,v,w,t);
    vector<pair<int,int>> seq=concat(jump(u,t),jump(v,t));
    for(int i=0;i<seq.size();i++)modify(1,seq[i].first,seq[i].second,w);
    vector<pair<int,int>> tmp=jump(t,1);
    for(int i=0;i<tmp.size();i++)active(1,tmp[i].first,tmp[i].second,0);
    seq.insert(seq.end(),tmp.begin(),tmp.end());
    sort(seq.begin(),seq.end());
    active(1,2,seq.front().first-1,1);
    active(1,seq.back().second+1,n,1);
    for(int i=1;i<seq.size();i++)active(1,seq[i-1].second+1,seq[i].first-1,1);
    cout<<p[1].res<<'\n';
  }
}
