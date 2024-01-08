#include<bits/stdc++.h>
using namespace std;
const int N=2e5+9;
int n,a[N],fa[N];
vector<int> G[N];
unsigned int ans,f[N],g[N],gmax[N],h[N];
void dfs1(int u){
    vector<unsigned int> q;
    for(int v:G[u])
        if(v!=fa[u]){
            fa[v]=u;
            dfs1(v);
            q.emplace_back(f[v]);
            gmax[u]=max(gmax[u],gmax[v]);
        }
    sort(q.begin(),q.end());
    reverse(q.begin(),q.end());
    g[u]=f[u]=a[u];
    if(q.size()>0){
        f[u]+=q[0];
        g[u]+=q[0];
    }
    if(q.size()>1){
        g[u]+=q[1];
    }
    gmax[u]=max(gmax[u],g[u]);
}
void dfs2(int u,unsigned int from){
    h[u]=from+a[u];
    vector<pair<unsigned int,int>> q={{from,-1}};
    for(int v:G[u])
        if(v!=fa[u]){
            q.emplace_back(f[v],v);
        }
    sort(q.begin(),q.end());
    reverse(q.begin(),q.end());
    unsigned int sum=0;
    for(int i=0;i<4&&i<q.size();i++)sum+=q[i].first;
    // fprintf(stderr,"dfs %d from=%d sum=%u\n",u,from,sum);
    ans=max(ans,sum);
    for(int v:G[u])
        if(v!=fa[u]){
            unsigned int another=0;
            for(int i=0;i<q.size();i++)
                if(q[i].second!=v){
                    another=q[i].first;
                    break;
                }
            dfs2(v,a[u]+another);
        }
}
void solve(int u){
    vector<pair<unsigned int,int>> q;
    for(int v:G[u])
        if(v!=fa[u]){
            solve(v);
            q.emplace_back(gmax[v],v);
        }
    sort(q.begin(),q.end());
    reverse(q.begin(),q.end());
    unsigned int sum=0;
    for(int i=0;i<2&&i<q.size();i++)sum+=q[i].first;
    ans=max(ans,sum);
    if(q.size()>0){
        ans=max(ans,h[u]+q[0].first);
        for(int v:G[u])
            if(v!=fa[u]){
                unsigned int another=0;
                for(int i=0;i<q.size();i++)
                    if(q[i].second!=v){
                        another=q[i].first;
                        break;
                    }
                ans=max(ans,h[u]+f[v]+another);
            }
    }
    if(q.size()>2){
        unsigned int dp[3][2];
        memset(dp,0,sizeof(dp));
        for(int v:G[u])
            if(v!=fa[u]){
                for(int i=2;i>=0;i--)
                    for(int j=1;j>=0;j--){
                        if(i<2)dp[i+1][j]=max(dp[i+1][j],dp[i][j]+f[v]);
                        if(j<1)dp[i][j+1]=max(dp[i][j+1],dp[i][j]+gmax[v]);
                    }
                // cerr<<u<<" => "<<v<<endl;
                // for(int i=0;i<=2;i++)
                //     for(int j=0;j<=1;j++)
                //         fprintf(stderr,"dp[%d][%d]=%u\n",i,j,dp[i][j]);
            }
        for(int i=0;i<=2;i++)
            for(int j=0;j<=1;j++){
                ans=max(ans,dp[i][j]+a[u]);
            }
    }
}
int main(){
#ifdef memset0
    freopen("G.in","r",stdin);
#endif
    ios::sync_with_stdio(0),cin.tie(0);
    cin>>n;
    if(n==1){
        cout<<0<<endl;
        return 0;
    }
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int u,v,i=1;i<n;i++){
        cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs1(1);
    dfs2(1,0);
    solve(1);
    cout<<ans<<endl;
    // for(int i=1;i<=n;i++)cerr<<f[i]<<" \n"[i==n];
    // for(int i=1;i<=n;i++)cerr<<g[i]<<" \n"[i==n];
    // for(int i=1;i<=n;i++)cerr<<h[i]<<" \n"[i==n];
    // for(int i=1;i<=n;i++)cerr<<gmax[i]<<" \n"[i==n];
}