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

const int N=262144,mod=998244353;
int n,m,a[N];

struct z {
  int x;
  z(int x=0):x(x){}
  friend inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
  friend inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
  friend inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
}F[N],G[N],B[N];
inline z fpow(z a,int b){z s=1;for(;b;b>>=1,a=a*a)if(b&1)s=s*a;return s;}

z fac[N],inv[N],ifac[N];
void initfac(int n){
  fac[0]=ifac[0]=inv[0]=inv[1]=1;
  for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i;
  for(int i=2;i<=n;i++)inv[i]=(mod-mod/i)*inv[mod%i];
  for(int i=1;i<=n;i++)ifac[i]=ifac[i-1]*inv[i];
}

struct NTT{
  int lim,k,rev[N];
  z invlim,w[N];

  void init(int n){
    lim=1,k=0; while(lim<=n)lim<<=1,++k;
    for(int i=0;i<lim;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(k-1));
    for(int len=1;len<lim;len<<=1){
      z wn=fpow(3,(mod-1)/(len<<1)); w[len]=1;
      for(int i=1;i<len;i++)w[i+len]=w[i+len-1]*wn;
    }
  }

  void dft(z *b,z *a,int n){
    memset(b+n,0,(lim-n)<<2);
    if(a==b){
      for(int i=0;i<lim;i++)if(i<rev[i])std::swap(a[i],a[rev[i]]);
    }else{
      for(int i=0;i<lim;i++)a[rev[i]]=b[i];
    }
    for(int len=1;len<lim;len<<=1)
      for(int i=0;i<lim;i+=(len<<1))
        for(int j=0;j<len;j++){
          z x=a[i+j],y=a[i+j+len]*w[j+len];
          a[i+j]=x+y,a[i+j+len]=x-y;
        }
  }

  void idft(z *b,z *a,int lim){
    dft(b,a,lim),std::reverse(b+1,b+lim),invlim=fpow(lim,mod-2);
    for(int i=0;i<lim;i++)a[i]=a[i]*invlim;
  }
};

struct Polynomial:NTT{
  void mul(z *a,z *b,z *c,int n,int m){
    static z T[N];
    init(n+m-1);
    dft(a,c,n),dft(b,T,m);
    for(int i=0;i<lim;i++)c[i]=c[i]*T[i];
    idft(c,c,lim);
  }

  void inv(z *a,z *b,int n){
    static z T[N];
    if(n==1){b[0]=fpow(a[0],mod-2); return;}
    inv(a,b,(n+1)/2),init(n+(n+1)/2),memcpy(T,a,n<<2);
    dft(T,T,n),dft(b,b,(n+1)/2);
    for(int i=0;i<lim;i++)b[i]=b[i]*(2-T[i]*b[i]);
    idft(b,b,lim);
  }

  void deri(z *a,z *b,int n){for(int i=0;i<n-1;i++)a[i]=b[i+1]*(i+1); b[n-1]=0;}
  void inte(z *a,z *b,int n){for(int i=1;i<n;i++)a[i]=b[i-1]*::inv[i-1]; b[0]=0;}
  void ln(z *a,z *b,int n){
    static z T[N];
    deri(a,b,n),inv(a,T,n),mul(T,b,T,n,n),inte(b,T,n);
  }
};
Polynomial p;

int main(){
#ifdef local
  freopen("1.in","r",stdin);
#endif
  static z a[N],b[N];
  read(n);
  for(int i=0;i<n;i++)read(a[i].x);
  p.inv(a,b,n);
  for(int i=0;i<n;i++)print(b[i].x," \n"[i+1==n]);
}

// void solveG(){
// }

// void solveB(){
//    for(int i=0;i<m;i++)
//       for(int j=0;j<m;j++)
//          B[i+j]=fpow(2,(i*j)%(mod-1))*ifac[i]*ifac[j];
// }

// void solveF(){

// }

// int main(){
// #ifdef local
//    freopen("1.in","r",stdin);
// #endif
//    read(n);
//    for(int i=1;i<=n;i++)read(a[i]),m=std::max(m,a[i]+1);
//    initfac(m);
//    solveG();
//    solveB();
//    solveF();
//    z ans=1;
//    for(int i=1;i<=n;i++)ans=ans*F[a[i]];
//    printf("%d\n",ans.x);
// }