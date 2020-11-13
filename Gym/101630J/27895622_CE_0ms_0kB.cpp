#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e3+10;
int n,m,k,w[N],u[N],v[N],dis[N];
vector<pair<int,int>> G[N];
struct Node{
  int id,val;
  inline Node(int id=0,int val=0):id(id),val(val){};
  inline bool operator<(const Node &rhs)const{
    return val==rhs.val?id<rhs.id:val>rhs.val;
  }
};
int solve(int x){
  for(int i=1;i<=m;i++){
    G[u[i]].push_back(v[i],max<int>(0,w[i]-x));
    G[v[i]].push_back(u[i],max<int>(0,w[i]-x));
  }
  for(int i=1;i<=n;i++)dis[i]=1e18;
  dis[1]=0;
  priority_queue<Node> q;
  q.push({1,0});
  while(!q.empty()){
    auto[u,x]=q.top();q.pop();
    if(dis[u]!=x)continue;
    for(auto[v,w]:G[u]){
      if(dis[v]>x+w){
        dis[v]=x+w;
        q.push({v,dis[v]});
      }
    }
  }
  for(int i=1;i<=n;i++) G[i].clear();
  return dis[n]+k*x;
}
int32_t main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>n>>m>>k;
  for(int i=1;i<=m;i++)cin>>u[i]>>v[i]>>w[i];
  int ans=solve(0);
  for(int i=1;i<=m;i++)ans=min(ans,solve(w[i]));
  cout<<ans<<endl;
}