#include<bits/stdc++.h>

template<class value_t> struct MaxFlow{
  struct Edge{
    int to;
    value_t val;
  };
  int s,e;
  std::vector<Edge> E;
  std::vector<int> dep,cur;
  std::vector<std::vector<int>> G;
  inline int add(int u,int v,value_t w){
    G[u].push_back(E.size()),E.push_back((Edge){v,w});
    G[v].push_back(E.size()),E.push_back((Edge){u,0});
    return E.size()-2;
  }
  bool bfs(){
    std::queue<int> q;
    memset(&dep[0],0,dep.size()<<2);
    dep[s]=1,q.push(s);
    while(q.size()){
      int u=q.front(); q.pop();
      for(int i:G[u])if(E[i].val&&!dep[E[i].to]){
        dep[E[i].to]=dep[u]+1;
        q.push(E[i].to);
      }
    }
    return dep[e];
  }
  value_t dfs(int u,value_t d){
    if(u==e)return d;
    value_t s=0;
    for(int &k=cur[u];k<G[u].size();k++){
      int i=G[u][k];
      if(E[i].val&&dep[E[i].to]==dep[u]+1)
        if(value_t flow=dfs(E[i].to,std::min(d-s,E[i].val))){
          s+=flow;
          E[i].val-=flow;
          E[i^1].val+=flow;
          if(s==d)return s;
        }
    }
    return s?s:dep[s]=0;
  }
  value_t dinic(){
    value_t res=0;
    while(bfs()){
      memset(&cur[0],0,cur.size()<<2);
      res+=dfs(s,std::numeric_limits<value_t>::max());
    }
    return res;
  }
  void init(int n){
    s=n+1,e=n+2;
    E.clear(),G.clear();
    G.resize(n+3),cur.resize(n+3),dep.resize(n+3);
  }
};

template<class value_t> struct BoundedFlow:MaxFlow<value_t>{
  std::vector<int> delta;
  int add(int u,int v,int x,int y){
    delta[u]-=x,delta[v]+=x;
    return MaxFlow<value_t>::add(u,v,y-x);
  }
  void init(int n){
    MaxFlow<value_t>::init(n);
    delta.resize(n+1);
  }
  bool check(){
    value_t ned=0;
    for(int i=1;i<delta.size();i++){
      if(delta[i]>0)MaxFlow<value_t>::add(MaxFlow<value_t>::s,i,delta[i]),ned+=delta[i];
      if(delta[i]<0)MaxFlow<value_t>::add(i,MaxFlow<value_t>::e,-delta[i]);
    }
    return MaxFlow<value_t>::dinic()==ned;
  }
};

/* 
============================
 Solution for: LOJ101 最大流
============================
int main(){
  std::ios::sync_with_stdio(0),std::cin.tie(0),std::cout.tie(0);
  MaxFlow<long long> flow;
  int n,m,s,e;
  std::cin>>n>>m>>s>>e;
  flow.init(n);
  flow.add(flow.s,s,LLONG_MAX);
  flow.add(e,flow.e,LLONG_MAX);
  for(int u,v,w,i=1;i<=m;i++){
    std::cin>>u>>v>>w;
    flow.add(u,v,w);
  }
  std::cout<<flow.dinic()<<std::endl;
}
*/

int main(){
  std::ios::sync_with_stdio(0),std::cin.tie(0),std::cout.tie(0);
  BoundedFlow<long long> flow;
  int n,m;
  std::cin>>n>>m;
  flow.init(n);
  std::vector<int> u(m),v(m),x(m),y(m),id(m);
  for(int i=0;i<m;i++){
    std::cin>>u[i]>>v[i]>>x[i]>>y[i];
    id[i]=flow.add(u[i],v[i],x[i],y[i]);
  }
  if(flow.check()){
    std::cout<<"YES"<<std::endl;
    for(int i=0;i<m;i++)std::cout<<x[i]+flow.E[id[i]^1].val<<std::endl;
  }else{
    std::cout<<"NO"<<std::endl;
  }
}
