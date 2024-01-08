#include<bits/stdc++.h>
using namespace std;
const int N=2e5+9,inf=1e9;
int n,fa[N],ch[N][2];
vector<int> G[N];
void dfs(int u){
	int t=0;
	for(int v:G[u])
		if(v!=fa[u]){
			fa[v]=u;
			ch[u][t++]=v;
			dfs(v);
		}
}
vector<int> solve(int u){
	if(!u){
		return {0};
	}
	if(!ch[u][0]&&!ch[u][1]){
		return {1,0};
	}
	vector<int> f=solve(ch[u][0]);
	vector<int> g=solve(ch[u][1]);
	if(f.size()>g.size()){
		f.swap(g);
	}
	vector<int> dp(1+min(g.size(),f.size()+1),inf);
	dp[0]=f[0]+g[0]+1;
	for(int i=0;i<=f.size();i++){
		if(i<f.size()&&i<g.size())dp[i+1]=min(dp[i+1],f[i]+g[i]);
		if(i){
			if(i<g.size())dp[i+1]=min(dp[i+1],f[i-1]+g[i]);
			if(i<f.size())dp[i+1]=min(dp[i+1],f[i]+g[i-1]);
		}
	}
	while(dp.back()==inf)dp.pop_back();
	// cerr<<"solve "<<u<<" :: ";for(int x:dp)cerr<<x<<" ";cerr<<endl;
	return dp;
}
int main(){
#ifdef memset0
	freopen("H.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n;
	for(int u,v,i=1;i<n;i++){
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1);
	auto vec=solve(1);
	cout<<vec.back()<<endl;
}