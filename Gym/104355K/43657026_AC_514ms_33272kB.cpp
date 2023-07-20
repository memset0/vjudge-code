#include<bits/stdc++.h>
#define update(u,v,w) if(w<f[u][v])g[u][v]=f[u][v],f[u][v]=w;else if(w<g[u][v])g[u][v]=w
using namespace std;
const int N=2048;
constexpr int inf = 1e9;
int n,m;
int f[N][N],g[N][N];
std::vector<std::pair<int, int>> e[N];

void dijkstra(int s, int f[], int g[]) {
    for (int u = 1; u <= n; u++) { f[u] = g[u] = inf; }
    f[s] = 0;
    std::priority_queue<std::pair<int, int>> que;
    que.push({0, s});
    for (; !que.empty(); ) {
        int d = -que.top().first;
        int u = que.top().second;
        que.pop();
        if (d > g[u]) { continue; }
        for (auto i : e[u]) {
            int v = i.first, w = i.second, t = d + w;
            if (f[v] > t) { std::swap(f[v], t); que.push({-f[v], v}); }
            if (g[v] > t) { std::swap(g[v], t); que.push({-g[v], v}); }
        }
    }
}

int main(){
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>m;
	for(int i=1,u,v,w;i<=m;i++){
		cin>>u>>v>>w;
		// update(u,v,w);
        e[u].push_back({v, w});
	}
	// for(int i=1;i<=n;i++){
		// f[i][i]=g[i][i]=0;
	// }
// 	for(int k=1;k<=n;k++)
// 		for(int i=1;i<=n;i++)
// 			if(i!=k)
// 				for(int j=1;j<=n;j++)
// 					if(j!=k){
// 						update(i,j,f[i][k]+f[k][j]);
// 						update(i,j,f[i][k]+g[k][j]);
// 						update(i,j,g[i][k]+f[k][j]);
// 					}
	// for(int i=1;i<=n;i++){
	// 	for(int j=1;j<=n;j++){
	// 		printf("(%d,%d)%c",f[i][j],g[i][j]," \n"[j==n]);
	// 	}
	// }
	for (int u = 1; u <= n; u++) { dijkstra(u, f[u], g[u]); }
	long long ans=1145141919810;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(i!=j){
				//cerr<<">> "<<i<<" "<<j<<" "<<(long long)f[1][i]+f[i][j]+g[i][j]+f[j][n]<<endl;
				ans=min(ans,(long long)f[1][i]+f[i][j]+g[i][j]+f[j][n]);
			}
	cout<<ans<<endl;
}