#include<bits/stdc++.h>
#define all(x) begin(x),end(x)
using namespace std;
const int N=1e5+9;
int n,a,b[N+10],ans,ar[N+10];
int main(){
#ifndef ONLINE_JUDGE
	//freopen(".in","r",stdin);
#endif
	cin.tie(0)->sync_with_stdio(0);
	cin>>n>>a;
	for(int i=0;i<n;++i)cin>>b[i];
	ans=n*3;
	for(int i=0;i<n;++i)ar[i]=(!b[(i+n-1)%n])+(!b[i])+(!b[(i+1)%n]);
	sort(ar,ar+n);
	for(int i=0;i<a;++i)ans-=ar[i];
	cout<<ans;
}