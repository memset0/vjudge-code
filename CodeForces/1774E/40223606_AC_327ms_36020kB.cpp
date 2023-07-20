#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,d,ans,m[2],a[2][N],b[2][N],fa[N],dep[N],f[2][N];
vector<int> G[N];
void dfs(int u){
//  cerr<<"dfs "<<u<<endl;
  dep[u]=dep[fa[u]]+1;
  for(int k=0;k<2;k++){
    if(b[k][u]){
      f[k][u]=dep[u];
    }else{
      f[k][u]=-1;
    }
  }
  for(int v:G[u]){
    if(v!=fa[u]){
      fa[v]=u;
      dfs(v);
      for(int k=0;k<2;k++){
        if(f[k][v]>f[k][u]){
          f[k][u]=f[k][v];
        }
      }
    }
  }
}
void solve(int u){
//  cerr<<"solve "<<u<<" "<<dep[u]<<" "<<f[0][u]<<" "<<f[1][u]<<endl;
  for(int v:G[u]){
    if(v!=fa[u]){
      for(int k=0;k<2;k++){
//        printf(">> %d %d : %d %d\n",k,v,f[k][v],f[k^1][v]);
        if(f[k][v]!=-1||f[k^1][v]-dep[u]>d){
          ans++;
//          cout<<"entry "<<k<<" "<<u<<"->"<<v<<endl;
        }
      }
      solve(v);
    }
  }
}
int main(){
  ios::sync_with_stdio(0),cin.tie(0);
  cin>>n>>d;
  for(int u,v,i=1;i<n;i++){
    cin>>u>>v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  for(int k=0;k<2;k++){
    cin>>m[k];
    for(int i=1;i<=m[k];i++){
      cin>>a[k][i];
      b[k][a[k][i]]=true;
    }
  }
  dfs(1);
  solve(1);
  cout<<(ans<<1)<<endl;
}