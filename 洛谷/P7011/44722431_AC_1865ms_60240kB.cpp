#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int T,n,t,fa[N];
int64_t s,w[N];
vector<int> G[N];
struct P{
	int64_t a,b;
	inline bool operator<(const P &y)const{return a==y.a?b>y.b:a>y.a;}
};
priority_queue<P> q[N];
void dfs(int u){	
	for(int v:G[u])if(v!=fa[u]){
		fa[v]=u,dfs(v);
		if(q[v].size()>q[u].size())q[u].swap(q[v]);
		while(q[v].size())q[u].push(q[v].top()),q[v].pop();
	}
	P x=(P){max<int64_t>(0,-w[u]),w[u]};
	while(q[u].size()&&(x.b<0||x.a>=q[u].top().a)){P y=q[u].top();q[u].pop();x=(P){max(x.a,y.a-x.b),x.b+y.b};}
	if(x.b>=0)q[u].push(x);
}
int main(){ 
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0),cin>>T;
	while(T--){
		cin>>n>>t;
		for(int i=1;i<=n;i++)cin>>w[i],G[i].clear();
		for(int u,v,i=1;i<n;i++)cin>>u>>v,G[u].push_back(v),G[v].push_back(u);
		w[++n]=1e13,G[n].clear(),G[t].push_back(n),dfs(1),s=0;
		while(q[1].size()){P x=q[1].top();if(s<x.a)break;q[1].pop(),s+=x.b;}
		puts(q[1].size()?"trapped":"escaped");
		while(q[1].size())q[1].pop();
	}
}//asdfasdfsdafasdfasdfasd