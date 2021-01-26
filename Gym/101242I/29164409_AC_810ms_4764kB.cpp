#include<bits/stdc++.h>
using namespace std;
const int N = 33, M = 110;
// #define double long double
typedef double db;
const db eps=1e-8,INF=1e9;

struct LP {
	int n,m;
	double a[M*5][M*5];
	int rcmp(double x) {if(x<-eps) return -1;if(x>eps) return 1;return 0;}
	void pivot(int x,int y) {
		double t=-a[x][y];a[x][y]=-1;
		for(int i=0;i<=n;i++)a[x][i]/=t;
		for(int i=0;i<=m;i++)
			if(x!=i&&rcmp(a[i][y])) {
				t=a[i][y];a[i][y]=0;
				for(int j=0;j<=n;j++) a[i][j]+=t*a[x][j];
			}
		// for(int i=0;i<=m;i++)for(int j=0;j<=n;j++)cout << a[i][j] << (j==n?'\n':' ');
	}
	double simplex() {
		for(int i=1;i<=m;i++)for(int j=1;j<=n;j++)a[i][j]=-a[i][j];
		// for(int i=0;i<=m;i++)for(int j=0;j<=n;j++)cout << a[i][j] << (j==n?'\n':' ');7
		while(1) {
			int i=0,j=0;
			double w=1e30;
			for(int k=1;k<=m;k++)if(rcmp(a[k][0])<0&&(w>a[k][0]))w=a[k][0], i=k;
			if(!i) break;
			w=-1e30;
			for(int k=1;k<=n;k++)if(rcmp(a[i][k])>0){j=k;break;}
			pivot(i,j);
		}
		while(1) {
			int i=0,j=0;
			double w=-1e30;
			for(int k=1;k<=n;k++)if(rcmp(a[0][k])>0&&(w<a[0][k]))w=a[0][k],j=k;
			if(!j) break;
			w=1e30;
			for(int k=1;k<=m;k++)if(rcmp(a[k][j])<0&&(w>-a[k][0]/a[k][j]))w=-a[k][0]/a[k][j],i=k;
			pivot(i,j);
		}
		return a[0][0];
	}
} A, B;
int ecnt=0;
int e[N][N],val[N][N],pre[N][N];
int v[M], fr[M], ed[M];
int n;

int main()
{
	cin >> n;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++){
		scanf("%d",&val[i][j]);
		if(val[i][j]>0){
			e[i][j]=++ecnt;
			fr[ecnt] = i, ed[ecnt] = j;
			v[ecnt]=val[i][j];
			pre[i][j] = ecnt;
		}else{
			val[i][j] = 0x3f3f3f3f;
		}
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++)for(int j=1;j<=n;j++){
			if(i!=k && j!=k && pre[i][k] && pre[k][j]){
				if(val[i][j] > val[i][k] + val[k][j]){
					val[i][j] = val[i][k] + val[k][j];
					pre[i][j] = pre[k][j];
				}
			}
		}
	}
	B.n = ecnt;
	for(int i=1;i<=ecnt;i++){
		// val[i] <= d[i]
		B.a[++B.m][0] = 0;
		B.a[B.m][i] = -1;
		B.a[++B.m][0] = v[i];
		B.a[B.m][i] = 1;
	}
	int r;cin >> r;
	for(int i=1;i<=r;i++){
		int u,v,w;cin >> u >> v >> w;
		if(u==v)continue;
		++u,++v;
		w -= val[u][v];
		B.m++;
		B.a[B.m][0]=w;
		B.a[B.m+1][0]=-w;
		while(v!=u){
			int id = pre[u][v];
			B.a[B.m][id]=1;
			B.a[B.m+1][id]=-1;
			v=fr[id];
		}
		B.m++;
	}
	int q;cin >> q;
	while(q--){
		A = B;
		int u,v;
		cin >> u >> v;++u,++v;
		int w=val[u][v];
		if(u==v)w = 0;
		int v2=v;
		while(u!=v){
			int id = pre[u][v];
			A.a[0][id]=1;
			v = fr[id];
		}
		db ans1 = w + A.simplex();
		A = B; v = v2;
		while(u!=v){
			int id = pre[u][v];
			A.a[0][id]=-1;
			v = fr[id];
		}
		db ans2 = w - A.simplex();
		printf("%d %d %.8lf %.8lf\n",u-1,v2-1,ans2,ans1);
	}
}
/* 
1 0 0 0 0
-1 0 0 0 0 
1 0 0 0 50
0 -1 0 0 0 
0 1 0 0 55
0 0 -1 0 0
0 0 1 0 40
-1 0 0 0 0
0 0 0 1 40
1 0 1 0 30 
-1 0 -1 0 -30
 */
