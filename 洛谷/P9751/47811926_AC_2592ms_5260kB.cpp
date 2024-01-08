#include<bits/stdc++.h>
using namespace std;
const int N=1e4+9,M=2e4+9,K=109;
int n,m,k,dis[N][K];
vector<pair<int,int>> G[N];
bool check(int s){
	for(int i=1;i<=n;i++)memset(dis[i],-1,k<<2);
	queue<pair<int,int>> q;
	q.push(make_pair(n,0));
	dis[n][0]=0;
	while(q.size()){
		auto [u,x]=q.front();
		int y=(x+1)%k;
		q.pop();
		for(auto [v,w]:G[u])
			if(dis[v][y]==-1&&dis[u][x]<=s-w-1){
				dis[v][y]=dis[u][x]+1;
				if(dis[v][y]<=s)q.push(make_pair(v,y));
			}
	}
	return dis[1][0]!=-1;
}
int main(){
#ifdef memset0
	freopen("bus2.in","r",stdin);
#endif
	cin.tie(0)->sync_with_stdio(0);
	cin>>n>>m>>k;
	for(int u,v,w,i=1;i<=m;i++){
		cin>>u>>v>>w;
		G[v].emplace_back(u,w);
	}
	int l=0,r=5e6,mid,res=-1;
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid*k)){
			res=mid*k;
			r=mid-1;
		}else{
			l=mid+1;
		}
	}
	cout<<res<<endl;
}