#include<bits/stdc++.h>
using namespace std;
const int N=5e3+9;
int n,fa[N],siz[N],dep[N];
long long ans[N];
vector<int> d,G[N];
void dfs(int u){
  d.push_back(dep[u]);
  for(int v:G[u])
    if(v!=fa[u]){
      dep[v]=dep[u]+1;
      fa[v]=u;
      dfs(v);
    }
}
void solve(int rt){
  memset(fa,0,sizeof(fa));
  d.clear();
  dep[rt]=0,dfs(rt);
  sort(d.begin(),d.end());
  long long sum=0;
  for(int i=0;i<=n;i++){
    if(i){
      sum+=d[i-1]*2;
    }
    ans[i]=max(ans[i],-sum);
//    cerr<<sum<<" \n"[i==n];
  }
}
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  memset(ans,-63,sizeof(ans));
  cin>>n;
  for(int u,v,i=1;i<n;i++){
    cin>>u>>v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  for(int i=1;i<=n;i++){
    solve(i);
  }
  for(int i=0;i<=n;i++){
    cout<<(ans[i]+(long long)i*(n-1))<<" \n"[i==n];
  }
}