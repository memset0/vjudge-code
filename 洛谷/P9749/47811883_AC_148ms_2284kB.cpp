#include<bits/stdc++.h>
using namespace std;
const int N=1e5+9;
int n,d,a[N];
long long v[N],c[N];
int main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>n>>d;
	for(int i=2;i<=n;i++){
		cin>>v[i];
		v[i]+=v[i-1];
		c[i]=(v[i]+d-1)/d;
	}
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(i>1)a[i]=min(a[i-1],a[i]);
	}
	long long ans=0;
	for(int i=2;i<=n;i++){
		ans+=(c[i]-c[i-1])*a[i-1];
//		cerr<<"i="<<i<<" "<<c[i]<<" "<<(c[i]-c[i-1])<<" "<<a[i-1]<<endl;
	}
	cout<<ans<<endl;
}