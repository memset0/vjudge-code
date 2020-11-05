#include<bits/stdc++.h>
using namespace std;
const int N=30,M=1e6+5;
int n,m,tot,f[N][N],len[M],to[M],g[M][N];
string s;
vector<int> G[N];
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>n;
  memset(f,-1,sizeof(f));
  for(int i=0;i<n;i++){
    f[i][i]=0;
    cin>>m;
    for(int j=1;j<=m;j++){
      cin>>s;
      len[++tot]=s.length();
      to[tot]=i;
      for(int k=0;k<len[tot];k++){
        G[s[k]-'a'].push_back(tot);
      }
    }
  }
  for(int t=0;t<n;t++){
    for(int i=0;i<n;i++)
      for(int j=0;j<n;j++)
        if(f[i][j]==t)
          for(int x:G[i]){
            g[x][j]++;
            if(g[x][j]==len[x]&&f[to[x]][j]==-1){
              f[to[x]][j]=t+1;
            }
          }
  }
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++)cout<<f[i][j]<<" ";
    printf("\n");
  }
}