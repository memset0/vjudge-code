#include<bits/stdc++.h>
#define uu ((stp)&1)
#define vv (((stp)&1)^1)
#define all(x) (x).begin(),(x).end()
using namespace std;
const int N=1e5+9,inf=1061109567;
int n,m,k;
int dp[2][N];
vector<pair<int,int>> G[N];
bool check(int x){
	memset(dp[0],0,(n+1)<<2);
	// fprintf(stderr,"=== check %d ===\n",x);
	for(int stp=0;stp<k*2+5;stp++){
		memset(dp[vv],63,(n+1)<<2);
		// for(int i=1;i<=n;i++)cerr<<dp[uu][i]<<" \n"[i==n];
		if(stp>=k){
			for(int i=1;i<=n;i++)
				if(dp[uu][i]!=inf&&(dp[uu][i]<<1)<stp){
					// fprintf(stderr,"stp=%d find=%d\n",stp,x);
					return true;
				}
		}
		for(int u=1;u<=n;u++)
			if(dp[uu][u]!=inf)
				for(const auto &[v,w]:G[u]){
					// fprintf(stderr,"%d -> %d : %d\n",u,v,dp[uu][u]+(w<x));
					dp[vv][v]=min(dp[vv][v],dp[uu][u]+(w<x));
				}
	}
	return false;
}
int main(){
#ifdef memset0
	freopen("H.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>m>>k;
	vector<int> val;
	for(int u,v,w,i=1;i<=m;i++){
		cin>>u>>v>>w;
		G[u].emplace_back(v,w);
		val.push_back(w);
	}
	sort(all(val));
	val.erase(unique(all(val)),val.end());
	// for(int u=1;u<=n;u++)
	// 	for(auto &[v,w]:G[u])
	// 		cerr<<u<<" "<<v<<" "<<w<<endl;
	int l=0,r=(int)val.size()-1,mid,ans=-1;
	while(l<=r){
		mid=(l+r)>>1;
		if(check(val[mid])){
			ans=val[mid];
			l=mid+1;
		}else{
			r=mid-1;
		}
	}
	cout<<ans<<endl;
}