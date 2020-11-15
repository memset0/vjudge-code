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
template<class T> inline void print(T x){
  if(x<0)putchar('-'),x=-x;
  if(x>9)print(x/10); putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}
const int N=5e5+10;
int n,m,a[N],b[N],fa[N],dep[N];
std::vector<int> G[N];
struct set:std::set<int>{
  using std::set<int>::set;
  inline int first(){return *begin();}
  inline int first(int x){return !empty()?first():x;}
  inline int second(){return *std::next(begin());}
  inline int second(int x){return size()>=2?second():x;}
}son[N];
struct tinySet{
  int a,b;
  inline tinySet(){a=b=-1;}
  inline int value(){return std::max(a,b);}
  inline void insert(int x){if(a==-1){a=x; return;} if(b==-1){b=x; return;} assert(0);}
  inline void erase (int x){if(a==x){a=-1; return;} if(b==x){b=-1; return;} assert(0);}
}max[N];
void dfs(int u){for(int v:G[u])if(v!=fa[u])fa[v]=u,dep[v]=dep[u]+1,dfs(v);}
namespace VAL{
  struct node{
    int l,r,mid,tag;
    struct value{
      int v,c;
      friend inline value operator^(const value &a,const value &b){
        return a.v==b.v?value{a.v,a.c+b.c}:(a.v<b.v?a:b);
      }
    }x;
  }p[N<<2];
  inline void pushup(int u,int x){p[u].x.v+=x,p[u].tag+=x;}
  inline void pushdown(int u){if(p[u].tag)pushup(u<<1,p[u].tag),pushup(u<<1|1,p[u].tag),p[u].tag=0;}
  void build(int u,int l,int r){
    p[u].l=l,p[u].r=r,p[u].mid=(l+r)>>1,p[u].x={0,p[u].r-p[u].l+1};
    if(l==r)return;
    build(u<<1,l,p[u].mid),build(u<<1|1,p[u].mid+1,r);
  }
  void modify(int u,int l,int r,int x){
    if(p[u].l==l&&p[u].r==r)return pushup(u,x);
    pushdown(u);
    if(r<=p[u].mid)modify(u<<1,l,r,x);
    else if(l>p[u].mid)modify(u<<1|1,l,r,x);
    else modify(u<<1,l,p[u].mid,x),modify(u<<1|1,p[u].mid+1,r,x);
    p[u].x=p[u<<1].x^p[u<<1|1].x;
  }
  node::value query(int u,int l,int r){
    if(p[u].l==l&&p[u].r==r)return p[u].x;
    pushdown(u);
    if(r<=p[u].mid)return query(u<<1,l,r);
    if(l>p[u].mid)return query(u<<1|1,l,r);
    return query(u<<1,l,p[u].mid)^query(u<<1|1,p[u].mid+1,r);
  }
  int queryAns(int x,int l,int r){auto res=query(1,l,r); return res.v==x?res.c:0;}
}
namespace LCA{
  struct node{
    int l,r,mid;
    struct value{
      int min,max;
      inline bool check(){return max<=min;}
      friend inline value operator^(const value &a,const value &b){
        return {std::min(a.min,b.min),std::max(a.max,b.max)};
      }
    }x;
  }p[N<<2];
  void build(int u,int l,int r){
    p[u].l=l,p[u].r=r,p[u].mid=(l+r)>>1;
    if(p[u].l==p[u].r){p[u].x={dep[b[l]],-1}; return;}
    build(u<<1,l,p[u].mid),build(u<<1|1,p[u].mid+1,r);
    p[u].x=p[u<<1].x^p[u<<1|1].x;
  }
  void modifyMin(int u,int k,int x){
    if(p[u].l==p[u].r){p[u].x.min=x; return;}
    modifyMin(k<=p[u].mid?u<<1:u<<1|1,k,x);
    p[u].x.min=std::min(p[u<<1].x.min,p[u<<1|1].x.min);
  }
  void modifyMax(int u,int k,int x){
    if(p[u].l==p[u].r){p[u].x.max=x; return;}
    modifyMax(k<=p[u].mid?u<<1:u<<1|1,k,x);
    p[u].x.max=std::max(p[u<<1].x.max,p[u<<1|1].x.max);
  }
  node::value query(int u,int l,int r){
    if(p[u].l==l&&p[u].r==r)return p[u].x;
    if(r<=p[u].mid)return query(u<<1,l,r);
    if(l>p[u].mid)return query(u<<1|1,l,r);
    return query(u<<1,l,p[u].mid)^query(u<<1|1,p[u].mid+1,r);
  }
}
inline void play(int u,int x){
  if(!u)return;
  int ka=son[u].first(n+1)-1;
  if(a[u]<=ka)VAL::modify(1,a[u],ka,x);
  int kb=son[u].second(-1);
  if(kb>=1){
    int k=std::max(a[u],kb);
    (x==1)?max[k].insert(dep[u]):max[k].erase(dep[u]);
    LCA::modifyMax(1,k,max[k].value());
  }
}
inline int qry(){
  int ans=0,k1=-1,k2=-1,l,r,mid;
  l=1,r=n;
  while(l<=r){
    mid=(l+r)>>1;
    if(LCA::query(1,1,mid).max==-1)k1=mid,l=mid+1; else r=mid-1;
  }
  l=k1+1,r=n;
  while(l<=r){
    mid=(l+r)>>1;
    if(LCA::query(1,1,mid).check())k2=mid,l=mid+1; else r=mid-1;
  }
  if(1<=k1)ans+=VAL::queryAns(1,1,k1);
  if(k1<k2)ans+=VAL::queryAns(2,k1+1,k2);
  return ans;
}
inline void ins(int u){son[fa[u]].insert(a[u]),LCA::modifyMin(1,a[u],dep[u]);}
inline void del(int u){son[fa[u]].erase(a[u]),LCA::modifyMin(1,a[u],1919810);}
int main(){
#ifdef memset0
  freopen("2.in","r",stdin);
  freopen("1.out","w",stdout);
#endif
  read(n);
  for(int i=1;i<=n;i++)read(a[i]),b[++a[i]]=i;
  for(int u,v,i=1;i<n;i++){
    read(u),read(v);
    G[u].push_back(v),G[v].push_back(u);
  }
  dep[1]=1,dfs(1);
  VAL::build(1,1,n);
  LCA::build(1,1,n);
  for(int i=1;i<=n;i++)son[fa[i]].insert(a[i]);
  for(int i=1;i<=n;i++)play(i,1);
  read(m);
  fprintf(stderr,"clocks: %.4lf\n",clock()/(double)CLOCKS_PER_SEC);
  for(int x,y,lst=qry(),i=1;i<=m;i++){
    read(x),read(y);
    if(x==y){print(lst,'\n'); continue;}
    std::set<int> set={x,y,fa[x],fa[y]};
    for(auto e=set.begin();e!=set.end();e++)play(*e,-1);
    del(x),del(y);
    std::swap(a[x],a[y]);
    std::swap(b[a[x]],b[a[y]]);
    ins(x),ins(y);
    for(auto e=set.rbegin();e!=set.rend();e++)play(*e,1);
    print(lst=qry(),'\n');
  }
  fprintf(stderr,"clocks: %.4lf\n",clock()/(double)CLOCKS_PER_SEC);
}