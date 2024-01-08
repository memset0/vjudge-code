#include<bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define debug(x) cerr<<#x<<": "<<x<<endl
using namespace std;
using ll=long long;
using lf=long double;
int main(){
	std::ios::sync_with_stdio(0),std::cin.tie(0);
	int n,t,k=2;
	std::cin>>n>>t;
	for(int i=1;i<=n;++i)
	{
		int x;
		std::cin>>x;
		k=std::max(k,(x+t-1)/t);
	}
	std::cout<<k<<std::endl;
	return 0;
}