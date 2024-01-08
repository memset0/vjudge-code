#define __AVX__ 1
#define __AVX2__ 1
#define __SSE__ 1
#define __SSE2__ 1
#define __SSE2_MATH__ 1
#define __SSE3__ 1
#define __SSE4_1__ 1
#define __SSE4_2__ 1
#define __SSE_MATH__ 1
#define __SSSE3__ 1
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#include<bits/stdc++.h>
#ifndef memset0
	#define endl '\n'
#endif
using namespace std;
const int N=1e3+9,M=1e4+9;
const long long inf=2242545357980376863;
const long long lim=-1e12;
int n,m;
bool ban[N],bancol[N];
long long f[N][N],ans[N];
struct edge{
	int u,v,w;
}e[M];
inline void chkmin(long long &a,long long b){
	if(b<a)a=b;
}
int dfn[N],low[N],cnt,sz,q[N],iq[N],col[N],tt;
vector<int>es[N];
void Tarjan(int x){
	dfn[x]=low[x]=++cnt;
	q[++sz]=x,iq[x]=1;
	for(int i=0;i<es[x].size();++i)if(!dfn[es[x][i]]){
		Tarjan(es[x][i]),low[x]=min(low[x],low[es[x][i]]);
	}else if(iq[es[x][i]])low[x]=min(low[x],dfn[es[x][i]]);
	if(low[x]==dfn[x]){
		++tt;
		while(q[sz]!=x)col[q[sz]]=tt,iq[q[sz--]]=0;
		col[x]=tt,iq[x]=0,--sz;
	}
}
void floyd(){
	for(int k=0;k<n;k++){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				chkmin(f[i][j],f[i][k]+f[k][j]);
			}
		}
		if(k%10==0){
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++){
					if(f[i][j]<lim)f[i][j]=lim;
				}
		}
	}
}
int main(){
#ifdef memset0
	freopen("B36.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>m;
	for(int i=0;i<m;i++){
		cin>>e[i].u>>e[i].v>>e[i].w;
	}
	// n=1000,m=10000;
	// for(int i=0;i<m;i++)e[i].w=i&1;
	//xryjr233
	// for(int i=0;i<m;++i)es[e[i].u].push_back(e[i].v);
	// for(int i=0;i<n;++i)if(!dfn[i])Tarjan(i);
	//xryjr233
	memset(f,31,sizeof(f));
	for(int i=0;i<n;i++){
		f[i][i]=0;
	}
	for(int i=0;i<m;i++)
		if(e[i].w%2==0){
			chkmin(f[e[i].u][e[i].v],e[i].w);
		}
	floyd();
	for(int i=0;i<m;i++)
		if(e[i].w%2!=0)
			for(int j=0;j<m;j++)
				if(e[j].w%2!=0){
					chkmin(f[e[i].u][e[j].v],e[i].w+f[e[i].v][e[j].u]+e[j].w);
				}
	floyd();
	memset(ans,31,sizeof(ans));
	// for(int i=0;i<n;i++)
	// 	for(int j=0;j<n;j++)
	// 		if(f[i][j]>(inf>>1)){
	// 			cerr<<"inf"<<" \n"[j+1==n];
	// 		}else{
	// 			cerr<<f[i][j]<<" \n"[j+1==n];
	// 		}
	for(int i=0;i<m;i++)
		if(e[i].w%2!=0){
			// fprintf(stderr,"> %d %d %d\n",e[i].u,e[i].v,e[i].w);
			for(int j=0;j<n;j++)
				if(!ban[j]){
					// fprintf(stderr,"  %d : %lld %d %lld\n",j,f[j][e[i].u],e[i].w,f[e[i].v][j]);
					if(f[j][e[i].u]<(inf>>1)&&f[e[i].v][j]<(inf>>1)){
						long long cur=f[j][e[i].u]+e[i].w+f[e[i].v][j];
						if(e[i].w+f[e[i].v][e[i].u]<0){
							ban[j]=true;
						}else{
							ans[j]=min(ans[j],cur);
							if(ans[j]<0)ban[j]=true;
						}
					}
				}
		}
	// for(int i=0;i<n;i++)
	// 	if(ban[i]){
	// 		bancol[col[i]]=true;
	// 	}
	// for(int i=0;i<n;i++)
	// 	if(bancol[col[i]]){
	// 		ban[i]=true;
	// 	}
	for(int i=0;i<n;i++){
		if(ban[i]){
			cout<<"Haha, stupid Honkai"<<endl;
		}else if(ans[i]>=(inf>>1)){
			cout<<"Battle with the crazy Honkai"<<endl;
		}else{
			cout<<ans[i]<<endl;
		}
	}
}//