#include<bits/stdc++.h>
using namespace std;
const int lim=1<<20,k=20,mod=998244353;
int n,l,r,ansv,ansi,T,invlim,a[lim],rev[lim],w[lim];
inline int dec(int a,int b){return (a-=b)<0&&(a+=mod),a;}
inline int inc(int a,int b){return (a+=b)>=mod&&(a-=mod),a;}
inline int fpow(int a,int b){
  int s=1;
  for(;b;b>>=1,a=(long long)a*a%mod)if(b&1)s=(long long)s*a%mod;
  return s;
}
void init(){
  invlim=fpow(lim,mod-2);
  for(int i=0;i<lim;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(k-1));
  for(int wn,len=1;len<lim;len<<=1){
    wn=fpow(3,(mod-1)/(len<<1)),w[len]=1;
    for(int i=1;i<len;i++)w[i+len]=(long long)w[i+len-1]*wn%mod;
  }
}
void dft(int *a){
  for(int i=0;i<lim;i++)if(i<rev[i])swap(a[i],a[rev[i]]);
  for(int len=1;len<lim;len<<=1)
    for(int i=0;i<lim;i+=(len<<1))
      for(int j=0;j<len;j++){
        int x=a[i+j],y=(long long)w[j+len]*a[i+j+len]%mod;
        a[i+j]=inc(x,y),a[i+j+len]=dec(x,y);
      }
}
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  for(int i=1;i<=500000;i++)
    for(int j=1;i*j<=500000;j++)
      a[i*j]++;
  init();
  dft(a);
  for(int i=0;i<lim;i++)a[i]=(long long)a[i]*a[i]%mod;
  dft(a),reverse(a+1,a+lim);
  for(int i=0;i<lim;i++)a[i]=(long long)a[i]*invlim%mod;
  for(cin>>T,ansv=-1;T-->0;ansv=-1){
    cin>>l>>r;
    for(int i=l;i<=r;i++)if(a[i]>ansv)ansv=a[i],ansi=i;
    cout<<ansi<<" "<<ansv<<endl;
  }
}