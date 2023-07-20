#include<bits/stdc++.h>
using namespace std;
const int N=5e5+9;
int n,m,s,t,pre[N];
bool vis[N];
long long dis[N];
vector<pair<int,int>> G[N];
priority_queue<pair<long long,int>> q;
int main(){
  cin.tie(0),ios::sync_with_stdio(0);
  cin>>n>>m>>s>>t;
  for(int u,v,w,i=1;i<=m;i++){
    cin>>u>>v>>w;
    G[u].push_back(make_pair(v,w)); 
  }
  memset(dis,63,sizeof(dis));
  dis[s]=0;
  q.push(make_pair(0,s));
  while(q.size()){
    int u=q.top().second;
    q.pop();
    if(vis[u])continue;vis[u]=true;
    for(auto it:G[u]){
      if(dis[u]+it.second<dis[it.first]){
        dis[it.first]=dis[u]+it.second;
        pre[it.first]=u;
        q.push(make_pair(-dis[it.first],it.first));
      }
    }
  }
  if(dis[t]==dis[0]){
    cout<<-1<<endl;
    return 0;
  }
  vector<int> p={t};
  int u=t;
  while(u!=s){
    u=pre[u];
    p.push_back(u);
  }
  cout<<dis[t]<<" "<<(p.size()-1)<<endl;
  for(int i=p.size()-1;i;i--){
    cout<<p[i]<<" "<<p[i-1]<<endl;
  }
}