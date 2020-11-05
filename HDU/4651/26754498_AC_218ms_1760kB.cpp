#include<bits/stdc++.h>
const int N=1e5+10,mod=1e9+7;
int T,n,m,f[N],g[N];
int main(){
    f[0]=1;
    for(int i=1;i*(3*i-1)/2<=100000;i++)g[m++]=i*(3*i-1)/2,g[m++]=i*(3*i+1)/2;
    for(int n=1;n<=100000;n++)for(int j=0;j<m&&g[j]<=n;j++)f[n]=(f[n]+(((j>>1)&1)?mod-1ll:1ll)*f[n-g[j]])%mod;
    for(scanf("%d",&T);T--;)scanf("%d",&n),printf("%d\n",f[n]);
}