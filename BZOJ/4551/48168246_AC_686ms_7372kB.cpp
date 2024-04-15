#include <bits/stdc++.h>
using namespace std;
const int mn=1e5+7;
struct node {
    int op,x;
}q[mn];
int fa[mn],tt,fr[mn],nx[mn*2],to[mn*2],cnt[mn],fa2[mn],ans[mn];
void add(int x,int y)
{
    ++tt;
    nx[tt]=fr[x];
    fr[x]=tt;
    to[tt]=y;
}
int find(int x)
{
    if(fa[x]==x)  return x;
    return fa[x]=find(fa[x]);
}
void dfs(int x,int f)
{
    fa2[x]=f;
    if(!cnt[x])  fa[x]=find(f);
    else  fa[x]=x;
    for(int i=fr[x];i;i=nx[i])
      if(to[i]!=f)  dfs(to[i],x);
}
int main()
{
    cnt[1]=1;
    int n,m;
    cin>>n>>m;
    for(int i=1;i<n;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        add(x,y);
        add(y,x);
    }
    for(int i=1;i<=m;++i)
    {
        int x;
        char c=getchar();
        while(c!='C'&&c!='Q')  c=getchar();
        scanf("%d",&x);
        if(c=='C')  q[i].op=1,q[i].x=x,++cnt[x];
        else  q[i].op=2,q[i].x=x;
    }
    dfs(1,0);
    for(int i=m;i>0;--i)
    {
        if(q[i].op==1)
        {
            --cnt[q[i].x];
            if(!cnt[q[i].x])  fa[q[i].x]=find(fa2[q[i].x]);
        }
        else  ans[i]=find(q[i].x);
    }
    for(int i=1;i<=m;++i)
      if(q[i].op==2)  printf("%d\n",ans[i]);
    return 0;
}