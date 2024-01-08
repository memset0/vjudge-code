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

// #define log(...) (void(0))
#define log(...) fprintf(stderr,__VA_ARGS__)
#define vname(x) #x
#define debug log("\33[2mPassing [%s] in LINE %d\33[0m\n",__FUNCTION__,__LINE__);

const int N=1e5+10,mod=998244353;

struct z{
  int x;
  z(int x=0):x(x){}
  friend inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
  friend inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
  friend inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
}inv[N],fac[N],ifac[N];
inline z fpow(z a,int b){z s=1;for(;b;b>>=1,a=a*a)if(b&1)s=s*a;return s;}
inline void initfac(int n){
  fac[0]=ifac[0]=inv[0]=inv[1]=1;
  for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i;
  for(int i=2;i<=n;i++)inv[i]=(mod-mod/i)*inv[mod%i];
  for(int i=1;i<=n;i++)ifac[i]=ifac[i-1]*inv[i];
}

struct poly:std::vector<z>{
  using std::vector<z>::vector;
  inline void read(int n){
    resize(n);
    for(int i=0;i<n;i++)::read(this->operator[](i).x);
  }
  inline void print()const{
    ::print(this->operator[](0).x);
    for(int i=1;i<size();i++)putchar(' '),::print(this->operator[](i).x);
    putchar('\n');
  }
};

struct NTT{
  int lim,k,rev[N<<2];
  z invlim,w[N<<2];
  void init(int n){
    lim=1,k=0; while(lim<n)lim<<=1,++k; invlim=fpow(lim,mod-2);
    for(int i=0;i<lim;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(k-1));
    for(int len=1;len<lim;len<<=1){
      z wn=fpow(3,(mod-1)/(len<<1)); w[len]=1;
      for(int i=1;i<len;i++)w[i+len]=w[i+len-1]*wn;
    }
  }
  void dft(poly &a){
    a.resize(lim);
    for(int i=0;i<lim;i++)if(i<rev[i])std::swap(a[i],a[rev[i]]);
    for(int len=1;len<lim;len<<=1)
      for(int i=0;i<lim;i+=(len<<1))
        for(int j=0;j<len;j++){
          z x=a[i+j],y=a[i+j+len]*w[j+len];
          a[i+j]=x+y,a[i+j+len]=x-y;
        }
  }
  void idft(poly &a){
    dft(a),std::reverse(&a[1],&a[lim]);
    for(int i=0;i<lim;i++)a[i]=a[i]*invlim;
  }
};

struct Polynomial:NTT{
  poly mul(poly a,poly b,int len=-1){
    // log("mul %d %d %d\n",a.size(),b.size(),len);
    init(len=~len?len:a.size()+b.size()-1),dft(a),dft(b);
    for(int i=0;i<lim;i++)a[i]=a[i]*b[i];
    return idft(a),a.resize(len),a;
  }
  poly inv(const poly &f,int n=-1){
    // log("inv %d %d\n",f.size(),n);
    if((n=(~n?n:f.size()))==1)return poly(1,fpow(f[0],mod-2));
    poly a=inv(f,(n+1)>>1),b(&f[0],&f[n]);
    init(n*2-1),dft(a),dft(b);
    for(int i=0;i<lim;i++)a[i]=a[i]*(2-a[i]*b[i]);
    return idft(a),a.resize(n),a;
  }
  poly inte(poly f){for(int i=f.size()-1;i>=1;i--)f[i]=f[i-1]*::inv[i]; return f[0]=0,f;}
  poly deri(poly f){for(int i=0;i<=f.size()-2;i++)f[i]=f[i+1]*(i+1); return f[f.size()-1]=0,f;}
  poly ln(poly f){return inte(mul(deri(f),inv(f),f.size()));}
}p;

int main(){
#ifdef local
  freopen("1.in","r",stdin);
#endif
  int n;
  poly a;
  read(n);
  initfac(n);
  a.read(n);
  for(int i=0;i<n;i++)a[i].x%=mod;
  p.ln(a).print();
}