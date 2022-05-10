#include<bits/stdc++.h>
using namespace std;
const int N=3e6+7,M=20;
int n,vx,vk,op,fa[N],dfs[N],dfn[N],len[N],dep[N],siz[N],e[N][M]; vector<int>v[N],vf[N];
inline int read(){
	int num=0; char g=getchar(); while(g<48||57<g) g=getchar();
	while(47<g&&g<58) num=(num<<1)+(num<<3)+g-48,g=getchar(); return num;
}
inline void write(long long u){
	if(u>9) write(u/10); putchar(u%10+'0');
}
inline void find(int u){
	dfs[u]=dfn[u]=++op;
	e[u][0]=fa[u],siz[u]=1; int z=1; while((1<<z)<dep[u]) e[u][z]=e[e[u][z-1]][z-1],z++;
	for(int i=0;i<len[u];i++){
		int x=v[u][i]; if(fa[u]!=x) fa[x]=u,dep[x]=dep[u]+1,find(x),siz[u]+=siz[x],dfn[u]=dfn[x];
	}
}
inline int lca(int u,int v){
	if(dep[u]<dep[v]) swap(u,v); int z=dep[u]-dep[v];
	for(int x=20;x>=0;x--) if(z&(1<<x)) u=e[u][x]; if(u==v) return u;
	for(int x=20;x>=0;x--) if(e[u][x]!=e[v][x]) u=e[u][x],v=e[v][x]; return fa[u];
}
inline void merge(int u){
	if(vx<0||vk<0) return;
	if(!vx) {vx=u; return;} if(!vk) {vk=u; return;}
	int va=lca(vx,vk),vb=lca(vx,u),vc=lca(vk,u); if(u==va) return;
	if(vb==vx&&vc==va) {vx=u; return;} if(vc==vk&&vb==va){vk=u; return;}
	if(vb==u&&vc==va) return; if(vc==u&&vb==va) return;
	if(va==vx||va==vk){
		if(vb==vc&&dep[vb]<=dep[vx]&&dep[vb]<=dep[vk]){
			if(dep[vx]>dep[vk]) vk=u; else vx=u; return;
		}
		if(vb!=vx&&vb!=vk&&vb!=u){
			vx=-1,vk=-1; return;
		}
		if(vc!=vx&&vc!=vk&&vc!=u){
			vx=-1,vk=-1;
			return;
		}
		if(dep[vx]<dep[vk]) swap(vx,vk);
		if(dep[u]<dep[vx]) vx=u;
		if(dep[u]>dep[vk]) vk=u;
		return;
	}
	vx=-1,vk=-1;
}
int main(){
	n=read(); int u,t; long long cnt=1ll*n*(n-1)/2;
	for(int i=1;i<=n;i++) vf[read()].push_back(i);
	for(int i=1;i<n;i++) u=read(),t=read(),v[u].push_back(t),v[t].push_back(u),len[u]++,len[t]++;
	dep[1]=1,find(1);
	for(int i=1;i<=n;i++){
		int x=vf[i].size(); vx=0,vk=0;
		for(int c=0;c<x;c++) merge(vf[i][c]);
		if(!vk){
			long long sum=cnt,opt=n-1;
			for(int i=0;i<len[vx];i++){
				int x=v[vx][i]; if(fa[vx]==x) continue;
				sum=sum-1ll*siz[x]*(siz[x]-1)/2,opt-=siz[x];
			}
			if(vx==0) opt=0;
			sum=sum-opt*(opt-1)/2;
			write(sum),putchar('\n');
		}
		else if(vx==-1&&vk==-1) write(0),putchar('\n');
		else{
			int vt=lca(vx,vk); if(dep[vx]>dep[vk]) swap(vx,vk);
			if(vx==vt){
				long long xh;
				for(int x=0;x<len[vx];x++){
					int c=v[vx][x];
					if(dfs[c]<=dfs[vk]&&dfs[vk]<=dfn[c]) xh=n-siz[c];
				}
				write(xh*siz[vk]),putchar('\n');
			}
			else write(1ll*siz[vx]*siz[vk]),putchar('\n');
		}
	}
	return 0;
}