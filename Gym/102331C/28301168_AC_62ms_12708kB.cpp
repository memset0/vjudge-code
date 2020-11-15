#include<bits/stdc++.h>
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
const int N=13,M=1<<13,mod=998244353;
int n,m,popc[M],map[N][N];
struct z {
  int x; z(){} z(int x):x(x){}
  friend inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
  friend inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
  friend inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
}s[M],f[M],g[N][M],a[N][N][M],c[N][N][M],b[N][M],d[N][M],inv[N],sum[N][M],tmp[M];
inline z fpow(z a,int b){z s=1;for(;b;b>>=1,a=a*a)if(b&1)s=s*a;return s;}
void fwt(z *f,int lim){
  long long a[M];
  for(int i=0;i<lim;i++)a[i]=f[i].x;
  for(int len=1;len<lim;len<<=1)
    for(int i=0;i<lim;i+=(len<<1))
      for(int j=0;j<len;j++){
        long long x=a[i+j],y=a[i+j+len];
        a[i+j]=x+y,a[i+j+len]=x-y;
      }
  for(int i=0;i<lim;i++){f[i].x=a[i]%mod; if(f[i].x<0)f[i].x+=mod;}
}
namespace power_series_bits{
  inline void clear(z a[N][M],size_t n){for(int i=0;i<=n;i++)std::fill(a[i],a[i]+(1<<n),0);}
  void dft(z a[N][M],z f[M],size_t n){
    clear(a,n);
    for(int i=0;i<(1<<n);i++)a[popc[i]][i]=f[i];
    for(int i=0;i<=n;i++)fwt(a[i],1<<n);
  }
  void idft(z a[N][M],z f[M],size_t n){
    z inv=fpow(1<<n,mod-2);
    for(int i=0;i<=n;i++)fwt(a[i],1<<n);
    for(int i=0;i<(1<<n);i++)f[i]=a[popc[i]][i]*inv;
  }
}
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  scanf("%d%d",&n,&m),inv[0]=inv[1]=1;
  for(int i=2;i<N;i++)inv[i]=(mod-mod/i)*inv[mod%i];
  for(int i=1;i<(1<<n);i++)popc[i]=popc[i>>1]+(i&1);
  for(int u,v,i=0;i<m;i++)scanf("%d%d",&u,&v),--u,--v,map[u][v]=map[v][u]=1;
  s[1]=1;
  for(int t=1;t<n;t++){
    power_series_bits::clear(b,t);
    for(int i=0;i<=t;i++)power_series_bits::clear(c[i],t);
    for(int i=0;i<t;i++){
      for(int x=0;x<(1<<t);x++)g[i][x]=(x>>i)&1?s[x]:0;
      power_series_bits::dft(a[i],g[i],t);
      if(map[t][i])for(int j=0;j<=t;j++)for(int x=0;x<(1<<t);x++)b[j][x]=b[j][x]+a[i][j][x];
    }
    for(int j=0;j<=t;j++){ //c[u][j][...]*a[v][k][...]*map[u][v]
      for(int i=0;i<t;i++)if(map[t][i])for(int x=0;x<(1<<t);x++)b[j][x]=b[j][x]+(c[i][j][x]=c[i][j][x]+a[i][j][x]);
      for(int v=0;v<t;v++)memset(sum[v],0,(1<<t)<<2);
      for(int u=0;u<t;u++)for(int v=0;v<t;v++)if(map[u][v])for(int x=0;x<(1<<t);x++)sum[v][x]=sum[v][x]+c[u][j][x];
      for(int v=0;v<t;v++)for(int k=1;j+k<=t;k++)for(int x=0;x<(1<<t);x++)c[v][j+k][x]=c[v][j+k][x]+sum[v][x]*a[v][k][x];
    }
    for(int i,j,x=0;x<(1<<t);x++){
      for(i=1;i<=n;i++)b[i][x]=b[i][x].x&1?(b[i][x].x+mod)>>1:b[i][x].x>>1;
      for(d[0][x]=1,i=1;i<=n;i++)for(d[i][x]=0,j=1;j<=i;j++)d[i][x]=d[i][x]+b[j][x]*d[i-j][x]*j*inv[i];
    }
    power_series_bits::idft(d,f,t);
    for(int x=0;x<(1<<t);x++)s[x|(1<<t)]=f[x];
  }
  printf("%d\n",s[(1<<n)-1].x);
}