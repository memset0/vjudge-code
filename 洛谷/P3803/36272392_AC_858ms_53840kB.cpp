// luogu-judger-enable-o2
// luogu-judger-enable-o2
#include<bits/stdc++.h>
#define ll long long
template<class T> inline void read(T &x){
    x=0;register char c=getchar();register bool f=0;
    while(!isdigit(c))f^=c=='-',c=getchar();
    while(isdigit(c))x=x*10+c-'0',c=getchar();
    if(f)x=-x;
}
template<class T> inline void print(T x){
    if(x<0)x=-x,putchar('-');
    if(x>9)print(x/10);
    putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}
const int N=1e6+10,mod=998244353;
int n,m,a[N<<1],b[N],w[N<<2],rev[N<<2];
inline int dec(int a,int b){return(a-=b)<0?a+mod:a;}
inline int inc(int a,int b){return(a+=b)>=mod?a-mod:a;}
inline int fpow(int a,int b){int s=1;for(;b;b>>=1,a=(ll)a*a%mod)if(b&1)s=(ll)s*a%mod;return s;}
inline int polyinit(int len){
    int lim=1,k=0;while(lim<len)lim<<=1,++k;
    for(int i=0;i<lim;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(k-1));
    for(int wn,len=1;len<lim;len<<=1){
        wn=fpow(3,(mod-1)/len/2),w[len]=1;
        for(int i=1;i<len;i++)w[i+len]=(ll)w[i+len-1]*wn%mod;
    }return lim;
}
inline void ntt(int *a,int lim){
    for(int i=0;i<lim;i++)if(i<rev[i])std::swap(a[i],a[rev[i]]);
    for(int i=0;i<lim;i+=2){int x=a[i],y=a[i+1];a[i]=inc(x,y),a[i+1]=dec(x,y);}
    for(int len=2;len<lim;len<<=1)
        for(int i=0;i<lim;i+=len<<1)
            for(int j=0;j<len;j++){
                int x=a[i+j],y=(ll)a[i+j+len]*w[j+len]%mod;
                a[i+j]=inc(x,y),a[i+j+len]=dec(x,y);
            }
}
inline void polymul(int *f,int *g,int *h,int n,int m,int l=-1){
    static int a[N<<2],b[N<<2];
    int lim=polyinit(l=~l?l:n+m-1),inv_lim=fpow(lim,mod-2);
    memcpy(a,f,n<<2),memset(a+n,0,(lim-n)<<2);
    memcpy(b,g,m<<2),memset(b+m,0,(lim-m)<<2);
    ntt(a,lim),ntt(b,lim);
    for(int i=0;i<lim;i++)a[i]=(ll)a[i]*b[i]%mod;
    std::reverse(a+1,a+lim),ntt(a,lim);
    for(int i=0;i<l;i++)h[i]=(ll)a[i]*inv_lim%mod;
}
int main(){
    // freopen("1.in","r",stdin);
    read(n),read(m);
    for(int i=0;i<=n;i++)read(a[i]);
    for(int i=0;i<=m;i++)read(b[i]);
    polymul(a,b,a,n+1,m+1);
    for(int i=0;i<=n+m;i++)print(a[i]," \n"[i==n+m]);
}