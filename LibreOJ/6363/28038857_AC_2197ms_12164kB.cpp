#include<bits/stdc++.h>
template<class T> inline void read(T &x){
  x=0; register char c=getchar(); register bool f=0;
  while(!isdigit(c))f^=c=='-',c=getchar();
  while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
const int N=1e5+10,mod=998244353;
int n,m,max;
struct z {
  int x;
  z(int x=0):x(x){}
  friend inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
  friend inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
  friend inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
}ans,inv[N],fac[N],ifac[N];
inline z fpow(z a,int b){z s=1;for(;b;b>>=1,a=a*a)if(b&1)s=s*a;return s;}
void init(int n){
  fac[0]=ifac[0]=inv[0]=inv[1]=1;
  for(int i=2;i<n;i++)inv[i]=(mod-mod/i)*inv[mod%i];
  for(int i=1;i<n;i++)fac[i]=fac[i-1]*i,ifac[i]=ifac[i-1]*inv[i];
}
namespace poly{
  int len=1,rev[N<<2];
  z w[N<<2];
  struct vec:std::vector<z>{
    using std::vector<z>::vector;
    inline vec setlen(size_t len){vec res=*this; return res.resize(len),res;}
    inline void input(){for(size_t i=0;i<size();i++)scanf("%d",&((int&)this->operator[](i)));}
    inline void output(){for(size_t i=0;i<size();i++)printf("%d%c",this->operator[](i).x," \n"[i+1==size()]);}
  };
  int init(int n){
    int lim=1,k=0; while(lim<n)lim<<=1,++k;
    for(int i=0;i<lim;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(k-1));
    for(;len<lim;len<<=1){
      z wn=fpow(3,(mod-1)/(len<<1)); w[len]=1;
      for(int i=1;i<len;i++)w[i+len]=w[i+len-1]*wn;
    }return lim;
  }
  void dft(vec &a,int lim){
    a.resize(lim);
    for(int i=0;i<lim;i++)if(i<rev[i])std::swap(a[i],a[rev[i]]);
    for(int i=0;i<lim;i+=2){z x=a[i],y=a[i+1]*w[1];a[i]=x+y,a[i+1]=x-y;}
    for(int len=2;len<lim;len<<=1)
      for(int i=0;i<lim;i+=(len<<1))
        for(int j=0;j<len;j++){
          z x=a[i+j],y=a[i+j+len]*w[j+len];
          a[i+j]=x+y,a[i+j+len]=x-y;
        }
  }
  void idft(vec &a,int lim){
    z inv=fpow(lim,mod-2); dft(a,lim),std::reverse(&a[1],&a[lim]);
    for(int i=0;i<lim;i++)a[i]=a[i]*inv;
  }
  vec operator+(vec a,const vec &b){
    a.resize(std::max(a.size(),b.size()));
    for(int i=0;i<b.size();i++)a[i]=a[i]+b[i]; return a;
  }
  vec operator-(vec a,const vec &b){
    a.resize(std::max(a.size(),b.size()));
    for(int i=0;i<b.size();i++)a[i]=a[i]-b[i]; return a;
  }
  vec operator*(vec a,vec b){
    if(a.size()<20||b.size()<20||(uint64_t)a.size()+b.size()<400){
      vec c(a.size()+b.size()-1);
      for(int i=0;i<a.size();i++)
        for(int j=0;j<b.size();j++)
          c[i+j]=c[i+j]+a[i]*b[j];
      return c;
    }
    int len=a.size()+b.size()-1,lim=init(len);
    dft(a,lim),dft(b,lim);
    for(int i=0;i<lim;i++)a[i]=a[i]*b[i];
    return idft(a,lim),a.resize(len),a;
  }
  vec inv(const vec &f,int len=-1){
    if((len=~len?len:f.size())==1)return vec{fpow(f[0],mod-2)};
    vec a=inv(f,(len+1)>>1),b(&f[0],&f[len]); int lim=init((len<<1)-1);
    dft(a,lim),dft(b,lim);
    for(int i=0;i<lim;i++)a[i]=a[i]*(2-a[i]*b[i]);
    return idft(a,lim),a.resize(len),a;
  }
  vec inte(vec a){for(int i=a.size()-1;i;i--)a[i]=a[i-1]*::inv[i];return *a.begin()=0,a;}
  vec deri(vec a){for(int i=0;i<a.size()-1;i++)a[i]=a[i+1]*(i+1);return *a.rbegin()=0,a;}
  vec ln(const vec &f){return inte((deri(f)*inv(f)).setlen(f.size()));}
  vec exp(const vec &f,int len=-1){
    if((len=~len?len:f.size())==1)return vec{1};
    vec a=exp(f,(len+1)>>1),b=a;b.resize(len),b=ln(b);
    for(int i=0;i<len;i++)b[i]=0-b[i]; b[0]=b[0]+1;
    for(int i=0;i<len;i++)b[i]=b[i]+f[i]; return (a*b).setlen(len);
  }
  vec pow(vec a,int b){a=ln(a); for(int i=0;i<a.size();i++)a[i]=a[i]*b; return exp(a);}
  vec slowpow(vec a,int b){
    int l=a.size(); vec s={1};
    for(;b;b>>=1,a=a*a,a.resize(l))if(b&1)s=s*a,s.resize(l);
    return s;
  }
}
namespace BCC{
  poly::vec A,B,D,G;
  void init(int max){
    D.resize(max),G.resize(max+1);
    for(int i=0;i<=max;i++)G[i]=fpow(2,(int64_t)i*(i-1)/2%(mod-1))*ifac[i];
    G=poly::ln(G);
    for(int i=0;i<max;i++)D[i]=G[i+1]*(i+1);
    A=poly::deri(D),B=poly::ln(D);
  }
  z eval(int n){
    if(n==1)return 1;
    return (A.setlen(n-1)*poly::exp(B.setlen(n-1)*poly::vec{mod-n}))[n-2]*fac[n-1]*inv[n-1];
  }
}
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  read(n),read(m);
  std::vector<int> a;
  for(int i=1,x;i<=m;i++)read(x),a.push_back(x);
  poly::vec A(*std::max_element(a.begin(),a.end()));
  init(std::max(n,(int)A.size())+5),BCC::init(A.size());
  for(int x:a)A[x-1]=BCC::eval(x)*ifac[x-1];
  A=poly::exp((poly::vec{n}*A).setlen(n));
  printf("%d\n",(A[n-1]*fac[n-1]*inv[n]).x);
}
