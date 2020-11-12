#include<bits/stdc++.h>
template<class T> inline void read(T &x){
  x=0; register char c=getchar(); register bool f=0;
  while(!isdigit(c))f^=c=='-',c=getchar();
  while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}

const int N=310;
int T,n,m;
std::bitset<N> a[N];

bool ganss(){
  for(int i=1;i<=n;i++){
    if(!a[i][i]){
      for(int j=i+1;j<=n;j++)if(a[j][i]){
        std::swap(a[i],a[j]);
        break;
      }
    }
    for(int j=i+1;j<=n;j++)if(a[j][i]){
      a[j]^=a[i];
    }
  }
  // for(int i=1;i<=n;i++){
  //   for(int j=1;j<=n+1;j++)
  //     putchar('0'+a[i][j]);
  //   putchar('\n');
  // }
  for(int i=1;i<=n;i++)if(a[i].count()==1&&a[i][n+1])return 0;
  return 1;
}

int main(){
#ifdef local
  freopen("1.in","r",stdin);
#endif
  for(read(T);T--;){
    read(n),read(m);
    for(int i=1;i<=n;i++)a[i].reset();
    for(int i=1,u,v,w;i<=m;i++){
      read(u),read(v),read(w);
      a[u].flip(v),a[v].flip(u);
      a[u].flip(u),a[v].flip(v);
      if(w)a[u].flip(n+1),a[v].flip(n+1);
    }
    // for(int i=1;i<=n;i++){
    //   for(int j=1;j<=n+1;j++)
    //     putchar('0'+a[i][j]);
    //   putchar('\n');
    // }
    puts(ganss()?"yes":"no");
  }
}