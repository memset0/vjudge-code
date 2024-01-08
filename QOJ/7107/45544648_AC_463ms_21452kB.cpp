#include<bits/stdc++.h>
#ifndef memset0
	#define endl '\n'
#endif
using namespace std;
const int N=1e5+9;
int T,n,m,p[N],deg[N];
vector<int> a,b,G[N];
set<int> set_a,set_b;
int solveF(){
	int cnt=0;
	for(int x:b)
		if(G[x].size()==a.size()){
			++cnt;
		}
	if(cnt){
		return cnt;
	}
	cnt=1;
	for(int x:b)
		if(G[x].size()==a.size()-1){
			++cnt;
		}
	return cnt;
}
int solveG(){
	for(int u=1;u<=n;u++){
		deg[u]=0;
		for(int v:G[u])
			if(!set_a.count(v)){
				deg[u]++;
			}
	}
	int cnt=0;
	for(int x:a)
		if(deg[x]==0){
			++cnt;
		}
	if(cnt){
		return cnt;
	}
	cnt=1;
	for(int x:a){
		if(deg[x]==1){
			++cnt;
		}
	}
	return cnt;
}
int main(){
#ifdef memset0
	freopen("F.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			G[i].clear();
		}
		for(int u,v,i=1;i<=m;i++){
			cin>>u>>v;
			G[u].push_back(v);
			G[v].push_back(u);
		}
		for(int i=1;i<=n;i++){
			p[i]=i;
		}
		sort(p+1,p+n+1,[&](int x,int y){
			return G[x].size()>G[y].size();
		});
		a.clear(),set_a.clear();
		b.clear(),set_b.clear();
		for(int i=1;i<=n;i++){
			int u=p[i];
			int cnt=0;
			for(int v:G[u]){
				if(set_a.count(v)){
					++cnt;
				}
			}
			if(cnt==(int)a.size()){
				a.push_back(u);
				set_a.insert(u);
			}
		}
		for(int i=1;i<=n;i++)
			if(!set_a.count(i)){
				b.push_back(i);
				set_b.insert(i);
			}
		cout<<solveF()<<" "<<solveG()<<endl;
	}
}