#include<bits/stdc++.h>
using namespace std;
const int N=1e6+9;
int T,n,m,s[N],fa[N],dep[N],siz[N];
bool vis[N];
vector<int> G[N];
void dfs(int u){
    siz[u]=1;
    for(int v:G[u]){
        dep[v]=dep[u]+1;
        dfs(v);
        siz[u]+=siz[v];
    }
}
int query(int u){
    int du=dep[u];
    int cnt=0;
    while(u&&!vis[u]){
        ++cnt;
        vis[u]=true;
        u=fa[u];
    }
    return u?du-cnt:0;
}
int main(){
#ifdef memset0
    freopen("K.in","r",stdin);
#endif
    ios::sync_with_stdio(0),cin.tie(0);
    cin>>T;
    for(int t=1;t<=T;t++){
        cin>>n;
        for(int i=1;i<=n;i++){
            G[i].clear();
        }
        for(int i=2;i<=n;i++){
            cin>>fa[i];
            G[fa[i]].push_back(i);
        }
        dfs(1);
        vector<pair<int,int>> vec;
        for(int i=1;i<=n;i++)
            if(siz[i]==1){
                vec.emplace_back(-dep[i],i);
            }
        sort(vec.begin(),vec.end());
        long long ans=0;
        fill_n(s,n+1,0);
        fill_n(vis+1,n,false);
        for(auto [_,u]:vec){
            ans+=dep[u];
            int x=query(u);
            // cerr<<"query "<<u<<" => "<<x<<endl;
            if(dep[u]-2*x<0){
                ans+=dep[u]-2*x;
            }
        }
        cout<<"Case #"<<t<<": "<<ans<<endl;
    }
}