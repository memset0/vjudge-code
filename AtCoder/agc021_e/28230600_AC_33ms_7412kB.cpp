#include<bits/stdc++.h>
#define ll long long
const int N=5e5+10,mod=998244353;
int n,m,ans,fc[N],fi[N];
int main(){
	std::cin>>n>>m,fc[0]=fc[1]=fi[0]=fi[1]=1;
	for(int i=2;i<=m;i++)fc[i]=(ll)fc[i-1]*i%mod;
	for(int i=2;i<=m;i++)fi[i]=(ll)(mod-mod/i)*fi[mod%i]%mod;
	for(int i=2;i<=m;i++)fi[i]=(ll)fi[i-1]*fi[i]%mod;
	for(int i=n;i<=m;i++)ans=(ans+(ll)fc[m-1]*fi[i-1]%mod*fi[m-i])%mod;
	std::cout<<ans;
}