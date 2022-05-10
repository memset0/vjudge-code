// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
const int MAXV=10000;
const int MAXN=100;
bool f[MAXV+10],g[MAXV+10];
int n;
int main()
{
    memset(f, -1, sizeof(f));
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        memset(g, 0, sizeof(g)); 
        g[0] = 1;
        int x = 0;
        while(scanf("%d", &x) == 1 && x != -1)
        {
            for(int j = MAXV; j >= 0; j--)
            if(g[j])
                g[j+x] = 1;
        }
        for(int j = 0; j <= MAXV; j++)
            f[j] &= g[j];
    }
    for(int i=MAXV; i>=0; i--)
        if(f[i])
        {
            printf("%d\n", i);
            return 0;
        }
}
     