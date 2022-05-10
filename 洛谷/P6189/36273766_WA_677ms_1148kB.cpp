#include<bits/stdc++.h>
const int N=1e5+10;
int T,n,m,mod,f[N],g[N];
int main(){
    f[0]=1,scanf("%d%d",&n,&mod);
    for(int i=1;i*(3*i-1)/2<=n;i++)g[m++]=i*(3*i-1)/2,g[m++]=i*(3*i+1)/2;
    for(int i=1;i<=n;i++)for(int j=0;j<m&&g[j]<=i;j++)f[i]=(f[i]+(((j>>1)&1)?-1ll:1ll)*f[i-g[j]])%mod;
    printf("%d\n",(f[n]+mod)%mod);
}