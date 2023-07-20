#include<bits/stdc++.h>
using namespace std;
const int N=2e5+9;
int n,k,w;
long long dp[N];
struct node{
  int l,r,w,id;
  friend inline bool operator<(const node &a,const node &b){
    return a.r==b.r?a.l>b.l:a.r<b.r;
  }
}a[N];
struct segment{
  int l,r,mid,maxk;
  long long max,tag;
}p[N<<2];
inline void pushdown(int u){
  p[u<<1].tag+=p[u].tag;
  p[u<<1].max+=p[u].tag;
  p[u<<1|1].tag+=p[u].tag;
  p[u<<1|1].max+=p[u].tag;
  p[u].tag=0;
}
inline void maintain(int u){
  if(p[u<<1].max>=p[u<<1|1].max){
    p[u].max=p[u<<1].max;
    p[u].maxk=p[u<<1].maxk;
  }else{
    p[u].max=p[u<<1|1].max;
    p[u].maxk=p[u<<1|1].maxk;
  }
}
void build(int u,int l,int r){
  p[u].l=l,p[u].r=r,p[u].mid=(l+r)>>1;
  if(l==r){
    p[u].max=l*w;
    p[u].maxk=l;
    return;
  }
  build(u<<1,l,p[u].mid);
  build(u<<1|1,p[u].mid+1,r);
  p[u].max=p[u<<1|1].max;
  p[u].maxk=p[u<<1|1].maxk;
}
void update(int u,int k){
  if(p[u].l==p[u].r){
    p[u].max+=dp[k];
    return;
  }
  if(k<=p[u].mid){
    update(u<<1,k);
  }else{
    update(u<<1|1,k);
  }
  maintain(u);
}
void modify(int u,int l,int r,int x){
//  cerr<<"modify "<<u<<" "<<l<<" "<<r<<" "<<x<<endl;
  if(p[u].l==l&&p[u].r==r){
    p[u].tag+=x;
    p[u].max+=x;
    return;
  }
  pushdown(u);
  if(r<=p[u].mid){
    modify(u<<1,l,r,x);
  }else if(l>p[u].mid){
    modify(u<<1|1,l,r,x);
  }else{
    modify(u<<1,l,p[u].mid,x);
    modify(u<<1|1,p[u].mid+1,r,x);
  }
  maintain(u);
}
pair<long long,int> query(int u,int l,int r){
  if(p[u].l==l&&p[u].r==r){
//    cerr<<"query "<<u<<" "<<l<<" "<<r<<" "<<p[u].max<<" "<<p[u].maxk<<endl;
    return make_pair(p[u].max,p[u].maxk);
  }
  pushdown(u);
  if(r<=p[u].mid){
    return query(u<<1,l,r);
  }else if(l>p[u].mid){
    return query(u<<1|1,l,r);
  }else{
    return max(
      query(u<<1,l,p[u].mid),
      query(u<<1|1,p[u].mid+1,r)
    );
  }
}
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  cin>>n>>k>>w;
  for(int i=1;i<=n;i++){
    cin>>a[i].l>>a[i].r>>a[i].w;
    a[i].r=k-a[i].r;
    a[i].id=i;
  }
  sort(a+1,a+n+1);
//  for(int i=1;i<=n;i++)cerr<<a[i].l<<" "<<a[i].r<<" "<<a[i].w<<" "<<a[i].id<<endl;
//  cerr<<"!!!"<<endl;
  build(1,0,k);
  int p=1;
  for(int i=0;i<=k;i++){
    while(p<=n&&a[p].r==i){
      modify(1,0,a[p].l,a[p].w);
      p++;
    }
    dp[i]=query(1,0,i).first-i*w;
    if(i){
      dp[i]=max(dp[i],dp[i-1]);
    }
//    cerr<<i<<" "<<dp[i]<<" >> ";
//    for(int i=0;i<=k;i++){
//      auto it=query(1,i,i);
//      fprintf(stderr,"(%lld,%d)%c",it.first,it.second," \n"[i==k]);
//    }
    update(1,i);
  }
  long long ans=-dp[k];
  for(int i=1;i<=n;i++)ans+=a[i].w;
//  int lst=a[n].r+1;
//  cerr<<"total: "<<ans<<endl;
//  for(int i=n;i>=1;i--){
//    if(a[i].r<lst&&sta[i].first>0){
//      lst=sta[i].second;
//      ans-=sta[i].first;
//      cerr<<"select: "<<sta[i].second<<" "<<a[i].r<<" for "<<sta[i].first<<endl;
//    }
//  }
  cout<<ans<<endl;
}