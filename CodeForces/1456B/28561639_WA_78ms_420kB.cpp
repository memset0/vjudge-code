#include<bits/stdc++.h>
using namespace std;
const int N=1e5+7;
int n,w[N];
int main(){
	cin>>n; int ans=1000;
	for(int i=1;i<=n;i++) scanf("%d",&w[i]);
	for(int i=1;i<=n;i++){
		int c=w[i];
		for(int j=1;j<=60;j++){
			c^=w[i+j];
			if(c>w[i+j+1]&&i+j+1<=n) ans=min(ans,j);
			if(i-1>=1&&c<w[i-1]) ans=min(ans,j);
		}
	}
	if(ans==1000) cout<<-1<<endl; else cout<<ans<<endl;
}