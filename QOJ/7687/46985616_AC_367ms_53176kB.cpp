#include "bits/stdc++.h"

typedef std::vector<int> P;
namespace solveN
{
    const int MAXN = 9,S = 362880;
    P a[211],seq[S*2+1];
    void solve(int n,int m)
    {
        for(int i=0;i<m;++i)
        {
            a[i].resize(n);
            for(int j=0;j<n;++j)scanf("%d",&a[i][j]),--a[i][j];
        }
        int sz=0;
        for(int i=0;i<m;++i)
        {
            for(int j=0;j<sz;++j)
            {
                seq[sz+j].resize(n);
                for(int k=0;k<n;++k)
                    seq[sz+j][k]=seq[j][a[i][k]];
            }
            seq[sz*2]=a[i];
            std::sort(seq,seq+sz*2+1);
            sz=std::unique(seq,seq+sz*2+1)-seq;
        }
        printf("%d\n",sz);
    }
}
namespace solveM
{
    const int MAXM = 18;
    P a[211],seq[1<<18];
    void solve(int n,int m)
    {
        for(int i=0;i<m;++i)
        {
            a[i].resize(n);
            for(int j=0;j<n;++j)scanf("%d",&a[i][j]),--a[i][j];
        }
        seq[0].resize(n);
        for(int j=0;j<n;++j)seq[0][j]=j;
        for(int s=1;s<(1<<m);++s)
        {
            int p=0;
            for(int i=0;i<m;++i)
                if(s&(1<<i))p=i;
            P &pre=seq[s^(1<<p)],&f=seq[s];
            f.resize(n);
            for(int i=0;i<n;++i)f[i]=pre[a[p][i]];
        }
        std::sort(seq+1,seq+(1<<m));
        int res=std::unique(seq+1,seq+(1<<m))-(seq+1);
        printf("%d\n",res);
    }
}
int main()
{
    //freopen("J.in","r",stdin);
    int n,m;
    scanf("%d%d",&n,&m);
    if(n<=9)solveN::solve(n,m);
    else solveM::solve(n,m);
    return 0;
}