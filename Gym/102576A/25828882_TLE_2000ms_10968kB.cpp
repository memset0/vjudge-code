#include<bits/stdc++.h>
const int N=7e5;
int T;
long long n,a[N],f[N];
int bf(int l,int r){
	const std::vector<int> prime={2,3,5,7,11,13,17,19,23,29};
	std::vector<int> vis(r+1),pri;
	int cnt=0;
	for(int i=2;i<=r;i++){
		if(!vis[i]){
			pri.push_back(i);
			cnt+=l<=i&&i<=r;
			// printf("%d %d : %d\n",l,r,i);
		}
		for(int j=0;j<pri.size()&&i*pri[j]<=r;j++){
			vis[i*pri[j]]=1;
			if(i%pri[j]==0)break;
		}
	}
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
	for(int i=1;i<=cnt;i++)f[i]=a[i]-1;
	for(int i=2;i<=sqn;i++)if(f[i]!=f[i-1]){
		long long sqr=(long long)i*i; ++pri;
		for(int j=cnt;a[j]>=sqr;j--)f[j]-=f[id(a[j]/i)]-(pri-1);
	}
	return f[cnt];
}
long long solve(long long n){
	if(n<=3)return n;
	return n-((n-1-calc(n)+calc(n>>1))>>1);
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	// for(int i=1;i<=40;i++)printf("%d : %d %lld\n",i,bf_solve(i),solve(i));
	for(std::cin>>T;T--;){
		std::cin>>n;
		std::cout<<solve(n)<<std::endl;
		fprintf(stderr,"clocks: %.4lf\n",clock()/(double)CLOCKS_PER_SEC);
	}
}