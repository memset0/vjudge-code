#include<bits/stdc++.h>
using namespace std;
const int N=1e6+9;
int n,root,total,a[N],fa[N],siz[N],mxp[N];
bool vis[N];
long long ans;
vector<int> G[N];
void getroot(int u){
	siz[u]=1;
	mxp[u]=0;
	for(int v:G[u])
		if(!vis[v]&&v!=fa[u]){
			fa[v]=u;
			getroot(v);
			siz[u]+=siz[v];
			mxp[u]=max(mxp[u],siz[v]);
		}
	mxp[u]=max(mxp[u],total-siz[u]);
	if(!root||mxp[u]<mxp[root])root=u;
}
long long calc(vector<pair<int,int>> &cur){
	sort(cur.begin(),cur.end());
	vector<long long> pre(cur.size());
	pre[0]=cur[0].second;
	for(int i=1;i<cur.size();i++){
		pre[i]=pre[i-1]+cur[i].second;
	}
	long long sum=0;
	for(int i=0;i<cur.size();i++){
		sum+=(long long)(i+1)*cur[i].first;
		sum-=pre[i];
	}
	return sum;
}
void collect(int u,int mx,int mn,vector<pair<int,int>> &cur){
	siz[u]=1;
	mx=max(mx,a[u]);
	mn=min(mn,a[u]);
	cur.emplace_back(mx,mn);
	for(int v:G[u])
		if(!vis[v]&&v!=fa[u]){
			fa[v]=u;
			collect(v,mx,mn,cur);
			siz[u]+=siz[v];
		}
}
void solve(int u){
	vis[u]=true;
	vector<pair<int,int>> dst={{a[u],a[u]}};
	for(int v:G[u])if(!vis[v]){
		vector<pair<int,int>> cur;
		collect(v,a[u],a[u],cur);
		ans-=calc(cur);
		dst.insert(dst.end(),cur.begin(),cur.end());
	}
	ans+=calc(dst);
	for(int v:G[u])if(!vis[v]){
		root=0,total=siz[v];
		getroot(v);
		solve(root);
	}
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int u,v,i=1;i<n;i++){
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	root=0,total=n;
	getroot(1);
	solve(root);
	cout<<ans<<endl;
}