#include<bits/stdc++.h>
#define log(...) printf(__VA_ARGS__)
// #define log(...) fprintf(stderr,__VA_ARGS__)
using namespace std;

typedef vector<int> poly;
typedef long long ll;
typedef unsigned long long ull;

namespace fastio{
  const int BUFFER=1<<18;
  char ibuf[BUFFER],*iS,*iT;
  inline int getc(){
    if(iS==iT){
      iT=(iS=ibuf)+fread(ibuf,1,BUFFER,stdin);
      return iS==iT?EOF:*iS++;
    }else{
      return *iS++;
    }
  }
  template<class T> inline void read(T &x){
    x=0;
    int c=getc(),f=0;
    while(!isdigit(c))f^=c=='-',c=getc();
    while(isdigit(c))x=x*10+c-'0',c=getc();
    if(f)x=-x;
  }
}
using fastio::read;

const int N=4e5+9,L=1<<20,mod=998244353,inv2=(mod+1)>>1;

int n,w,ql,qr,lim,p[N],f1[N],f2[N],a[N];
poly *all[N<<1];

inline int mul(int a,int b){return 1ll*a*b%mod;}
inline int add(int a,int b){
  a+=b;
  return a>=mod?a-mod:a;
}
inline int sub(int a,int b){
  a-=b;
  return a<0?a+mod:a;
}
inline int qpow(int a,int b){
  int ret=1;
  for(;b;b>>=1,a=mul(a,a))if(b&1)ret=mul(ret,a);
  return ret;
}

int fac[N],ifac[N];
inline void init(int n=4e5){
  fac[0]=ifac[0]=1;
  for(int i=1;i<=n;i++)fac[i]=mul(fac[i-1],i);
  ifac[n]=qpow(fac[n],mod-2);
  for(int i=n-1;i;i--)ifac[i]=mul(ifac[i+1],i+1);
}

int rev[L],_w[L];
ull f[L];
template<const int type>
inline void dft(int *a){
  for(int i=0;i<lim;i++)f[i]=a[rev[i]];
  for(int len=1;len<lim;len<<=1){
    for(int i=0;i<lim;i+=len<<1)
      for(int x,y,j=0;j<len;j++){
        ull tmp=_w[j+len]*f[i+j+len]%mod;
        f[i+j+len]=f[i+j]+mod-tmp;
        f[i+j]+=tmp;
      }
    // for(int i=0;i<lim;i++)f[i]%=mod;
  }
  if(type){
    int inv=qpow(lim,mod-2);
    for(int i=0;i<lim;i++)a[i]=f[i]%mod*inv%mod;
    reverse(a+1,a+lim);
  }else{
    for(int i=0;i<lim;i++)a[i]=f[i]%mod;
  }
}

int g0[L],g1[L];
inline void mul(poly &a,poly &b){
  int len=(int)a.size()+(int)b.size()-1;
  int lim=1;
  while(lim<(len<<1))lim<<=1;
  // log("=== ffp [%d] [%d] (lim=%d) ===\n",(int)a.size(),(int)b.size(),lim);
  // for(int i=0;i<a.size();i++)log("%d ",a[i]);log("\n");
  // for(int i=0;i<b.size();i++)log("%d ",b[i]);log("\n");
  if(lim!=::lim){
    ::lim=lim;
    int k=0;
    for(int tmp=lim>>1;tmp;tmp>>=1)++k;
    for(int i=0;i<lim;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(k-1));
    copy(ifac,ifac+(lim>>1),g0);
    copy(ifac,ifac+(lim>>1),g1);
    assert(!g0[lim>>1]);
    for(int i=1;i<(lim>>1);i+=2)g1[i]=sub(0,g1[i]);
    dft<0>(g0);
    dft<0>(g1);
  }
  a.resize(lim);
  dft<0>(&a[0]);
  for(int i=0;i<lim;i++)a[i]=(ll)a[i]*g0[i]%mod;
  dft<1>(&a[0]);
  b.resize(lim);
  // for(int i=0;i<a.size();i++)log("%d ",a[i]);log("\n");
  dft<0>(&b[0]);
  for(int i=0;i<lim;i++)b[i]=(ll)b[i]*g0[i]%mod;
  dft<1>(&b[0]);
  // for(int i=0;i<b.size();i++)log("%d ",b[i]);log("\n");
  for(int i=0;i<len;i++)a[i]=(ll)fac[i]*a[i]%mod*b[i]%mod;
  fill(&a[0]+len,&a[0]+lim,0);
  dft<0>(&a[0]);
  for(int i=0;i<lim;i++)a[i]=(ll)a[i]*g1[i]%mod;
  dft<1>(&a[0]);
  a.resize(len);
  // for(int i=0;i<a.size();i++)log("%d ",a[i]);log("\n");
}

inline void solve(vector<int> s,int ans[N]){
  if(!s.size()){
    ans[0]=1;
    return;
  }
  sort(s.begin(),s.end());
  vector<int> q;
  int l=0,r=s.size()-1;
  while(l<=r){
    if(l==r)q.push_back(s[l++]);
    else{
      if((ll)s[l]*s[r]<=w)q.push_back(s[l++]);
      else q.push_back(s[r--]);
    }
  }
  int cur=0;
  for(int j=0;j<(int)q.size();j++){
    a[j]=cur;
    if(j+1<(int)q.size()){
      if((ll)q[j]*q[j+1]<=w)cur=cur+1;
      else cur=cur-1;
    }
  }
  ql=0,qr=q.size();
  for(int i=0;i<q.size();i++){
    all[i]=new poly{(a[i]+mod)%mod,1};
  }
  while(qr-ql>1){
    poly *c=new poly();
    mul(*all[ql],*all[ql+1]);
    all[qr++]=all[ql];
    delete all[ql+1];
    ql+=2;
  }
  for(int i=1;i<=(int)s.size();i++)ans[i]=(ll)fac[i]*(*all[ql])[i]%mod;
  delete all[ql];
}

int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
  // freopen("1.out","w",stdout);
#endif
  for(int len=1;len*2<=L;len<<=1){
    int wn=qpow(3,(mod-1)/(len<<1));
    for(int j=len,w=1;j<len<<1;j++,w=mul(w,wn))_w[j]=w;
  }
  init();
  read(n),read(w);
  vector<int> A,B;
  for(int i=1;i<=n;i++){
    read(p[i]);
    if(p[i]>=0)A.push_back(p[i]);
    else B.push_back(-p[i]);
  }
  solve(A,f1);
  memset(g0,0,sizeof(g0));
  memset(g1,0,sizeof(g1));
  solve(B,f2);
  int ans=0;
  for(int i=0;i<=n;i++)
    for(int j=max(0,i-1);j<=i+1;j++){
      ans=(ans+(1ll+(i==j))*f1[i]*f2[j])%mod;
    }
  cout<<(ans%mod+mod)%mod<<endl;
}