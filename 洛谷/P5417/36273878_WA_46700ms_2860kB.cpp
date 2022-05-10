#include<bits/stdc++.h>
// #define log(...) (void(0))
#define log(...) fprintf(stderr,__VA_ARGS__)
#define debug log("\33[2mPassing [%s] in LINE %d\33[0m\n",__FUNCTION__,__LINE__);
template<class T> inline void read(T &x){
  x=0; register char c=getchar(); register bool f=0;
  while(!isdigit(c))f^=c=='-',c=getchar();
  while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
template<class T> inline void print(T x){
  if(x<0)putchar('-'),x=-x;
  if(x>9)print(x/10); putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}

const int N=510,mod=1e9+7;
int n,m,a[N],s[N];

struct z {
  int x;
  z(int x=0):x(x){}
  inline void operator-=(z o){if((x-=o.x)<0)x+=mod;}
  inline void operator+=(z o){if((x+=o.x)>=mod)x-=mod;}
  friend inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
  friend inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
  friend inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
}ans,fac[N],ifac[N],mem[2][N][N],(*f)[N]=mem[0],(*g)[N]=mem[1];

int main(){
#ifdef local
  freopen("1.in","r",stdin);
#endif
  read(n),read(m);
  for(int i=1;i<=m;i++)if(read(a[i]),!a[i])i--,m--;
  for(int i=1;i<=m;i++)s[i]=s[i-1]+a[i];
  fac[0]=fac[1]=ifac[0]=ifac[1]=1;
  for(int i=2;i<=std::max(n,m);i++)fac[i]=fac[i-1]*i;
  for(int i=2;i<=std::max(n,m);i++)ifac[i]=(mod-mod/i)*ifac[mod%i];
  for(int i=2;i<=std::max(n,m);i++)ifac[i]=ifac[i-1]*ifac[i];
  f[0][0]=fac[n];
  for(int i=1;i<=m;i++){
    memset(g,0,N*N<<2);
    for(int j=0;j<=n;j++)
      for(int k=0;k<=n;k++)
        for(int l=1;l<=a[i]&&l<=j&&l<=k&&j+l<=n;l++){
          g[j][0]+=f[j-l][k-l]*ifac[k];
          if(l!=a[i])g[j][k]-=f[j-l][k-l];
        }
    // printf("> %d\n",g[n][0].x);
    ans+=g[n][0];
    std::swap(f,g);
    // for(int i=0;i<=n;i++)for(int j=0;j<=n;j++)if(f[i][j].x){
    //   printf("f[%d][%d]=%d\n",i,j,f[i][j].x);
    // }
  }
  printf("%d\n",ans.x);
}