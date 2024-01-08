#include<bits/stdc++.h>
using namespace std;
const int N=4e5+9;
int n,a[N],f[N],g[N];
char op[N];
pair<int,int> t[N];
int main(){
#ifdef memset0
	freopen("A.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n,++n;
	for(int i=1;i<=n;i++){
		cin>>t[i].first;
		t[i].second=i;
	}
	vector<pair<int,int>> tmp(t+1,t+n+1);
	sort(tmp.begin(),tmp.end());
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(tmp.begin(),tmp.end(),t[i])-tmp.begin()+1;
	}
	// for(int i=1;i<=n;i++)cerr<<a[i]<<" \n"[i==n];
	int ans=0;
	for(int i=1;i<=n;i++){
		if(a[i]<i){
			op[i]='L';
		}else if(a[i]>i){
			op[i]='R';
		}
	}
	for(int i=1;i<=n;i++)
		if(op[i]=='L'){
			if(i%2==1)f[i]=1;
			if(op[i-1]=='L'&&a[i-1]<a[i]){
				while(f[i]<=f[i-1])f[i]+=2;
			}
			// cerr<<"L "<<i<<" "<<a[i]<<" :: "<<f[i]<<" "<<(i-a[i])<<endl;
			ans=max(ans,f[i]+i-a[i]);
		}
	for(int i=n;i>=1;i--)
		if(op[i]=='R'){
			if(i%2==0)g[i]=1;
			if(op[i+1]=='R'&&a[i+1]>a[i]){
				while(g[i]<=g[i+1])g[i]+=2;
			}
			// cerr<<"R "<<i<<" "<<a[i]<<" :: "<<g[i]<<" "<<(a[i]-i)<<endl;
			ans=max(ans,g[i]+a[i]-i);
		}
	cout<<ans<<endl;
}