#include<bits/stdc++.h>
using namespace std;
const int N=5e3,mod=1e9+7;
int n,v,k,p[N+10],fac[N+10],invf[N+10];
int sz[N+10],ss[N+10],tt[N+10],l;
int ans=1,sum[N+10][N+10],tmp;
vector<int>e[N+10];
int POW(int x,int y){
	int ret=1;
	while(y)y&1?ret=1ll*ret*x%mod:0,x=1ll*x*x%mod,y>>=1;
	return ret;
}
int dfs(int x){
	int fl=0;
	sz[x]=1;
	for(int i:e[x]){
		if(dfs(i)){
			fl=1;
		}else{
			sz[x]+=sz[i];
			ans=1ll*ans*invf[sz[i]]%mod;
		}
	}
	//cout<<"(ans="<<ans<<")\n";
	ans=1ll*ans*fac[sz[x]-1]%mod;
	//cout<<"SZ "<<x<<"="<<sz[x]<<"\n";
	//cout<<"DFS "<<x<<" ans="<<ans<<"\n";
	if(x==v||fl)return ss[++l]=sz[x],1;
	return 0;
}
int C(int x,int y){
	return x>=y?1ll*fac[x]*invf[y]%mod*invf[x-y]%mod:0;
}
int main(){
	scanf("%d",&n);
	fac[0]=1;
	for(int i=1;i<=n;++i)fac[i]=1ll*fac[i-1]*i%mod;
	invf[n]=POW(fac[n],mod-2);
	for(int i=n-1;i>=0;--i)invf[i]=1ll*invf[i+1]*(i+1)%mod;
	for(int i=2;i<=n;++i)scanf("%d",&p[i]),e[p[i]].push_back(i);
	scanf("%d%d",&v,&k);
	dfs(1);
	ans=1ll*ans*C(n-k,ss[1]-1)%mod;
	sum[k][1]=1;
	tt[1]=ss[1];
	for(int j=2;j<=l;++j)tt[j]=tt[j-1]+ss[j];
	for(int i=k-1;i>=1;--i){
		sum[i][1]=1;
		for(int j=2;j<=l;++j)if(n-i-tt[j-1]>=ss[j]-1){
			tmp=1ll*C(n-i-tt[j-1],ss[j]-1)*sum[i+1][j-1]%mod;
			sum[i][j]=(sum[i+1][j]+tmp)%mod;
			//cout<<"SUM "<<i<<" "<<j<<"="<<sum[i][j]<<"\n";
		}
	}
	//cout<<ans<<"*"<<sum[1][l]-sum[2][l]<<"\n";
	printf("%lld",1ll*ans*(sum[1][l]-sum[2][l]+mod)%mod);
	return 0;
}
/*
6
1 1 1 2 3
2 3
5 4
*/