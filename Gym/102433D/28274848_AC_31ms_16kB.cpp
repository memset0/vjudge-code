#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll fd(ll x,ll y){
	ll ret=x/y;x%=y;
	for(;x;x>>=1)ret+=(x&1);
	return ret;
}
int main(){
	ll a,b,ans;
	cin>>a>>b;ans=1000000007;
	for(ll f=1,s=0;b<=a*2||s<=0;f*=2,b*=2,s++)if(b>=a)ans=min(ans,fd(b-a,f)+s);
	cout<<ans;
	return 0;
}
