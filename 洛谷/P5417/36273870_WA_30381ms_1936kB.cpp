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
}ans,fac[N],ifac[N],g[N][N];

int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  read(n),read(m);
  for(int i=1;i<=m;i++)if(read(a[i]),!a[i])i--,m--;
  for(int i=1;i<=m;i++)s[i]=s[i-1]+a[i];
  fac[0]=fac[1]=ifac[0]=ifac[1]=1;
  for(int i=2;i<=std::max(n,m);i++)fac[i]=fac[i-1]*i;
  for(int i=2;i<=std::max(n,m);i++)ifac[i]=(mod-mod/i)*ifac[mod%i];
  for(int i=2;i<=std::max(n,m);i++)ifac[i]=ifac[i-1]*ifac[i];
  for(int i=0;i<=m;i++){
    memset(g,0,sizeof(g));
    g[0][0]=1;
    for(int j=0;j<=m;j++)
      for(int k=j+1;k<=m;k++){
        int l=s[k-1]-s[j]+1,r=s[k]-s[j];
        log("j=%d k=%d : l=%d r=%d\n",j,k,l,r);
        for(int v=l;v<=r;v++)
          for(int u=0;u+v<=n;u++){
            g[k][u+v]-=g[j][u]*ifac[v];
          }
      }
    for(int i=0;i<=m;i++)
      for(int j=0;j<=m;j++)if(g[i][j].x){
        log("g[%d][%d]=%d\n",i,j,g[i][j].x);
      }
    z p=i&1?mod-1:1;
    for(int i=1;i<=m;i++){
      ans=ans+p*g[i][n]*fac[n];
    }
    log("%d => %d %d\n",i,ans,p);
  }
  printf("%d\n",ans.x);
}