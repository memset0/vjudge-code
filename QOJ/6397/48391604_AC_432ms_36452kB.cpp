#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=22,mod=998244353;
const ll INF=1e15;
int n,w[N+10],t,ans;
ll f[(1<<N)+10];
int Lsh(int x,int y){
	return((x<<y)+(x>>(n-y)))&((1<<n)-1);
}
int main(){
	cin.sync_with_stdio(0),cin.tie(0);
	cin>>n;
	for(int i=0;i<n;++i)cin>>w[n-i];
	for(int i=2;i<(1<<n);++i)f[i]=INF;
	for(int i=1;i<n;++i){
		for(int j=1;j<(1<<n);++j)t=(j|Lsh(j,i)),f[t]=min(f[t],f[j]+w[i]);
	}
	for(int i=(1<<n)-1;i>0;--i){
		for(int j=0;j<n;++j)if(!(i&(1<<j)))f[i]=min(f[i],f[i|(1<<j)]);
		//cout<<"F "<<i<<"="<<f[i]<<"\n";
		ans=(ans+f[i]%mod*i)%mod;
	}
	cout<<ans;
	return 0;
}
/*
3
2 1 2
*/
/*
4
1919810 999999998 999999997 114114514
*/