// luogu-judger-enable-o2
// test

#include<stdio.h>
int head[131072],last[131072],to[131072],cnt=0;
void add(int u,int v)
{
    cnt++;
    last[cnt]=head[u];
    head[u]=cnt;
    to[cnt]=v;
}
int num[131072];
char c[131072];
int wz[131072];
char s[131072];
int ss[131072];
int f[131072];
int len[131072];
int answer[131072];
void dfs(int u,int d,int ans)
{
    if(d==1)
    {
        f[d]=0;
        s[d]=c[u];
        ss[d]=num[u];
        len[d]=ss[d];
        ans=(long long)num[u]*(num[u]-1)/2%998244353;
    }
    else if(d>0)
    {
        s[d]=c[u];
        ss[d]=num[u];
        len[d]=len[d-1]+ss[d];
        if(len[d]>=998244353)
        {
            len[d]-=998244353;
        }
        int x=f[d-1];
        int now=0;
        int dd=d-1-x;
        while(1)
        {
            if(s[x+1]==s[d])
            {
                int now2=ss[x+1];
                if(now2>ss[d])
                {
                    now2=ss[d];
                }
                if(now2>now)
                {
                    ans+=((long long)len[x]+len[x]+now+now2+1)*(now2-now)/2%998244353;
                    if(ans>=998244353)
                    {
                        ans-=998244353;
                    }
                    now=now2;
                }
                if(x==0)
                {
                    if(ss[1]<=ss[d])
                    {
                        ans+=(long long)(ss[d]-now)*ss[1]%998244353;
                        if(ans>=998244353)
                        {
                            ans-=998244353;
                        }
                        x=1;
                        break;
                    }
                }
                if(ss[x+1]==ss[d])
                {
                    x++;
                    break;
                }
            }
            if(x==0)
            {
                break;
            }
            if(x-f[x]==dd)
            {
                x=x%dd+dd;
            }
            dd=x-f[x];
            x=f[x];
        }
        f[d]=x;
    }
    answer[u]=ans;
    for(int i=head[u];i;i=last[i])
    {
        dfs(to[i],d+1,ans);
    }
}
int main()
{
    int n=0;
    int q;
    scanf("%d",&q);
    for(int i=1;i<=q;i++)
    {
        int opt;
        scanf("%d",&opt);
        if(opt==1)
        {
            n++;
            add(wz[i-1],n);
            wz[i]=n;
            scanf("%d",&num[n]);
            c[n]=getchar();
            while(c[n]==' ')
            {
                c[n]=getchar();
            }
        }
        else
        {
            int x;
            scanf("%d",&x);
            wz[i]=wz[x];
        }
    }
    dfs(0,0,0);
    for(int i=1;i<=q;i++)
    {
        printf("%d\n",answer[wz[i]]);
    }
    return 0;
}