#include<bits/stdc++.h>
const int S=(1<<20)*10; char ibuf[S<<1],*iS=ibuf,obuf[S],*oS=obuf;
#define getchar() *iS++
#define putchar(x) *oS++=(x)
template<class T> inline void read(T &x){
  x=0; char c=getchar();
  while(!isdigit(c))c=getchar();
  while(isdigit(c))x=x*10+c-'0',c=getchar();
}
template<class T> inline void print(T x){
  if(x>9)print(x/10); putchar(x%10+'0');
}
const int N=20,mod=1e9+9;
int n,lim,a[N+1][1<<N],b[N+1][1<<N],c[N+1][1<<N];
void fwt(int *a){
  for(int len=1;len<lim;len<<=1)
    for(int i=0;i<lim;i+=(len<<1))
      for(int j=0;j<len;j++){
        a[i+j+len]+=a[i+j];
        if(a[i+j+len]>=mod)a[i+j+len]-=mod;
      }
}
void ifwt(int *a){
  for(int len=1;len<lim;len<<=1)
    for(int i=0;i<lim;i+=(len<<1))
      for(int j=0;j<len;j++){
        a[i+j+len]-=a[i+j];
        if(a[i+j+len]<0)a[i+j+len]+=mod;
      }
}
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  fread(ibuf,1,S<<1,stdin),read(n),lim=1<<n;
  for(int i=0;i<lim;i++)read(a[__builtin_popcount(i)][i]);
  for(int i=0;i<lim;i++)read(b[__builtin_popcount(i)][i]);
  for(int i=0;i<=n;i++)fwt(a[i]),fwt(b[i]);
  for(int i=0;i<=n;i++)for(int j=0;j<=i;j++){
    for(int k=0;k<lim;k++)c[i][k]=(c[i][k]+(long long)a[j][k]*b[i-j][k])%mod;
  }
  for(int i=0;i<=n;i++)ifwt(c[i]);
  for(int i=0;i<lim;i++)print(c[__builtin_popcount(i)][i]),putchar(" \n"[i+1==lim]);
  fwrite(obuf,1,oS-obuf,stdout),oS=obuf,void();
}
