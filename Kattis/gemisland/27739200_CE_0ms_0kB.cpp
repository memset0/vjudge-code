#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,popcnt,abm,mmx,avx,avx2,fma,tune=native") 
#include<bits/stdc++.h>
using namespace std;
const int N=510;
int n,d,r;
long double C[N][N],f[N][N],g[N][N];
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>n>>d>>r;
  for(int i=0;i<=n;i++){
    C[i][0]=1;
    for(int j=1;j<=i;j++)C[i][j]=C[i-1][j]+C[i-1][j-1];
  }
  f[0][0]=0,g[0][0]=1;
  for(int i=d;i>=0;i--){
    for(int x=n;x>=0;x--)//count
      for(int y=d;y>=0;y--){//sigma
        for(int j=1;j<=x&&i*j<=y;j++){
          // if(g[x-j][y-i*j])printf("DP[%d][%d] <= DP[%d][%d] (%d %d)\n",x,y,x-j,y-i*j,i,j);
          f[x][y]+=f[x-j][y-i*j]*C[x][j]+g[x-j][y-i*j]*C[x][j]*i*(min(x,r)-min(x-j,r));
          g[x][y]+=g[x-j][y-i*j]*C[x][j];
        }
      }
  }
  printf("%.12lf\n",(double)(f[n][d]/g[n][d]+r));
}