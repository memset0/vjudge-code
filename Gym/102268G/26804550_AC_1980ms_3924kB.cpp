#include<bits/stdc++.h>
const int N=5e5+10,mod=998244353;
int T,n,m,f[N],g[N];
int main(){
	scanf("%d",&n),++n,f[0]=1;
	for(int i=1;i*(3*i-1)/2<=n;i++)g[m++]=i*(3*i-1)/2,g[m++]=i*(3*i+1)/2;
	for(int i=1;i<=n;i++)for(int j=0;j<m&&g[j]<=i;j++)f[i]=(f[i]+(((j>>1)&1)?mod-1ll:1ll)*f[i-g[j]])%mod;
	printf("%d\n",(f[n]+mod-1)%mod);
}