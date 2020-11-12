#include<bits/stdc++.h>
#define log(...) (void(0))
// #define log(...) fprintf(stderr,__VA_ARGS__)
#define debug log("\33[2mPassing [%s] in LINE %d\33[0m\n",__FUNCTION__,__LINE__);

const int S=1<<21; char ibuf[S],*iS,*iT,obuf[S],*oS=obuf,*oT=oS+S-1;
#define flush() (fwrite(obuf,1,oS-obuf,stdout),oS=obuf,void())
#define getchar() (iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,S,stdin),(iS==iT?EOF:*iS++)):*iS++)
#define putchar(x) (*oS++=(x),oS==oT?flush():void())
struct Flusher_{~Flusher_(){flush();}}flusher_;

template<class T> inline void read(T &x){ // warn: 忽略负数
   x=0; char c=getchar();
   while(!isdigit(c))c=getchar();
   while(isdigit(c))x=x*10+c-'0',c=getchar();
}
template<class T> inline void print(T x){ // warn: 忽略负数和0
   static int t,ch[35];
   while(x)ch[++t]=x%10+'0',x/=10;
   while(t)putchar(ch[t--]);
}

const int N=1e6+10;
int n,m,q,a[N],ans[N];

struct pair{
   int first,second;
   inline pair(){}
   inline pair(int x,int y):first(x),second(y){}
};

template<const int N,const int M,class T>
struct vectorLib{
   int hed[N],cnt;
   struct node{
      T ele;
      int nxt;
   }mem[M];
   inline void push_back(int i,T x){
      mem[++cnt]=(node){x,hed[i]};
      hed[i]=cnt;
   }
   // inline const node* operator[](int k)const{
   //    return &mem[k];
   // }
};
vectorLib<N,N,int> e;
vectorLib<N,(N<<1),pair> c;

struct SegmentTreeBeats{
#define lc u<<1
#define rc u<<1|1
   int loc[N];
   struct node{
      int l,r,mid,max,smx,tag;
   }p[N<<2];
   inline void pushdown(int u){
      if(p[u].tag){
         if(p[u].max<p[lc].max)p[lc].max=p[u].max,p[lc].tag+=p[u].tag;
         if(p[u].max<p[rc].max)p[rc].max=p[u].max,p[rc].tag+=p[u].tag;
         p[u].tag=0;
      }
   }
   inline void maintain(int u){
      // if(p[lc].max>p[rc].max){
      //    p[u].max=p[lc].max,p[u].smx=std::max(p[lc].smx,p[rc].max);
      // }else{
      //    p[u].max=p[rc].max,p[u].smx=std::max(p[rc].smx,p[lc].max);
      // }
      if(p[lc].max>p[rc].max){
         p[u].max=p[lc].max;
         p[u].smx=std::max(p[lc].smx,p[rc].max);
      }else if(p[lc].max<p[rc].max){
         p[u].max=p[rc].max;
         p[u].smx=std::max(p[rc].smx,p[lc].max);
      }else{
         p[u].max=p[lc].max;
         p[u].smx=std::max(p[lc].smx,p[rc].smx);
      }
   }
   void build(int u,int l,int r){
      p[u].l=l,p[u].r=r,p[u].mid=(l+r)>>1;
      p[u].max=2e9,p[u].smx=-1;
      if(l==r){
         loc[l]=u;
         return;
      }
      build(lc,l,p[u].mid);
      build(rc,p[u].mid+1,r);
   }
   void modify(int u,int l,int r,int x){
      if(u==1)log("modify %d %d %d\n",l,r,x);
      if(p[u].l==l&&p[u].r==r&&x>=p[u].smx){
         if(x<p[u].max)p[u].max=x,p[u].tag++;
         return;
      }
      pushdown(u);
      if(r<=p[u].mid)modify(lc,l,r,x);
      else if(l>p[u].mid)modify(rc,l,r,x);
      else modify(lc,l,p[u].mid,x),modify(rc,p[u].mid+1,r,x);
      maintain(u);
   }
   inline void modify(int l,int r,int x){
      if(l<=r)modify(1,l,r,x);
   }
   // int query(int u,int k){
   //    if(u==1)log("query %d\n",k);
   //    if(p[u].l==p[u].r)return p[u].tag;
   //    pushdown(u);
   //    return query(k<=p[u].mid?lc:rc,k);
   // }
   int query(int k){
      int u=loc[k],val=p[u].max,res=p[u].tag;
      for(u>>=1;u;u>>=1)if(p[u].max<val){
         val=p[u].max,res+=p[u].tag;
      }
      return res;
   }
   void dfs(int u){
      if(p[u].l!=p[u].r)pushdown(u);
      log("dfs %d %d %d : %d %d %d\n",u,p[u].l,p[u].r,p[u].max,p[u].smx,p[u].tag);
      if(p[u].l==p[u].r){
         // log("%d%c",p[u].max," \n"[p[u].l==p[1].r]);
         return;
      }
      dfs(lc),dfs(rc);
   }
#undef lc
#undef rc
}seg;

int main(){
#ifdef local
   freopen("1.in","r",stdin);
   // freopen("1.out","w",stdout);
#endif
   read(n),read(q);
   for(int i=1;i<=n;i++){
      read(a[i]);
      c.push_back(i,pair(a[i],1));
   }
   for(int i=1,o,x,y;i<=q;i++)if(read(o),o==1){
      read(x),read(y);
      c.push_back(x,pair(y,m+1));
   }else{
      read(x);
      e.push_back(x,++m);
   }
   seg.build(1,1,m);
   for(int i=n;i>=1;i--){
      if(c.hed[i]){
         const pair hed=c.mem[c.hed[i]].ele;
         seg.modify(hed.second,m,hed.first);
         int lst=hed.second;
         for(int t=c.mem[c.hed[i]].nxt;t;t=c.mem[t].nxt){
            seg.modify(c.mem[t].ele.second,lst-1,c.mem[t].ele.first);
            lst=c.mem[t].ele.second;
         }
      }
      for(int t=e.hed[i];t;t=e.mem[t].nxt){
         ans[e.mem[t].ele]=seg.query(e.mem[t].ele);
      }
   }
   for(int i=1;i<=m;i++)print(ans[i]),putchar('\n');
   fprintf(stderr,"clocks: %.4lf\n",clock()/(double)CLOCKS_PER_SEC);
}