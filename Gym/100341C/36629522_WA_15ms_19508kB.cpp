#include<bits/stdc++.h>
using namespace std;
const int N=65536<<2,mod=786433;
int n,k,h,lim,f[17][N],w[N],rev[N];
inline int dec(int x,int y){return (x-=y)<0?x+mod:x;}
inline int inc(int x,int y){return (x+=y)>=mod?x-mod:x;}
inline int fpow(int a,int b){int s=1;for(;b;b>>=1,a=1ll*a*a%mod)if(b&1)s=1ll*s*a%mod;return s;}
void dft(int *a){
  for(int i=0;i<lim;i++)if(i<rev[i])swap(a[i],a[rev[i]]);
  for(int len=1;len<lim;len<<=1)
    for(int i=0;i<lim;i+=len<<1)
      for(int j=0;j<len;j++){
        int x=a[i+j],y=1ll*a[i+j+len]*w[j+len]%mod;
        a[i+j]=inc(x,y),a[i+j+len]=dec(x,y);
      }
}
void idft(int *a){
  reverse(a+1,a+lim),dft(a);
  int inv_lim=fpow(lim,mod-2);
  for(int i=0;i<lim;i++)a[i]=1ll*a[i]*inv_lim%mod;
}
int main(){
  freopen("avl.in","r",stdin);
  freopen("avl.out","w",stdout);
  cin>>n>>h;
  ++h,lim=1;
  while(lim<n*2+1)lim<<=1,++k;
  for(int i=0;i<lim;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(k-1));
  for(int wn,len=1;len<lim;len<<=1){
    wn=fpow(10,(mod-1)/(len<<1)),w[len]=1;
    for(int i=1;i<len;i++)w[i+len]=1ll*w[i+len-1]*wn%mod;
  }
  f[0][0]=1,dft(f[0]);
  f[1][1]=1,dft(f[1]);
  for(int j=2;j<=h;j++){
    for(int i=0;i<lim;i++)f[j][i]=(1ll*f[j-1][i]*f[j-1][i]+2ll*f[j-1][i]*f[j-2][i])%mod;
    idft(f[j]);
    for(int i=lim-1;i>0;i--)f[j][i]=f[j][i-1];
//    for(int i=0;i<lim;i++)cout<<f[j][i]<<" \n"[i+1==lim];
    f[j][0]=0,dft(f[j]);
  }
  idft(f[h]);
  cout<<f[h][n]<<endl;
//  for(int i=1;i<=h;i++){
//    if(i!=h)idft(f[i]);
//    for(int j=0;j<lim;j++)cout<<f[i][j]<<" \n"[j+1==lim];
//  }
}