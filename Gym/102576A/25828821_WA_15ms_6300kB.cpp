#include<bits/stdc++.h>
const int N=4e5;
int T;
long long n,a[N],g[N];
int bf(int l,int r){
	const std::vector<int> prime={2,3,5,7,11,13,17,19,23,29};
	std::vector<int> vis(r+1);
	for(int i=0;i<prime.size();i++){
		int x=prime[i];
		if((x<<1)>r)break;
		for(int i=x;i<=r;i+=x)vis[i]=1;
	}
	int cnt=0;
	for(int i=l;i<=r;i++)cnt+=vis[i]^1;
	return cnt;
}
int bf_solve(int n){
	if(n<=3)return n;
	return n-((n-1-bf((n>>1)+1,n))>>1);
}
long long calc(long long n){
	int sqn=sqrt(n),cnt=0,pri=0;
	auto id=[&](long long x){return x<=sqn?x:cnt-(n/x)+1;};
	for(long long i=1;i<=n;i=a[cnt]+1)a[++cnt]=n/(n/i);
	for(int i=1;i<=cnt;i++)g[i]=a[i]-1;
	for(int i=2;i<=sqn;i++)if(g[i]!=g[i-1]){
		long long sqr=(long long)i*i; ++pri;
		for(int j=cnt;a[j]>=sqr;j--)g[j]-=g[id(a[j]/i)]-(pri-1);
	}
	return g[cnt];
}
long long query(long long l,long long r){
	return calc(r)-calc(l);
}
long long solve(long long n){
	if(n<=3)return n;
	return n-((n-1-query(n>>1,n))>>1);
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	// for(int i=1;i<=40;i++)printf("%d : %d %lld\n",i,bf_solve(i),solve(i));
	for(std::cin>>T;T--;){
		std::cin>>n;
		std::cout<<bf_solve(n)<<std::endl;
	}
}