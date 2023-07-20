#include<bits/stdc++.h>
using namespace std;
const int N=2e5+9;
int T,n,q,fa[N],cnt[N];
vector<int> G[N];
void dfs(int u){
  if(fa[u]&&G[u].size()==1){
    cnt[u]=1;
  }
  for(int v:G[u])
    if(v!=fa[u]){
      fa[v]=u;
      dfs(v);
      cnt[u]+=cnt[v];
    }
}
void solve(){
  cin>>n;
  for(int i=1;i<=n;i++)fa[i]=cnt[i]=0,G[i].clear();
  for(int u,v,i=1;i<n;i++){
    cin>>u>>v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  dfs(1);
  cin>>q;
  for(int x,y,i=1;i<=q;i++){
    cin>>x>>y;
    cout<<(long long)cnt[x]*cnt[y]<<endl;
  }
}
int main(){
  ios::sync_with_stdio(0),cin.tie(0);
  cin>>T;
  while(T--){
    solve();
  }
} 