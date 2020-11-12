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

const int N=252,M=N*N,L=65536,mod=998244353;
int n,a,b,lim,rev[M<<2];

struct z {
  int x;
  z(int x=0):x(x){}
  z(long long x):x(x%mod){}
  inline z operator-=(z o){x-=o.x;if(x<0)x+=mod;return *this;}
  inline z operator*=(z o){x=(long long)x*o.x%mod;return *this;}
  inline z operator+=(z o){x+=o.x;if(x>=mod)x-=mod;return *this;}
  friend inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
  friend inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
  friend inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
};
inline z finv(z a){return a.x<2?1:(mod-mod/a.x)*finv(mod%a.x);}
inline z fpow(z a,int b){z s=1;for(;b;b>>=1,a=a*a)if(b&1)s=s*a;return s;}

z ans,ilim,w[M<<2],p[M<<2],t[M<<2],fac[M],ifac[M],s[M],f[2][M],g[N][M],h[M<<2];
inline z C(int n,int m){return n<m?0:fac[n]*ifac[m]*ifac[n-m];}

void init(int n){
  fac[0]=ifac[0]=ifac[1]=1;
  for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i;
  for(int i=2;i<=n;i++)ifac[i]=(mod-mod/i)*ifac[mod%i];
  for(int i=2;i<=n;i++)ifac[i]=ifac[i-1]*ifac[i];
  int k=-1;lim=1;
  while(lim<=n)lim<<=1,++k;
  log("init %d => %d\n",n,lim);
  for(int i=0;i<lim;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<k);
  for(int len=1;len<lim;len<<=1){
    z wn=fpow(3,(mod-1)/(len<<1)); w[len]=1;
    for(int i=1;i<len;i++)w[i+len]=w[i+len-1]*wn;
  }
  ilim=fpow(lim,mod-2);
}

void dft(z *a,z *b){
  for(int i=0;i<lim;i++)b[rev[i]]=a[i];
  for(int len=1;len<lim;len<<=1)
    for(int i=0;i<lim;i+=(len<<1))
      for(int j=0;j<len;j++){
        z x=b[i+j],y=b[i+j+len]*w[j+len];
        b[i+j]=x+y,b[i+j+len]=x-y;
      }
}

void idft(z *a,z *b){
  dft(a,b),std::reverse(b+1,b+lim);
  for(int i=0;i<lim;i++)b[i]=b[i]*ilim;
}

int main(){
#ifdef local
  freopen("b3.in","r",stdin);
#endif
  read(n),read(a),read(b),init(n*a);
  for(int i=b;i<a;i++)p[i]=ifac[i];
  for(int i=0;i<lim;i++)t[i]=1;
  g[0][0]=1,dft(p,h);
  for(int i=1;i<=n;i++){
    for(int j=0;j<lim;j++)t[j]*=h[j];
    idft(t,p);
    for(int j=1;j<=a*n;j++)g[i][j]=p[j]*fac[j];
  }
  log("clocks: %.4lf\n",clock()/(double)CLOCKS_PER_SEC);
  f[0][0]=1;
  for(int i=1;i<=n;i++){
    z p=1,t;
    s[0]=f[(i&1)^1][0];
    for(int j=1;j<=a*n;j++){
      s[j]=s[j-1]+f[(i&1)^1][j]*(p=p*(n-i+1));
    }
    memset(f[i&1],0,(a*i)<<2);
    p=fpow(n-i+1,mod-a*i),t=fpow(n-i+1,mod-2);
    for(int j=a*i;j<=a*n;j++){
      f[i&1][j]=C(j-a*(i-1)-1,a-1)*s[j-1]*(p=p*t);
    }
    p=fpow(n-i+1,mod-a*(i-1)-b);
    for(int j=a*(i-1)+b;j<=a*n;j++){
      ans+=s[j-1]*(i-1)*C(n,i)*fac[i]*C(j-a*(i-1)-1,b-1)*g[n-i][j-a*(i-1)-b]*(p=p*t);
    }
  }
  print(ans.x,'\n');
  log("clocks: %.4lf\n",clock()/(double)CLOCKS_PER_SEC);
}