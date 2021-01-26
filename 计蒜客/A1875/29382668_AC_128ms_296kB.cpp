#include<bits/stdc++.h>
using namespace std;
const int N=109;
int n,m,k,all,c[N],ans[N],anc[N];
bool I[N];
string str;
struct Edge{
  int u,v,w,c;
}e[N];
struct SPFA{
  int u,cst[N],dis[N],pre[N];
  bool inq[N];
  queue<int> q;
  vector<int> G[N];
  inline void reset(){for(int i=0;i<=m+1;i++)G[i].clear();}
  inline void add(int u,int v){G[u].push_back(v);}
  inline int spfa(){
    memset(dis,-63,(m+2)<<2),q.push(0),inq[0]=1,dis[0]=0,pre[m+1]=-1;
    while(q.size()){
      u=q.front(),q.pop(),inq[u]=false;
      for(int v:G[u])if(dis[u]+cst[v]>dis[v]){
        dis[v]=dis[u]+cst[v],pre[v]=u;
        if(!inq[v])q.push(v),inq[v]=true;
      }
    }
    return ~pre[m+1];
  }
}graph;
inline int find(int x){return anc[x]==x?x:anc[x]=find(anc[x]);}
inline bool check(char ext){ 
  for(int i=1;i<=n;i++)anc[i]=i;
  for(int i=1;i<=m;i++)if(e[i].c!=ext&&!I[i])anc[find(e[i].u)]=find(e[i].v);
  for(int i=1;i<=n;i++)if(find(i)!=find(1))return false;
  return true;
}
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  memset(ans,-1,sizeof(ans));
  cin>>n>>m;
  for(int i=1;i<=m;i++)cin>>e[i].u>>e[i].v>>e[i].w>>str,e[i].c=str[0],all+=e[i].w;
  for(int k=m-1;k>=0;k--){
    for(int i=1;i<=m;i++)graph.cst[i]=I[i]?-e[i].w:e[i].w;
    graph.reset();
    for(int i=1;i<=m;i++)if(!I[i]){
      I[i]^=1;
      if(check('R'))graph.add(0,i);
      if(check('B'))graph.add(i,m+1);
      I[i]^=1;
    }
    for(int i=1;i<=m;i++)if(I[i])
      for(int j=1;j<=m;j++)if(!I[j]){
        I[i]^=1,I[j]^=1;
        if(check('R'))graph.add(i,j);
        if(check('B'))graph.add(j,i);
        I[i]^=1,I[j]^=1;
      }
    if(!graph.spfa())break;
    for(int u=graph.pre[m+1];u;u=graph.pre[u])I[u]^=1;
    ans[k]=all;
    for(int i=1;i<=m;i++)if(I[i])ans[k]-=e[i].w;
  }
  ans[m]=all;
  for(int i=1;i<=m;i++)cout<<ans[i]<<'\n';
}//