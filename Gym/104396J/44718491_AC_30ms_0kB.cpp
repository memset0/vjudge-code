#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstring>

const int MAXN = 55;
char s[MAXN][MAXN];
int f[MAXN][MAXN];
int main()
{
    int task;scanf("%d",&task);
    while(task--)
    {
        int n;scanf("%d",&n);
        for(int i=1;i<=n;++i)scanf("%s",s[i]+1);
        int ans=0;
        for(int x=1;x<=n;++x)
            for(int y=x+1;y<=n;++y)
            {
                int lx=strlen(s[x]+1),ly=strlen(s[y]+1);
                for(int i=1;i<=lx;++i)
                    for(int j=1;j<=ly;++j)
                    {
                        if(s[x][i]==s[y][j])f[i][j]=f[i-1][j-1]+1;
                        else f[i][j]=0;
                        ans=std::max(ans,f[i][j]);
                    }
                        
            }
        printf("%d\n",ans);
    }
    return 0;
}