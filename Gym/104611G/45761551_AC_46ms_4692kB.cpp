#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
typedef long long ll;
const int MAXN = 200011,mod = 1e9+7;
typedef std::pair<int,int> pii;
pii a[MAXN];
struct BIT
{
    int t[MAXN];
#define lowb (i&-i)
    void modify(int i,int k)
    {
        while(i<MAXN)t[i]+=k,i+=lowb;
    }
    int Qsum(int i)
    {
        int res=0;
        while(i)res+=t[i],i-=lowb;
        return res;
    }
    int Qkth(int k)
    {
        int pos=0;
        for(int i=18;i>=0;--i)
            if(pos+(1<<i)<MAXN&&t[pos+(1<<i)]<k)pos+=1<<i,k-=t[pos];
        return pos+1;
    }
}bt;
int fac[MAXN],Ifac[MAXN],inv[MAXN];
void init(int n)
{
    fac[0]=1;
    for(int i=1;i<=n;++i)fac[i]=ll(fac[i-1])*i%mod;
    inv[1]=1;
    for(int i=2;i<=n;++i)inv[i]=ll(mod-mod/i)*inv[mod%i]%mod;
    Ifac[0]=1;
    for(int i=1;i<=n;++i)Ifac[i]=ll(Ifac[i-1])*inv[i]%mod;
}
int C(int n,int m){return ll(fac[n])*Ifac[m]%mod*Ifac[n-m]%mod;}
int A(int n,int m){return ll(fac[n])*Ifac[n-m]%mod;}
int main()
{
    int n;
    scanf("%d",&n);
    init(n);
    for(int i=1;i<=n;++i)scanf("%d%d",&a[i].second,&a[i].first);
    std::sort(a+1,a+n+1),std::reverse(a+1,a+n+1);
    int ans=1,size=0,c=0;
    for(int l=1,r;l<=n;l=r+1)
    {
        r=l;
        while(r<n&&a[r+1].first==a[r].first)++r;
        int v=a[l].first;
        int f=bt.Qsum(MAXN-1)-bt.Qsum(v-1);
        int k=r-l+1;
        if(f>=k)
        {
            ans=ll(ans)*A(f,k)%mod;
            for(int w=1;w<=k;++w)
            {
                int p=bt.Qkth(bt.Qsum(v-1)+1);
                bt.modify(p,-1);
            }
            for(int i=l;i<=r;++i)bt.modify(a[i].second,1);
        }
        else
        {
            ans=ll(ans)*A(k,f)%mod;
            for(int w=1;w<=f;++w)
            {
                int p=bt.Qkth(bt.Qsum(v-1)+1);
                bt.modify(p,-1);
            }
            for(int i=l;i<=r;++i)bt.modify(a[i].second,1);
        }
    }
    printf("%lld\n",ans);
    return 0;
}