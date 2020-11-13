#include "template.h"
using namespace mem;

const int N=5e5+5;
int n,l[N],r[N],limitL,limitR,rnk[N];

inline void updmax(int &a,int b){if(b>a)a=b;}
inline void updmin(int &a,int b){if(b<a)a=b;}

struct tarp{
  int x0,y0,x1,y1;
}a[N];
int scanner;
struct tarpCompare{
  inline bool operator()(int i,int j){
    return (i128)(scanner-a[i].x0)*(a[i].y1-a[i].y0)*(a[j].x1-a[j].x0)<(i128)(scanner-a[j].x0)*(a[j].y1-a[j].y0)*(a[i].x1-a[i].x0);
  }
};
set<int,tarpCompare> s;
map<int,vector<pair<bool,int>>> op;

int deg[N];
vector<int> G[N];
inline void addedge(int u,int v){
  G[u].push_back(v);
  deg[v]++;
}

int limit;
namespace seg{
  struct atom{
    int val,pos;
  };
  inline atom mergeMin(const atom &a,const atom &b){
    return a.val<=b.val?a:b;
  }
  inline atom mergeMax(const atom &a,const atom &b){
    return a.val>=b.val?a:b;
  }

  struct segment{
    int l,r,mid;
    atom min,max;
    long long sum;
  }p[N*12];
  
  inline void maintain(int u){
    p[u].sum=p[u<<1].sum+p[u<<1|1].sum;
    p[u].min=mergeMin(p[u<<1].min,p[u<<1|1].min);
    p[u].max=mergeMax(p[u<<1].max,p[u<<1|1].max);
  }
  
  void build(int u,int l,int r){
    if(l==r){
      p[u].min={0,l};
      p[u].max={0,l};
      p[u].sum=0;
      return;
    }
    build(u<<1,l,p[u].mid);
    build(u<<1|1,p[u].mid+1,r);
    maintain(u);
  }
  
  void modify(int u,int k,int x){
    if(p[u].l==p[u].r){
      p[u].sum=p[u].max=p[u].min=x;
      return;
    }
    if(k<=p[u].mid){
      modify(u<<1,k,x);
    }else{
      modify(u<<1|1,k,x);
    }
    maintain(u);
  }
  
  void modifyUp(int u,int k,int x){
    if(p[u].l==p[u].r){
      p[u].sum+=x;
      p[u].max.val+=x;
      p[u].min.val+=x;
      return;
    }
    if(k<=p[u].mid){
      modifyUp(u<<1,k,x);
    }else{
      modifyUp(u<<1|1,k,x);
    }
    maintain(u);
  }

  atom queryMax(int u,int l,int r){
    if(p[u].l==l&&p[u].r==r){
      return p[u].max;
    }
    if(r<=p[u].mid){
      return queryMax(u<<1,l,r);
    }else if(l>p[u].mid){
      return queryMax(u<<1|1,l,r);
    }else{
      return mergeMax(queryMax(u<<1,l,p[u].mid),queryMax(u<<1|1,p[u].mid+1,r));
    }
  }

  atom queryMin(int u,int l,int r){
    if(p[u].l==l&&p[u].r==r){
      return p[u].min;
    }
    if(r<=p[u].mid){
      return queryMin(u<<1,l,r);
    }else if(l>p[u].mid){
      return queryMin(u<<1|1,l,r);
    }else{
      return mergeMin(queryMin(u<<1,l,p[u].mid),queryMin(u<<1|1,p[u].mid+1,r));
    }
  }
  
  long long querySum(int u,int l,int r){
    if(p[u].l==l&&p[u].r==r){
      return p[u].sum;
    }
    if(r<=p[u].mid){
      return querySum(u<<1,l,r);
    }else if(l>p[u].mid){
      return querySum(u<<1|1,l,r);
    }else{
      return querySum(u<<1,l,p[u].mid)+querySum(u<<1|1,p[u].mid+1,r);
    }
  }
}

int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  read(limitL,limitR,n);
  for(int i=1;i<=n;i++){
    read(a[i].x0,a[i].y0,a[i].x1,a[i].y1);
    if(a[i].x0>a[i].x1)swap(a[i].x0,a[i].x1),swap(a[i].y0,a[i].y1);
    op[a[i].x0].push_back({0,i});
    op[a[i].x1].push_back({1,i});
  }
  
  for(const auto &iter:op){
    const auto &tarpVector=iter.second;
    for(const auto &it:tarpVector)
      if(!it.first){
        s.erase(it.second);
      }
    scanner=iter.first;
    for(const auto &it:tarpVector)
      if(it.first){
        auto pos=s.insert(it.second).first;
        if(pos!=s.begin()){
          auto prevItem=*prev(pos);
          addedge(prevItem,it.second);
        }
        if(next(pos)!=s.end()){
          auto nextItem=*next(pos);
          addedge(it.second,nextItem);
        }
      }
  }
  
  queue<int> q;
  for(int i=1;i<=n;i++)
    if(!deg[i]){
      q.push(i);
    }
  int ranker=n;
  while(q.size()){
    int u=q.front();
    rnk[u]=ranker--;
    q.pop();
    for(int v:G[u]){
      --deg[v];
      if(!deg[v]){
        q.push(v);
      }
    }
  }
  
  vector<double> tmp;
  for(int i=1;i<=n;i++){
    tmp.push_back(a[i].x0);
    tmp.push_back(a[i].x1);
    if(a[i].y0<a[i].y1){ // to left side
      tmp.push_back(a[i].x0-0.1);
    }else{ // to right side
      tmp.push_back(a[i].x1+0.1);
    }
  }
  sort(tmp.begin(),tmp.end());
  tmp.erase(unique(tmp.begin(),tmp.end()),tmp.end());
  limit=tmp.size();
  for(int i=1;i<=n;i++){
    l[i]=lower_bound(tmp.begin(),tmp.end(),a[i].x0)-tmp.begin()+1;
    r[i]=lower_bound(tmp.begin(),tmp.end(),a[i].x1)-tmp.begin()+1;
  }
  
  seg::build(1,1,limit);
  vector<int> order;
  for(int i=1;i<=n;i++)order.push_back(i);
  sort(order.begin(),order.end(),[&](int x,int y){
    return rnk[x]>rnk[y];
  });
  for(int i:order){
    log<RED>("tarp[%d] %d %d %d %d\n",i,a[i].x0,a[i].y0,a[i].x1,a[i].y1);
    int ql,qr;
    if(a[i].y0<a[i].y1){ // to left side
      ql=l[i],qr=r[i];
    }else{ // to right side
      ql=l[i]+1,qr=r[i]+1;
    }
    int oldvalue=seg::querySum(1,0,qr+1);
    if(a[i].y0<a[i].y1){
      seg::updateMin()
    }else{

    }
    int newvalue=seg::querySum(1,0,qr+1);
    if(oldvalue!=newvalue){
      seg::modifyUp(1,qr+1,oldvalue-newvalue);
    }
    seg::modifyUp(1,l[i],1);
    seg::modifyUp(1,r[i]+1,1);
  }
};