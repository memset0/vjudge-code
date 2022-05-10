#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10,C=500;
int n,m,k,a[N],dp[N],pos[N],nxt[2][C];
long long ans=-1;
inline void update(int len,int val){
	if(len>=k){
//		printf("len=%d val=%d\n",len,val);
		ans=max(ans,(long long)(len-1)*val);
	}
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		dp[i]=INT_MAX;
		int pre=INT_MAX;
		for(int j=i-1;j>=i-C&&j>=1;j--){
			pre=min(pre,abs(a[i]-a[j]));
			dp[j]=min(dp[j],pre);
			update(i-j+1,dp[j]);
		}
	}
//	cout<<ans<<endl;
	for(int i=1;i<=m;i++)pos[i]=n+1;
	for(int i=n;i>=1;i--){
		for(int j=0;j<C;j++){
			nxt[i&1][j]=n;
			if(a[i]-j>=1)nxt[i&1][j]=min(nxt[i&1][j],pos[a[i]-j]-1);
			if(a[i]+j<=m)nxt[i&1][j]=min(nxt[i&1][j],pos[a[i]+j]-1);
		}
		for(int j=1;j<C;j++)nxt[i&1][j]=min(nxt[i&1][j],nxt[i&1][j-1]);
		if(i!=n){
			for(int j=0;j<C;j++){
				nxt[i&1][j]=min(nxt[i&1][j],nxt[i&1^1][j]);
			}
		}
		for(int j=0;j<C;j++){
			update(nxt[i&1][j]-i+1,j+1);
		}
//		for(int j=0;j<20;j++)printf("%d%c",nxt[i][j]," \n"[j==19]);
		pos[a[i]]=i;
	}
	cout<<ans<<endl;
}