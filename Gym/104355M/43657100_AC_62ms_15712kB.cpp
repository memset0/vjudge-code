#include<bits/stdc++.h>
using namespace std;
const int N=1e5+9;
int n,fa[N],p[N],q[N],mn[N],mx[N],v[N],s[N];
vector<int> G[N];
void dfs(int u){
	mx[u]=mn[u]=q[u];
	for(int v:G[u]){
		dfs(v);
		mx[u]=max(mx[u],mx[v]);
		mn[u]=min(mn[u],mn[v]);
	}
	v[mn[u]]++;
	v[mx[u]]--;
	//cerr<<u<<" "<<mn[u]<<" "<<mx[u]<<endl;
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n;
	for(int i=2;i<=n;i++){
		cin>>fa[i];
		G[fa[i]].push_back(i);
	}
	for(int i=1;i<=n;i++){
		cin>>p[i];
		q[p[i]]=i;
	}
	dfs(1);
	for(int i=1;i<=n;i++){
		s[i]=s[i-1]+v[i];
	}
	for(int i=1;i<=n;i++){
		cout<<s[i]<<" \n"[i==n];
	}
}