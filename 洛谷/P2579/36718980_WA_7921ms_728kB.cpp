// 2022.6.19
#include<bits/stdc++.h>
using namespace std;
const int N=64,M=16;
int n,m,s,e,r,t,q,p[M],G[N][N],F[M][N][N],A[N][N];
void mul(int a[N][N],int b[N][N],int s[N][N]){
  static int c[N][N];
  memset(c,0,sizeof(c));
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
      for(int k=0;k<n;k++){
        c[i][j]=(c[i][j]+a[i][k]*b[k][j])%10000;
      }
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++){
      s[i][j]=c[i][j];
    }
}
int main(){
  ios::sync_with_stdio(0),cin.tie(0);
  cin>>n>>m>>s>>e>>r;
  for(int u,v,i=0;i<m;i++){
    cin>>u>>v;
    G[u][v]=G[v][u]=1;
  }
  for(int k=0;k<12;k++)
    for(int i=0;i<n;i++)
      for(int j=0;j<n;j++){
        F[k][i][j]=G[i][j];
      }
  cin>>q;
  for(int i=0;i<q;i++){
    cin>>t;
    for(int j=0;j<t;j++)cin>>p[j];
    for(int j=0;j<12;j++)
      for(int i=0;i<n;i++){
        F[j][p[j%t]][i]=F[j][i][p[j%t]]=0;
      }
  }
  A[s][0]=1;
  for(int i=0;i<r;i++){
    mul(F[i%12],A,A);
  }
  cout<<A[e][0]<<endl;
}