#include<bits/stdc++.h>

const int MAXN = 600011;
int a[MAXN],b[MAXN], n;
bool check(int lim)
{
    int premin=0,f=0,c=0;
    for(int i=1;i<=n;++i)c+= a[i]>=lim;
    int now=0;
    for(int i=1;i<=n;++i)
    {
        now+= int(b[i]>=lim)-int(a[i]>=lim);
        f=std::max(f,now-premin);
        premin=std::min(premin,now);
    }
    return c+f>=(n+1)/2;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)scanf("%d%d",&a[i],&b[i]);
    int l=1,r=1e9;
    while(l<r)
    {
        int mid=(l+r+1)>>1;
        if(check(mid))l=mid;
        else r=mid-1;
    }
    printf("%d\n",l);
    return 0;
}