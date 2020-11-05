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
const int N=1e6+10;
int n,q,l,r,x,k,op;
long long s[N];
inline void add(int k,int x){
  for(;k<=n;k+=k&-k)s[k]+=x;
}
inline long long ask(int k){
  long long res=0;
  for(;k;k-=k&-k)res+=s[k];
  return res;
}
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  read(n),read(q),++n;
  for(int i=1,x,y=0;i<n;i++)read(x),add(i,x-y),y=x;
  while(q--){
    read(op);
    if(op==1){
      read(l),read(r),read(x);
      add(l,x),add(r+1,-x);
    }else{
      read(k);
      print(ask(k),'\n');
    }
  }
}
