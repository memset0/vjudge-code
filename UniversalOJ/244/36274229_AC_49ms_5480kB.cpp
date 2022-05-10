#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,l,r,a[N],q[N];
long long ans,sum[N],dp[N];
inline long long f(int j,int i){
	return dp[j]+sum[j]-sum[i-1]+(long long)(j-i-1)*a[j];
}
inline long double slope(int i,int j){
	return ((dp[i]+sum[i]+(long long)(i-1)*a[i])-(dp[j]+sum[j]+(long long)(j-1)*a[j]))/(long double)(a[i]-a[j]);
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n,++n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum[i]=a[i]+sum[i-1];
		ans+=(i==1?1ll:4ll)*a[i];
	}
	dp[n]=a[n];
	q[l=r=1]=n;
	for(int i=n-1;i>=2;i--){
		while(l<r&&f(q[l],i)>=f(q[l+1],i))l++;
		dp[i]=f(q[l],i);
		while(l<r&&slope(q[r-1],q[r])>=slope(q[r],i))r--;
		q[++r]=i;
	}
	for(int i=2;i<=n;i++){
//		cerr<<"dp["<<i<<"]="<<dp[i]<<"*2+"<<(long long)((i<<2)-5)*a[i]<<endl;
		ans=min(ans,(dp[i]<<1)+(long long)((i<<2)-5)*a[i]);
	}
	cout<<ans<<endl;
}