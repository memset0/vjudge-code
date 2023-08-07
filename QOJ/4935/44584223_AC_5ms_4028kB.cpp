#include<bits/stdc++.h>
using namespace std;
const int N=1e5+9;
int n,b[N];
int main(){
#ifdef memset0
	freopen("E.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n;
	for(int i=2;i<=n;i++){
		cin>>b[i];
	}
	b[2]=1;
	int ans=1;
	while(b[n]==0)--n,++ans;
	for(int i=2;i<=n;i++)if(b[i]==0)ans=max(ans,2);
	cout<<ans<<endl;
}