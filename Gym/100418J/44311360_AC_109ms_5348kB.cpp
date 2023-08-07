#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long ll;
typedef unsigned long long ull;
ull f[70][70][70][2];
int a[70];
ull calc(ull n,int k)
{
    memset(f,0,sizeof f);
    f[67][0][0][1]=1;
    for(int i=66;i>=0;--i)
        for(int j=0;j<=k;++j)
            for(int r=0;r<k;++r)
            {
                ull x=f[i+1][j][r][0];
                if(x)
                {
                    f[i][j][(r*2)%k][0]+=x;
                    if(j+1<=k)f[i][j+1][(r*2+1)%k][0]+=x;
                }
                ull y=f[i+1][j][r][1];
                if(y)
                {
                    if(a[i]==0)f[i][j][(r*2)%k][1]+=y;
                    else
                    {
                        f[i][j][(r*2)%k][0]+=y;
                        if(j+1<=k)f[i][j+1][(r*2+1)%k][1]+=y;
                    }
                }
            }
    return f[0][k][0][0]+f[0][k][0][1];
}
int main()
{
    ull n,ans=0;
    scanf("%llu",&n);
    int len=0;
    while(n)a[len]=n&1,n>>=1,++len;
    for(int x=1;x<=65;++x)
    {
        ans+=calc(n,x);
    }
    printf("%llu\n",ans);
    return 0;
}