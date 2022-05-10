#include<bits/stdc++.h>
using namespace std;
const int N=1e3+9,mod=1e9+7;
int n,m,dp[N][N];
inline void add(int &x,int y){x+=y; if(x>=mod)x-=mod;}
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  cin>>n>>m;
  dp[0][m]=1;
  for(int i=0;i<n;i++)
    for(int j=0;j<=m;j++){
      add(dp[i+1][min(m,j+1)],dp[i][j]);
      for(int k=0;k<=j&&k<m;k++)add(dp[i+1][k],dp[i][j]);
    }
  // for(int i=0;i<=n;i++){
  //   for(int j=0;j<=m;j++)cout<<dp[i][j]<<" \n"[j==m];
  // }
  int ans=0;
  for(int i=0;i<=m;i++)add(ans,dp[n][i]);
  cout<<ans<<endl;
}