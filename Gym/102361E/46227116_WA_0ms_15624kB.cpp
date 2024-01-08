#include<bits/stdc++.h>

const int MAXN = 1000011;
typedef std::pair<int,int> pii;
int fx[MAXN],diff;
struct BIT
{
    int t[MAXN];
    #define lowb (i&-i)
    void clear()
    {
        for(int i=1;i<=diff;++i)t[i]=0;
    }
    void modify(int i,int k)
    {
        while(i<=diff)t[i]+=k,i+=lowb;
    }
    int Qsum(int i)
    {
        int res=0;
        while(i)res+=t[i],i-=lowb;
        return res;
    }
}bt;
int place(int val)
{
    return std::lower_bound(fx+1,fx+diff+1,val)-fx;
}
pii a[MAXN];
int main()
{
    int task;
    scanf("%d",&task);
    for(int T=1;T<=task;++T)
    {
        int n,p;
        diff=0;
        scanf("%d%d",&n,&p);
        
        for(int i=1;i<=n;++i)
        {
            scanf("%d%d",&a[i].first,&a[i].second),fx[++diff]=a[i].first,fx[++diff]=a[i].second;
            fx[++diff]=(1ll*a[i].first*p+99)/100;   
        }
        std::sort(a+1,a+n+1);
        int mxb=0;
        //fx[++diff]=0;
        std::sort(fx+1,fx+diff+1),diff=std::unique(fx+1,fx+diff+1)-fx-1;
        
        for(int i=1;i<=n;++i)bt.modify(place(a[i].first),1);
        int ans=0;
        for(int i=n;i;--i)
        {
            if(a[i].first<mxb)break;
            int v=(1ll*a[i].first*p+99)/100;
            v=place(v);
            ans=std::max(ans,bt.Qsum(diff)-bt.Qsum(v-1));
            bt.modify(place(a[i].first),-1);
            bt.modify(place(a[i].second),1);
            mxb=std::max(mxb,a[i].second);
        }
        int v=(1ll*mxb*p+99)/100;
        v=place(v);
        ans=std::max(ans,bt.Qsum(diff)-bt.Qsum(v-1));
        printf("Case #%d: %d\n",T,ans);
        bt.clear();
    }
    return 0;
}