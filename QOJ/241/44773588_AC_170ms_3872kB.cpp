#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7,i2=(mod+1>>1);
int T,ans;
long long n,l,r,mid;
long long Calc(long long x){
	long long ret=0;
	for(int i=0;i<64;++i)ret+=(x>>i);
	return ret;
}
int Sum(long long x){
	return (x%mod)*((x+1)%mod)%mod*i2%mod;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%lld",&n),--n,ans=1;
		l=1,r=n;
		while(l<r){
			mid=(l+r>>1);
			if(Calc(mid)>=n)r=mid;
			else l=mid+1;
		}
		for(int i=0;i<64;++i)ans=(ans+(1ll<<i)%mod*Sum((l-1)>>i))%mod;
		ans=(ans+(l%mod)*(n-Calc(l-1)))%mod;
		printf("%d\n",ans);
	}
	return 0;
}