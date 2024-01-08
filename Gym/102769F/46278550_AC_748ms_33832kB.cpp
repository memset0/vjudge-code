#include<bits/stdc++.h>
using namespace std;
const int N=3e5;
int T,n,m,u,v,cnt,tt,TIM,vis[N+10],ans;
vector<int>e[N+10];
void dfs(int x){
    ++tt;
    cnt+=e[x].size();
    vis[x]=TIM;
    for(int i:e[x])if(vis[i]!=TIM)dfs(i);
}
int main(){
    cin.sync_with_stdio(0),cin.tie(0);
    cin>>T;
    for(int fr=1;fr<=T;++fr){
        cin>>n>>m;
        ans=0;
        for(int i=1;i<=n;++i)e[i].clear();
        for(int i=1;i<=m;++i)cin>>u>>v,e[u].push_back(v),e[v].push_back(u);
        ++TIM;
        for(int i=1;i<=n;++i)if(vis[i]!=TIM){
            cnt=0,tt=0;
            dfs(i);
            if((cnt>>1)>tt)ans+=(cnt>>1)-tt;
        }
        cout<<"Case #"<<fr<<": "<<ans<<"\n";
    }
    return 0;
}