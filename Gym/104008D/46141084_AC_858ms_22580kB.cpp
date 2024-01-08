#include <bits/stdc++.h>
const int mod = 998244353;
inline int S(int x){return x<mod?x:x-mod;}
inline int D(int x){return x>=0?x:x+mod;}
typedef long long ll;
ll Qpow(ll a,ll p)
{
    ll res=1;
    while(p)
    {
        if(p&1)res=res*a%mod;
        a=a*a%mod,p>>=1;
    }
    return res;
}
const int MAXN = 525011;
int fac[MAXN],Ifac[MAXN],inv[MAXN];
int RT[MAXN];
int init(int n)
{
    int len=1;
    while(len<=n+n+1)len<<=1;
    n=len;
    fac[0]=1;
    for(int i=1;i<=n;++i)fac[i]=ll(fac[i-1])*i%mod;
    inv[1]=1;
    for(int i=2;i<=n;++i)inv[i]=ll(mod-mod/i)*inv[mod%i]%mod;
    Ifac[0]=1;
    for(int i=1;i<=n;++i)Ifac[i]=ll(Ifac[i-1])*inv[i]%mod;
    for(int i=1;i<len;i<<=1)
    {
        int R=Qpow(3,(mod-1)/(i<<1));
        RT[i]=1;
        for(int j=1;j<i;++j)RT[i+j]=ll(RT[i+j-1])*R%mod;
    }
    return len;
}
int rev[MAXN];
void DFT(int* a,int n)
{
    for(int i=0;i<n;++i)
        rev[i]=(rev[i>>1]>>1)|(i&1?(n>>1):0);
    for(int i=0;i<n;++i)
        if(rev[i]>i)std::swap(a[i],a[rev[i]]);
    for(int cur=1;cur<n;cur<<=1)
        for(int j=0;j<n;j+=cur<<1)
            for(int k=0;k<cur;++k)
            {
                int x=a[j+k],y=ll(RT[cur+k])*a[j+cur+k]%mod;
                a[j+k]=S(x+y),a[j+cur+k]=D(x-y);
            }
}
void IDFT(int* a,int n)
{
    std::reverse(a+1,a+n);
    DFT(a,n);
    for(int i=0;i<n;++i)a[i]=ll(a[i])*inv[n]%mod;
}
int C(int n,int m)
{
    return ll(fac[n])*Ifac[m]%mod*Ifac[n-m]%mod;
}
int f[MAXN],g[MAXN],h[MAXN];
void Mul(int* f,int* g,int* res,int n)
{
    for(int i=0;i<=n;++i)res[i]=0;
    for(int i=0;i<=n;++i)
        for(int j=0;j<=n-i;++j)
            res[i+j]=(res[i+j]+ll(f[i])*g[j])%mod;
}
void Mul_b(int* f,int* g,int* res,int n)
{
    for(int i=0;i<=n;++i)res[i]=0;
    for(int i=0;i<=n;++i)
        for(int j=0;j<=i;++j)
            res[i]=(res[i]+ll(C(i,j))*f[j]%mod*g[i-j])%mod;
}

//calc f=f*g
int tf[MAXN],tg[MAXN],res[MAXN];
void solve(int l,int r)
{
    if(l+1==r){f[l]=S(f[l]+Ifac[l]);return;}
    int mid=(l+r)>>1,len=r-l;
    solve(l,mid);
    for(int i=l;i<mid;++i)tf[i-l]=f[i];
    for(int i=(len>>1);i<len;++i)tf[i]=0;
    for(int i=0;i<len;++i)tg[i]=g[i];
    DFT(tf,len),DFT(tg,len);
    for(int i=0;i<len;++i)tf[i]=ll(tf[i])*tg[i]%mod;
    IDFT(tf,len);
    for(int i=mid;i<r;++i)f[i]=S(f[i]+tf[i-l]);
    solve(mid,r);
}
int main()
{
    // freopen("D.in","r",stdin);
    int n,m,a,b;
    scanf("%d%d%d%d",&n,&m,&a,&b);
    int p=ll(a)*Qpow(b,mod-2)%mod,rp=Qpow(p,mod-2);
    int len=init(m);
    for(int i=0;i<len;++i)g[i]=ll(D(rp-1))*Ifac[i]%mod;
    solve(0,len);
    for(int i=0;i<=m;++i)f[i]=ll(f[i])%mod;
    for(int i=m+1;i<len;++i)f[i]=0;
    // g[0]=1;
    // for(int w=1;w<=n;++w)
    // {
    //     Mul_b(f,g,h,m);
    //     for(int i=0;i<=m;++i)g[i]=h[i],h[i]=0;
    // }
    res[0]=1;
    while(n)
    {
        if(n&1)
        {
            DFT(f,len),DFT(res,len);
            for(int i=0;i<len;++i)res[i]=ll(res[i])*f[i]%mod;
            IDFT(res,len),IDFT(f,len);
            for(int i=m+1;i<len;++i)res[i]=0;
        }
        DFT(f,len);
        for(int i=0;i<len;++i)f[i]=ll(f[i])*f[i]%mod;
        IDFT(f,len);
        for(int i=m+1;i<len;++i)f[i]=0;
        n>>=1;
        // printf("Res:");
        // for(int i=0;i<len;++i)printf("%d ",res[i]);
        // puts("");
        
        // printf("F:");
        // for(int i=0;i<len;++i)printf("%d ",f[i]);
        // puts("");
    }
    for(int i=0;i<=m;++i)printf("%lld\n",ll(res[i])*fac[i]%mod);
    return 0;
}