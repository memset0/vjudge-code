// luogu-judger-enable-o2
// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
int n, a[1000005], q;
int f[1000005][25];

inline int read()
{
    int red = 0, f_f = 1;   char ch = getchar();
    if(ch>'9' || ch<'0') {if(ch == '-') f_f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9') red = red*10+ch-'0', ch = getchar();
    return red * f_f;
}

void RMQ()
{
    for(int j = 1; j <= log2(n); j++)
        for(int i = 1; i <= n-(1<<j)+1; i++)
            f[i][j] = max(f[i][j-1], f[i+(1<<(j-1))][j-1]);
}

int main()
{
    n = read(), q = read();
    for(int i = 1; i <= n; i++)
    {
        a[i] = read();
        f[i][0] = a[i];
    }
    RMQ();
    while(q != 0)
    {
        q--;
        int x = read(), y = read();
        if (x == y) {
            printf("%d\n", a[x]);
            continue;
        }
        int j = log2(y-x+1);
        printf("%d\n", max(f[x][j], f[y-(1 << j)+1][j]));
    }
    return 0;
}