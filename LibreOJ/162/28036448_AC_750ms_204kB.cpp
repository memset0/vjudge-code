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
const int mod=998244352;
int x,n;
int fpow(int a,int b){
  int s=1;
  for(;b;b>>=1,a=(long long)a*a%mod)
    if(b&1)s=(long long)s*a%mod;
  return s;
}
int main(){
  read(x),read(n);
  for(int i=1,t;i<=n;i++){
    read(t);
    print(fpow(x,t),' ');
  }
}
