#include<bits/stdc++.h>
const int N=1048576,mod=998244353;
int k,rev[N];
long long n;
struct z{
  int x;
  z(int x=0):x(x){}
  friend inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
  friend inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
  friend inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
}w[N];
inline z fpow(z a,int b){z s=1;for(;b;b>>=1,a=a*a)if(b&1)s=s*a;return s;}
inline void out(const std::vector<z> &a){
  for(int i=0;i<a.size();i++)printf("%d%c",a[i].x,' '); putchar('\n');
}
inline void dft(std::vector<z> &a,int lim){
  a.resize(lim);
  for(int i=0;i<lim;i++)if(i<rev[i])std::swap(a[i],a[rev[i]]);
  for(int len=1;len<lim;len<<=1)
    for(int i=0;i<lim;i+=(len<<1))
      for(int j=0;j<len;j++){
        z x=a[i+j],y=a[i+j+len]*w[j+len];
        a[i+j]=x+y,a[i+j+len]=x-y;
      }
}
inline std::vector<z> operator*(std::vector<z> a,std::vector<z> b){
  int len=a.size()+b.size()-1,lim=1,bit=0;
  while(lim<len)lim<<=1,++bit;
  for(int i=0;i<lim;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
  z inv=fpow(lim,mod-2);
  dft(a,lim),dft(b,lim);
  for(int i=0;i<lim;i++)a[i]=a[i]*b[i];
  dft(a,lim),std::reverse(&a[1],&a[lim]);
  for(int i=0;i<lim;i++)a[i]=a[i]*inv;
  if(len>=k)for(int i=k;i<lim;i++)a[i%k]=a[i%k]+a[i];
  a.resize(std::min(k,len));
  return a;
}
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  for(int len=1;len<(N>>1);len<<=1){
    z wn=fpow(3,(mod-1)/(len<<1)); w[len]=1;
    for(int i=1;i<len;i++)w[i+len]=w[i+len-1]*wn;
  }
  std::cin>>n>>k;
  std::vector<z> s={1};
  std::vector<z> a={1,1};
  while(n){
    if(n&1)s=s*a;
    n>>=1;
    if(n)a=a*a;
  }
  std::cout<<s[0].x<<std::endl;
  std::cerr<<"clocks: "<<clock()/(double)CLOCKS_PER_SEC<<std::endl;
}