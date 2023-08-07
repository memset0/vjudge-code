#include<iostream>
#include<cstdio>
typedef long long ll;
typedef unsigned un;
ll read()
{
    ll x=0;
    char c=getchar();
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=x*10+(c-'0'),c=getchar();
    return x;
}
void write(ll x)
{
    if(x==0){printf("0 ");return;}
    if(x<0)x=-x,putchar('-');
    int s[35],top=0;
    while(x)s[++top]=x%10,x/=10;
    while(top)putchar(s[top--]+'0');
    putchar(' ');
}
const int MAXN = 1<<20;
int cnt[MAXN+1];
inline int merge(int x,int y)
{
    if(cnt[x]<cnt[y])return y;
    else return x;
}
struct Segment_Tree
{
    int t[MAXN*2+5];
    #define rt t[num]
    void init(un l=1,un r=MAXN,un num=1)
    {
        if(l==r){rt=l;return;}
        un mid=(l+r)>>1;
        init(l,mid,num<<1),init(mid+1,r,num<<1|1);
        rt=merge(t[num<<1],t[num<<1|1]);
    }
    void dec(int pos)
    {
        --cnt[pos];
        int num=(MAXN+pos-1)>>1;
        while(num>=1)rt=merge(t[num<<1],t[num<<1|1]),num>>=1;
    }
    int Qmax(){return t[1];}
}sgt;
int rest;
int f(int i)
{
    //printf("F[%d]\n",i);
    int p=sgt.Qmax();
    if(p!=i&&cnt[p]>(rest)/2)
        {
                write(p);
                sgt.dec(p);
                --rest;
                return p;
        }
            write(i);
            sgt.dec(i);
            --rest;
    return i;
}
int main()
{
    int n=read();
    for(int i=1;i<=n;++i)++cnt[read()];
    sgt.init();
    rest=n;
    int r=sgt.Qmax();
    if(cnt[r]>(n+1)/2)
    {
        puts("-1");
        return 0;
    }
    int nxt=0;
    while(nxt<MAXN&&!cnt[nxt])++nxt;
    for(int i=1;i<MAXN;++i)
    {
        if(nxt==i)++nxt;
        while(nxt<MAXN&&!cnt[nxt])++nxt;
        while(cnt[i])
        {
            int x=f(i);
            // if(x==pre)
            // {
            //     fprintf(stderr,"Unexpected answer!\n");
            //     exit(-5);
            // }
            //printf("i=%d,x=%d,nxt=%d\n",i,x,nxt);
            if(x==i&&cnt[i])
            {
                if(nxt<MAXN)
                {
                    //printf("rest=%d\n",rest);
                    f(nxt);
                    while(nxt<MAXN&&!cnt[nxt])++nxt;
                }
            }
        }
    }
        
    puts("");
    return 0;
}