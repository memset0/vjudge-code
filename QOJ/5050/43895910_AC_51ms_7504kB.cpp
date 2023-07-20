#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll a[100010],b[100010],c[100010],d[100010],n;
ll val[100010];
bool vis[100010];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i];
	ll ans=a[1];
	for(int i=2;i<=n;i++)if(!vis[i]){
		int t=0;
		for(ll j=i;j<=n;j*=i,t++)vis[j]=1,c[t]=a[j],d[t]=b[j];
		ll res=0;
		for(int j=0;j<(1<<t);j++)val[j]=0;
		for(int j=1;j<(1<<t);j++){
			for(int k=t-1;k>=0;k--)if(j>>k&1){
				int fla=0;
				for(int s=0;s<k;s++)if((k+1)%(s+1)==0&&(j>>s&1))fla++;
				val[j]=max(val[j],val[j^(1<<k)]+c[k]-d[k]*fla);
				res=max(res,val[j]);
				break;
			}
			
		}
		ans+=res;
	}
	cout<<ans;
	return 0;
}