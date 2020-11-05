#include<bits/stdc++.h>
long long n,a,b;
int main(){
	std::cin>>n>>a>>b;
	if(a>b)std::swap(a,b);
	long long ans=LLONG_MAX;
	if((b-a)%2==0)ans=std::min(ans,b-a>>1);
	ans=std::min(ans,b-1);
	ans=std::min(ans,n-a);
	if((b-a)%2==1){
		ans=std::min(ans,a+(b-a-1>>1));
		ans=std::min(ans,n-b+1+(-a+b-1>>1));
	}
	std::cout<<ans<<std::endl;
}