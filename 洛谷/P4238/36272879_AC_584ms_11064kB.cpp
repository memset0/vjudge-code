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
};
inline z fpow(z a,int b){z s=1;for(;b;b>>=1,a=a*a)if(b&1)s=s*a;return s;}

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
  int len,lim,k,rev[N<<2];
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
  poly mul(poly a,poly b){
    init(len=a.size()+b.size()-1),dft(a),dft(b);
    for(int i=0;i<lim;i++)a[i]=a[i]*b[i];
    return idft(a),a.resize(len),a;
  }
  poly inv(poly f,int n=-1){
    if((n=(~n?n:f.size()))==1)return poly(1,fpow(f[0],mod-2));
    poly a=inv(f,(n+1)>>1),b(&f[0],&f[n]);
    init(n*2-1),dft(a),dft(b);
    for(int i=0;i<lim;i++)a[i]=a[i]*(2-a[i]*b[i]);
    return idft(a),a.resize(n),a;
  }
}p;

int main(){
#ifdef local
  freopen("1.in","r",stdin);
#endif
  int n;
  poly a;
  read(n);
  a.read(n);
  p.inv(a).print();
}