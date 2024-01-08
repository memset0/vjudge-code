#include<bits/stdc++.h>
using namespace std;
const int N=709,M=(N<<1)*(N<<1)+9;
const double r=5,l=r*acos(-1.0)/2;
int n,m,tot,id[N<<1][N<<1];
bool a[N][N],vis[M];
string str;
double dis[M];
vector<pair<int,double>> G[M];
inline void addedge(int x1,int y1,int x2,int y2,double w){
	G[id[x1][y1]].emplace_back(id[x2][y2],w);
	G[id[x2][y2]].emplace_back(id[x1][y1],w);
}
int main(){
#ifdef memset0
	freopen("D.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>m;
	getline(cin,str);
	for(int i=1;i<=n;i++){
		getline(cin,str);
		for(int j=1;j<=m;j++)a[i][j]=str[j-1]=='O';
	}
	for(int i=0;i<=(n<<1);i++)
		for(int j=0;j<=(m<<1);j++){
			id[i][j]=++tot;
		}
	for(int i=0;i<=(n<<1);i+=2)
		for(int j=0;j<(m<<1);j++){
			addedge(i,j,i,j+1,r);
		}
	for(int i=0;i<(n<<1);i++)
		for(int j=0;j<=(m<<1);j+=2){
			addedge(i,j,i+1,j,r);
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(a[i][j]){
				addedge(i*2-1,(j-1)*2,(i-1)*2,j*2-1,l);
				addedge((i-1)*2,j*2-1,i*2-1,j*2,l);
				addedge(i*2-1,j*2,i*2,j*2-1,l);
				addedge(i*2,j*2-1,i*2-1,(j-1)*2,l);
			}
	priority_queue<pair<double,int>,vector<pair<double,int>>,greater<pair<double,int>>> q;
	fill_n(dis+1,tot,1e9);
	dis[id[0][0]]=0;
	q.push({0,id[0][0]});
	while(q.size()){
		auto it=q.top();
		q.pop();
		if(vis[it.second])continue;
		int u=it.second;
		vis[u]=true;
		for(const auto &[v,w]:G[u]){
			if(dis[u]+w<dis[v]){
				dis[v]=dis[u]+w;
				q.push({dis[v],v});
			}
		}
	}
	cout<<fixed<<setprecision(12)<<dis[id[n<<1][m<<1]]<<endl;
}