#include<bits/stdc++.h>
#define all(x) begin(x),end(x)
using namespace std;
const int N=1e5+9;
int T,n;
vector<int> G[N],vec[N];
int solve(){
	if(n==2)return -1;
	for(int i=1;i<=n;i++)
		if(G[i].size()==1){
			// fprintf(stderr,"%d -> %d\n",i,G[i][0]);
			vec[G[i][0]].push_back(i);
		}
	set<pair<int,int>> st;
	for(int i=1;i<=n;i++)
		if(vec[i].size()){
			st.insert(make_pair(vec[i].size(),i));
		}
	if(st.size()==1)return -1;
	int ans=0;
	while(st.size()>1){
		auto it=*st.begin();
		st.erase(st.begin());
		auto jt=*--st.end();
		st.erase(--st.end());
		// fprintf(stderr,"! %d[%d] %d[%d]\n",it.second,vec[it.second].back(),jt.second,vec[jt.second].back());
		vec[it.second].pop_back();
		vec[jt.second].pop_back();
		++ans;
		if(it.first>1){
			st.insert(make_pair(it.first-1,it.second));
		}
		if(jt.first>1){
			st.insert(make_pair(jt.first-1,jt.second));
		}
	}
	if(st.size()){
		auto it=*st.begin();
		ans+=vec[it.second].size();
	}
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("J.in","r",stdin);
#endif
	cin.tie(0)->sync_with_stdio(0);
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++){
			G[i].clear();
			vec[i].clear();
		}
		for(int u,v,i=1;i<n;i++){
			cin>>u>>v;
			G[u].push_back(v);
			G[v].push_back(u);
		}
		cout<<solve()<<endl;
	}
}