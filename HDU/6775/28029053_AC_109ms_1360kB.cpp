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
int T,n,m,p,q;
int main(){
#ifdef memset0
    freopen("1.in","r",stdin);
#endif
    read(T);
    while(T--){
        read(n),read(m),read(p),q=m-m*(100-p)/100;
        print(n<m?0:(n-m)/q+1,'\n');
    }
}