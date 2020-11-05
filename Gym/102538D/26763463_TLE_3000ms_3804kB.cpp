#include<bits/stdc++.h>
 
const int N=100,mod=998244353;
int n,sum,a[N];
long long fac,inv[N];
 
void dfs(int u,int x,int l){
	if(!l){
		int n=u-1;
		long long ans=1;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=(a[i]+n-i);j++){
				ans=ans*inv[j]%mod;
			}
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++){
				ans=ans*(a[i]-i-a[j]+j)%mod;
			}
		// for(int i=1;i<=n;i++)printf("%d%c",a[i]," \n"[i==n]);
		ans=fac*ans%mod;
		// printf("> %d\n",ans);
		sum=(sum+ans*ans)%mod;
	}
	for(int i=std::min(x,l);i>=1;i--){
		a[u]=i;
		dfs(u+1,i,l-i);
	}
}
 
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	scanf("%d",&n);
	inv[0]=inv[1]=fac=1;
	for(int i=1;i<=n;i++)fac=fac*i%mod;
	for(int i=2;i<=n;i++)inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	for(int i=1;i<=(n>>1);i++){
		a[1]=a[2]=i;
		dfs(3,i,n-(i<<1));
	}
	printf("%d\n",sum);
}