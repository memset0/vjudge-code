#include<bits/stdc++.h>
using namespace std;
const int N=3000;
const long long INF=1e18;
int n,a[N+10];
long long dp[N+10],sum[N+10],tot;
int main(){
	freopen("ebola.in","r",stdin);
	freopen("ebola.out","w",stdout);
	while(1){
		scanf("%d",&n);
		if(!n)return 0;
		for(int i=1;i<=n;++i)scanf("%d",&a[i]),dp[i]=INF,sum[i]=sum[i-1]+a[i];
		for(int i=1;i<=n;++i){
			//cout<<"------------------------i="<<i<<"\n";
			tot=0;
			for(int j=i;j>=1;--j){
				tot+=min(3ll*a[j]*(i-j)+sum[i]-sum[j],sum[i]-sum[j]<<1);
				//cout<<"["<<j<<","<<i<<"] tot="<<tot<<"\n";
				dp[i]=min(dp[i],dp[j-1]+tot+((i-j+1<<2)-2)*(sum[n]-sum[i]));
			}
			//cout<<"DP "<<i<<"="<<dp[i]<<"\n";
		}
		printf("%lld\n",dp[n]);
	}
	return 0;
}
/*
6
40 200 1 300 2 10
6
40 200 1 300 2 10
6
40 200 1 300 2 10
0
*/