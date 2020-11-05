#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
template<class T> inline T gcd(T n,T m){return m?gcd(m,n%m):n;}
const int N=1e6+10;
int n;
long long A,B,l,r,ans;
std::map<long long,int> sum;
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n),read(A),read(B);
	A/=gcd(A,B+1);
	if(A>(long long)(2e18)/B){
		for(int i=1;i<=n;i++){
			read(l),read(r);
			ans+=r-l+1;
		}
		printf("%lld\n",ans);
		return 0;
	}
	// printf("%lld %lld\n",A,B);
	for(int i=1;i<=n;i++){
		read(l),read(r);
		if(r-l+1>=A*B){
			// printf("%lld\n",A*B);
			return 0;
		}
		l%=A*B,r%=A*B;
		// printf("> %lld %lld\n",l,r);
		if(l<=r){
			sum[l]++,sum[r+1]--;
		}else{
			sum[0]++,sum[r+1]--;
			sum[l]++,sum[A*B]--;
		}
	}
	sum[A*B]+=0;
	long long cnt=0,lst=0;
	for(const auto &it:sum){
		if(cnt)ans+=it.first-lst;
		cnt+=it.second;
		lst=it.first;
	}
	printf("%lld\n",ans);
}