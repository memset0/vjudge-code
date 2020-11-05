#include<bits/stdc++.h>
const int N=410,M=N*N*4;
int n,m,a[N][N],b[N][N],c[N][N],pre[M];
bool vis[M],bt[N][N],ct[N][N];
long long dis[M];
std::vector<std::pair<int,int>> G[M];
std::priority_queue<std::pair<long long,int>> q;
inline int idx(int u){return (u-1)/(m+1)+1;}
inline int idy(int u){return (u-1)%(m+1)+1;}
inline int id(int i,int j){return (i-1)*(m+1)+j;}
inline int id(int i,int j,int k){return (i-1)*(m+1)+j+k*(n+1)*(m+1);}
inline void add(int u,int v,int w){G[u].push_back({v,w}),G[v].push_back({u,w});}
void dij(int n){
  memset(vis+1,0,n),memset(dis+1,63,n<<3),dis[1]=0,q.push({0,1});
  while(q.size()){
    auto t=q.top(); q.pop(); int u=t.second; if(vis[u])continue; vis[u]=1;
    for(const auto &e:G[u]){int v=e.first,w=e.second;if(dis[v]>dis[u]+w)dis[v]=dis[u]+w,pre[v]=u,q.push({-dis[v],v});}
  }
}
int main(){
  scanf("%d%d",&n,&m);
  for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)scanf("%d",&a[i][j]);
  for(int i=1;i<=n;i++)for(int j=0;j<=m;j++)scanf("%d",&b[i][j]);
  for(int i=0;i<=n;i++)for(int j=1;j<=m;j++)scanf("%d",&c[i][j]);
  for(int i=1;i<=n;i++)for(int j=0;j<=m;j++)add(id(i,j+1),id(i+1,j+1),b[i][j]);
  for(int i=0;i<=n;i++)for(int j=1;j<=m;j++)add(id(i+1,j),id(i+1,j+1),c[i][j]);
  dij((n+1)*(m+1));
  for(int u=1;u<=(n+1)*(m+1);u++)G[u].clear();
  for(int i=1;i<=n+1;i++)for(int j=1;j<=m+1;j++)if(a[i][j]){
    bt[i][j]=bt[i][j-1]=ct[i][j]=ct[i-1][j]=1;
    for(int u=id(i,j);u!=1;u=pre[u])u>pre[u]?
      (u-pre[u]==1?ct[idx(u)-1][idy(u)-1]:bt[idx(u)-1][idy(u)-1])=1:
      (pre[u]-u==1?ct[idx(pre[u])-1][idy(pre[u])-1]:bt[idx(pre[u])-1][idy(pre[u])-1])=1;
  }
  for(int i=1;i<=n;i++)for(int j=0;j<=m;j++)add(id(i,j+1,3),id(i+1,j+1,0),b[i][j]),add(id(i,j+1,2),id(i+1,j+1,1),b[i][j]);
  for(int i=0;i<=n;i++)for(int j=1;j<=m;j++)add(id(i+1,j,1),id(i+1,j+1,0),c[i][j]),add(id(i+1,j,2),id(i+1,j+1,3),c[i][j]);
  add(id(1,1,0),id(1,1,1),0);
  for(int i=1;i<=n+1;i++)for(int j=i==1?2:1;j<=m+1;j++){
    if(!bt[i-1][j-1])add(id(i,j,0),id(i,j,1),0);//printf("%d %d : %d %d\n",i,j,0,1);
    if(!ct[i-1][j])add(id(i,j,1),id(i,j,2),0);//printf("%d %d : %d %d\n",i,j,1,2);
    if(!bt[i][j-1])add(id(i,j,2),id(i,j,3),0);//printf("%d %d : %d %d\n",i,j,2,3);
    if(!ct[i-1][j-1])add(id(i,j,3),id(i,j,0),0);//printf("%d %d : %d %d\n",i,j,3,0);
  }
  dij((n+1)*(m+1)*4),printf("%lld\n",dis[id(1,1,3)]);
}
