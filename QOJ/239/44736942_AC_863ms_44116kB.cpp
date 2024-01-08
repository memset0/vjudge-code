#include<bits/stdc++.h>
#define log(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
const int N=2e5+9,mod=1e9+7;
int T,n,m,tot;
enum type{
	normal,
	series, //串联
	parallel, //并联
};
struct edge{
	int u,v,w,x,y;
	type t;
}e[N];
struct atom{
	long long sum;
	int cnt;
	friend constexpr atom operator|(const atom &a,const atom &b){
		if(a.sum>b.sum)return a;
		if(a.sum<b.sum)return b;
		return {a.sum,(a.cnt+b.cnt)%mod};
	}
	friend constexpr atom operator+(const atom &a,const atom &b){
		return {a.sum+b.sum,(int)((long long)a.cnt*b.cnt%mod)};
	}
}dp[N][2][2];
map<int,int> G[N];
set<int> deg2;
queue<tuple<int,int,int>> multi;
int newnode(type t,int u,int v,int x,int y){
	++tot;
	e[tot].u=u,e[tot].v=v;
	e[tot].x=x,e[tot].y=y;
	e[tot].t=t;
	return tot;
}
void link(int u,int v,int x){
	// log("link %d %d %d\n",u,v,x);
	if(G[u].find(v)!=G[u].end()){
		multi.push({u,v,x});
	}else{
		if(G[u].size()==2)deg2.erase(u);
		if(G[v].size()==2)deg2.erase(v);
		G[u][v]=G[v][u]=x;
		// log("u=%d v=%d su=%d sv=%d\n",u,v,(int)G[u].size(),(int)G[v].size());
		if(G[u].size()==2)deg2.insert(u);
		if(G[v].size()==2)deg2.insert(v);
	}
	// cerr<<"size: ";for(int i=1;i<=n;i++)cerr<<G[i].size()<<" \n"[i==n];
	// cerr<<"deg2: ";for(int x:deg2)cerr<<x<<" ";cerr<<endl;
}
void merge_series(int t){
	// log("merge series %d\n",t);
	assert(G[t].size()==2);
	auto [u,x]=*G[t].begin();
	auto [v,y]=*G[t].rbegin();
	deg2.erase(t);
	G[t].clear();
	if(G[u].size()==2)deg2.erase(u);
	if(G[v].size()==2)deg2.erase(v);
	G[u].erase(G[u].find(t));
	G[v].erase(G[v].find(t));
	if(G[u].size()==2)deg2.insert(u);
	if(G[v].size()==2)deg2.insert(v);
	int z=newnode(series,u,v,x,y);
	link(u,v,z);
}
void merge_parallel(int u,int v,int x){
	// log("merge parallel %d %d %d\n",u,v,x);
	int y=G[u][v];
	int z=newnode(parallel,u,v,x,y);
	G[u][v]=G[v][u]=z;
}
inline void debug(int x){
	log("dp[%d]: ..%lld .x%lld x.%lld xx%lld\n",x,dp[x][0][0].sum,dp[x][0][1].sum,dp[x][1][0].sum,dp[x][1][1].sum);
}
void dfs(int z){
	// log("dfs[z=%d] x=%d y=%d u=%d v=%d\n",z,e[z].x,e[z].y,e[z].u,e[z].v);
	if(e[z].t==normal){
		dp[z][0][0]={0,1};
		dp[z][1][1]={(long long)e[z].w,1};
	}else{
		int x=e[z].x,y=e[z].y,u=e[z].u,v=e[z].v;
		if(e[z].t==parallel){
			if(e[x].u!=e[z].u)swap(e[x].u,e[x].v);
			if(e[y].u!=e[z].u)swap(e[y].u,e[y].v);
			dfs(x);
			dfs(y);
			dp[z][0][0]=dp[x][0][0]+dp[y][0][0];
			dp[z][0][1]=dp[x][0][1]+dp[y][0][0]|dp[x][0][0]+dp[y][0][1];
			dp[z][1][0]=dp[x][1][0]+dp[y][0][0]|dp[x][0][0]+dp[y][1][0];
			dp[z][1][1]=dp[x][1][1]+dp[y][0][0]|dp[x][0][0]+dp[y][1][1]|dp[x][0][1]+dp[y][1][0]|dp[x][1][0]+dp[y][0][1];
			// log("PAR z[%d][u=%d v=%d] x[%d][u=%d v=%d] y=[%d][u=%d v=%d]\n",z,e[z].u,e[z].v,x,e[x].u,e[x].v,y,e[y].u,e[y].v);
			// debug(x),debug(y),debug(z);
		}else if(e[z].t==series){
			if(e[x].u!=e[z].u&&e[x].v!=e[z].u){
				swap(e[z].x,e[z].y);
				swap(x,y);
			}
			if(e[x].u!=e[z].u)swap(e[x].u,e[x].v);
			if(e[y].v!=e[z].v)swap(e[y].u,e[y].v);
			dfs(x);
			dfs(y);
			dp[z][0][0]=dp[x][0][0]+dp[y][0][0]|dp[x][0][1]+dp[y][0][0]|dp[x][0][0]+dp[y][1][0];
			dp[z][1][0]=dp[x][1][0]+dp[y][0][0]|dp[x][1][1]+dp[y][0][0]|dp[x][1][0]+dp[y][1][0];
			dp[z][0][1]=dp[x][0][0]+dp[y][0][1]|dp[x][0][1]+dp[y][0][1]|dp[x][0][0]+dp[y][1][1];
			dp[z][1][1]=dp[x][1][0]+dp[y][0][1]|dp[x][1][1]+dp[y][0][1]|dp[x][1][0]+dp[y][1][1];
			// log("SER z[%d][u=%d v=%d] x[%d][u=%d v=%d] y=[%d][u=%d v=%d]\n",z,e[z].u,e[z].v,x,e[x].u,e[x].v,y,e[y].u,e[y].v);
			// debug(x),debug(y),debug(z);
		}
	}
}
int main(){
#ifdef memset0
	freopen("E.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>m,tot=m;
		for(int i=1;i<=n;i++)G[i].clear();
		// cerr<<"! "<<n<<" "<<m<<endl;
		for(int u,v,w,i=1;i<=m;i++){
			cin>>u>>v>>w;
			e[i].u=u;
			e[i].v=v;
			e[i].w=w;
			e[i].t=normal;
			link(u,v,i);
		}
		while(tot<m*2-1){
			if(multi.size()){
				auto [u,v,x]=multi.front();
				multi.pop();
				merge_parallel(u,v,x);
			}else if(deg2.size()){
				merge_series(*deg2.begin());
			}
			// for(int u=1;u<=n;u++)
			// 	for(auto [v,w]:G[u]){
			// 		log("%d->%d:%d\n",u,v,w);
			// 	}
		}
		// assert(multi.empty());
		// assert(deg2.empty());
		for(int i=1;i<=tot;i++){
			for(int x=0;x<2;x++)
				for(int y=0;y<2;y++){
					dp[i][x][y].sum=-1e16;
					dp[i][x][y].cnt=0;
				}
		}
		dfs(tot);
		atom ans={0ll,0};
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
				ans=ans|dp[tot][i][j];
		cout<<ans.sum<<" "<<ans.cnt<<'\n';
	}
}