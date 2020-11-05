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
const int N=1e5+10;
int T,n,a[N];
int main(){
#ifdef memset0
    freopen("1.in","r",stdin);
#endif
    read(T);
    while(T--){
        read(n);
        for(int i=1;i<=n;i++)read(a[i]);
        std::sort(a+1,a+n+1);
        long long ans=0;
        for(int i=1;i<=n;i++){
            if(i>1)ans=ans+(long long)a[i]*(i-1);
            if(i<n)ans=ans-(long long)a[i]*(n-i);
        }
        printf("%lld\n",ans);
    }
}