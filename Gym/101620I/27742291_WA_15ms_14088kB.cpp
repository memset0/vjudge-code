#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,m,a[N],l[N],r[N],ansl[N],ansr[N],tmp[N];
vector<pair<int,int>> sec,maxs,mins,stk,qry[N];
struct atom{int v,k;};
inline atom operator^(const atom &a,const atom &b){
  if(a.v==b.v)return a.k<b.k?a:b;
  return a.v<b.v?a:b;
}
struct segment{
  int l,r,mid,sum;
  atom dat;
}p[N<<2];
inline void maintain(int u){
  p[u].dat=p[u<<1].dat^p[u<<1|1].dat;
  p[u].dat.v+=p[u].sum;
}
void build(int u,int l,int r){
  p[u].l=l,p[u].r=r,p[u].mid=(l+r)>>1,p[u].sum=0;
  if(l==r)return p[u].sum=1e9,p[u].dat={p[u].sum,p[u].l},void();
  build(u<<1,l,p[u].mid);
  build(u<<1|1,p[u].mid+1,r);
  maintain(u);
}
void update(int u,int k,int v){
  if(p[u].l==p[u].r)return p[u].sum=p[u].dat.v=v,void();
  update(k<=p[u].mid?u<<1:u<<1|1,k,v);
  maintain(u);
}
void modify(int u,int l,int r,int v){
  // if(u==1)printf("modify %d %d %d\n",l,r,v);
  if(p[u].l==l&&p[u].r==r)return p[u].sum+=v,p[u].dat.v+=v,void();
  if(r<=p[u].mid)modify(u<<1,l,r,v);
  else if(l>p[u].mid)modify(u<<1|1,l,r,v);
  else modify(u<<1,l,p[u].mid,v),modify(u<<1|1,p[u].mid+1,r,v);
  maintain(u);
}
void forward(vector<pair<int,int>> &s){
  while(s.size()>1){
    auto a=s[s.size()-2],b=s[s.size()-1];
    if(a.second>=b.second)break;
    modify(1,a.first,b.first-1,b.second-a.second);
    s.pop_back(),s.pop_back(),s.push_back({a.first,b.second});
  }
}
void solve(int *ans){
  stk.clear(),maxs.clear(),mins.clear();
  for(int i=1;i<=n;i++)qry[i].clear();
  build(1,1,n);
  // for(int i=1;i<=n;i++)printf("%d%c",a[i]," \n"[i==n]);
  // for(int i=1;i<=m;i++)printf("> %d %d\n",l[i],r[i]);
  for(int i=1;i<=n;i++){//max-min=r-l
    maxs.push_back({i,a[i]}),forward(maxs);
    mins.push_back({i,-a[i]}),forward(mins);
    tmp[i]=p[1].dat.v==i?p[1].dat.k:-1;
    update(1,i,i);
  }
  // for(int i=1;i<=n;i++)printf("%d%c",tmp[i]," \n"[i==n]);
  for(int i=1;i<=m;i++)qry[r[i]].push_back({i,l[i]});
  for(int i=n;i>=1;i--){
    if(~tmp[i]){
      while(stk.size()>1&&stk.back().first>=tmp[i])stk.pop_back();
      stk.push_back({tmp[i],i});
    }
    for(auto it:qry[i])ans[it.first]=(--upper_bound(stk.begin(),stk.end(),pair<int,int>{it.second,114514}))->second;
  }
  // for(int i=1;i<=m;i++)printf("%d%c",ans[i]," \n"[i==m]);
}
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>n;
  for(int i=1;i<=n;i++)cin>>a[i];
  cin>>m;
  for(int i=1;i<=m;i++)cin>>l[i]>>r[i];
  solve(ansr);
  reverse(a+1,a+n+1);
  for(int i=1;i<=m;i++)tie(l[i],r[i])=make_pair(n-r[i]+1,n-l[i]+1);
  solve(ansl);
  for(int i=1;i<=m;i++)cout<<(n-ansl[i]+1)<<" "<<ansr[i]<<endl;
}