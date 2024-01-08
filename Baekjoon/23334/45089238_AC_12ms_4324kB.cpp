#include<bits/stdc++.h>
using namespace std;
const int N=309;
int n;
tuple<int,int,int,string> a[N];
int main(){
#ifdef memset0
	freopen("A.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>(get<0>(a[i]))>>(get<1>(a[i]))>>(get<2>(a[i]));
		getline(cin,get<3>(a[i]));
	}
	sort(a+1,a+n+1);
	auto ans=get<3>(a[n]);
	ans.erase(ans.begin());
	cout<<ans<<endl;
}