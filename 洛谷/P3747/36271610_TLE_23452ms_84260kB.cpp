// luogu-judger-enable-o2
// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
const long long N=5e4+7,M=100;
const long long power=1;
bool flag,used[N][M];
long long n,m,p,k,s,q,e,opt,ans,w[N],f[M],t[N][M],dp[N][M];
struct tree{long long a,b,c,sum,tag;}tr[N<<2];
inline long long read()
{
    long long num=0; char g=getchar();
    while(g<48||57<g) g=getchar();
    while(47<g&&g<58) num=(num<<1)+(num<<3)+g-48,g=getchar();
    return num; 
}
long long Max(long long a,long long b) {if(a>b) return a; return b;}
long long Min(long long a,long long b) {if(a<b) return a; return b;}
long long pow(long long a,long long b,long long c)
{
    long long u=0,ans=1;
    while(true)
    {
        if(b&(power<<u)) {if(ans*a>=c) flag=true; ans=(ans*a)%c;}
        u++; if(b<(power<<u)) break;
        if(a*a>=c) flag=true; a=(a*a)%c;
    }
    return ans;
}
long long phi(long long u) {long long ans=u,tot=u; for(long long i=2;i<=sqrt(u);i++) if(!(tot%i)) {ans=(ans/i)*(i-1); while(!(tot%i)) tot/=i;} if(tot>1) ans=ans/tot*(tot-1); return ans;}
long long find(long long r,long long a,long long b)
{
    if(!used[r][a]) return pow(k,find(r,a-1,phi(b)),b)+b;
    else if(t[r][a]>=b) return (t[r][a]%b)+b;
    else return t[r][a]%b;
}
void build(long long a,long long b,long long c)
{
    tr[c].a=a,tr[c].b=b,tr[c].c=(a+b)>>1; 
    if(a==b) {tr[c].sum=dp[a][0]; return;}
    build(tr[c].a,tr[c].c,(c<<1));
    build(tr[c].c+1,tr[c].b,(c<<1)+1);
    tr[c].sum=tr[c<<1].sum+tr[(c<<1)+1].sum;
}
void change(long long a,long long b,long long c)
{
    if(tr[c].a==tr[c].b&&tr[c].tag<opt)
    {
        tr[c].tag++,tr[c].sum=dp[a][tr[c].tag];c=c>>1;
        while(c>0) tr[c].sum=(tr[c<<1].sum+tr[(c<<1)+1].sum)%p,tr[c].tag=Min(tr[c<<1].tag,tr[(c<<1)+1].tag),c=c>>1; 
    }
    else return;
    if(tr[c].a<=b&&a<=tr[c].c&&tr[c<<1].tag<opt) change(a,Min(b,tr[c].c),(c<<1));
    if(tr[c].c<b&&a<=tr[c].b&&tr[(c<<1)+1].tag<opt)  change(Max(a,tr[c].c+1),b,(c<<1)+1);
}
void search(long long a,long long b,long long c)
{
    if(tr[c].a==a&&tr[c].b==b) {ans=(ans+tr[c].sum)%p; return;}
    if(tr[c].a<=b&&a<=tr[c].c) search(a,Min(b,tr[c].c),(c<<1));
    if(tr[c].c<b&&a<=tr[c].b)  search(Max(a,tr[c].c+1),b,(c<<1)+1);
}
int main()
{
    long long a,b,c;
    n=read(),m=read(),p=read(),k=read(),e=p,opt+=5;
    while(phi(e)>1) e=phi(e),opt++,e=phi(e); 
    for(long long i=1;i<=n;i++) dp[i][0]=t[i][0]=read(),used[i][0]=true;
    for(long long i=1;i<=n;i++)
        for(long long x=1;x<=opt;x++) {flag=false; t[i][x]=pow(k,t[i][x-1],p); if(flag) {t[i][x]=0; break;} used[i][x]=true;}
    for(long long i=1;i<=n;i++)
        for(long long x=1;x<=opt;x++)
            dp[i][x]=pow(k,find(i,x-1,phi(p)),p);
    build(1,n,1);
    for(int i=1;i<=m;i++)
    {
        a=read(),b=read(),c=read();
        if(!a) change(b,c,1);
        else ans=0,search(b,c,1),printf("%lld\n",ans);
    }
    return 0;
}