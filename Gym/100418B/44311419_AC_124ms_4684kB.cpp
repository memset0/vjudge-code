#include<iostream>
#include<cstdio>
typedef long long ll;
void write(__int128 x)
{
    if(x==0){puts("0");return;}
    if(x<0)x=-x,putchar('-');
    int s[55],top=0;
    while(x)s[++top]=x%10,x/=10;
    while(top)putchar(s[top--]+'0');
    puts("");
}
const int MAXN = 100011;
struct BIT
{
    ll t[MAXN];
    #define lowb (i&-i)
    void modify(int i,ll k)
    {
        while(i<MAXN)t[i]+=k,i+=lowb;
    }
    ll Qsum(int i)
    {
        ll res=0;
        while(i)res+=t[i],i-=lowb;
        return res;
    }
    ll Qall(){return Qsum(MAXN-1);}
}t0,ts,tj,tsj;
ll a[MAXN],b[MAXN];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)scanf("%d",&a[i]);
    for(int i=1;i<=m;++i)
    {
        scanf("%d",&b[i]);
        t0.modify(b[i],1);
        ts.modify(b[i],b[i]);
        tj.modify(b[i],i);
        tsj.modify(b[i],ll(b[i])*i);
    }
    __int128 ans=0;
    for(int i=1;i<=n;++i)
    {
        int x=a[i];
        ans+=2*(t0.Qsum(x)*i*a[i]-ts.Qsum(x)*i-tj.Qsum(x)*a[i]+tsj.Qsum(x));
        ans-=(t0.Qall()*i*a[i]-ts.Qall()*i-tj.Qall()*a[i]+tsj.Qall());
    }
    write(ans);
    return 0;
}