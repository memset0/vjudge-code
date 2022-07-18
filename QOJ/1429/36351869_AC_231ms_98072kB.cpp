#include<bits/stdc++.h>
// #define log(...) (void(0))
#define log(...) fprintf(stderr,__VA_ARGS__)
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
const int N=6e5+10,M=21;
int T,n,t,tn,ta[N],maxl[N],maxr[N],mrk[N],nxt[N][M];
std::vector<int> pos,ans;
struct node{
  int l,r;
}a[N];
inline bool inside(int l,int r){return l<=r&&maxl[r]>=l;}
inline bool outside(int l,int r){return l>r||maxr[l]>=r;}
namespace seg{
  struct node{
    int l,r,mid,s;
  }p[N<<2];
  void build(int u,int l,int r){
    p[u].l=l,p[u].r=r,p[u].mid=(l+r)>>1,p[u].s=0;
    if(l==r)return;
    build(u<<1,l,p[u].mid);
    build(u<<1|1,p[u].mid+1,r);
  }
  void modify(int u,int k,int x){
    if(p[u].l==p[u].r){p[u].s+=x; return;}
    modify(k<=p[u].mid?u<<1:u<<1|1,k,x);
    p[u].s=p[u<<1].s+p[u<<1|1].s;
  }
  int query(int u,int l,int r){
    if(p[u].l==l&&p[u].r==r)return p[u].s;
    if(r<=p[u].mid)return query(u<<1,l,r);
    if(l>p[u].mid)return query(u<<1|1,l,r);
    return query(u<<1,l,p[u].mid)+query(u<<1|1,p[u].mid+1,r);
  }
}
int main(){
#ifdef local
  freopen("1.in","r",stdin);
#endif
  for(read(T);T--;){
    t=tn=0,ans.clear(),pos.clear();
    read(n);
    ta[++tn]=1e9+10,ta[++tn]=-1e9-10;
    for(int i=1;i<=n;i++){
      read(a[i].l),ta[++tn]=a[i].l;
      read(a[i].r),ta[++tn]=a[i].r;
      ta[++tn]=a[i].l-1,ta[++tn]=a[i].l+1;
      ta[++tn]=a[i].r-1,ta[++tn]=a[i].r+1;
    }
    std::sort(ta+1,ta+tn+1);
    tn=std::unique(ta+1,ta+tn+1)-ta-1;
    for(int i=1;i<=n;i++){
      a[i].l=std::lower_bound(ta+1,ta+tn+1,a[i].l)-ta;
      a[i].r=std::lower_bound(ta+1,ta+tn+1,a[i].r)-ta;
    }
    memset(maxl+1,0,tn<<2);
    memset(maxr+1,0,tn<<2);
    for(int i=1;i<=n;i++){
      maxl[a[i].r]=std::max(maxl[a[i].r],a[i].l);
      maxr[a[i].l]=std::max(maxr[a[i].l],a[i].r);
    }
    for(int i=1;i<=tn;i++){
      maxl[i]=std::max(maxl[i-1],maxl[i]);
      maxr[i]=std::max(maxr[i-1],maxr[i]);
    }
    std::sort(a+1,a+n+1,[](const node &a,const node &b){
      return a.r==b.r?a.l<b.l:a.r<b.r;
    });
    seg::build(1,1,tn);
    for(int i=1;i<=n;i++)
      if(!seg::query(1,a[i].l,a[i].r)){
        seg::modify(1,a[i].r,1);
        ans.push_back(a[i].r);
      }
    for(int i=1;i<=n;i++){
      t=std::max(t,seg::query(1,a[i].l,a[i].r));
    }
    if(t>1){
      // log(">> %d\n",n);
      // for(int i=1;i<=n;i++)log("(%d %d)%c",a[i].l,a[i].r," \n"[i==n]);
      memset(mrk+1,0,tn);
      pos.push_back(tn),mrk[tn]=1;
      for(int i=0;i<M;i++)nxt[tn][i]=tn;
      for(int i=tn-1,j,l,r,mid,s,k;i>=1;i--){
        l=0,r=pos.size()-1,nxt[i][0]=-1;
        while(l<=r){
          mid=(l+r)>>1;
          if(!inside(i+1,pos[mid]-1)){
            nxt[i][0]=pos[mid];
            r=mid-1;
          }else{
            l=mid+1;
          }
        }
        if(!~nxt[i][0])continue;
        for(j=nxt[i][0],k=M-1,s=t-2;k>=0;k--){
          if((s>>k)&1)j=nxt[j][k];
        }
        // log("i=%d nxt_i=%d nxt^t-1_i=%d\n",i,nxt[i][0],j);
        if(outside(i,j))continue;
        pos.push_back(i),mrk[i]=1;
        for(int j=1;j<M;j++){
          nxt[i][j]=nxt[nxt[i][j-1]][j-1];
        }
      }
      // for(int i=1;i<=tn;i++)log("%d%c",mrk[i]," \n"[i==tn]);
      int minl=tn;
      for(int i=1;i<=n;i++)minl=std::min(minl,a[i].l);
      // log("minl=%d\n",minl);
      if(mrk[minl-1]){
        --t,ans.clear();
        int u=minl-1;
        while(u!=tn)ans.push_back(u),u=nxt[u][0];
        if(ans.front()==1)ans.erase(ans.begin());
      }
    }
    print(t,' ');
    print(ans.size(),' ');
    for(int i=0;i<ans.size();i++){
      print(ta[ans[i]]," \n"[i+1==ans.size()]);
    }
    // printf("%d\n",t);
  }
}