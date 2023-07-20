#include<bits/stdc++.h>
int n,m;
long long ans;
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	std::cin>>n>>m;
	for(int i=0;i<=n;i+=2)
		for(int j=i?0:2;j<=m;j+=2){
			ans+=(n-i+1)*(m-j+1);
			if(i&&j)ans+=(n-i+1)*(m-j+1);
		}
	std::cout<<ans<<std::endl;
}