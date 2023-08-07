#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
int n,a,b,p,ans,lf,mu;
int POW(int x,int y){
	int ret=1;
	while(y)y&1?ret=1ll*ret*x%mod:0,x=1ll*x*x%mod,y>>=1;
	return ret;
}
int main(){
	scanf("%d%d%d",&n,&a,&b),p=1ll*a*POW(b,mod-2)%mod;
	ans=1,lf=1,mu=1;
	for(int i=2;i<=n;++i){
		mu=1ll*mu*(1-p+mod)%mod;
		lf=(1ll*lf*p+mu)%mod;
		ans=1ll*ans*lf%mod;
	}
	printf("%d",ans);
	return 0;
}