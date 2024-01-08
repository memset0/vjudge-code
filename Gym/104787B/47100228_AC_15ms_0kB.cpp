#include<bits/stdc++.h>

typedef long long ll;
const int mod = 998244353;
struct matrix
{
    int a[3][3];
    matrix(){memset(a,0,sizeof a);}
    matrix(int tp[3][3]){memcpy(a,tp,sizeof a);}
    matrix operator* (matrix you)
    {
        ///puts("Mul:");
        see(),you.see();
        static int tp[3][3];
        memset(tp,0,sizeof tp);
        for(int i=0;i<3;++i)
            for(int k=0;k<3;++k)
                for(int j=0;j<3;++j)
                    tp[i][j]=(tp[i][j]+(ll)a[i][k]*you.a[k][j])%mod;
        matrix res(tp);
        res.see();
        return res;
    }
    void see()
    {
        //for(int i=0;i<3;++i,puts(""))
        //    for(int j=0;j<3;++j)printf("%d ",a[i][j]);
    }
}m0,m1;
matrix Pow(matrix a,ll p)
{
    //printf("Pow %lld\n",p);
    a.see();
    matrix res;
    res.a[0][0]=res.a[1][1]=res.a[2][2]=1;
    while(p)
    {
        if(p&1)res=res*a;
        a=a*a,p>>=1;
    }
    res.see();
    return res;
}
matrix Wan(ll a,ll b,matrix m0,matrix m1)
{
    if(!a)return Pow(m1,b);
    if(!b)return Pow(m0,a);
    if(a<=b)
    {
        return Wan(a,b%a,m0*Pow(m1,b/a),m1);
    }
    return Wan(a-(a-1)/b*b,b,m0,m1*Pow(m0,(a-1)/b));
}
int main()
{
    int task;
    scanf("%d",&task);
    m0.a[0][2]=mod-1;
    m0.a[1][1]=1;
    m0.a[2][0]=1,m0.a[2][2]=2;
    
    m1.a[0][0]=1;
    m1.a[1][2]=mod-1;
    m1.a[2][1]=1,m1.a[2][2]=2;
    while(task--)
    {
        ll a,b;
        scanf("%lld%lld",&a,&b);
        matrix f=Wan(a,b,m0,m1);
        printf("%d\n",f.a[2][2]);
        //matrix g=m0*m1;
        //printf("G::%d\n",g.a[2][2]);
    }
    return 0;
}