#include<bits/stdc++.h>
using namespace std;
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
  char obuf[BUFFER],*oS=obuf,*oT=oS+BUFFER-1;
  inline void flush(){
    fwrite(obuf,1,oS-obuf,stdout);
    oS=obuf;
  }
  inline void putc(int x){
    *oS++=x;
    if(oS==oT)flush();
  }
  struct Flusher{~Flusher(){flush();}}flusher;
}
using fastio::getc;
using fastio::putc;
template<class T> inline void read(T &x){
  x=0;char c=getc();bool f=0;
  while(!isdigit(c))f^=c=='-',c=getc();
  while(isdigit(c))x=x*10+c-'0',c=getc(); if(f)x=-x;
}
template<class T> inline void print(T x){
  if(x<0)putc('-'),x=-x;
  if(x>9)print(x/10); putc(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putc(c);}
const int N=2e3+5,inf=1e9+5;
int n,m,q,ux,uy,tim,vis[N],lst[N],nxt[N],a[N][N];
struct section{
  int l,r;
};
inline int r(int x){return (x%n+n)%n;}
inline int c(int y){return (y%m+m)%m;}
inline int findNext(int x,int y){
  int max=-1,res=-1;
  for(int i=x-1;i<=x+1;i++)
    if(max<a[r(i)][c(y+1)]){
      res=i,max=a[r(i)][c(y+1)];
    }
  return res;
}
inline int moveToFirst(int x,int y){
  while(y<m){
    x=r(findNext(x,y));
    y++;
  }
  return x;
}
void modify(int x,int y){
  section cur{x,x},tmp;
  int pos=moveToFirst(x,y);
  while(y--){
    tmp={inf,-inf};
    for(int i=cur.l+1;i>=cur.l-1;i--){
      int p=findNext(i,y);
      if(p>=cur.l&&p<=cur.r)tmp.l=i;
    }
    for(int i=cur.r-1;i<=cur.r+1;i++){
      int p=findNext(i,y);
      if(p>=cur.l&&p<=cur.r)tmp.r=i;
    }
    if(tmp.l>tmp.r)return;
    cur=tmp;
  }
  if(cur.r-cur.l>=n){
    for(int i=0;i<n;i++)nxt[i]=pos;
  }else{
    for(int i=cur.l;i<=cur.r;i++)nxt[r(i)]=pos;
  }
}
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  read(n),read(m);
  for(int i=0;i<n;i++)
    for(int j=0;j<m;j++){
      read(a[i][j]);
    }
  for(int i=0;i<n;i++){
    nxt[i]=moveToFirst(i,0);
  }
  read(q);
  while(q-->0){
    int x,y,t;
    char op;
    op=getc();
    while(!isalpha(op))op=getc();
    if(op=='m'){
      read(t);
      if(t>=m-uy){
        while(uy){
          ux=r(findNext(ux,uy));
          uy=c(uy+1);
          t--;
        }
      }
      tim++;
      while(t>=m){
        t-=m;
        ux=nxt[ux];
        if(vis[ux]==tim){
          t%=(lst[ux]-t);
        }else{
          vis[ux]=tim;
          lst[ux]=t;
        }
      }
      while(t--){
        ux=r(findNext(ux,uy));
        uy=c(uy+1);
      }
      print(ux+1);
      putc(' ');
      print(uy+1);
      putc('\n');
    }else{
      read(x),read(y);
      x--,y--;
      read(a[x][y]);
      modify(r(x-1),c(y-1));
      modify(r(x),c(y-1));
      modify(r(x+1),c(y-1));
    }
  }
}