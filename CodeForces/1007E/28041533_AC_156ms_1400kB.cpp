#include<bits/stdc++.h>
const int N=210;
int n,t,m;
long long x,a[N],b[N],c[N],f[N][N][2],g[N][N][2];
inline void upd(long long &a,long long b){if(b<a)a=b;}
inline long long ceildiv(long long a,long long b){return (a+b-1)/b;}
int main(){
  memset(f,63,sizeof(f)),memset(g,63,sizeof(g));
  memset(f[0],0,sizeof(f[0])),memset(g[0],0,sizeof(g[0]));
  scanf("%d%d%d",&n,&t,&m);
  for(int i=1;i<=n;i++)scanf("%lld%lld%lld",&a[i],&b[i],&c[i]);
  ++n,a[n]=c[n]=1e12;
  for(int i=2;i<=n;i++)a[i]+=a[i-1],b[i]+=b[i-1];
  for(int i=1;i<=n;i++)
    for(int j=0;j<=t;j++)
      for(int k=0;k<2;k++){
        if(k*(a[i]-a[i-1])+j*(b[i]-b[i-1])<=c[i]&&f[i-1][j][k]<=1e18){
          upd(f[i][j][k],f[i-1][j][k]);
          x=ceildiv(k*a[i-1]+j*b[i-1],m);
          if(x*m<=k*a[i]+j*b[i])upd(g[i][j][k],x);
        }
        for(int r=0;r<j;r++)if(g[i][r][k]<1e18&&f[i-1][j-r][0]<1e18){
          x=std::max(ceildiv(k*a[i]+(r-j)*b[i-1]+j*b[i]-c[i],m),g[i][r][k]);
          if(x*m>k*a[i]+r*b[i])continue;
          upd(f[i][j][k],x+f[i-1][j-r][0]);
          x=(k*a[i-1]+j*b[i-1]+x*m-k*a[i-1]-r*b[i-1]+m-1)/m;
          if(x*m>k*a[i]+j*b[i])continue;
          upd(g[i][j][k],x);
        }
      }
  printf("%lld\n",f[n][t][1]);
}