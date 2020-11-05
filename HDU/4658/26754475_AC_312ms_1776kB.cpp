#include<bits/stdc++.h>
const int N=5e5+10,mod=1e9+7;
int T,n,m,k,res,f[N],g[N];
int main(){
    f[0]=1;
    for(int k=1;k*(3*k-1)/2<=100000;k++)g[m++]=k*(3*k-1)/2,g[m++]=k*(3*k+1)/2;
    for(int i=1;i<=100000;i++)for(int j=0;j<m&&g[j]<=i;j++)f[i]=(f[i]+f[i-g[j]]*((j>>1)&1?mod-1ll:1ll))%mod;
    for(scanf("%d",&T);T--;){
        scanf("%d%d",&n,&k),res=f[n];
        for(int i=0;i<m&&g[i]*k<=n;i++)res=(res+f[n-g[i]*k]*((i>>1)&1?1ll:mod-1ll))%mod;
        printf("%d\n",res);
    }
}