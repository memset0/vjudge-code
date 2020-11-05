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
const int N=1e3+10,M=1e6+10;
int T,n,m;
long long f[M],g[M];
struct node{
    int w,v;
    inline bool operator<(const node &rhs)const{
        return w<rhs.w;
    }
}a[N],b[N];
inline void upd(long long &x,long long y){
    if(y>x)x=y;
}
void DP(node *a,long long *f,int n,int l){
    memset(f,-63,(l+1)<<3);
    f[0]=0;
    int s=0;
    for(int i=1;i<=n;i++){
        for(int j=s;j>=0;j--){
            upd(f[j+a[i].w],f[j]+a[i].v);
        }
        s+=a[i].w;
    }
    // for(int i=0;i<=s;i++)print(f[i]," \n"[i==s]);
}
int main(){
#ifdef memset0
    freopen("1.in","r",stdin);
#endif
    for(read(T);T--;){
        int sa=0,sb=0;
        read(n),read(m);
        for(int i=1;i<=n;i++){
            read(a[i].w),read(a[i].v);
            sa+=a[i].w;
        }
        for(int i=1;i<=m;i++){
            read(b[i].w),read(b[i].v);
            sb+=b[i].w;
        }
        DP(a,f,n,sa);
        DP(b,g,n,sb);
        long long ans=0;
        for(int i=1;i<=std::min(sa,sb);i++){
            upd(ans,f[i]+g[i]);
        }
        print(ans,'\n');
    }
}
// adfkdsiofiaosdjfasjdfkasddafdsfadfasdfasdf