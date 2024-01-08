#include<bits/stdc++.h>
using namespace std;
int T,n,m,x,y,ans;
int main(){
#ifdef memset0
	freopen("A.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>m;
		x=m,y=n-m;
		ans=x/(y+1);
		if(x%(y+1))++ans;
		cout<<m<<' '<<ans<<'\n';
	}
}