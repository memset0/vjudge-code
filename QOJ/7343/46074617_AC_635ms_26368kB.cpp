#include<bits/stdc++.h>
using namespace std;
const int N=1e5+9,S=400;
int n,m,ans=-1;
vector<pair<int,int>> G[N];
unordered_map<int,int> mp[N];
struct edge{
	int u,v,w;
}e[N];
inline void updmax(edge &u,const edge &v){
	if(v.w>u.w){
		u=v;
	}
}
inline int get(int u,int v){
	if(u>v)swap(u,v);
	auto it=mp[u].find(v);
	if(it==mp[u].end())return 0;
	return it->second;
}
void solve(const vector<edge> &q){
	// for(const auto &it:q)cerr<<">> "<<it.u<<" "<<it.v<<" "<<it.w<<endl;
	if(q.empty())return;
	edge tmp[4];
	tmp[0].w=tmp[1].w=tmp[2].w=tmp[3].w=-1;
	for(const auto &it:q)updmax(tmp[0],it);
	for(const auto &it:q){
		if(it.u!=tmp[0].u&&it.v!=tmp[0].u)updmax(tmp[1],it);
		if(it.u!=tmp[0].v&&it.v!=tmp[0].v)updmax(tmp[2],it);
		if(it.u!=tmp[0].u&&it.v!=tmp[0].u&&it.u!=tmp[0].v&&it.v!=tmp[0].v)updmax(tmp[3],it);
	}
	// for(int i=0;i<4;i++)fprintf(stderr,"tmp[%d] = %d %d %d\n",i,tmp[i].u,tmp[i].v,tmp[i].w);
	for(const auto &it:q)
		for(int i=0;i<4;i++)
			if(tmp[i].w!=-1&&it.u!=tmp[i].u&&it.v!=tmp[i].u&&it.u!=tmp[i].v&&it.v!=tmp[i].v){
				// fprintf(stderr,"find (%d %d %d) (%d %d %d)\n",it.u,it.v,it.w,tmp[i].u,tmp[i].v,tmp[i].w);
				ans=max(ans,it.w+tmp[i].w);
			}
}
int main(){
#ifdef memset0
	freopen("A.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>m;
	for(int u,v,w,i=1;i<=m;i++){
		cin>>u>>v>>w;
		e[i]={u,v,w};
		mp[min(u,v)][max(u,v)]=w;
		G[u].emplace_back(v,w);
		G[v].emplace_back(u,w);
	}
	for(int i=1;i<=n;i++){
		vector<edge> q;
		if(G[i].size()<S){
			for(int j=0,w;j<G[i].size();j++)
				for(int k=j+1;k<G[i].size();k++)
					if(w=get(G[i][j].first,G[i][k].first)){
						q.push_back({G[i][j].first,G[i][k].first,G[i][j].second+G[i][k].second+w});
					}
		}else{
			for(int wu,wv,j=1;j<=m;j++)
				if((wu=get(i,e[j].u))&&(wv=get(i,e[j].v))){
					q.push_back({e[j].u,e[j].v,wu+wv+e[j].w});
				}
		}
		// cerr<<"=== solve "<<i<<" ==="<<endl;
		solve(q);
	}
	cout<<ans<<endl;
}