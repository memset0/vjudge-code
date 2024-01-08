#include<bits/stdc++.h>
using namespace std;
const int N=5e4+9;
int n,a[N];
struct segment{
  int l,r,mid;
  long long sum,tag;
}p[N<<2];
inline void pushup(int u,long long x){
  p[u].tag+=x;
  p[u].sum+=x*(p[u].r-p[u].l+1);
}
inline void pushdown(int u){
  if(p[u].tag){
    pushup(u<<1,p[u].tag);
    pushup(u<<1|1,p[u].tag);
    p[u].tag=0;
  }
}
void build(int u,int l,int r){
  p[u].l=l,p[u].r=r,p[u].mid=(l+r)>>1;
  if(l==r){
    p[u].sum=a[l];
    return;
  }
  build(u<<1,l,p[u].mid);
  build(u<<1|1,p[u].mid+1,r);
  p[u].sum=p[u<<1].sum+p[u<<1|1].sum;
}
void modify(int u,int l,int r,int x){
  if(p[u].l==l&&p[u].r==r){
    pushup(u,x);
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
  p[u].sum=p[u<<1].sum+p[u<<1|1].sum;
}
long long query(int u,int l,int r){
  if(p[u].l==l&&p[u].r==r){
    return p[u].sum;
  }
  pushdown(u);
  if(r<=p[u].mid){
    return query(u<<1,l,r);
  }else if(l>p[u].mid){
    return query(u<<1|1,l,r);
  }else{
    return query(u<<1,l,p[u].mid)+query(u<<1|1,p[u].mid+1,r);
  }
}
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  ios::sync_with_stdio(0),cin.tie(0);
  cin>>n;
  for(int i=1;i<=n;i++){
    cin>>a[i];
  }
  build(1,1,n);
  for(int op,l,r,c,i=1;i<=n;i++){
    cin>>op>>l>>r>>c;
    if(op==0){
      modify(1,l,r,c);
    }else{
      long long ans=query(1,l,r);
      cout<<ans%(c+1)<<'\n';
    }
  }
}