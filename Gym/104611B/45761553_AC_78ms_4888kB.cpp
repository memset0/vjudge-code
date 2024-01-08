#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
const int MAXN = 1000011;
int sg[MAXN];
bool vis[MAXN];
int main()
{
    sg[0]=0;
    for(int i=1;i<MAXN;++i)
    {
        int r=sqrt(i);
        if(i!=r*r&&i!=r*r+1)
        {
            sg[i]=sg[i-1];continue;
        }
        for(int j=0;j<=r+2;++j)vis[j]=0;
        
        for(int k=0;k*r<i;++k)
        {
            vis[sg[k*r]]=1;
        }
        for(int j=0;j<=r+2;++j)
            if(!vis[j])
            {
                sg[i]=j;break;
            }
        //printf("i=%d,sg=%d\n",i,sg[i]);
        //printf("%d ",sg[i]);
    }
    int n,res=0;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        res^=sg[x];
    }
    puts(res?"First":"Second");
    return 0;
}