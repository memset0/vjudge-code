#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
typedef long long ll;
const int mod = 1e9+9;
const int MAXN = 21;
struct matrix
{
    int a[MAXN][MAXN];
    matrix(){memset(a,0,sizeof a);}
    matrix operator* (matrix you)
    {
        matrix res;
        for(int i=1;i<MAXN;++i)
            for(int k=1;k<MAXN;++k)
                for(int j=1;j<MAXN;++j)
                    res.a[i][j]=(res.a[i][j]+ll(a[i][k])*you.a[k][j])%mod;
        return res;
    }
    
};
matrix Qpow(matrix a,int p)
{
    matrix res;
    for(int i=1;i<MAXN;++i)
        res.a[i][i]=1;
    while(p)
    {
        if(p&1)res=res*a;
        a=a*a,p>>=1;
    }
    return res;
}
std::vector<int>seq;
matrix a,b;
bool ban[MAXN];
int main()
{
    int n,m,k,p;
    scanf("%d%d%d%d",&n,&m,&k,&p);
    --p;
    seq.resize(k);
    for(int i=0;i<k;++i)scanf("%d",&seq[i]);
    for(int i=1;i<=m;++i)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        a.a[u][v]=a.a[v][u]=1;
    }
    int ans=0;
    for(int s=0;s<(1<<k);++s)
    {
        memset(ban,0,sizeof ban);
        int sgn=1;
        for(int i=0;i<k;++i)
            if(s&(1<<i))sgn*=-1,ban[seq[i]]=1;
        b=a;
        for(int u=1;u<=n;++u)
            for(int v=1;v<=n;++v)
            {
                if(ban[u]||ban[v])b.a[u][v]=0;
                // printf("%d ",b.a[u][v]);
            }
                
        b=Qpow(b,p);
        int cur=0;
        for(int u=1;u<=n;++u)
            for(int v=1;v<=n;++v)
                if(!ban[u]&&!ban[v])
                {
                    cur=(cur+b.a[u][v])%mod;
                    // printf("F[%d,%d]=%d\n",u,v,b.a[u][v]);
                }
        ans=(ans+sgn*cur)%mod;
        // printf("S=%d,sgn=%d,cur=%d\n",s,sgn,cur);
    }
    printf("%d\n",(ans+mod)%mod);
    return 0;
}