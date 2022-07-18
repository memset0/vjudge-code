// 2022.6.19
#include<bits/stdc++.h>
using namespace std;
const int N=64,M=16;
int n,m,s,e,r,t,q,p[M],G[N][N],F[M][N][N],A[N][N],T[N][N],S[N][N];
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
void pow(int a[N][N],int k,int s[N][N]){
  memset(s,0,sizeof(s));
  for(int i=0;i<n;i++)s[i][i]=1;
  while(k){
    if(k&1)mul(a,s,s);
    mul(a,a,a),k>>=1;
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
        F[j][i][p[j%t]]=0;
      }
  }
  for(int i=0;i<n;i++)T[i][i]=1;
  for(int i=0;i<12;i++)mul(F[i],T,T);
  pow(T,r/12,S),A[s][0]=1,mul(S,A,A);
  for(int i=0;i<r%12;i++)mul(F[i],A,A);
  cout<<A[e][0]<<endl;
}