#include<iostream>
#include<cstdio>
#include<cstring>
#define int long long
using namespace std;
int ans,n,m,a[105][105],map[105][105],match[105],vis[105],maxn[105],maxm[105];
bool find(int k) {
	for(int i=1; i<=m; i++)
		if(vis[i]==0&&map[k][i]) {
			vis[i]=1;
			if(find(match[i])||match[i]==0) {
				match[i]=k;
				return 1;
			}
		}
	return 0;
}
signed main() {
	while(cin>>n>>m) {
		ans=0;
		memset(a,0,sizeof(a));
		memset(maxn,0,sizeof(maxn));
		memset(maxm,0,sizeof(maxm));
		memset(map,0,sizeof(map));
		memset(match,0,sizeof(match));
		for(int i=1; i<=n; i++)
			for(int j=1; j<=m; j++) {
				scanf("%d",&a[i][j]);
			}
		for(int i=1; i<=n; i++)
			for(int j=1; j<=m; j++) {
				maxn[i]=max(maxn[i],a[i][j]);
			}
		for(int i=1; i<=m; i++)
			for(int j=1; j<=n; j++) {
				maxm[i]=max(maxm[i],a[j][i]);
			}
		for(int i=1; i<=n; i++)
			for(int j=1; j<=m; j++)
				if(a[i][j]!=0) {
					ans+=(a[i][j]-1);
				}
		for(int i=1; i<=n; i++)
			if(maxn[i]!=0) {
				ans-=(maxn[i]-1);
			}
		for(int i=1; i<=m; i++)
			if(maxm[i]!=0) {
				ans-=(maxm[i]-1);
			}
		for(int i=1; i<=n; i++)
			for(int j=1; j<=m; j++)
				if(maxn[i]==maxm[j]&&a[i][j]!=0) {
					map[i][j]=1;
				}
		for(int i=1; i<=n; i++) {
			memset(vis,0,sizeof(vis));
			if(find(i)) {
				ans+=(maxn[i]-1);
			}
		}
		printf("%lld\n",ans);
	}
}