// luogu-judger-enable-o2
#include<bits/stdc++.h>
#define ll long long
#define poly std::vector<int>
template<class T> inline void read(T &x){
    x=0;register char c=getchar();register bool f=0;
    while(!isdigit(c))f^=c=='-',c=getchar();
    while(isdigit(c))x=x*10+c-'0',c=getchar();
    if(f)x=-x;
}
template<class T> inline void print(T x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)print(x/10);
    putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}
const int mod=998244353;
inline int inc(int a,int b){return (a+=b)>=mod?a-mod:a;}
inline int fpow(int a,int b){int s=1;for(;b;b>>=1,a=(ll)a*a%mod)if(b&1)s=(ll)s*a%mod;return s;}
poly BM(const poly &a){
    poly Ci={1},Cj={1};
    for(int i=0,j=-1,d,b=1;d=0,i<a.size();i++){
        for(int j=0;j<Ci.size();j++)d=(d+(ll)Ci[j]*a[i-j])%mod;
        if(!d)continue;
        int mov=(ll)(mod-1)*d%mod*fpow(b,mod-2)%mod;
        poly nxt(i-j+Cj.size());
        for(int k=0;k<Cj.size();k++)nxt[k+i-j]=(ll)Cj[k]*mov%mod;
        if(Ci.size()>nxt.size())nxt.resize(Ci.size());
        for(int i=0;i<Ci.size();i++)nxt[i]=inc(nxt[i],Ci[i]);
        if((int)Ci.size()-i<(int)Cj.size()-j)Cj=Ci,j=i,b=d;
        Ci=nxt;
    }
    int mov=(mod-Ci[0])%mod; Ci.erase(Ci.begin());
    for(int i=0;i<Ci.size();i++)Ci[i]=(ll)Ci[i]*mov%mod;
    return Ci;
}
int main(){
#ifdef memset0
    freopen("1.in","r",stdin);
#endif
    int n,m; read(n),read(m);
    poly a(n); for(int i=0;i<n;i++)read(a[i]);
    poly res=BM(a);
    // print(res.size(),'\n');
    for(int i=0;i<res.size();i++)print(res[i]," \n"[i==res.size()-1]);
}