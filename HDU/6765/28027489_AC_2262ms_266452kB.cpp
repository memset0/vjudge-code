#include<bits/stdc++.h>
const int S=1<<21; char ibuf[S],*iS,*iT,obuf[S],*oS=obuf,*oT=oS+S-1;
#define flush() (fwrite(obuf,1,oS-obuf,stdout),oS=obuf,void())
#define getchar() (iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,S,stdin),(iS==iT?EOF:*iS++)):*iS++)
#define putchar(x) (*oS++=(x),oS==oT?flush():void())
struct Flusher_{~Flusher_(){flush();}}flusher_;
template<class T> inline void read(T &x){
  x=0; register char c=getchar(); register bool f=0;
  while(!isdigit(c))f^=c=='-',c=getchar();
  while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
const int N=5e5+10,K=29;
int T,n,m,pos,fa[N],son[N],siz[N],dep[N],top[N],col[N],dfn[N],idfn[N];
std::vector<int> G[N];
unsigned int seed=142857;
inline unsigned rng(){seed^=seed>>3,seed^=seed<<17,seed^=seed>>5;return seed;}
struct atom{
  unsigned int v[K];
  inline void gen(){
    for(int i=0;i<K;i++)v[i]=rng();
  }
  inline void setmax(){
    for(int i=0;i<K;i++)v[i]=UINT_MAX;
  }
  inline atom operator^(const atom &rhs)const{
    atom res;
    for(int i=0;i<K;i++)res.v[i]=std::min(v[i],rhs.v[i]);
    return res;
  }
  inline void operator^=(const atom &rhs){
    for(int i=0;i<K;i++)if(rhs.v[i]<v[i])v[i]=rhs.v[i];
  }
}set[N];
struct node{
  int l,r,mid;
  atom x;
}p[N<<2];
void dfs(int u){
  siz[u]=1,son[u]=0;
  for(int v:G[u])if(v!=fa[u]){
    fa[v]=u,dep[v]=dep[u]+1,dfs(v),siz[u]+=siz[v];
    if(siz[v]>siz[son[u]])son[u]=v;
  }
}
void dfs(int u,int tpt){
  top[u]=tpt,dfn[u]=++pos,idfn[dfn[u]]=u;
  if(siz[u]==1)return;
  dfs(son[u],tpt);
  for(int v:G[u])if(v!=son[u]&&v!=fa[u])dfs(v,v);
}
void build(int u,int l,int r){
  p[u].l=l,p[u].r=r,p[u].mid=(l+r)>>1;
  if(l==r){
    p[u].x=set[col[idfn[l]]];
    return;
  }
  build(u<<1,l,p[u].mid);
  build(u<<1|1,p[u].mid+1,r);
  p[u].x=p[u<<1].x^p[u<<1|1].x;
  // printf("build %d %d %d > ",u,l,r);
  // for(int i=0;i<K;i++)printf("%u%c",p[u].x.v[i]," \n"[i+1==K]);
}
void modify(int u,int k,int c){
  if(p[u].l==p[u].r){
    p[u].x=set[c];
    return;
  }
  modify(k<=p[u].mid?u<<1:u<<1|1,k,c);
  p[u].x=p[u<<1].x^p[u<<1|1].x;
}
atom ans;
void query(int u,int l,int r){
  if(p[u].l==l&&p[u].r==r){
    ans^=p[u].x;
    return;
  }
  if(r<=p[u].mid)return query(u<<1,l,r);
  if(l>p[u].mid)return query(u<<1|1,l,r);
  return query(u<<1,l,p[u].mid),query(u<<1|1,p[u].mid+1,r);
}
atom query(int u,int v){
  ans.setmax();
  while(top[u]!=top[v]){
    if(dep[top[u]]>dep[top[v]])std::swap(u,v);
    query(1,dfn[top[v]],dfn[v]);
    v=fa[top[v]];
  }
  if(dep[u]>dep[v])std::swap(u,v);
  query(1,dfn[u],dfn[v]);
  return ans;
}
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
  // freopen("1.out","w",stdout);
#endif
  read(T);
  while(T--){
    read(n),read(m);
    for(int i=1;i<=n;i++)read(col[i]);
    for(int i=1;i<=n;i++)set[i].gen();
    for(int i=1;i<=n;i++)G[i].clear();
    for(int u,v,i=1;i<n;i++){
      read(u),read(v);
      G[u].push_back(v);
      G[v].push_back(u);
    }
    pos=0,dep[1]=1;
    dfs(1);
    dfs(1,1);
    build(1,1,n);
    int tot=0;
    for(int a,b,c,d,x,op,i=1;i<=m;i++){
      read(op);
      if(op==1){
        read(x),read(c),x^=tot,c^=tot;
        modify(1,dfn[x],c);
      }else{
        read(a),read(b),read(c),read(d),a^=tot,b^=tot,c^=tot,d^=tot;
        atom f=query(a,b),g=query(c,d);
        // for(int i=0;i<K;i++)printf("%u%c",f.v[i]," \n"[i+1==K]);
        // for(int i=0;i<K;i++)printf("%u%c",g.v[i]," \n"[i+1==K]);
        // int cnt=0;
        // for(int i=0;i<K;i++)cnt+=f.v[i]<g.v[i];
        long long sum=0;
        for(int i=0;i<K;i++){
          sum+=f.v[i];
          sum-=g.v[i];
        }
        // if(cnt>(K>>1)){
        if(sum<0){
          putchar('Y'),putchar('e'),putchar('s'),putchar('\n');
          ++tot;
        }else{
          putchar('N'),putchar('o'),putchar('\n');
        }
      }
    }
  }
}