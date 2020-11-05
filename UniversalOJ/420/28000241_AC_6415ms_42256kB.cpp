#include<bits/stdc++.h>
#define DD fprintf(stderr,"Passing [%s] in LINE %d\n",__FUNCTION__,__LINE__)
const int S=1<<21; char ibuf[S],*iS,*iT;
#define getchar() (iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,S,stdin),(iS==iT?EOF:*iS++)):*iS++)
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
int T,n,m,mod;
struct z{
    int x; inline z(int x=0):x(x){}
    friend inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
    friend inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
    friend inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
}a,b,c,h,hm,f[N],inv[N],powA[N],powB[N],powHm[N];
template<class T> z fpow(z a,T b){
    b%=(mod-1); if(b<0)b+=mod-1;
    z s=1; for(;b;b>>=1,a=a*a)if(b&1)s=s*a; return s;
}
z C(int n,int m){z s=1;for(int i=1;i<=m;i++)s=s*(n-i+1)*fpow(i,mod-2);return s;}
void fill(z *G,z b,int m){
    if(b.x==1){
        z tmp=1; G[0]=(m+1)%mod;
        for(int i=1;i<=n;i++)G[i]=G[i-1]*inv[i+1]*(i+m+1);
    }else{
        z tmp=1,X=fpow(b,m+1),Y=fpow(1-b,mod-2); G[0]=(1-X)*Y;
        for(int i=1;i<=n;i++)tmp=tmp*(i+m)*inv[i],G[i]=(G[i-1]-tmp*X)*Y;
    }
}
z calcC(){
    static z ans,tmp=1,F[N],H[N],G[N];
    if(h.x==1){
        fill(G,b,m-1);
        if(b.x==1){
            z tmp=m; H[0]=z(m)*m-G[1];
            for(int i=1;i<=n;i++)tmp=tmp*(i+m)*inv[i+1],H[i]=tmp*m-G[i+1];
        }else{
            z tmp=1,X=fpow(b,m)*m,Y=fpow(1-b,mod-2); H[0]=(b*G[0]-X)*Y;
            for(int i=1;i<=n;i++)tmp=tmp*(m-1+i)*inv[i],H[i]=(H[i-1]+b*G[i]-tmp*X)*Y;
        }
        for(int i=0;i<n;i++)F[i+1]=F[i]+powA[i]*(G[i]*m-H[i]);
        for(int i=1;i<=n;i++)ans=ans+powHm[i]*F[i];
    }else{
        fill(G,b*h,m-1),fill(H,b,m-1);
        for(int i=0;i<n;i++)F[i+1]=F[i]+powA[i]*(G[i]-H[i]*hm);
        for(int i=1;i<=n;i++)ans=ans+powHm[i]*F[i]; ans=ans*h*fpow(1-h,-1);
    }
    return ans*c;
}
z calcF(){
    static z ans,F[N],G[N];
    fill(G,b*h,m-1);
    for(int i=0;i<n;i++)F[n-i]=F[n-i+1]+powA[i]*powHm[i]*G[i];
    for(int i=1;i<=n;i++)ans=ans+powHm[i]*F[i]*f[i];
    return ans*b*h;
}
int main(){
#ifdef memset0
   freopen("1.in","r",stdin);
#endif
    read(T),read(n),read(m),read(h.x),read(mod),read(a.x),read(b.x),read(c.x);
    if(!h.x){read(f[1].x),printf("%d\n",(f[1]*b+c).x); return 0;}
    inv[0]=inv[1]=powA[0]=powB[0]=powHm[0]=1,hm=fpow(h,m);
    for(int i=1;i<=n;i++)read(f[i].x);
    for(int i=2;i<=n+1;i++)inv[i]=(mod-mod/i)*inv[mod%i];
    for(int i=1;i<=n;i++)powA[i]=powA[i-1]*a,powB[i]=powB[i-1]*b,powHm[i]=powHm[i-1]*hm;
    printf("%d\n",((calcC()+calcF())*fpow(h,-m-1)).x);
}