#include<bits/stdc++.h>
using namespace std;
int mod;
long long p;
int POW(int x,long long y){
	int ret=1;
	while(y)y&1?ret=1ll*ret*x%mod:0,x=1ll*x*x%mod,y>>=1;
	return ret;
}
int Solve(long long x){
	if(!x)return 0;
	if(x==1)return 1;
	int tmp=Solve(x>>1);
	if(x&1)return(1ll*(POW(10,(x>>1)+1)+1)*tmp+POW(10,x>>1))%mod;
	return(1ll*POW(10,x>>1)+1)*tmp%mod;
}
int main(){
	freopen("zeroes.in","r",stdin);
	freopen("zeroes.out","w",stdout);
	scanf("%lld%d",&p,&mod);
	//cout<<(1ll*(p%mod)*POW(10,p-1))<<"-"<<Solve(p)<<"+"<<p<<"\n";
	printf("%lld",((1ll*(p%mod)*POW(10,p-1)-Solve(p)+p)%mod+mod)%mod);
	return 0;
}