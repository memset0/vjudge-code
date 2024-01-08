#include "bits/stdc++.h"

using namespace std;
const int MAXN = 1000011;
struct DSU
{
    int fa[MAXN];
    void init(int n)
    {
        for(int i=1;i<=n;++i)fa[i]=i;
    }
    int find(int x)
    {
        if(fa[x]==x)return x;
        return fa[x]=find(fa[x]);
    }
    bool uni(int x,int y)
    {
        x=find(x),y=find(y);
        if(x==y)return 0;
        return fa[x]=y,1;
    }
}s;
typedef std::pair<int,int> pii;
std::vector<pii>g[MAXN];
pii a[MAXN];
std::vector<int>res;
int f[MAXN],fe[MAXN];
void dfs(int u)
{
    for(auto [v,i]:g[u])
        if(v!=f[u])f[v]=u,fe[v]=i,dfs(v);
}
int main()
{
    
    cin.sync_with_stdio(0),cin.tie(0);
    int task;
    cin>>task;
    while(task--)
    {
        int n,m;
        cin>>n>>m;
        s.init(n),res.clear();
        for(int i=1;i<=n;++i)g[i].clear(),f[i]=0;
        
        for(int i=1;i<=m;++i)cin>>a[i].first>>a[i].second;
        bool flag=0;
        for(int i=1;i<=m;++i)
            if(!s.uni(a[i].first,a[i].second))
            {
                //printf("uni %d %d\n",a[i].first,a[i].second);
                dfs(a[i].first);
                int p=a[i].second;
                while(p!=a[i].first)res.emplace_back(fe[p]),p=f[p];
                res.emplace_back(i);
                flag=1;
                break;
            }
            else g[a[i].first].emplace_back(pii(a[i].second,i)),g[a[i].second].emplace_back(pii(a[i].first,i));
        if(!flag){puts("-1");continue;}
        std::sort(res.begin(),res.end());
        printf("%d",res[0]);
        for(int i=1;i<res.size();++i)printf(" %d",res[i]);
        puts("");
    }
    return 0;
}