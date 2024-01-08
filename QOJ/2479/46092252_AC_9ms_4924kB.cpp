#include<bits/stdc++.h>
using namespace std;
const int N=1e5+9;
int n,a[N],s[N],ans[N],pre[10];
int main(){
#ifdef memset0
	freopen("F.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=n;i>=1;i--){
		s[i]=(s[i+1]+a[i])%10;
	}
	memset(pre,-1,sizeof(pre));
	pre[0]=n+1;
	for(int i=n;i>=1;i--){
		ans[i]=pre[s[i]];
		pre[s[i]]=i;
	}
	for(int i=1;i<=n;i++){
		if(ans[i]!=-1){
			ans[i]=ans[i]-i;
		}
		cout<<ans[i]<<" \n"[i==n];
	}
}