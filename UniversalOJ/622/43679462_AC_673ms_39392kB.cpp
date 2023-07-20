#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;
const int N=5e5+9;
template<const int N,class dis_t> struct ShortestPath{
  int L,pre[N];
  dis_t INF,dis[N],seg[N<<2];
  vector<pair<int,int>> G[N];
  inline void add_edge(int u,int v,int w){
    G[u].push_back(make_pair(v,w));
  }
  void init(int n){
    for(L=1;L<=n;L<<=1);
    memset(dis,63,(n+2)*sizeof(dis_t));
    INF=dis[0];
    for(int i=1;i<=n;i++)seg[L+i]=i;
  }
  void solve(int s){
    dis[s]=0;
    for(int i=(L+s)>>1;i;i>>=1)seg[i]=s;
    while(dis[seg[1]]!=INF){
      int u=seg[1];
      seg[L+u]=0;
      for(int i=(L+u)>>1;i;i>>=1)seg[i]=dis[seg[i<<1]]<dis[seg[i<<1|1]]?seg[i<<1]:seg[i<<1|1];
      for(auto it:G[u]){
        if(dis[u]+it.second<dis[it.first]){
          pre[it.first]=u;
          dis[it.first]=dis[u]+it.second;
          for(int i=L+it.first;i>>1;i>>=1){
            if(dis[seg[i]]<dis[seg[i^1]])seg[i>>1]=seg[i];
            else break;
          }
        }
      }
    }
  }
  vector<int> find_path(int s,int t){
    vector<int> p={t};
    for(int u=t;u!=s;p.push_back(u=pre[u]));
    reverse(p.begin(),p.end());
    return p;
  }
};
ShortestPath<N,long long> sp;
int main(){
  cin.tie(0),ios::sync_with_stdio(0);
  int n,m,s,u,v,w;
  cin>>n>>m>>s;
  sp.init(n);
  while(m--){
    cin>>u>>v>>w;
    sp.add_edge(u,v,w);
  }
  sp.solve(s);
  for(int i=1;i<=n;i++){
    cout<<(sp.dis[i]==sp.INF?-1:sp.dis[i])<<" \n"[i==n];
  }
}