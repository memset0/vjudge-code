#include<bits/stdc++.h>
#define val_t long long
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
const int N=110,L=40;
int n,m,q;
val_t p[N],h[N],g[N][N][N],f[N];
inline val_t _xor(val_t a,val_t b){return a^b;}
int32_t main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  read(n),read(m),read(q);
  for(int i=1;i<=n;i++)read(f[i]);
  for(int i=1,u,v;i<=m;i++)read(u),read(v),g[u][v][0]=g[v][u][0]=1;
  for(int i=1;i<L;i++)
    for(int a=1;a<=n;a++)
      for(int b=1;b<=n;b++)
        for(int c=1;c<=n;c++){
          g[a][c][i]=(g[a][b][i-1]*g[b][c][i-1]+g[a][c][i])&1;
        }
  for(val_t v;q--;){
    memset(p,0,sizeof(p)),memset(h,0,sizeof(h));
    read(v),p[1]=1;
    for(int i=0;i<L;i++)if((v>>i)&1){
      memset(h,0,sizeof(h));
      for(int a=1;a<=n;a++)
        for(int b=1;b<=n;b++){
          h[b]=(h[b]+p[a]*g[a][b][i])&1;
        }
      for(int a=1;a<=n;a++)p[a]=h[a];
    }
    for(int i=1;i<=n;i++)if(p[i])p[i]=f[i];
    print(std::accumulate(p+1,p+n+1,0ll,_xor),'\n');
  }
}