#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int T,n,t,fa[N];
long long w[N];
vector<int> G[N];
struct atom{
	long long a,b;
	inline bool operator<(const atom &rhs)const{
		return a==rhs.a?b>rhs.b:a>rhs.a;
	}
};
priority_queue<atom> q[N];
void dfs(int u){	
	for(int v:G[u])if(v!=fa[u]){
		fa[v]=u,dfs(v);
		if(q[v].size()>q[u].size())q[u].swap(q[v]);
		while(q[v].size())q[u].push(q[v].top()),q[v].pop();
	}
	atom cur=(atom){max(0ll,-w[u]),w[u]};
	while(q[u].size()&&(cur.b<0||cur.a>=q[u].top().a)){
		atom rhs=q[u].top();q[u].pop();
		cur=(atom){max(cur.a,rhs.a-cur.b),cur.b+rhs.b};
	}
	if(cur.b>=0)q[u].push(cur);
}
int main(){ 
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>t;
		for(int i=1;i<=n;i++)cin>>w[i],G[i].clear();
		for(int u,v,i=1;i<n;i++){
			cin>>u>>v;
			G[u].push_back(v),G[v].push_back(u);
		}
		w[++n]=1e13,G[n].clear(),G[t].push_back(n);
		dfs(1);
		long long life=0;
		while(q[1].size()){
			atom cur=q[1].top();
			if(life<cur.a)break;
			q[1].pop(),life+=cur.b;
		}
		puts(q[1].size()?"trapped":"escaped");
		while(q[1].size())q[1].pop();
	}
}