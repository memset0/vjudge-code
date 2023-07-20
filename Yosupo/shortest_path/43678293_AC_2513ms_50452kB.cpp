#include<bits/stdc++.h>
using namespace std;
const int N=5e5+9;
template<const int N,class dis_t> struct ShortestPath{
  int L,pre[N];
  dis_t INF,dis[N],seg[N<<2];
  vector<pair<int,int>> G[N];
  inline void add_edge(int u,int v,int w){
    G[u].push_back(make_pair(v,w));
  }
  inline void update(int k){
    for(int i=(L+k)>>1;i;i>>=1)seg[i]=dis[seg[i<<1]]<dis[seg[i<<1|1]]?seg[i<<1]:seg[i<<1|1];
  } 
  void init(int n){
    for(L=1;L<=n;L<<=1);
    memset(dis,63,(n+2)*sizeof(dis_t));
    INF=dis[0];
    for(int i=1;i<=n;i++)seg[L+i]=i;
    cerr<<L<<endl;
  }
  void solve(int s){
    cerr<<"solve "<<s<<endl; 
    dis[s]=0,update(s);
    while(dis[seg[1]]!=INF){
      int u=seg[1];
      cerr<<u<<" "<<dis[u]<<endl;
      seg[L+u]=0,update(u);
      for(auto it:G[u]){
        if(dis[u]+it.second<dis[it.first]){
          pre[it.first]=u;
          dis[it.first]=dis[u]+it.second;
          update(it.first);
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
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  cin.tie(0),ios::sync_with_stdio(0);
  int n,m,s,t,u,v,w;
  cin>>n>>m>>s>>t;
  sp.init(n);
  while(m--){
    cin>>u>>v>>w;
    sp.add_edge(u+1,v+1,w);
  }
  sp.solve(s+1);
  if(sp.dis[t+1]==sp.INF){
    cout<<-1<<endl;
  }else{
    vector<int> p=sp.find_path(s+1,t+1);
    cout<<sp.dis[t+1]<<" "<<(p.size()-1)<<endl;
    for(int i=1;i<p.size();i++){
      cout<<(p[i-1]-1)<<" "<<(p[i]-1)<<endl;
    }
  }
}