#include<bits/stdc++.h>
using namespace std;
const int N=1e5;
const long long INF=-1e12;
struct edge{
	int t,v,nxt;
}e[(N<<1)+10];
int n,u,v,w,be[N+10],cnt,d[N+10];
long long dp[N+10][2];
void add(int x,int y,int vl){
	e[++cnt]=(edge){y,vl,be[x]},be[x]=cnt,++d[y];
}
void Merge(int x,int y,int vl){
	//cout<<"MERGE "<<x<<" "<<y<<" "<<vl<<"\n";
	long long t0=dp[x][0],t1=dp[x][1];
	dp[x][0]=max(t0+dp[y][0],t1+dp[y][1]+vl);
	dp[x][1]=max(t0+dp[y][1]+vl,t1+dp[y][0]);
	//cout<<"DP "<<x<<"=["<<dp[x][0]<<","<<dp[x][1]<<"]\n";
}
void dfs(int x,int fa){
	dp[x][1]=(d[x]==1?0:INF);
	for(int i=be[x];i;i=e[i].nxt)if(e[i].t!=fa){
		dfs(e[i].t,x),Merge(x,e[i].t,e[i].v);
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;++i)scanf("%d%d%d",&u,&v,&w),add(u,v,w),add(v,u,w);
	if(n==2)return printf("%d",w),0;
	for(int i=1;i<=n;++i)if(d[i]>1){
		dfs(i,0);
		printf("%lld",dp[i][0]);
		return 0;
	}
	return 0;
}