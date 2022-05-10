#include<cstdio>
#include<cstring>
#include<iostream>
#include<vector>
using namespace std;
vector<int> g[10010];
vector<int> l[10010];
int n, m, s, ex[10010], dis[10010];

int main()
{
    scanf("%d%d%d", &n, &m, &s);
    for(int i = 1; i <= m; i ++)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        g[a].push_back(b);
        l[a].push_back(c);
    }
    for (int i = 1; i <= n; i++)
    	dis[i] = 2147483647;
    int f = 1 , e = 1;
    int q[1000001];
    q[f] = s, dis[s] = 0;
ex[s] = 1;
    while(f <= e)
    {
        int u = q[f++];
        ex[u] = 0;
        for(int i = 0; i < g[u].size(); i ++)
        {
            if(dis[u] + l[u][i] < dis[g[u][i]])
            dis[g[u][i]] = dis[u] + l[u][i];
            q[++e] = g[u][i];
            ex[g[u][i]] = 1;
        }
        
    }
    for(int i = 1; i <= n; i ++)
    {
        printf("%d ", dis[i]);
    }
    return 0;
}