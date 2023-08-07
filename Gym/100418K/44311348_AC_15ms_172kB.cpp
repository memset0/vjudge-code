#include<iostream>
#include<cstdio>
typedef __int128 I128;
typedef __float128 lf;
void write(__int128 x)
{
    if(x==0){puts("0");return;}
    if(x<0)x=-x,putchar('-');
    int s[55],top=0;
    while(x)s[++top]=x%10,x/=10;
    while(top)putchar(s[top--]+'0');
    puts("");
}

const int MAXN = 111;
I128 C[MAXN][MAXN];
int main()
{
    int n;std::cin>>n;
    C[0][0]=1;
    for(int i=1;i<=n;++i)
    {
        C[i][0]=1;
        for(int j=1;j<=i;++j)
            C[i][j]=C[i-1][j-1]+C[i-1][j];
    }

    int p=0;
    lf ans=0;
    for(int x=1;x<n;++x)
    {
        lf all=C[n][x],sum=0;
        for(int m=x;m<n;++m)
        {
            
            sum+=lf(C[m-1][x-1])/(n-m);
        }
        sum/=all;
        if(sum>ans)p=x,ans=sum;
    }
    printf("%d\n",p);
    return 0;
}