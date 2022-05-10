#include<bits/stdc++.h>
const int N=1510,mov[8][2]={{1,0},{0,1},{-1,0},{0,-1},{1,1},{-1,-1},{1,-1},{-1,1}};
int n,m,l,r,qx[N*N],qy[N*N],b[N*N];
char str[N];
bool a[N][N],vis[N][N];
int bfs(int sx,int sy){
	l=r=1,qx[1]=sx,qy[1]=sy,vis[sx][sy]=1;
	while(l<=r){
		int ux=qx[l],uy=qy[l];
		l++;
		for(int i=0;i<8;i++){
			int vx=ux+mov[i][0],vy=uy+mov[i][1];
			if(vx<1||vy<1||vx>n||vy>m||vis[vx][vy]||!a[vx][vy])continue;
			vis[vx][vy]=1;
			++r,qx[r]=vx,qy[r]=vy;
		}
	}
	return r;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%s",str+1);
		for(int j=1;j<=m;j++)a[i][j]=str[j]=='*';
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(a[i][j]&&!vis[i][j])b[bfs(i,j)]++;
	int cnt=0,max=0;
	for(int i=1;i<=n*m;i++)cnt+=b[i]>0,max=std::max(max,i*b[i]);
	printf("%d %d\n",cnt,max);
}