#include<bits/stdc++.h>
#define getl get<0>
#define getr get<1>
#define getid get<2>
#ifndef memset0
  #define endl '\n'
#endif
using namespace std;
const int N=3e5+9;
int T,n,m,k,tot,cnt,fa[N],s[N];
long long sum;
vector<int> used;
vector<pair<int,int>> ins[N],del[N];
vector<tuple<int,int,int>> a[N],b[N];
inline void add(int k,int x){
  for(;k<N;k+=k&-k)s[k]+=x;
}
inline int ask(int k){
  int r=0;
  for(;k;k-=k&-k)r+=s[k];
  return r;
}
int find(int x){
  if(fa[x]==x)return x;
  return fa[x]=find(fa[x]);
}
void merge(int u,int v){
  u=find(u);
  v=find(v);
  if(u!=v){
    fa[u]=v;
    --cnt;
  }
}
void shrink(vector<tuple<int,int,int>> &a){
  sort(a.begin(),a.end());
  vector<tuple<int,int,int>> b;
  for(const auto &it:a){
    if(b.size()&&getr(b.back())+1==getl(it)){
      fa[getid(it)]=getid(b.back());
      getr(b.back())=getr(it);
    }else{
      b.push_back(it);
    }
  }
  a.swap(b);
}
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  ios::sync_with_stdio(0),cin.tie(0);
  cin>>T;
  while(T--){
    cin>>n>>m>>k;
    tot=0;
    for(int x1,y1,x2,y2,i=1;i<=k;i++){
      cin>>x1>>y1>>x2>>y2;
      if(x1==x2){
        a[x1].emplace_back(y1,y2,-1);
      }else{
        used.push_back(y1);
        b[y1].emplace_back(x1,x2,++tot);
        ins[x1].emplace_back(y1,tot);
        del[x2].emplace_back(y1,tot);
        a[x1].emplace_back(y1,y1,tot);
        a[x2].emplace_back(y2,y2,tot);
      }
    }
    sort(used.begin(),used.end());
    used.erase(unique(used.begin(),used.end()),used.end());
    for(int i=1;i<=tot;i++)fa[i]=i;
    for(int i=1;i<=n;i++)shrink(a[i]);
    for(int i:used)shrink(b[i]);
    sum=cnt=0;
    for(int cur=0,i=1;i<=n;i++){
      for(const auto &[k,id]:ins[i]){
        add(k,1);
        ++cur;
        ++cnt;
      }
      sum+=cur;
      for(const auto &[l,r,id]:a[i]){
        sum+=r-l+1;
        sum-=ask(r)-ask(l-1);
        ++cnt;
      }
      if(i>1&&a[i].size()&&a[i-1].size()){
        auto &x=a[i-1];
        auto &y=a[i];
        auto process=[&](const tuple<int,int,int> &x,const tuple<int,int,int> &y){
          // fprintf(stderr,"check (%d %d %d) (%d %d %d)\n",getl(x),getr(x),getid(x),getl(y),getr(y),getid(y));
          if(getl(x)<getl(y)){
            if(getl(y)<=getr(x)){
              merge(getid(x),getid(y));
            }
          }else{
            if(getl(x)<=getr(y)){
              merge(getid(x),getid(y));
            }
          }
        };
        int i=0,j=0;
        process(x[0],y[0]);
        while(i+1<x.size()||j+1<y.size()){
          if(i+1<x.size()&&j+1<y.size()){
            if(getl(x[i])<getl(y[j])){
              i++;
            }else{
              j++;
            }
          }else if(i+1<x.size()){
            i++;
          }else{
            j++;
          }
          process(x[i],y[j]);
        }
      }
      for(const auto &[k,id]:del[i]){
        add(k,-1);
        --cur;
      }
      cout<<sum<<" "<<cnt<<endl;
    }
    for(int i=1;i<=n;i++){
      a[i].clear();
      ins[i].clear();
      del[i].clear();
    }
    for(int i:used)b[i].clear();
    used.clear();
  }
}