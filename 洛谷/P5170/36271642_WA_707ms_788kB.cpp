#include<bits/stdc++.h>
#define ll long long
const int mod=998244353;
int T,n,a,b,c;
std::tuple<int,int,int> F(int n,int a,int b,int c){
	// printf("F %d %d %d %d\n",n,a,b,c);
	if(n==-1){
		return std::make_tuple(0,0,0);
	}if(a==0){
		return std::make_tuple(
			(int)((ll)(n+1)*(b/c)%mod),
			0,
			0
		);
	}else if(a>=c||b>=c){
		auto it=F(n,a%c,b%c,c);
		return std::make_tuple(
			(int)((std::get<0>(it)+(ll)n*(n+1)/2%mod*(a/c)+(ll)(b/c)*(n+1))%mod),
			0,
			0
		);
	}else{
		int m=(a*n+b)/c;
		auto it=F(m-1,c,c-b-1,a);
		return std::make_tuple(
			(int)(((ll)n*m-std::get<0>(it)+mod)%mod),
			0,
			0
		);
	}
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	for(scanf("%d",&T);T--;){
		scanf("%d%d%d%d",&n,&a,&b,&c);
		auto it=F(n,a,b,c);
		printf("%d %d %d\n",std::get<0>(it),std::get<1>(it),std::get<2>(it));
	}
}