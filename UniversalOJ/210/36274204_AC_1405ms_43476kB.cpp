#include<bits/stdc++.h>
using namespace std;
const int N=1e5+9,M=4e5+9;
int n,m,cnt,tim,top,all,col[M],stk[M],dfn[M],low[M],ins[M],id[N][2];
vector<int> pre[N],suf[N],G[M];
vector<pair<int,int>> e[N];
inline void add(int u,int v){
	G[u].push_back(v);
}
void tarjan(int u){
	dfn[u]=low[u]=++tim,stk[++top]=u,ins[u]=true;
	for(int v:G[u])if(!dfn[v]){
		tarjan(v);
		low[u]=min(low[u],low[v]);
	}else if(ins[v]){
		low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]){
		++all;
		do{
			col[stk[top]]=all;
			ins[stk[top]]=false;
		}while(stk[top--]!=u);
	}
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int u,v,t,i=1;i<=m;i++){
		cin>>u>>v>>t;
		e[u].emplace_back(v,t);
	}
	for(int u=1;u<=n;u++){
		id[u][0]=++cnt;
		id[u][1]=++cnt;
		pre[u].resize(e[u].size());
		suf[u].resize(e[u].size());
		for(int i=0;i<e[u].size();i++){
			pre[u][i]=++cnt;
			suf[u][i]=++cnt;
		}
	}
	for(int u=1;u<=n;u++)
		for(int i=0;i<e[u].size();i++){
			add(id[u][1],id[e[u][i].first][e[u][i].second]);
			add(id[e[u][i].first][e[u][i].second^1],id[u][0]);
			if(i)add(id[e[u][i].first][e[u][i].second^1],pre[u][i-1]);
			if(i+1<e[u].size())add(id[e[u][i].first][e[u][i].second^1],suf[u][i+1]);
			add(pre[u][i],id[e[u][i].first][e[u][i].second]);
			add(suf[u][i],id[e[u][i].first][e[u][i].second]);
			if(i)add(pre[u][i],pre[u][i-1]);
			if(i+1<e[u].size())add(suf[u][i],suf[u][i+1]);
		}
	for(int i=1;i<=cnt;i++)if(!dfn[i])tarjan(i);
	for(int i=1;i<=n;i++)
		if(col[id[i][0]]==col[id[i][1]]){
			cout<<"Impossible"<<endl;
			return 0;
		}
	vector<int> prison;
	for(int i=1;i<=n;i++)
		if(col[id[i][0]]<col[id[i][1]]){
			prison.push_back(i);
		}
	cout<<prison.size()<<endl;
	for(int i=0;i<prison.size();i++)cout<<prison[i]<<" \n"[i+1==prison.size()];
}//