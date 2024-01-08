#include<bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define debug(x) cerr<<#x<<": "<<x<<endl
using namespace std;
using ll=long long;
using lf=long double;
const int N=1e6;
int n,m,u,v,vis[N+10],a[N+10],ne[N+10],cnt;
long long ans;
vector<int>e[N+10];
void dfs(int x){
	vis[x]=1,++a[cnt];
	ne[cnt]+=e[x].size();
	for(int i:e[x])if(!vis[i])dfs(i);
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;++i)cin>>u>>v,e[u].push_back(v),e[v].push_back(u);
	for(int i=1;i<=n;++i)if(!vis[i]){
		++cnt,dfs(i);
		ans+=((1ll*a[cnt]*(a[cnt]-1)-ne[cnt])>>1);
	}
	sort(a+1,a+cnt+1);
	if(!ans)printf("%lld",1ll*a[1]*a[2]);
	else printf("%lld",ans);
	return 0;
}