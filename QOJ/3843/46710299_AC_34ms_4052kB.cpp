#include "bits/stdc++.h"
using namespace std;
const int N=200,mod=1e9+7;
int n,r,u,v,lc,dp[N+10][N+10],f[N+10],t[N+10][N+10],ts;
int fa[N+10],dep[N+10],sz[N+10];
int a[N+10],b[N+10],s1,s2;
int C[N+10][N+10],tmp,ans;
vector<int>e[N+10];
void dfs(int x,int ff){
    fa[x]=ff,dep[x]=dep[ff]+1;
    sz[x]=1,f[x]=1;
    for(int i:e[x])if(i!=fa[x]){
        dfs(i,x);
        sz[x]+=sz[i];
        f[x]=1ll*f[x]*f[i]%mod*C[sz[x]-1][sz[i]]%mod;
    }
    for(int i:e[x])if(i!=fa[x]){
        t[x][i]=1;
        ts=0;
        for(int j:e[x])if(j!=fa[x]&&j!=i){
            ts+=sz[j];
            t[x][i]=1ll*t[x][i]*f[j]%mod*C[ts][sz[j]]%mod;
        }
        //cout<<"T "<<x<<" "<<i<<"="<<t[x][i]<<"\n";
    }
    //cout<<"F "<<x<<"="<<f[x]<<"\n";
}
int main(){
    cin.sync_with_stdio(0),cin.tie(0);
    cin>>n>>r;
    for(int i=0;i<=n;++i){
        C[i][0]=1;
        for(int j=1;j<=n;++j)(C[i][j]=C[i-1][j]+C[i-1][j-1])>=mod?C[i][j]-=mod:0;
    }
    for(int i=1;i<n;++i)cin>>u>>v,e[u].push_back(v),e[v].push_back(u);
    dfs(r,0);
    for(int i=1;i<=n;++i)for(int j=i+1;j<=n;++j){
        s1=0,s2=0;
        u=i,v=j;
        while(u!=v){
            if(dep[u]<dep[v])b[++s2]=v,v=fa[v];
            else a[++s1]=u,u=fa[u];
        }
        lc=u;
        if(!s1){
            if(s2==1){
                tmp=f[b[1]];
            }else continue;
        }else if(!s2){
            if(s1==1){
                tmp=f[a[1]];
            }else continue;
        }else{
            for(int j=1;j<=s1;++j)for(int k=1;k<=s2;++k)dp[j][k]=0;
            dp[1][1]=2ll*f[a[1]]*f[b[1]]%mod*C[sz[a[1]]+sz[b[1]]-2][sz[a[1]]-1]%mod;
            for(int j=1;j<=s1;++j)for(int k=1;k<=s2;++k){
                if(j<s1){
                    u=a[j+1],v=a[j];
                    dp[j+1][k]=(dp[j+1][k]+1ll*dp[j][k]*t[u][v]%mod*C[sz[u]+sz[b[k]]-2][sz[u]-sz[v]-1])%mod;
                }
                if(k<s2){
                    u=b[k+1],v=b[k];
                    dp[j][k+1]=(dp[j][k+1]+1ll*dp[j][k]*t[u][v]%mod*C[sz[u]+sz[a[j]]-2][sz[u]-sz[v]-1])%mod;
                }
            }
            tmp=dp[s1][s2];
        }
        ts=sz[a[s1]]+sz[b[s2]]-1;
        for(int j:e[lc])if(j!=fa[lc]&&j!=a[s1]&&j!=b[s2])ts+=sz[j],tmp=1ll*tmp*f[j]%mod*C[ts][sz[j]]%mod;
        ++ts;
        for(int j=fa[lc],ls=lc;j;ls=j,j=fa[j]){
            tmp=1ll*tmp*t[j][ls]%mod*C[sz[j]-2][ts]%mod;
            ts=sz[j]-1;
        }
        ans=(ans+1ll*(j-i)*tmp)%mod;
    }
    cout<<ans<<"\n";
    return 0;
}