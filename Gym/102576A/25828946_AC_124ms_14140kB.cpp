#include<bits/stdc++.h>
const int N=7e5;
long long a[N],f[N];
namespace he{
	// source: https://loj.ac/submission/796720
	using namespace std;
	using i64 = long long;
	i64 prime_pi(const i64 N) {
		if (N <= 1) return 0;
		if (N == 2) return 1;
		const int v = sqrtl(N);
		int s = (v + 1) / 2;
		vector<int> smalls(s); for (int i = 1; i < s; ++i) smalls[i] = i;
		vector<int> roughs(s); for (int i = 0; i < s; ++i) roughs[i] = 2 * i + 1;
		vector<i64> larges(s); for (int i = 0; i < s; ++i) larges[i] = (N / (2 * i + 1) - 1) / 2;
		vector<bool> skip(v + 1);
		const auto divide = [] (i64 n, i64 d) -> int { return double(n) / d; };
		const auto half = [] (int n) -> int { return (n - 1) >> 1; };
		int pc = 0;
		for (int p = 3; p <= v; p += 2) if (!skip[p]) {
			int q = p * p;
			if (i64(q) * q > N) break;
			skip[p] = true;
			for (int i = q; i <= v; i += 2 * p) skip[i] = true;
			int ns = 0;
			for (int k = 0; k < s; ++k) {
				int i = roughs[k];
				if (skip[i]) continue;
				i64 d = i64(i) * p;
				larges[ns] = larges[k] - (d <= v ? larges[smalls[d >> 1] - pc] : smalls[half(divide(N, d))]) + pc;
				roughs[ns++] = i;
			}
			s = ns;
			for (int i = half(v), j = ((v / p) - 1) | 1; j >= p; j -= 2) {
				int c = smalls[j >> 1] - pc;
				for (int e = (j * p) >> 1; i >= e; --i) smalls[i] -= c;
			}
			++pc;
		}
		larges[0] += i64(s + 2 * (pc - 1)) * (s - 1) / 2;
		for (int k = 1; k < s; ++k) larges[0] -= larges[k];
		for (int l = 1; l < s; ++l) {
			int q = roughs[l];
			i64 M = N / q;
			int e = smalls[half(M / q)] - pc;
			if (e < l + 1) break;
			i64 t = 0;
			for (int k = l + 1; k <= e; ++k) t += smalls[half(divide(M, roughs[k]))];
			larges[0] += t - i64(e - l) * (pc + l - 1);
		}
		return larges[0] + 1;
	}
}
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
	return he::prime_pi(n);
	// int sqn=sqrt(n),cnt=0,pri=0;
	// auto id=[&](long long x){return x<=sqn?x:cnt-(n/x)+1;};
	// for(long long i=1;i<=n;i=a[cnt]+1)a[++cnt]=n/(n/i);
	// for(int i=1;i<=cnt;i++)f[i]=a[i]-1;
	// for(int i=2;i<=sqn;i++)if(f[i]!=f[i-1]){
	// 	long long sqr=(long long)i*i; ++pri;
	// 	for(int j=cnt;a[j]>=sqr;j--)f[j]-=f[id(a[j]/i)]-(pri-1);
	// }
	// return f[cnt];
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
	int T; long long n;
	for(std::cin>>T;T--;){
		std::cin>>n;
		std::cout<<solve(n)<<std::endl;
		fprintf(stderr,"clocks: %.4lf\n",clock()/(double)CLOCKS_PER_SEC);
	}
}