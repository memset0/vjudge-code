#include<bits/stdc++.h>
const int N=110,M=2e5+10,mod=1000003;
int n,m,ans,fac[M],deg[N],a[N][N];
int fpow(int a,int b){
	int s=1;
	for(;b;b>>=1,a=(long long)a*a%mod)
		if(b&1)s=(long long)s*a%mod;
	return s;
}
int gauss(int n){
	int det=1;
	for(int i=1,j;i<=n;i++){
		for(j=i;!a[j][i];j++);
		if(j>n)return 0;
		if(i!=j)det=-det,std::swap(a[i],a[j]);
		int inv=fpow(a[i][i],mod-2);
		for(int j=i+1;j<=n;j++){
			int tmp=(long long)a[j][i]*inv%mod;
			for(int k=i;k<=n;k++){
				a[j][k]=(a[j][k]-(long long)a[i][k]*tmp)%mod;
			}
		}
		det=(long long)det*a[i][i]%mod;
	}
	// for(int i=1;i<=n;i++)
	// 	for(int j=1;j<=n;j++)
	// 		printf("%d%c",a[i][j]," \n"[j==n]); 
	return (det+mod)%mod;
}
int main(){
#ifdef local
	freopen("1.in","r",stdin);
#endif
	fac[0]=1;
	for(int i=1;i<M;i++)fac[i]=(long long)fac[i-1]*i%mod;
	while(scanf("%d",&n),n){
		memset(a,0,sizeof(a));
		memset(deg,0,sizeof(deg));
		for(int u=1,v,m;u<=n;u++){
			scanf("%d",&deg[u]);
			for(int i=1;i<=deg[u];i++){
				scanf("%d",&v);
				a[v][v]++,a[u][v]--;
			}
		}
		ans=gauss(n-1);
		// printf("det=%d\n",ans);
		for(int i=1;i<=n;i++)if(deg[i]){
			ans=(long long)ans*fac[deg[i]-1]%mod;
		}
		ans=(long long)ans*deg[1]%mod;
		printf("%d\n",ans);
	}
}