#include<bits/stdc++.h>
#pragma GCC target("avx")
#pragma GCC target("popcnt,tune=native")
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("inline-functions-called-once")
#define log(...) (void(0))
// #define log(...) fprintf(stderr,__VA_ARGS__)
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
const int N=1e5+10,M=1e4+10,S1=256,S2=4;
int n,m,x,blocks,a[N],c[N],bln[N],anc[N],pre[N],siz[N],ans[N];
std::vector<int> G[N];
struct query{
  int l,r,id;
};
std::vector<query> q;
template<class T,int N> struct static_vector{
  T a[N];
  size_t top;
  inline T& operator[](size_t k){return a[k];}
  inline T operator[](size_t k)const{return a[k];}
  inline T& back(){return a[top-1];}
  inline T back()const{return a[top-1];}
  inline void clear(){top=0;}
  inline void pop_back(){top--;}
  inline void push_back(const T &e){a[top++]=e;}
  inline size_t size(){return top;}
};
int mempool[N<<5],*mempointer=mempool;
int* memselect(int n){
  int *res=mempointer;
  log("\e[32mmem select [%d] => %d\e[0m\n",n,res);
  mempointer+=n;
  return res;
}
struct combinable_vector{
  int lim;
  int *l,*r;
  inline size_t size()const{return r-l;}
  inline void clear(){r=l;}
  inline void assign(){l=r=memselect(lim=16);}
  inline void re_assign(){
    int *tl=l,*tr=r;
    lim<<=2,l=memselect(lim),r=l+(tr-tl);
    memcpy(l,tl,size()<<2);
  }
  inline void push_back(int x){if(size()==lim)re_assign(); *(r++)=x;}
  inline void pop_back(){r--;}
  inline void concat(const combinable_vector &rhs){
    if(size()+rhs.size()>lim)re_assign();
    memcpy(r,rhs.l,rhs.size()<<2),r+=rhs.size();
  }
  inline void concat_reverse(const combinable_vector &rhs){r-=rhs.size();}
};
namespace tree{
  int ans,delta,anc[N];
  bool roll,mrk[N];
  std::bitset<M> mem[N/S2+5];
  static_vector<size_t,(N/S2+5)> rub;
  static_vector<std::tuple<int,int,int>,(N<<1)> history;
  struct unicom_block{
    int id,cnt,bitset,key[S2];
    combinable_vector vec;
    inline unicom_block(){bitset=-1,memset(key,-1,sizeof(key)),vec.assign();}
    inline void clear(){
      if(~bitset)mem[bitset].reset(),rub.push_back(bitset),bitset=-1;
      cnt=0,vec.clear(),memset(key,-1,sizeof(key));
    }
    inline void pushup(int k){
      ans-=a[cnt];
      if(~bitset){
        if(mem[bitset][k]){
          mem[bitset][k]=0,--cnt;
        }else{
          mem[bitset][k]=1,++cnt;
        }
      }else{
        for(int i=0;i<S2;i++)if(key[i]==k){key[i]=-1,--cnt; goto out;}
        for(int i=0;i<S2;i++)if(key[i]==-1){key[i]=k,++cnt; goto out;}
        bitset=rub.back(),rub.pop_back();
        mem[bitset][k]=1,++cnt;
        for(int i=0;i<S2;i++)mem[bitset][key[i]]=1;
      }
      out:ans+=a[cnt];
    }
  }uni[N];
  inline void merge(unicom_block &u,unicom_block &v){
    log("\e[31mmerge %d %d\e[0m\n",(int)u.vec.size(),(int)v.vec.size());
    for(int *it=u.vec.l;it!=u.vec.r;it++)v.pushup(*it);
  }
  int find(int x){return x==anc[x]?x:find(anc[x]);}
  void reset(){
    log("\e[2mreset\e[0m\n");
    ans=roll=0;
    for(int i=1;i<=n;i++){
      anc[i]=i;
      if(mrk[i])uni[i].clear(),mrk[i]=0;
    }
    mempointer=mempool;
    for(int i=1;i<=n;i++)uni[i].vec.assign();
  }
  void add(int x){
    log("\e[2madd %d\e[0m\n",x);
    ans+=a[0]; if(roll)delta+=a[0];
    if(roll)history.push_back({0,x,0});
    mrk[x]=1,uni[x].pushup(c[x]);
    uni[x].vec.push_back(c[x]);
    for(int i=0;i<G[x].size();i++)if(mrk[G[x][i]]){
      int y=G[x][i],u=find(x),v=find(y);
      if(uni[u].vec.size()>uni[v].vec.size())std::swap(u,v);
      log("merge %d[%d] %d[%d]\n",x,u,y,v);
      if(roll)history.push_back({u,v,anc[u]});
      merge(uni[u],uni[v]);
      anc[u]=v;
      uni[v].vec.concat(uni[u].vec);
      ans-=a[uni[u].cnt]; if(roll)delta-=a[uni[u].cnt];
    }
  }
  int query(){return ans;}
  void rollback(){
    log("\e[2mrollback\e[0m\n");
    ans-=delta,delta=0;
    for(int u,v,t,i=(int)history.size()-1;i>=0;i--){
      std::tie(u,v,t)=history[i];
      if(u){
        anc[u]=t;
        merge(uni[u],uni[v]);
        uni[v].vec.concat_reverse(uni[u].vec);
      }else{
        mrk[v]=0,uni[v].pushup(c[v]),uni[v].clear();
      }
    }
    history.clear();
  }
}
struct block{
  int id,l,r;
  std::vector<query> q;
  void init(){
    for(int i=l;i<=r;i++)bln[i]=id;
  }
  void solve(){
    std::sort(q.begin(),q.end(),[](const query &a,const query &b){return a.l>b.l;});
    tree::reset();
    int cur=l,i;
    for(const auto &it:q){
      while(it.l<=cur)tree::add(cur--);
      for(tree::roll^=1,i=l+1;i<=it.r;i++)tree::add(i);
      ans[it.id]=tree::query();
      tree::roll^=1,tree::rollback();
    }
  }
}block[S1<<1];
void build(){
  std::function<int(int)> find=[&](int x){return anc[x]==x?x:anc[x]=find(anc[x]);};
  for(int i=1;i<=n;i++)anc[i]=i,siz[i]=1;
  for(int u=1;u<=n;u++){
    for(int v:G[u])if(v<u){
      int fu=find(u),fv=find(v); if(fu==fv)continue;
      if(siz[fu]>siz[fv])std::swap(fu,fv);
      pre[u]+=siz[fu],anc[fu]=fv,siz[fv]+=siz[fu];
    }
    pre[u]+=G[u].size();
  }
  int S=std::accumulate(pre+1,pre+n+1,0)/S1+1;
  fprintf(stderr,"> block limit = %d\n",S);
  std::vector<std::tuple<int,int,int>> seq={{n+1,n,0}};
  for(int i=n;i>=1;i--){
    std::get<0>(seq.back())--,std::get<2>(seq.back())+=pre[i];
    if(i==1||std::get<2>(seq.back())+pre[i]>S)seq.push_back({i,i-1,0});
  }
  seq.pop_back(),std::reverse(seq.begin(),seq.end()),blocks=seq.size();
  for(int _,i=0;i<blocks;i++){
    std::tie(block[i].l,block[i].r,_)=seq[i];
    block[i].id=i,block[i].init();
  }
}
void solve(){
  for(int i=1;i<=n;i++)tree::uni[i].id=i;
  for(const auto &it:q)if(bln[it.l]==bln[it.r]){
    tree::reset();
    for(int i=it.l;i<=it.r;i++)tree::add(i);
    ans[it.id]=tree::query();
  }else{
    block[bln[it.r]].q.push_back(it);
  }
  for(int i=0;i<blocks;i++)block[i].solve();
}
int main(){
  for(int i=0;i<N/S2+5;i++)tree::rub.push_back(i);
#ifdef memset0
  freopen("1.in","r",stdin);
  freopen("1.out","w",stdout);
#endif
  read(n),read(m),read(x);
  for(int i=1;i<=n;i++)read(c[i]),--c[i];
  for(int u,v,i=1;i<n;i++){
    read(u),read(v);
    G[u].push_back(v),G[v].push_back(u);
  }
  for(int i=0;i<=x;i++)read(a[i]);
  build();
  for(int l,r,i=1;i<=m;i++){
    read(l),read(r);
    q.push_back({l,r,i});
  }
  solve();
  for(int i=1;i<=m;i++)print(ans[i],'\n');
  fprintf(stderr,"clocks: %.4lf\n",clock()/(double)CLOCKS_PER_SEC);
}