#include<bits/stdc++.h>
using namespace std;
const int N=209,M=1e4+9;
int n,m,s,t,tot,hed[N],cur[N],to[M],dep[N],val[M],nxt[M];
inline void add(int u,int v,int w){
  nxt[tot]=hed[u],to[tot]=v,val[tot]=w,hed[u]=tot++;
  nxt[tot]=hed[v],to[tot]=u,val[tot]=0,hed[v]=tot++;
}
bool bfs(){
  static int u,l,r,q[N];
  memset(dep,0,sizeof(dep)),l=r=dep[s]=1,q[1]=s;
  while(l<=r){
    u=q[l++];
    for(int i=hed[u];~i;i=nxt[i])if(val[i]&&!dep[to[i]])dep[to[i]]=dep[u]+1,q[++r]=to[i];
  }
  return dep[t];
}
int dfs(int u,int d){
  if(u==t)return d; int s=0;
  for(int &i=cur[u];~i;i=nxt[i])if(val[i]&&dep[to[i]]==dep[u]+1)
    if(int e=dfs(to[i],min(d-s,val[i]))){
      s+=e,val[i]-=e,val[i^1]+=e;
      if(s==d)return s;
    }
  return s?s:dep[u]=0;
}
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  memset(hed,-1,sizeof(hed));
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>n>>m>>s>>t;
  for(int u,v,w,i=1;i<=m;i++){
    cin>>u>>v>>w;
    add(u,v,w);
  }
  long long ans=0;
  while(bfs()){
//    for(int i=1;i<=n;i++)cerr<<dep[i]<<" \n"[i==n];
    memcpy(cur+1,hed+1,n<<2);
    ans+=dfs(s,INT_MAX);
  }
  cout<<ans<<endl;
}