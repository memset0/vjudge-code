#include<bits/stdc++.h>
const int N=1e5+10,mod=998244353;
int t,n,m,f[N],g[N];
int main(){
    f[0]=1,scanf("%d",&t);
    for(int i=1;i*(3*i-1)/2<=t;i++)g[m++]=i*(3*i-1)/2,g[m++]=i*(3*i+1)/2;
    for(int n=1;n<=t;n++)for(int j=0;j<m&&g[j]<=n;j++)f[n]=(f[n]+(((j>>1)&1)?mod-1ll:1ll)*f[n-g[j]])%mod;
    for(int n=1;n<=t;n++)printf("%d\n",f[n]);
}
