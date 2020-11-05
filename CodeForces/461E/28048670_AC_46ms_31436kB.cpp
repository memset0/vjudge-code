// test

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn=100010;
ll n,ans;
int m,tot;
char str[maxn];
int ch[maxn*20][4],cnt[4][4][22];
struct M
{
    ll v[4][4];
    M () {memset(v,0x3f,sizeof(v));}
    ll * operator [] (const int &a) {return v[a];}
    M operator * (const M &a) const
    {
        M b;
        int i,j,k;
        for(i=0;i<4;i++) for(j=0;j<4;j++) for(k=0;k<4;k++) b.v[i][j]=min(b.v[i][j],v[i][k]+a.v[k][j]);
        return b;
    }
    inline bool check()
    {
        int i,j;
        for(i=0;i<4;i++) for(j=0;j<4;j++) if(v[i][j]<n)    return 1;
        return 0;
    }
}f[64],g,h;
int main()
{
    scanf("%lld%s",&n,str),m=strlen(str);
    int i,j,u,a,b,mx;
    tot=1;
    for(i=0;i<m;i++)
    {
        a=str[i]-'A';
        for(u=1,j=i;j<m&&j<i+20;j++)
        {
            b=str[j]-'A';
            if(!ch[u][b])   ch[u][b]=++tot,cnt[a][b][j-i]++;
            u=ch[u][b];
        }
    }
    for(a=0;a<4;a++) for(b=0;b<4;b++)
    {
        for(j=1;cnt[a][b][j]==(1<<((j-1)<<1));j++);
        f[0][a][b]=j;
    }
    memset(g.v,0,sizeof(g.v));
    //if(n>=100) for(a=0;a<4;a++) for(b=0;b<4;b++) printf("%d %d:%lld\n",a,b,f[0][a][b]);
    for(mx=0;f[mx].check();mx++)    f[mx+1]=f[mx]*f[mx];
    for(i=mx-1;i>=0;i--)
    {
        h=g*f[i];
        if(h.check())   g=h,ans|=1ll<<i;
    }
    printf("%lld",ans+1);
    return 0;
}//260048835025948762 AAAABAACAADA