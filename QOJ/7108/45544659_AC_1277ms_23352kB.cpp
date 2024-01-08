#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<map>
#include<set>
typedef long long ll;
typedef std::pair<int,int> pii;

const int MAXN = 100011;
struct BIT
{
    std::vector<int>t;
    #define lowb (i&-i)
    int n;
    void init(int l)
    {
        n=l;
        t.clear(),t.resize(l+1);
    }
    void modify(int i,int k)
    {
        while(i<=n)t[i]+=k,i+=lowb;
    }
    int Qsum(int i)
    {
        int res=0;
        while(i)res+=t[i],i-=lowb;
        return res;
    }
}bt[MAXN];
ll val[MAXN];
std::vector<int>seq[MAXN];
std::map<pii,int>S;
std::multiset<ll>ans;
int a[MAXN],cnt;
int place(auto& q,int val)
{
    return std::lower_bound(q.begin(),q.end(),val)-q.begin()+1;
}
void brute(int l,int r)
{
    //printf("brute[%d,%d]\n",l,r);
    if(l>r)return;
    int cur=++cnt;
    bt[cur].init(r-l+1);
    auto &q=seq[cur];
    q.resize(r-l+1);
    for(int i=l;i<=r;++i)q[i-l]=a[i];
    std::sort(q.begin(),q.end());
    q.resize(std::unique(q.begin(),q.end())-q.begin());
    val[cur]=0;
    for(int i=r;i>=l;--i)
    {
        //printf("i=%d,a[i]=%d\n",i,a[i]);
        int x=place(q,a[i]);
        //printf("x=%d\n",x);
        val[cur]+=bt[cur].Qsum(x-1);
        bt[cur].modify(x,1);
    }
    ans.insert(val[cur]);
    S[pii(l,r)]=cur;
    //printf("Quit!\n");
}
int main()
{
    int task;
    scanf("%d",&task);
    while(task--)
    {
        S.clear(),ans.clear();
        int n;
        scanf("%d",&n);
        for(int i=1;i<=n;++i)scanf("%d",&a[i]);
        brute(1,n);
        for(int w=1;w<=n;++w)
        {
            ll res=ans.size()?*--ans.end():0;
            printf("%lld ",res);
            int p;
            scanf("%d",&p);
            p=p^res;
            auto it=--S.lower_bound(pii(p+1,0));
            int l=it->first.first,r=it->first.second;
            int cur=it->second;
            //printf("[%d,%d,%d]\n",l,r,cur);
            ans.erase(ans.find(val[cur]));
            ll rest=val[cur];
            if(p-l<=r-p)
            {
                for(int i=l;i<=p;++i)
                {
                    int x=place(seq[cur],a[i]);
                    rest-=bt[cur].Qsum(x-1);
                    bt[cur].modify(x,-1);
                }
                S.erase(it);
                S[pii(p+1,r)]=cur;
                val[cur]=rest;
                brute(l,p-1);
            }
            else
            {
                for(int i=r;i>=p;--i)
                {
                    int x=place(seq[cur],a[i]);
                    rest-= i-l+1-bt[cur].Qsum(x);
                    bt[cur].modify(x,-1);
                }
                S.erase(it);
                S[pii(l,p-1)]=cur;
                val[cur]=rest;
                brute(p+1,r);
            }
            ans.insert(val[cur]);
            //puts("ok!");
        }
        puts("");
        while(cnt)bt[cnt].init(0),seq[cnt].clear(),--cnt;
    }
    return 0;
}