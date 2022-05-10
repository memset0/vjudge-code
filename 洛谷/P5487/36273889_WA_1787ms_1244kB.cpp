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

const int N=5e3+10,mod=998244353;

inline int dec(int a,int b){return (a-=b)<0?a+mod:a;}
inline int inc(int a,int b){return (a+=b)>=mod?a-mod:a;}
inline int fpow(int a,int b){int s=1;for(;b;b>>=1,a=(ll)a*a%mod)if(b&1)s=(ll)s*a%mod;return s;}

inline poly operator~(const poly &a){
    int res=a.size();
    while(res&&!a[res-1])--res;
    return poly(a.begin(),a.begin()+res);
}

inline poly operator+(poly a,const poly &b){
    if(b.size()>a.size())a.resize(b.size());
    for(int i=0;i<b.size();i++)a[i]=inc(a[i],b[i]);
    return ~a;
}

inline poly operator-(poly a,const poly &b){
    if(b.size()>a.size())a.resize(b.size());
    for(int i=0;i<b.size();i++)a[i]=dec(a[i],b[i]);
    return ~a;
}

inline poly operator*(const poly &a,const poly &b){
    poly c(a.size()+b.size()-1);
    for(int i=0;i<a.size();i++)
        for(int j=0;j<b.size();j++)
            c[i+j]=(c[i+j]+(ll)a[i]*b[j])%mod;
    return ~c;
}

inline poly operator<<(const poly &a,int b){
    poly res(b,0);
    res.insert(res.end(),a.begin(),a.end());
    return res;
}

poly berlekamp_massey(const poly &a){
    poly Ci={1},Cj={1};
    for(int i=0,j=-1,b=1,d;d=0,i<a.size();i++){
        for(int j=0;j<Ci.size();j++)d=(d+(ll)a[i-j]*Ci[j])%mod;
        if(d){
            poly nxt=Ci-((Cj*poly{(int)((ll)d*fpow(b,mod-2)%mod)})<<(i-j));
            if((int)Ci.size()-i<(int)Cj.size()-j)Cj=Ci,j=i,b=d;
            Ci=nxt;
        }        
    }
    poly res(Ci.begin()+1,Ci.end());
    int inv=fpow((mod-Ci[0]),mod-2);
    for(int i=0;i<res.size();i++)res[i]=(ll)res[i]*inv%mod;
    return res;
}

int main(){
#ifdef memset0
    freopen("1.in","r",stdin);
#endif
    int n; read(n); poly a(n);
    for(int i=0;i<n;i++)read(a[i]),a[i]%=mod;
    poly res=berlekamp_massey(a);
    // print(res.size(),'\n');
    for(int i=0;i<res.size();i++)print(res[i]," \n"[i==res.size()-1]);
}