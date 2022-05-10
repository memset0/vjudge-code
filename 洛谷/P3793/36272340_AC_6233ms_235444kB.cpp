#include<cstdio>

const int maxn=20000010,maxs=100;
int N,*val,ls[maxn],rs[maxn],stk[maxs],top,root;
void init(int n, int m, int*a)
{
    // initialize the program
    N=n;val=a;
    for(int i=0;i<n;i++){
        while(top&&a[stk[top]]<=a[i])ls[i]=stk[top--];
        rs[stk[top]]=i;stk[++top]=i;
    }
    root=stk[1];
}

int query(int l, int r)
{
    // return the maximum value in a[l, r]
    int x=root;
    for(;;x=(r<x?ls:rs)[x])if(l<=x&&x<=r)return val[x];
}

// -----

namespace GenHelper
{
    unsigned z1,z2,z3,z4,b;
    unsigned rand_()
    {
        b=((z1<<6)^z1)>>13;
        z1=((z1&4294967294U)<<18)^b;
        b=((z2<<2)^z2)>>27;
        z2=((z2&4294967288U)<<2)^b;
        b=((z3<<13)^z3)>>21;
        z3=((z3&4294967280U)<<7)^b;
        b=((z4<<3)^z4)>>12;
        z4=((z4&4294967168U)<<13)^b;
        return (z1^z2^z3^z4);
    }
}
void srand(unsigned x)
{
    using namespace GenHelper;
    z1=x; z2=(~x)^0x233333333U; z3=x^0x1234598766U; z4=(~x)+51;
}
int read()
{
    using namespace GenHelper;
    int a=rand_()&32767;
    int b=rand_()&32767;
    return a*32768+b;
}
int a_[20000001];
int main(){
    int n,m,s;
    unsigned long long ans=0;
    scanf("%d%d%d",&n,&m,&s);
    srand(s);
    for(int i=0;i<n;i++)a_[i]=read();
    init(n,m,a_);
    for(int i=0,l,r;i<m;i++)l=read()%n,r=read()%n,ans+=query(l<r?l:r,l>r?l:r);
    printf("%lld\n",ans);
}