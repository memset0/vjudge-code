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
bool actived[N];
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
	// cerr<<"! merge "<<u<<" "<<v<<endl;
  u=find(u);
  v=find(v);
  if(u!=v){
    fa[u]=v;
    --cnt;
  }
}
void insert(int x){
	// cerr<<"! insert "<<x<<endl;
	x=find(x);
	if(actived[x]){
		return;
	}
	actived[x]=true;
	++cnt;
}
int main(){
#ifdef memset0
  freopen("D.in","r",stdin);
#endif
  ios::sync_with_stdio(0),cin.tie(0);
  cin>>T;
  while(T--){
    cin>>n>>m>>k;
    tot=0;
    for(int x1,y1,x2,y2,i=1;i<=k;i++){
      cin>>x1>>y1>>x2>>y2;
      if(x1==x2){
        a[x1].emplace_back(y1,y2,++tot);
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
		fill_n(actived+1,tot,false);
    // for(int i=1;i<=n;i++)for(auto [l,r,id]:a[i])cerr<<"a"<<i<<"::"<<l<<" "<<r<<" "<<id<<endl;
    // for(int i:used)for(auto [l,r,id]:b[i])cerr<<"b"<<i<<"::"<<l<<" "<<r<<" "<<id<<endl;
    sum=cnt=0;
		map<int,int> mp;
    for(int cur=0,i=1;i<=n;i++){
      for(const auto &[k,id]:ins[i]){
        add(k,1);
        ++cur;
        auto it=mp.find(k);
        if(it!=mp.end())merge(id,it->second);
				mp[k]=id;
        insert(id);
      }
      for(const auto &[k,id]:del[i-1]){
        add(k,-1);
				mp.erase(k);
        --cur;
      }
      sum+=cur;
      sort(a[i].begin(),a[i].end());
      for(int k=0;k<a[i].size();k++){
        const auto &[l,r,id]=a[i][k];
        sum+=r-l+1;
        sum-=ask(r)-ask(l-1);
        insert(id);
				auto it=mp.find(l-1);
				if(it!=mp.end())merge(id,it->second);
				it=mp.find(r+1);
				if(it!=mp.end())merge(id,it->second);
        if(k>0&&getr(a[i][k-1])+1==getl(a[i][k])){
          merge(getid(a[i][k-1]),getid(a[i][k]));
        }
        if(k+1<a[i].size()&&getr(a[i][k])+1==getl(a[i][k+1])){
          merge(getid(a[i][k]),getid(a[i][k+1]));
        }
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